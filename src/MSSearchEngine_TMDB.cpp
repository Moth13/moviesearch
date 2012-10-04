
/*
 * MSSearchEngine.cpp
 *
 * Author(s):
 * - Jeremie GUERINEL
 *
 * Created 2012-9-17
 */

#include <MSSearchEngine_TMDB.h>

#include <resources/qjson/include/qjson/parser.h>
#include <resources/qjson/include/qjson/qobjecthelper.h>

#include <MSTools.h>

#include <MSData_TMDB.h>

namespace Tools
{

    MSSearchEngine_TMDB::MSSearchEngine_TMDB()
        :   m_pNetworkManager   ( NULL )
    {
        m_pNetworkManager = new QNetworkAccessManager( this );

        bool bIsConnected = QObject::connect( m_pNetworkManager
                                              , SIGNAL( finished( QNetworkReply* ) )
                                              , this
                                              , SLOT( onNetworkManagerReply( QNetworkReply* ) )
                                              , Qt::UniqueConnection );

        Q_ASSERT( bIsConnected && "Network manager has been not successfully connected" );
    }

    MSSearchEngine_TMDB::~MSSearchEngine_TMDB()
    {
        SAFE_DELETE( m_pNetworkManager );
    }

    uint MSSearchEngine_TMDB::getMoviesFromTitle( const QString& _rstrTitle )
    {
        QNetworkRequest request;
        QNetworkReply* pReply = NULL;

        request.setRawHeader( "Accept","application/json" );
        request.setUrl( QUrl( "http://api.themoviedb.org/3/search/movie?api_key=dc005c14d5fdaa914da77a1855473768&query=" + _rstrTitle ) );
        pReply = m_pNetworkManager->get( request );

        uint uiQueryId = qHash( _rstrTitle );
        m_mQuery.insert( pReply, PQT( uiQueryId, 0 ) );

        return uiQueryId;
    }

    uint MSSearchEngine_TMDB::getBasicMovieInfo( const Data::MSMovieSearchResult& _rMovieSearchResult )
    {
        return 0;
    }

    void MSSearchEngine_TMDB::onNetworkManagerReply( QNetworkReply* _pReply )
    {
        PQT pairQueryType = m_mQuery[ _pReply ];
        QJson::Parser parser;

        switch( pairQueryType.second )
        {
        case 0 :
        {
            bool bOk;
            QList< Data::MSMovieSearchResult* > lpResult;
            QVariantMap res = parser.parse( _pReply->readAll(), &bOk ).toMap();
            if( bOk )
            {
                foreach( QVariant result, res[ "results" ].toList() )
                {
                    Data::MSMovieSearchResult* pResult  = new Data::MSMovieSearchResult();
                    pResult->setName( result.toMap()[ "original_title" ].toString() );
                    lpResult.push_back( pResult );

//                    hContent.insert( i, result.toMap()[ "original_title" ].toString() );
//                    ++i;
//                    hContent.insert( i, QString( "http://cf2.imgobject.com/t/p/w185" ) + result.toMap()[ "poster_path" ].toString() );
//                    ++i;
//                    hContent.insert( i, result.toMap()[ "id" ].toString() );
//                    ++i;

//                    qDebug() << result.toMap()[ "original_title" ].toString().toUtf8().constData();
                }

                emit sigMoviesFromTitleFound( pairQueryType.first, lpResult );
            }
            else
            {
                qDebug( "parsing failed" );
            }
        }
        break;
        default :
        break;
        }
    }

    //QNetworkRequest request;

    ////        request.setUrl( QUrl( "http://api.themoviedb.org/3/authentication/token/new?api_key=dc005c14d5fdaa914da77a1855473768" ) );

    //request.setRawHeader( "Accept","application/json" );
    //request.setUrl( QUrl( "http://api.themoviedb.org/3/search/movie?api_key=dc005c14d5fdaa914da77a1855473768&query=" + strResearch ) );
    //QNetworkReply* reply = m_pNetworkManager->get( request );

    //    QHash< int, QString > MSSearchEngine::parseContentToResultList( const QByteArray& _rstrContent )
    //    {
    //        QHash< int, QString > hContent;

    //        QJson::Parser parser;
    //        bool bOk;

    //        qDebug() << _rstrContent;

    //        QVariantMap res = parser.parse( _rstrContent, &bOk ).toMap();
    //        if( bOk )
    //        {
    //            int i = 0;
    //            foreach( QVariant result, res[ "results" ].toList() )
    //            {
    //                hContent.insert( i, result.toMap()[ "original_title" ].toString() );
    //                ++i;
    //                hContent.insert( i, QString( "http://cf2.imgobject.com/t/p/w185" ) + result.toMap()[ "poster_path" ].toString() );
    //                ++i;
    //                hContent.insert( i, result.toMap()[ "id" ].toString() );
    //                ++i;

    //                qDebug() << result.toMap()[ "original_title" ].toString().toUtf8().constData();
    //            }
    //        }
    //        else
    //        {
    //            qDebug( "parsing failed" );
    //        }

    //        return hContent;
    //    }

    //    MSMovieInfo* MSSearchEngine::parseContentToMovie( const QByteArray& _rstrContent )
    //    {
    //        qDebug( "parsing movie" );

    //        MSMovieInfo_TMDB* pMovie  = new MSMovieInfo_TMDB();
    //        QJson::Parser   parser;
    //        bool            bOk;

    //        QVariantMap res = parser.parse( _rstrContent, &bOk ).toMap();
    //        QJson::QObjectHelper::qvariant2qobject( res, pMovie );

    //        qDebug( "parsing done" );

    //        return pMovie;
    //    }
}
