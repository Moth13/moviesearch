#include <MSSearchEngine.h>

#include <MSDataMovie.h>
#include <MSDataPerson.h>

namespace Tools
{
    MSSearchEngine::MSSearchEngine()
        :   m_strName       ( "Fake SearchEngine" )
        ,   m_pPixIcon      ( NULL )
    {
    }

    MSSearchEngine::~MSSearchEngine()
    {
        qDebug() << QString( "Destroying %1" ).arg( m_strName );

        delete m_pPixIcon;
    }

    QList< MSSearchEngine* > MSSearchEngineManager::s_lpSearchEngine = QList< MSSearchEngine* >();

    QList< MSSearchEngine* > MSSearchEngineManager::getAllSearchEngine()
    {
        return s_lpSearchEngine;
    }

    void MSSearchEngineManager::loadAllSearchEngines()
    {
        QDir pluginDir  = QDir( "/home/jguerinel/work/perso/m13moviesearch/build/debug/plugins" );

        foreach( QString file, pluginDir.entryList( QDir::Files ) )
        {
            qDebug() << "test " << pluginDir.absoluteFilePath( file );
            QPluginLoader loader( pluginDir.absoluteFilePath( file ) );
            loader.setLoadHints(QLibrary::ResolveAllSymbolsHint);
            QObject* pPlugin = loader.instance();

            qDebug() << loader.errorString();
            if( NULL != pPlugin )
            {
                qDebug() << "test";
                MSSearchEngine* pSearchEngine = static_cast< MSSearchEngine* >( pPlugin );
                s_lpSearchEngine.push_back( pSearchEngine );
                qDebug() << pSearchEngine->getName();
            }
            else
            {
                qDebug() << "Failed to load a plugin!!!";
            }
        }
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
