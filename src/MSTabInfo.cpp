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
        ,   m_xpSearchEngine    ( NULL )
        ,   m_uiDataQueryID     ( 0 )
    {
        m_pUI->setupUi( this );
    }

    MSTabInfo::~MSTabInfo()
    {
        if( NULL != m_xpSearchEngine )
        {
            m_xpSearchEngine->doDisconnection( this );
        }

        if( m_pData )
        {
            delete m_pData;
            m_pData = NULL;
        }

        delete m_pUI;

        m_mQueryImage.clear();
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

    void MSTabInfo::setQueryID( uint _uiQueryID )
    {
        m_uiDataQueryID = _uiQueryID;
    }

    void MSTabInfo::setSearchEngine( Tools::MSSearchEngine* _xpSearchEngine )
    {
        m_xpSearchEngine = _xpSearchEngine;
    }

    void MSTabInfo::setContent( const Data::MSData& rMSData )
    {
        bool bContentUsed = false;

        if( rMSData.getType().contains( "MSMovieInfo" ) )
        {
            bContentUsed = true;

            m_mQueryImage.clear();

            qDebug() <<"rMSData is a MSMovie";
            qDebug() << rMSData.toString();

            const Data::MSMovieInfo& rMovie = static_cast< const Data::MSMovieInfo& >( rMSData );
            m_pUI->TabInfo_Title_Label->setText( rMovie.getTitle() );
            m_pUI->TabInfo_Tagline_Label->setText(rMovie.getTagline() );
            m_pUI->TabInfo_Overview_Label->setText( rMovie.getOverview() );
            m_pUI->TabInfo_ReleaseDate_Label->setText( rMovie.getReleaseDate().toString() );
            m_pUI->TabInfo_VoteAverage_Label->setText( QString::number( rMovie.getVoteAverage() ) );
            m_pUI->TabInfo_VoteCount_Label->setText( QString::number( rMovie.getVoteCount() ) );
            m_pUI->TabInfo_Homepage_Label->setText( rMovie.getHomepage().toString() );

            if( NULL != m_xpSearchEngine )
            {
                uint uiQueryId = m_xpSearchEngine->getImage( rMovie.getPosterPath(), Tools::MSSearchEngine::POSTER );
                m_mQueryImage.insert( uiQueryId, m_pUI->TabInfo_Image_Label );
            }

            qDebug() <<"Setting it done";
        }
        if( rMSData.getType().contains( "MSPersonInfo" ) )
        {
            bContentUsed = true;
            qWarning( "Not yet implemented" );
        }

        if( bContentUsed )
        {
            if( m_pData )
            {
                delete m_pData;
                m_pData = NULL;
            }
            m_pData = &const_cast< Data::MSData& >( rMSData );
        }
        else
        {
            qFatal( "MSData can't be handled!!" );
        }
    }

    void MSTabInfo::onMovieBasicInfoFound( uint _uiQueryID, Data::MSMovieInfo* _pMovie )
    {
        if( m_uiDataQueryID == _uiQueryID
            && NULL != _pMovie )
        {
            setContent( *_pMovie );
        }
    }

    void MSTabInfo::onImageFound( uint _uiQueryID, QPixmap* _pPixmap )
    {
        if( m_mQueryImage.contains( _uiQueryID )
            && NULL != m_mQueryImage[ _uiQueryID ]
            && NULL != _pPixmap )
        {
            m_mQueryImage[ _uiQueryID ]->onPixmapReceived( *_pPixmap );
        }
    }
}
