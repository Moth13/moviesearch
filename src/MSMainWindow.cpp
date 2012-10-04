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

        connectToSearchEngine( Tools::MSSearchEngineManager::getAllSearchEngine()[ 0 ]);
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
//            SAFE_LIST_DELETE( m_lpDataSearchResult );
            m_lpDataSearchResult.clear();
            m_pUI->History_View->clear();

            Data::MSMovieSearchResult* pData = NULL;
            for( int i = 0; i<_lpResults.size(); ++i )
            {
                pData = _lpResults[ i ];
                m_pUI->History_View->insertItem( i, pData->getName() );
                m_lpDataSearchResult.push_back( pData );
            }

            m_uiLastQueryID = -1;
        }
    }

    void MSMainWindow::onMovieBasicInfoFound( uint _uiQueryID, Data::MSMovieInfo* _pMovie )
    {
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
        if( NULL != m_xpCurrentSearchEngine )
        {
            m_pUI->History_View->clear();
            QString strResearch     = m_pUI->SearchFor_TextEdit->text();
            m_uiLastQueryID          = m_xpCurrentSearchEngine->getMoviesFromTitle( strResearch );
        }
        else
        {
            QMessageBox::warning( this
                                  , QObject::tr( "Error" )
                                  , QObject::tr( "Please selecte a search engine." ) );
        }
    }

    void MSMainWindow::on_History_View_itemDoubleClicked(QListWidgetItem *item)
    {
//        pTab->searchFor( m_mMovieByID[ item->text() ] );

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
}
