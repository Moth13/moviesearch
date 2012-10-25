
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
        m_strPixIconName    = "./plugins/resources/tmdb-logo.png";
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
        AUTOLOG
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
        AUTOLOG
        QNetworkRequest request;
        QNetworkReply* pReply = NULL;

        request.setRawHeader( "Accept","application/json" );
        request.setUrl( QUrl( "http://api.themoviedb.org/3/movie/" + QString::number( _rMovieSearchResult.getMovieID() ) +"?api_key=dc005c14d5fdaa914da77a1855473768" ) );

        pReply = m_pNetworkManager->get( request );

        uint uiQueryId = qHash( _rMovieSearchResult.getName() );
        m_mQuery.insert( pReply, PQT( uiQueryId, Movie_Info ) );

        return uiQueryId;
    }

    uint MSSearchEngine_TMDB::getMovieCast( const Data::MSMovieInfo& _rMovie )
    {
        QNetworkRequest request;
        QNetworkReply* pReply = NULL;

        request.setRawHeader( "Accept","application/json" );
        request.setUrl( QUrl( "http://api.themoviedb.org/3/movie/" + QString::number( _rMovie.getId() ) +"/casts?api_key=dc005c14d5fdaa914da77a1855473768" ) );

        pReply = m_pNetworkManager->get( request );

        uint uiQueryId = qHash( _rMovie.getTitle() );
        m_mQuery.insert( pReply, PQT( uiQueryId, Movie_Cast ) );

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

    uint MSSearchEngine_TMDB::getPersonCredits( const Data::MSPersonInfo& _rPerson )
    {
        QNetworkRequest request;
        QNetworkReply* pReply = NULL;

        request.setRawHeader( "Accept","application/json" );
        request.setUrl( QUrl( "http://api.themoviedb.org/3/person/" + QString::number( _rPerson.getId() ) +"/credits" +"?api_key=dc005c14d5fdaa914da77a1855473768" ) );

        pReply = m_pNetworkManager->get( request );

        uint uiQueryId = qHash( _rPerson.getName() );
        m_mQuery.insert( pReply, PQT( uiQueryId, Person_Credits ) );

        return uiQueryId;
    }

    uint MSSearchEngine_TMDB::getDataImageFrom( const Data::MSData& _rMSData )
    {
        QString strQuery;
        QString strSearchType;
        int iID = 0;
        if( _rMSData.getType().contains( "MSMovieInfo" ) )
        {
            strSearchType   = "movie";
            iID             = static_cast< const Data::MSMovieInfo& >( _rMSData ).getId();
            strQuery        = "DataImage_" + static_cast< const Data::MSMovieInfo& >( _rMSData ).getTitle();
        }
        if( _rMSData.getType().contains( "MSPersonInfo" ) )
        {
            strSearchType   = "person";
            iID             = static_cast< const Data::MSPersonInfo& >( _rMSData ).getId();
            strQuery        = "DataImage_" + static_cast< const Data::MSPersonInfo& >( _rMSData ).getName();
        }

        uint uiQueryId = 0;
        if( !strSearchType.isEmpty() )
        {
            QNetworkRequest request;
            QNetworkReply* pReply = NULL;

            request.setRawHeader( "Accept","application/json" );
            request.setUrl( QUrl( "http://api.themoviedb.org/3/" + strSearchType + "/" + QString::number( iID ) +"/images?api_key=dc005c14d5fdaa914da77a1855473768" ) );

            pReply = m_pNetworkManager->get( request );

            uiQueryId = qHash( strQuery );
            m_mQuery.insert( pReply, PQT( uiQueryId, DataImage_Get ) );
        }

        return uiQueryId;
    }

    uint MSSearchEngine_TMDB::getImage( const QString& _rstrImageName, eImageType _eImageType )
    {
        QNetworkRequest request;
        QNetworkReply* pReply = NULL;

        QString strImage;
        switch( _eImageType )
        {
            case ICON :
                strImage = "w92";
            break;
            case POSTER :
                strImage = "w185";
            break;
            default :
                strImage = "original";
            break;
        }

        request.setRawHeader( "Accept","application/json" );
        request.setUrl( QUrl( "http://cf2.imgobject.com/t/p/w185/" + _rstrImageName ) );

        pReply = m_pNetworkManager->get( request );

        uint uiQueryId = qHash( _rstrImageName );
        m_mQuery.insert( pReply, PQT( uiQueryId, Image_Get ) );

        return uiQueryId;
    }

    void MSSearchEngine_TMDB::onNetworkManagerReply( QNetworkReply* _pReply )
    {
        AUTOLOG
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
            case Movie_Cast :
            {
                QVariantMap res = parser.parse( _pReply->readAll(), &bOk ).toMap();

                if( bOk )
                {
                    QList< Data::MSMovieCast* > lpMovieCast;

                    foreach( QVariant result, res[ "cast" ].toList() )
                    {
                        Data::MSMovieCast_TMDB* pMovieCast  = new Data::MSMovieCast_TMDB();
                        QJson::QObjectHelper::qvariant2qobject( result.toMap(), pMovieCast );

                        lpMovieCast.push_back( pMovieCast );
                    }

                    emit sigMovieCastFound( pairQueryType.first, lpMovieCast );
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
            case Person_Credits :
            {
                QVariantMap res = parser.parse( _pReply->readAll(), &bOk ).toMap();

                if( bOk )
                {
                    QList< Data::MSPersonCredits* > lpResult;

                    foreach( QVariant result, res[ "cast" ].toList() )
                    {
                        Data::MSPersonCredits_TMDB* pPersonCredits = new Data::MSPersonCredits_TMDB();
                        QJson::QObjectHelper::qvariant2qobject( result.toMap(), pPersonCredits );
                        lpResult.push_back( pPersonCredits );
                    }
                    qSort( lpResult.begin(), lpResult.end(), Data::MSPersonCredits::reclentlier );


                    emit sigPersonCreditsFound( pairQueryType.first, lpResult );
                }
                else
                {
                    qDebug()<< "parsing failed";
                }
            }
            break;
            case DataImage_Get :
            {
                QVariantMap res = parser.parse( _pReply->readAll(), &bOk ).toMap();

                if( bOk )
                {
                    QList< Data::MSDataImage* > lpResult;

                    foreach( QVariant result, res[ "backdrops" ].toList() )
                    {
                        Data::MSDataImage_TMDB* pDataImage  = new Data::MSDataImage_TMDB();
                        QJson::QObjectHelper::qvariant2qobject( result.toMap(), pDataImage );

                        pDataImage->setImageType( Data::MSDataImage::BACKDROP );

                        lpResult.push_back( pDataImage );
                    }

                    foreach( QVariant result, res[ "posters" ].toList() )
                    {
                        Data::MSDataImage_TMDB* pDataImage  = new Data::MSDataImage_TMDB();
                        QJson::QObjectHelper::qvariant2qobject( result.toMap(), pDataImage );

                        pDataImage->setImageType( Data::MSDataImage::POSTER );

                        lpResult.push_back( pDataImage );
                    }

                    foreach( QVariant result, res[ "profiles" ].toList() )
                    {
                        Data::MSDataImage_TMDB* pDataImage  = new Data::MSDataImage_TMDB();
                        QJson::QObjectHelper::qvariant2qobject( result.toMap(), pDataImage );

                        pDataImage->setImageType( Data::MSDataImage::PROFILES );

                        lpResult.push_back( pDataImage );
                    }

                    emit sigDataImagesFound( pairQueryType.first, lpResult );
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

Q_EXPORT_PLUGIN2( MSPlugins_TMDB, Tools::MSSearchEngine_TMDB )
