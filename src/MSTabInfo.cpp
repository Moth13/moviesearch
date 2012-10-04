/*
 * MSTabInfo.cpp
 *
 * Author(s):
 * - Jeremie GUERINEL
 *
 * Created 2012-9-17
 */

#include "include/MSTabInfo.h"
#include "ui_MSTabInfo.h"
#include <MSSearchEngine.h>

#include <MSData.h>

namespace UI
{
    MSTabInfo::MSTabInfo( QWidget* _pParent )
        :   QWidget     ( _pParent )
        ,   m_pUI       ( new Ui::MSTabInfo )
        ,   m_pData     ( NULL )
    {
        m_pUI->setupUi( this );

        m_pNetworkManager = new QNetworkAccessManager( this );

        bool bIsConnected = QObject::connect( m_pNetworkManager
                                              , SIGNAL( finished( QNetworkReply* ) )
                                              , this
                                              , SLOT( onReplyFinished( QNetworkReply* ) )
                                              , Qt::QueuedConnection );

        if( bIsConnected )
        {
            qDebug( "Network manager successfully connected" );
        }
        else
        {
            qFatal( "Network manager failed to be connected" );
        }
    }

    MSTabInfo::~MSTabInfo()
    {
        delete m_pUI;
        delete m_pNetworkManager;

        if( m_pData )
        {
            delete m_pData;
            m_pData = NULL;
        }
    }

    void MSTabInfo::searchFor( int iID )
    {
        qDebug( "searchFor" );

        QNetworkRequest request;
        request.setRawHeader( "Accept","application/json" );
        request.setUrl( QUrl( "http://api.themoviedb.org/3/movie/" + QString::number( iID ) + "?api_key=dc005c14d5fdaa914da77a1855473768" ) );
        m_pQueriesMap.insert( m_pNetworkManager->get( request ), 0 );
    }

    bool MSTabInfo::hasData() const
    {
        return m_pData != NULL ;
    }

    const Data::MSData& MSTabInfo::getCurrentData() const
    {
        Q_ASSERT( m_pData );

        return *m_pData;
    }

    void MSTabInfo::setContent( const Data::MSData& rMSData )
    {
        bool bContentUsed = false;
        if( m_pData )
        {
            delete m_pData;
            m_pData = NULL;
        }
        m_pData = &const_cast< Data::MSData& >( rMSData );

        qDebug( "setContent" );

        if( rMSData.getType().contains( "MSMovieInfo" ) )
        {
            bContentUsed = true;

            qDebug() <<"rMSData is a MSMovie";
            qDebug() << rMSData.toString();

            const Data::MSMovieInfo& rMovie = static_cast< const Data::MSMovieInfo& >( rMSData );
            m_pUI->TabInfo_Title_Label->setText( rMovie.getTitle() );
            m_pUI->TabInfo_Tagline_Label->setText(rMovie.getTagline() );
            m_pUI->TabInfo_Overview_Label->setText( rMovie.getOverview() );
            m_pUI->TabInfo_ReleaseDate_Label->setText( rMovie.getReleaseDate().toString() );
            //        m_pUI->TabInfo_OriTitle_Label->setText( rMovie.getOrignalTitle() );
            m_pUI->TabInfo_VoteAverage_Label->setText( QString::number( rMovie.getVoteAverage() ) );
            m_pUI->TabInfo_VoteCount_Label->setText( QString::number( rMovie.getVoteCount() ) );
            m_pUI->TabInfo_Homepage_Label->setText( rMovie.getHomepage().toString() );

            QNetworkRequest request;
            request.setRawHeader( "Accept","application/json" );
            request.setUrl( QUrl( QString( "http://cf2.imgobject.com/t/p/w185/" ) + rMovie.getPosterPath() ) );
            m_pQueriesMap.insert( m_pNetworkManager->get( request ), 1 );
        }
        if( rMSData.getType().contains( "MSPersonInfo" ) )
        {
            bContentUsed = true;
            qWarning( "Not yet implemented" );
        }


        if( !bContentUsed )
        {
            qFatal( "MSData can't be handled!!" );
        }
    }

    void MSTabInfo::onReplyFinished( QNetworkReply* _pReply )
    {
        if( m_pQueriesMap[ _pReply ] == 1 )
        {
            m_pQueriesMap.take( _pReply );
            const QByteArray data( _pReply->readAll() );

            QPixmap pixmap;
            pixmap.loadFromData(data);

            m_pUI->TabInfo_Image_Label->setPixmap( pixmap );
        }
        else
        {
//            Tools::MSSearchEngine parser;
//            Data::MSMovieInfo* pMovie = parser.parseContentToMovie( _pReply->readAll() );

//            if( pMovie )
//            {
//                setContent( *pMovie );
//            }
        }
    }
}
