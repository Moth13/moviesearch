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
#include <MSData.h>
#include <MSTabInfo.h>
#include <MSSearchEngine.h>

namespace UI
{
    MSMainWindow::MSMainWindow( QWidget* _pParent )
        : QMainWindow               ( _pParent )
        , m_pUI                     ( new Ui::MSMainWindow )
        , m_xpCurrentSearchEngine   ( NULL )
        , m_uiLastQueryID           ( 0 )
    {
        m_pUI->setupUi( this );

        connectToSearchEngine( Tools::MSSearchEngineManager::getAllSearchEngine()[ 0 ] );

        QStandardItemModel *model = new QStandardItemModel();
        m_pUI->SearchFor_TextEdit->setCompleter( new QCompleter(model, this) );
        m_pUI->SearchFor_TextEdit->installEventFilter( this );
        m_pUI->SearchFor_TextEdit->completer()->setCompletionMode( QCompleter::UnfilteredPopupCompletion );
        m_pUI->SearchFor_TextEdit->completer()->setCaseSensitivity( Qt::CaseInsensitive );
    }

    MSMainWindow::~MSMainWindow()
    {
        SAFE_DELETE( m_pUI );
//        SAFE_LIST_DELETE( m_lpTabsInfo );
//        SAFE_LIST_DELETE( m_lpDataSearchResult );
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

    void MSMainWindow::onMoviesFromTitleFound( uint _uiQueryID, QList< Data::MSMovieSearchResult* > _lpResults )
    {
        if( m_uiLastQueryID == _uiQueryID )
        {
            m_lpDataSearchResult.clear();

            QStandardItemModel *model = (QStandardItemModel*)(m_pUI->SearchFor_TextEdit->completer()->model());
            model->setRowCount( _lpResults.size() );
            model->setColumnCount( 1 );

            for( int i = 0; i<_lpResults.size(); i++ )
            {
                m_lpDataSearchResult.insert( _lpResults[ i ]->getName(), _lpResults[ i ] );
                QStandardItem* item = new QStandardItem( _lpResults[ i ]->getName() );
                item->setText( _lpResults[ i ]->getName() );
                item->setIcon( QIcon( "../../../resources/simpson_Me.jpg" ) );
    //            item->setSizeHint( QSize(192,98) );
                model->setItem( i, 0, item );

                ++i;
            }
        }
    }

    void MSMainWindow::onMovieBasicInfoFound( uint _uiQueryID, Data::MSMovieInfo* _pMovie )
    {
        qDebug() << "onMovieBasicInfoFound";
        if( m_uiLastQueryID == _uiQueryID )
        {
            MSTabInfo* pTab = new MSTabInfo();

            m_pUI->lTabInfo_Widget->addTab( pTab, _pMovie->getTitle() );
            m_pUI->lTabInfo_Widget->setCurrentIndex( m_lpTabsInfo.size() );
            m_lpTabsInfo.push_back( pTab );
        }
    }

    void MSMainWindow::on_SearchFor_TextEdit_returnPressed()
    {
        qDebug() << "on_SearchFor_TextEdit_returnPressed";

        if( NULL != m_xpCurrentSearchEngine )
        {
            QString strResearch     = m_pUI->SearchFor_TextEdit->text();
            m_uiLastQueryID         = m_xpCurrentSearchEngine->getBasicMovieInfo( *static_cast< Data::MSMovieSearchResult* > ( m_lpDataSearchResult[ strResearch ] ) );
        }
        else
        {
            QMessageBox::warning( this
                                  , QObject::tr( "Error" )
                                  , QObject::tr( "Please selecte a search engine." ) );
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
        if( NULL != m_xpCurrentSearchEngine )
        {
            QString strResearch = m_pUI->SearchFor_TextEdit->text();

            if( !strResearch.isEmpty() )
            {
                m_uiLastQueryID         = m_xpCurrentSearchEngine->getMoviesFromTitle( strResearch );
            }
        }
        else
        {
            QMessageBox::warning( this
                                  , QObject::tr( "Error" )
                                  , QObject::tr( "Please selecte a search engine." ) );
        }
    }
}
