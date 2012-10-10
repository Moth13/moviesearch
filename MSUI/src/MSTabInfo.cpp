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
#include <MSDataPerson.h>

#include <MSSearchEngine.h>

#include <QMovie>

namespace UI
{
    MSTabInfo::MSTabInfo( QWidget* _pParent )
        :   QWidget             ( _pParent )
        ,   m_pUI               ( new Ui::MSTabInfo )
        ,   m_pData             ( NULL )
        ,   m_xpSearchEngine    ( NULL )
        ,   m_uiDataQueryID     ( 0 )
        ,   m_uiCastQueryID     ( 0 )
        ,   m_uiCreditsQueryID  ( 0 )
        ,   m_uiImagesQueryID   ( 0 )
    {
        m_pUI->setupUi( this );
    }

    MSTabInfo::~MSTabInfo()
    {
        setSearchEngine( NULL );

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
        if( NULL != m_xpSearchEngine )
        {
            QObject::disconnect( m_xpSearchEngine
                                 , SIGNAL( sigMovieBasicInfoFound( uint, Data::MSMovieInfo* ) )
                                 , this
                                 , SLOT( onMovieBasicInfoFound( uint, Data::MSMovieInfo* ) ) );

            QObject::disconnect( m_xpSearchEngine
                                 , SIGNAL( sigMovieCastFound( uint, QList< Data::MSMovieCast* > ) )
                                 , this
                                 , SLOT( onMovieCastFound( uint, QList< Data::MSMovieCast* > ) ) );

            QObject::disconnect( m_xpSearchEngine
                                 , SIGNAL( sigPersonBasicInfoFound( uint, Data::MSPersonInfo* ) )
                                 , this
                                 , SLOT( onPersonBasicInfoFound( uint, Data::MSPersonInfo* ) ) );

            QObject::disconnect( m_xpSearchEngine
                                 , SIGNAL( sigPersonCreditsFound( uint, QList<Data::MSPersonCredits*> ) )
                                 , this
                                 , SLOT( onPersonCreditsFound( uint, QList<Data::MSPersonCredits*> ) ) );

            QObject::disconnect( m_xpSearchEngine
                                 , SIGNAL( sigDataImagesFound( uint, QList< Data::MSDataImage* > ) )
                                 , this
                                 , SLOT( onDataImagesFound( uint, QList< Data::MSDataImage* > ) ) );

            QObject::disconnect( m_xpSearchEngine
                                 , SIGNAL( sigImageFound( uint, QPixmap* ) )
                                 , this
                                 , SLOT( onImageFound( uint, QPixmap* ) ) );
        }

        m_xpSearchEngine = _xpSearchEngine;

        if( NULL != m_xpSearchEngine )
        {
            QObject::connect( m_xpSearchEngine
                              , SIGNAL( sigMovieBasicInfoFound( uint, Data::MSMovieInfo* ) )
                              , this
                              , SLOT( onMovieBasicInfoFound( uint, Data::MSMovieInfo* ) )
                              , Qt::UniqueConnection );

            QObject::connect( m_xpSearchEngine
                              , SIGNAL( sigMovieCastFound( uint, QList< Data::MSMovieCast* > ) )
                              , this
                              , SLOT( onMovieCastFound( uint, QList< Data::MSMovieCast* > ) )
                              , Qt::UniqueConnection );

            QObject::connect( m_xpSearchEngine
                              , SIGNAL( sigPersonBasicInfoFound( uint, Data::MSPersonInfo* ) )
                              , this
                              , SLOT( onPersonBasicInfoFound( uint, Data::MSPersonInfo* ) )
                              , Qt::UniqueConnection );

            QObject::connect( m_xpSearchEngine
                              , SIGNAL( sigPersonCreditsFound( uint, QList<Data::MSPersonCredits*> ) )
                              , this
                              , SLOT( onPersonCreditsFound( uint, QList<Data::MSPersonCredits*> ) )
                              , Qt::UniqueConnection );

            QObject::connect( m_xpSearchEngine
                              , SIGNAL( sigDataImagesFound( uint, QList< Data::MSDataImage* > ) )
                              , this
                              , SLOT( onDataImagesFound( uint, QList< Data::MSDataImage* > ) )
                              , Qt::UniqueConnection );

            QObject::connect( m_xpSearchEngine
                              , SIGNAL( sigImageFound( uint, QPixmap* ) )
                              , this
                              , SLOT( onImageFound( uint, QPixmap* ) )
                              , Qt::UniqueConnection );
        }
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
                uint uiQueryId = 0;
                uiQueryId = m_xpSearchEngine->getImage( rMovie.getPosterPath(), Tools::MSSearchEngine::POSTER );
                m_mQueryImage.insert( uiQueryId, m_pUI->TabInfo_Image_Label );

                m_uiCastQueryID     = m_xpSearchEngine->getMovieCast( rMovie );
                m_uiImagesQueryID   = m_xpSearchEngine->getDataImageFrom( rMovie );
            }

            qDebug() <<"Setting it done";
        }
        if( rMSData.getType().contains( "MSPersonInfo" ) )
        {
            bContentUsed = true;

            m_mQueryImage.clear();

            qDebug() <<"rMSData is a MSPersonInfo";
            qDebug() << rMSData.toString();

            const Data::MSPersonInfo& rPerson = static_cast< const Data::MSPersonInfo& >( rMSData );
            m_pUI->TabInfo_Title_Label->setText( rPerson.getName() );
            m_pUI->TabInfo_Tagline_Label->setText( "" );

            QString strOverview;
            strOverview += rPerson.getBirthday().toString( "dd.MM.yyyy" ) + " ";
            strOverview += rPerson.getPlaceOfBirth();
            m_pUI->TabInfo_Overview_Label->setText( strOverview );
            m_pUI->TabInfo_ReleaseDate_Label->setText( "" );
            m_pUI->TabInfo_VoteAverage_Label->setText( "" );
            m_pUI->TabInfo_VoteCount_Label->setText( "" );
            m_pUI->TabInfo_Homepage_Label->setText( rPerson.getHomepage().toString() );

            if( NULL != m_xpSearchEngine )
            {
                uint uiQueryId = 0;
                uiQueryId = m_xpSearchEngine->getImage( rPerson.getProfilePath(), Tools::MSSearchEngine::POSTER );
                m_mQueryImage.insertMulti( uiQueryId, m_pUI->TabInfo_Image_Label );

                m_uiCreditsQueryID  = m_xpSearchEngine->getPersonCredits( rPerson );
                m_uiImagesQueryID   = m_xpSearchEngine->getDataImageFrom( rPerson );
            }

            qDebug() <<"Setting it done";
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

    void MSTabInfo::onMovieCastFound( uint _uiQueryID, QList< Data::MSMovieCast* > _lpMovie )
    {
        if( m_uiCastQueryID == _uiQueryID )
        {
            // clear old list
            while( !m_lpMovieCast.isEmpty() )
            {
                delete m_lpMovieCast.takeLast();
            }
            Q_ASSERT( m_lpMovieCast.isEmpty() );

            m_lpMovieCast = _lpMovie;

            m_pUI->TabInfo_Cast->clear();
            m_pUI->TabInfo_Cast->setRowCount( m_lpMovieCast.size() );
            m_pUI->TabInfo_Cast->setColumnCount( 2 );
            m_mQueryIcon.clear();

            int i = 0;
            foreach( Data::MSMovieCast* pMovieCast, m_lpMovieCast )
            {
                QTableWidgetItem* pItemCast = new QTableWidgetItem();
                QTableWidgetItem* pItemIcon = new QTableWidgetItem();
                pItemCast->setText( pMovieCast->getActorName() + QObject::tr( " as " ) + pMovieCast->getCharacterName() );
                m_pUI->TabInfo_Cast->setItem( i, 0, pItemIcon );
                m_pUI->TabInfo_Cast->setItem( i, 1, pItemCast );


                m_pUI->TabInfo_Cast->setColumnWidth( 1, m_pUI->TabInfo_Cast->geometry().size().width() - m_pUI->TabInfo_Cast->columnWidth( 0 ) - 25 );

                if( NULL != m_xpSearchEngine )
                {
                    uint uiQueryId = m_xpSearchEngine->getImage( pMovieCast->getActorImage(), Tools::MSSearchEngine::ICON );
                    m_mQueryIcon.insert( uiQueryId, pItemIcon );
                }
                ++i;
            }
        }
    }

    void MSTabInfo::onPersonBasicInfoFound( uint _uiQueryID, Data::MSPersonInfo* _pPerson )
    {
        if( m_uiDataQueryID == _uiQueryID
            && NULL != _pPerson )
        {
            setContent( *_pPerson );
        }
    }

    void MSTabInfo::onPersonCreditsFound( uint _uiQueryID, QList< Data::MSPersonCredits* > _lpPersonCredits )
    {
        if( m_uiCreditsQueryID == _uiQueryID )
        {
            // clear old list
            while( !m_lpPersonCredits.isEmpty() )
            {
                delete m_lpPersonCredits.takeLast();
            }
            Q_ASSERT( m_lpPersonCredits.isEmpty() );

            m_lpPersonCredits = _lpPersonCredits;

            m_pUI->TabInfo_Cast->clear();
            m_pUI->TabInfo_Cast->setRowCount( m_lpPersonCredits.size() );
            m_pUI->TabInfo_Cast->setColumnCount( 2 );
            m_mQueryIcon.clear();

            int i = 0;
            foreach( Data::MSPersonCredits* pMSPersonCredits, m_lpPersonCredits )
            {
                QTableWidgetItem* pItemChar = new QTableWidgetItem();
                QTableWidgetItem* pItemIcon = new QTableWidgetItem();
                pItemChar->setText( pMSPersonCredits->getCharacterName() + QObject::tr( " in " ) + pMSPersonCredits->getMovieTitle() );
                m_pUI->TabInfo_Cast->setItem( i, 0, pItemIcon );
                m_pUI->TabInfo_Cast->setItem( i, 1, pItemChar );

                m_pUI->TabInfo_Cast->setColumnWidth( 1, m_pUI->TabInfo_Cast->geometry().size().width() - m_pUI->TabInfo_Cast->columnWidth( 0 ) - 25 );

                if( NULL != m_xpSearchEngine )
                {
                    uint uiQueryId = m_xpSearchEngine->getImage( pMSPersonCredits->getMoviePosterPath(), Tools::MSSearchEngine::ICON );
                    m_mQueryIcon.insert( uiQueryId, pItemIcon );
                }
                ++i;
            }
        }
    }

    void MSTabInfo::onDataImagesFound( uint _uiQueryID, QList< Data::MSDataImage* > _lpDataImage )
    {
        if( m_uiImagesQueryID == _uiQueryID )
        {
            // clear old list
            while( !m_lpImages.isEmpty() )
            {
                delete m_lpImages.takeLast();
            }
            Q_ASSERT( m_lpImages.isEmpty() );

            m_pUI->TabInfo_Images->clear();
            m_pUI->TabInfo_Images->setRowCount( 1 );
            m_pUI->TabInfo_Images->setColumnCount( _lpDataImage.size() );

            int i = 0;
            foreach( Data::MSDataImage* pDataImage, _lpDataImage )
            {
                MSImage* pImage = new MSImage();
                m_pUI->TabInfo_Images->setCellWidget( 0, i, pImage );

                 m_pUI->TabInfo_Images->setColumnWidth( i, ( m_pUI->TabInfo_Images->geometry().height() - 5 ) * ( pDataImage->getAspectRatio() ) );

                if( NULL != m_xpSearchEngine )
                {
                    uint uiQueryId = m_xpSearchEngine->getImage( pDataImage->getImageFile(), Tools::MSSearchEngine::POSTER );
                    m_mQueryImage.insertMulti( uiQueryId, pImage );
                }
                m_lpImages.push_back( pImage );
                ++i;
            }
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

        if( m_mQueryIcon.contains( _uiQueryID )
            && NULL != m_mQueryIcon[ _uiQueryID ]
            && NULL != _pPixmap )
        {
            m_mQueryIcon[ _uiQueryID ]->setIcon( QIcon( *_pPixmap ) );
            m_mQueryImage.take( _uiQueryID );
        }
    }

    void MSTabInfo::on_TabInfo_Cast_cellDoubleClicked(int row, int /*column*/)
    {
//        if( NULL != m_xpSearchEngine )
//        {
//            m_xpSearchEngine->get
//        }
//        m_lpMovieCast[ row ];
    }
}
