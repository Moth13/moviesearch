
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
        :   MSSearchEngine      ( )
        ,   m_pNetworkManager   ( NULL )
    {
        m_strPixIconName    = "../../../resources/tmdb-logo.png";
        m_strName           = "TMDB";

        m_pNetworkManager   = new QNetworkAccessManager( this );

        bool bIsConnected   = QObject::connect( m_pNetworkManager
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
        m_mQuery.insert( pReply, PQT( uiQueryId, Movie_Search ) );

        return uiQueryId;
    }

    uint MSSearchEngine_TMDB::getBasicMovieInfo( const Data::MSMovieSearchResult& _rMovieSearchResult )
    {
        QNetworkRequest request;
        QNetworkReply* pReply = NULL;

        request.setRawHeader( "Accept","application/json" );
        request.setUrl( QUrl( "http://api.themoviedb.org/3/movie/" + QString::number( _rMovieSearchResult.getMovieID() ) +"?api_key=dc005c14d5fdaa914da77a1855473768" ) );

        pReply = m_pNetworkManager->get( request );

        uint uiQueryId = qHash( _rMovieSearchResult.getName() );
        m_mQuery.insert( pReply, PQT( uiQueryId, Movie_Info ) );

        return uiQueryId;
    }

    uint MSSearchEngine_TMDB::getPersonsFromName( const QString& _rstrName )
    {
        QNetworkRequest request;
        QNetworkReply* pReply = NULL;

        request.setRawHeader( "Accept","application/json" );
        request.setUrl( QUrl( "http://api.themoviedb.org/3/search/person?api_key=dc005c14d5fdaa914da77a1855473768&query=" + _rstrName ) );

        pReply = m_pNetworkManager->get( request );

        uint uiQueryId = qHash( _rstrName );
        m_mQuery.insert( pReply, PQT( uiQueryId, Person_Search ) );

        return uiQueryId;
    }

    uint MSSearchEngine_TMDB::getBasicPersonInfo( const Data::MSPersonSearchResult& _rPersonSearchResult )
    {
        QNetworkRequest request;
        QNetworkReply* pReply = NULL;

        request.setRawHeader( "Accept","application/json" );
        request.setUrl( QUrl( "http://api.themoviedb.org/3/person/" + QString::number( _rPersonSearchResult.getPersonID() ) +"?api_key=dc005c14d5fdaa914da77a1855473768" ) );

        pReply = m_pNetworkManager->get( request );

        uint uiQueryId = qHash( _rPersonSearchResult.getName() );
        m_mQuery.insert( pReply, PQT( uiQueryId, Person_Info ) );

        return uiQueryId;
    }

    uint MSSearchEngine_TMDB::getImage( const QString& _rstrImageName, eImageType /*_eImageType*/ )
    {
        qDebug()<< "getImage";
        QNetworkRequest request;
        QNetworkReply* pReply = NULL;

        request.setRawHeader( "Accept","application/json" );
        request.setUrl( QUrl( "http://cf2.imgobject.com/t/p/w185/" + _rstrImageName ) );

        pReply = m_pNetworkManager->get( request );

        uint uiQueryId = qHash( _rstrImageName );
        m_mQuery.insert( pReply, PQT( uiQueryId, Image_Get ) );

        return uiQueryId;
    }

    void MSSearchEngine_TMDB::onNetworkManagerReply( QNetworkReply* _pReply )
    {
        PQT pairQueryType = m_mQuery[ _pReply ];
        QJson::Parser parser;
        bool bOk;
        switch( pairQueryType.second )
        {
            case Movie_Search :
            {
                QVariantMap res = parser.parse( _pReply->readAll(), &bOk ).toMap();

                if( bOk )
                {
                    QList< Data::MSMovieSearchResult* > lpResult;

                    foreach( QVariant result, res[ "results" ].toList() )
                    {
                        Data::MSMovieSearchResult* pResult = new Data::MSMovieSearchResult();
                        pResult->setName( result.toMap()[ "original_title" ].toString() );
                        pResult->setPoster( result.toMap()[ "poster_path" ].toString() );
                        pResult->setMovieID( result.toMap()[ "id" ].toInt() );
                        lpResult.push_back( pResult );
                    }
                    qSort( lpResult.begin(), lpResult.end(), Data::MSMovieSearchResult::lesser );

                    emit sigMoviesFromTitleFound( pairQueryType.first, lpResult );
                }
                else
                {
                    qDebug( "parsing failed" );
                }
            }
            break;
            case Movie_Info :
            {
                QVariantMap res = parser.parse( _pReply->readAll(), &bOk ).toMap();

                if( bOk )
                {
                    Data::MSMovieInfo_TMDB* pMovie  = new Data::MSMovieInfo_TMDB();
                    QJson::QObjectHelper::qvariant2qobject( res, pMovie );

                    emit sigMovieBasicInfoFound( pairQueryType.first, pMovie );
                }
                else
                {
                    qDebug()<< "parsing failed";
                }
            }
            break;
            case Person_Search :
            {
                QVariantMap res = parser.parse( _pReply->readAll(), &bOk ).toMap();

                if( bOk )
                {
                    QList< Data::MSPersonSearchResult* > lpResult;

                    foreach( QVariant result, res[ "results" ].toList() )
                    {
                        Data::MSPersonSearchResult* pResult = new Data::MSPersonSearchResult();
                        pResult->setName( result.toMap()[ "name" ].toString() );
                        pResult->setPoster( result.toMap()[ "profile_path" ].toString() );
                        pResult->setPersonID( result.toMap()[ "id" ].toInt() );
                        lpResult.push_back( pResult );
                    }
                    qSort( lpResult.begin(), lpResult.end(), Data::MSPersonSearchResult::lesser );

                    emit sigPersonsFromNameFound( pairQueryType.first, lpResult );
                }
                else
                {
                    qDebug()<< "parsing failed";
                }
            }
            break;
            case Person_Info :
            {
                QVariantMap res = parser.parse( _pReply->readAll(), &bOk ).toMap();

                if( bOk )
                {
                    Data::MSPersonInfo_TMDB* pPerson  = new Data::MSPersonInfo_TMDB();
                    QJson::QObjectHelper::qvariant2qobject( res, pPerson );

                    emit sigPersonBasicInfoFound( pairQueryType.first, pPerson );
                }
                else
                {
                    qDebug()<< "parsing failed";
                }
            }
            break;
            case Image_Get :
            {
                QPixmap* pPixmap = new QPixmap();
                pPixmap->loadFromData( _pReply->readAll() );

                emit sigImageFound( pairQueryType.first, pPixmap );
            }
            break;
            default :
            break;
        }
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
