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
        QDir pluginDir      = QDir( "./plugins" );
        QDir libPluginDir   = QDir( "./plugins/lib" );

        // Load plugins libs
        QStringList lstrLibFileName = libPluginDir.entryList( QDir::Files );
        qDebug() << "Trying to load " << lstrLibFileName.size() << " additionnal libs...";
        foreach( QString strLibFileName, lstrLibFileName )
        {
            qDebug() << "Trying to load " << strLibFileName;
            QLibrary lib( libPluginDir.absoluteFilePath( strLibFileName ) );
            bool bIsLoaded = lib.load();
            if( bIsLoaded )
            {
                qDebug() << strLibFileName << " has been successfully loaded.";
            }
            else
            {
                qDebug() << strLibFileName << " has not been loaded : " << lib.errorString();
            }
        }

        // Load plugins
        QStringList lstrPluginFileName = pluginDir.entryList( QDir::Files );
        qDebug() << "Trying to load " << lstrPluginFileName.size() << " plugins...";
        foreach( QString strPluginFileName, lstrPluginFileName )
        {
            qDebug() << "Trying to load " << strPluginFileName;

            QPluginLoader loader( pluginDir.absoluteFilePath( strPluginFileName ) );
            loader.setLoadHints(QLibrary::ResolveAllSymbolsHint);
            QObject* pPlugin = loader.instance();

            if( NULL != pPlugin )
            {
                MSSearchEngine* pSearchEngine = static_cast< MSSearchEngine* >( pPlugin );
                s_lpSearchEngine.push_back( pSearchEngine );
                qDebug() << pSearchEngine->getName() << " has been successfully loaded.";
            }
            else
            {
                qDebug() << strPluginFileName << " has not been loaded : " << loader.errorString();
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
