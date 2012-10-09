/*
 * MSMainwindow.cpp
 *
 * Author(s):
 * - Jeremie GUERINEL
 *
 * Created 2012-9-17
 */

#include <MSMainWindow.h>
#include <ui_MSMainwindow.h>

#include <QMessageBox>

#include <MSTools.h>

#include <MSDataMovie.h>
#include <MSDataPerson.h>

#include <MSSearchEngine.h>

#include <MSTabInfo.h>

namespace UI
{
    MSMainWindow::MSMainWindow( QWidget* _pParent )
        :   QMainWindow                 ( _pParent )
        ,   m_pUI                       ( new Ui::MSMainWindow )
        ,   m_pCompleter                ( NULL )
        ,   m_pCompleterModel           ( NULL )
        ,   m_xpCurrentSearchEngine     ( NULL )
        ,   m_uiLastQueryID             ( 0 )
    {
        m_pUI->setupUi( this );
        m_pUI->radioButton_Movie->setChecked( true );

        QList< Tools::MSSearchEngine* > lxpAllSearchEngine = Tools::MSSearchEngineManager::getAllSearchEngine();

        foreach( Tools::MSSearchEngine* xpSE, lxpAllSearchEngine )
        {
            m_pUI->SearchEngine_Combox->addItem( xpSE->getIcon(), xpSE->getName() );
        }

        if( !lxpAllSearchEngine.isEmpty() )
        {
            connectToSearchEngine( lxpAllSearchEngine.first() );
        }

        m_pCompleterModel   = new QStandardItemModel();
        m_pCompleter        = new QCompleter( m_pCompleterModel, this );

        m_pUI->SearchFor_TextEdit->setCompleter( m_pCompleter );
        m_pUI->SearchFor_TextEdit->installEventFilter( this );

        m_pCompleter->setCompletionMode( QCompleter::UnfilteredPopupCompletion );
        m_pCompleter->setModelSorting( QCompleter::CaseSensitivelySortedModel );
        m_pCompleter->setCaseSensitivity( Qt::CaseInsensitive );

        on_SearchFor_TextEdit_textEdited( "" );
    }

    MSMainWindow::~MSMainWindow()
    {
        SAFE_DELETE( m_pUI );
//        SAFE_LIST_DELETE( m_lpTabsInfo );
//        SAFE_LIST_DELETE( m_lpDataSearchResult );
        cleanResults();
    }

    void MSMainWindow::connectToSearchEngine( Tools::MSSearchEngine* _pSearchEngine )
    {
        if( NULL != m_xpCurrentSearchEngine )
        {
            m_xpCurrentSearchEngine->doDisconnection( this );
        }

        m_xpCurrentSearchEngine = _pSearchEngine;

        if( NULL != _pSearchEngine )
        {
            m_xpCurrentSearchEngine->doConnection( this );
        }
    }

    void MSMainWindow::cleanResults()
    {
        QStringList lstrKeys = m_mDataSearchResult.keys();
        foreach( QString strKey, lstrKeys )
        {
            delete m_mDataSearchResult.take( strKey );
        }

        m_mQueryImage.clear();
    }

    void MSMainWindow::onMoviesFromTitleFound( uint _uiQueryID, QList< Data::MSMovieSearchResult* > _lpResults )
    {
        if( m_uiLastQueryID == _uiQueryID )
        {
            m_pUI->statusBar->showMessage( QObject::tr( "Results found!!" ) );
            cleanResults();

            m_pCompleterModel->setRowCount( _lpResults.size() );
            m_pCompleterModel->setColumnCount( 1 );

            for( int i = 0; i<_lpResults.size(); i++ )
            {
                m_mDataSearchResult.insert( _lpResults[ i ]->getName(), _lpResults[ i ] );

                QStandardItem* pItem = new QStandardItem( "" );
                pItem->setText( _lpResults[ i ]->getName() );
                pItem->setIcon( QIcon( "../../../resources/simpson_Me.jpg" ) );
                m_pCompleterModel->setItem( i, 0, pItem );

                uint uiQueryId = m_xpCurrentSearchEngine->getImage( _lpResults[ i ]->getPoster(), Tools::MSSearchEngine::ICON );
                m_mQueryImage.insert( uiQueryId, pItem );
            }
            m_pCompleter->complete();
            m_pCompleter->setCurrentRow( 0 );
        }
    }

    void MSMainWindow::onPersonsFromNameFound( uint _uiQueryID, QList< Data::MSPersonSearchResult* > _lpResults )
    {
        if( m_uiLastQueryID == _uiQueryID )
        {
            m_pUI->statusBar->showMessage( QObject::tr( "Results found!!" ) );
            cleanResults();

            m_pCompleterModel->setRowCount( _lpResults.size() );
            m_pCompleterModel->setColumnCount( 1 );

            for( int i = 0; i<_lpResults.size(); i++ )
            {
                m_mDataSearchResult.insert( _lpResults[ i ]->getName(), _lpResults[ i ] );

                QStandardItem* pItem = new QStandardItem( "" );
                pItem->setText( _lpResults[ i ]->getName() );
                pItem->setIcon( QIcon( "../../../resources/simpson_Me.jpg" ) );
                m_pCompleterModel->setItem( i, 0, pItem );

                uint uiQueryId = m_xpCurrentSearchEngine->getImage( _lpResults[ i ]->getPoster(), Tools::MSSearchEngine::ICON );
                m_mQueryImage.insert( uiQueryId, pItem );
            }
            m_pCompleter->complete();
            m_pCompleter->setCurrentRow( 0 );
        }
    }

    void MSMainWindow::onImageFound( uint _uiQueryID, QPixmap* _pPixmap )
    {
        if( m_mQueryImage.contains( _uiQueryID )
            && NULL != m_mQueryImage[ _uiQueryID ]
            && NULL != _pPixmap )
        {
            m_mQueryImage[ _uiQueryID ]->setIcon( QIcon( *_pPixmap ) );
        }

    }

    void MSMainWindow::on_SearchFor_TextEdit_returnPressed()
    {
        QString strResearch         = m_pUI->SearchFor_TextEdit->text();
        if( NULL != m_xpCurrentSearchEngine
            && m_mDataSearchResult.contains( strResearch ) )
        {
            MSTabInfo* pTab         = new MSTabInfo();

            m_xpCurrentSearchEngine->doConnection( pTab );

            m_pUI->lTabInfo_Widget->addTab( pTab, strResearch );
            m_pUI->lTabInfo_Widget->setCurrentIndex( m_lpTabsInfo.size() );
            m_lpTabsInfo.push_back( pTab );

            uint uiQueryID = 0;
            if( m_pUI->radioButton_Movie->isChecked() )
            {
                uiQueryID = m_xpCurrentSearchEngine->getBasicMovieInfo( *static_cast< Data::MSMovieSearchResult* > ( m_mDataSearchResult[ strResearch ] ) );
            }
            else if( m_pUI->radioButton_Person->isChecked() )
            {
                uiQueryID = m_xpCurrentSearchEngine->getBasicPersonInfo( *static_cast< Data::MSPersonSearchResult* > ( m_mDataSearchResult[ strResearch ] ) );
            }
            pTab->setQueryID( uiQueryID );

            m_mDataSearchResult.clear();
        }
        else
        {
            QString strErrorMsg = "";

            if( NULL == m_xpCurrentSearchEngine )
            {
                strErrorMsg = QObject::tr( "Please selecte a search engine." );
            }

            if( !m_mDataSearchResult.contains( strResearch ) )
            {
                strErrorMsg = QObject::tr( "No movie/personn found with this entry : " ) + strResearch;
            }

            QMessageBox::warning( this
                                  , QObject::tr( "Error" )
                                  , strErrorMsg );
        }
    }

    void MSMainWindow::on_lTabInfo_Widget_tabCloseRequested(int index)
    {
        MSTabInfo* pTab = m_lpTabsInfo.takeAt( index );
        m_pUI->lTabInfo_Widget->removeTab( index );

        delete pTab;
    }

    void MSMainWindow::on_actionClose_triggered()
    {
        close();
    }

    void MSMainWindow::on_actionAbout_MovieSearch_triggered()
    {
        QString strMessage  = "Designed by J. Guerinel";
        strMessage          += QString( "/n jeremie.guerinel@gmail.com" );
        strMessage          += QString( "/n Version : " );// + QString::number( MS_VERSION );
        QMessageBox::about( this, "About Movie search", strMessage );
    }

    void MSMainWindow::on_SearchFor_TextEdit_textEdited( const QString &arg1 )
    {
        m_pCompleter->complete();

        if( NULL != m_xpCurrentSearchEngine )
        {
            QString strResearch = m_pUI->SearchFor_TextEdit->text();

//            if( !strResearch.isEmpty() )
            if( m_pUI->radioButton_Movie->isChecked() )
            {
                m_uiLastQueryID = m_xpCurrentSearchEngine->getMoviesFromTitle( strResearch );
            }
            else if( m_pUI->radioButton_Person->isChecked() )
            {
                m_uiLastQueryID = m_xpCurrentSearchEngine->getPersonsFromName( strResearch );
            }
            m_pUI->statusBar->showMessage( QObject::tr( "Searching for " ) + strResearch + "..." );
        }
        else
        {
            QMessageBox::warning( this
                                  , QObject::tr( "Error" )
                                  , QObject::tr( "Please selecte a search engine." ) );
        }
    }

    void MSMainWindow::on_SearchEngine_Combox_activated(int index)
    {
        connectToSearchEngine( Tools::MSSearchEngineManager::getAllSearchEngine()[ index ] );
    }
}
