/*
 * MSTabInfo.cpp
 *
 * Author(s):
 * - Jeremie GUERINEL
 *
 * Created 2012-9-17
 */

#include <include/MSTabInfo.h>
#include <ui_MSTabInfo.h>

#include <MSDataMovie.h>
#include <MSDataPersonn.h>

#include <MSSearchEngine.h>

namespace UI
{
    MSTabInfo::MSTabInfo( QWidget* _pParent )
        :   QWidget             ( _pParent )
        ,   m_pUI               ( new Ui::MSTabInfo )
        ,   m_pData             ( NULL )
        ,   m_pWaitingAnimation ( NULL )
    {
        m_pUI->setupUi( this );

        m_pWaitingAnimation = new QMovie( "../../../resources/waiting.gif" );
        m_pUI->TabInfo_Image_Label->setMovie( m_pWaitingAnimation );
        m_pUI->TabInfo_Image_Label->setFrameStyle( QFrame::Panel | QFrame::Sunken );
        m_pWaitingAnimation->start();
    }

    MSTabInfo::~MSTabInfo()
    {
        m_pWaitingAnimation->stop();
        delete m_pWaitingAnimation;

        if( m_pData )
        {
            delete m_pData;
            m_pData = NULL;
        }

        delete m_pUI;
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

//            QNetworkRequest request;
//            request.setRawHeader( "Accept","application/json" );
//            request.setUrl( QUrl( QString( "http://cf2.imgobject.com/t/p/w185/" ) + rMovie.getPosterPath() ) );
//            m_pQueriesMap.insert( m_pNetworkManager->get( request ), 1 );
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

    void MSTabInfo::onMovieBasicInfoFound( uint /*_uiQueryID*/, Data::MSMovieInfo* _pMovie )
    {
        if( NULL != _pMovie )
        {
            setContent( *_pMovie );
        }
    }

//    void MSTabInfo::onReplyFinished( QNetworkReply* _pReply )
//    {
//        if( m_pQueriesMap[ _pReply ] == 1 )
//        {
//            m_pQueriesMap.take( _pReply );
//            const QByteArray data( _pReply->readAll() );

//            QPixmap pixmap;
//            pixmap.loadFromData(data);

//            m_pUI->TabInfo_Image_Label->setPixmap( pixmap );
//        }
//        else
//        {
////            Tools::MSSearchEngine parser;
////            Data::MSMovieInfo* pMovie = parser.parseContentToMovie( _pReply->readAll() );

////            if( pMovie )
////            {
////                setContent( *pMovie );
////            }
//        }
//    }
}
