#include <MSSearchEngine.h>

#include <MSDataMovie.h>
#include <MSDataPersonn.h>

#include <MSMainWindow.h>
#include <MSTabInfo.h>

#include <MSSearchEngine_TMDB.h>

namespace Tools
{
    MSSearchEngine::MSSearchEngine()
        :   m_strName       ( "Fake SearchEngine" )
//        ,   m_pixIcon       ( "../../resources/simpson_Me.jpg" )
    {
    }

    MSSearchEngine::~MSSearchEngine()
    {
        qDebug() << QString( "Destroying %1" ).arg( m_strName );
    }

    void MSSearchEngine::doConnection( UI::MSMainWindow* _xpMainWindow )
    {
        if( NULL != _xpMainWindow )
        {
            QObject::connect( this
                              , SIGNAL( sigMoviesFromTitleFound( uint, QList<Data::MSMovieSearchResult*> ) )
                              , _xpMainWindow
                              , SLOT( onMoviesFromTitleFound( uint, QList<Data::MSMovieSearchResult*> ) )
                              , Qt::UniqueConnection );
        }
    }

    void MSSearchEngine::doConnection( UI::MSTabInfo* _xpTabInfo )
    {
        if( NULL != _xpTabInfo )
        {
            _xpTabInfo->setSearchEngine( this );

            QObject::connect( this
                              , SIGNAL( sigMovieBasicInfoFound( uint, Data::MSMovieInfo* ) )
                              , _xpTabInfo
                              , SLOT( onMovieBasicInfoFound( uint,Data::MSMovieInfo* ) )
                              , Qt::UniqueConnection );

            QObject::connect( this
                              , SIGNAL( sigImageFound( uint, QPixmap* ) )
                              , _xpTabInfo
                              , SLOT( onImageFound( uint, QPixmap* ) )
                              , Qt::UniqueConnection );
        }
    }

    void MSSearchEngine::doDisconnection( UI::MSMainWindow* _xpMainWindow )
    {
        if( NULL != _xpMainWindow )
        {
            QObject::disconnect( this
                              , SIGNAL( sigMoviesFromTitleFound( uint, QList<Data::MSMovieSearchResult*> ) )
                              , _xpMainWindow
                              , SLOT( onMoviesFromTitleFound( uint, QList<Data::MSMovieSearchResult*> ) ) );
        }
    }

    void MSSearchEngine::doDisconnection( UI::MSTabInfo* _xpTabInfo )
    {
        if( NULL != _xpTabInfo )
        {
            QObject::disconnect( this
                              , SIGNAL( sigMovieBasicInfoFound( uint, Data::MSMovieInfo* ) )
                              , _xpTabInfo
                              , SLOT( onMovieBasicInfoFound( uint, Data::MSMovieInfo* ) ) );

            QObject::disconnect( this
                              , SIGNAL( sigImageFound( uint, QPixmap* ) )
                              , _xpTabInfo
                              , SLOT( onImageFound( uint, QPixmap* ) ) );

            _xpTabInfo->setSearchEngine( NULL );
        }
    }

    QList< MSSearchEngine* > MSSearchEngineManager::s_lpSearchEngine = QList< MSSearchEngine* >();

    QList< MSSearchEngine* > MSSearchEngineManager::getAllSearchEngine()
    {
        return s_lpSearchEngine;
    }

    void MSSearchEngineManager::loadAllSearchEngines()
    {
        s_lpSearchEngine.push_back( new Tools::MSSearchEngine_TMDB() );
    }

    void MSSearchEngineManager::unloadSearchEngines()
    {
        while( !s_lpSearchEngine.isEmpty() )
        {
            MSSearchEngine* pSE = s_lpSearchEngine.takeLast();
            delete pSE;
            pSE = NULL;
        }
    }
}
