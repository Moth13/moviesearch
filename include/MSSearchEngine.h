/*
 * MSParser.h
 *
 * Author(s):
 * - Jeremie GUERINEL
 *
 * Created 2012-9-17
 */

#ifndef MSSEARCHENGINE_H
#define MSSEARCHENGINE_H

#include <QtCore>
#include <QPixmap>

namespace Data
{
    class MSData;
    class MSDataImage;

    class MSMovieSearchResult;
    class MSMovieInfo;
    class MSMovieCast;

    class MSPersonSearchResult;
    class MSPersonInfo;
}

namespace UI
{
    class MSMainWindow;
    class MSTabInfo;
}

namespace Tools
{
    /*! \class Describing a search engine */
    class MSSearchEngine : public QObject
    {
        Q_OBJECT
        friend class MSSearchEngineManager;
    public :
        /*! \enum Image type*/
        enum eImageType
        {   ICON    = 0
        ,   POSTER
        ,   MAX
        };
//        typedef uint eImageType;

        //------------------------------------------------------//
        // Attributs functions
        /*! \return Search Engine's name */
        inline const QString& getName() const{ return m_strName; }
        /*! \return Search Engine's icon */
        const QPixmap& getIcon()
        {
            if( NULL == m_pPixIcon )
            {
                m_pPixIcon = new QPixmap( m_strPixIconName );
            }
            return *m_pPixIcon;
        }
        //------------------------------------------------------//

        //------------------------------------------------------//
        // Tools function
        void doConnection( UI::MSMainWindow* _xpMainWindow = NULL );
        void doConnection( UI::MSTabInfo* _xpTabInfo = NULL );

        void doDisconnection( UI::MSMainWindow* _xpMainWindow = NULL );
        void doDisconnection( UI::MSTabInfo* _xpTabInfo = NULL );
        //------------------------------------------------------//

        //------------------------------------------------------//
        // Search functions
        /*!
            Get all movie from a title
            \return aqueryId
        */
        virtual uint getMoviesFromTitle( const QString& _rstrTitle ) = 0;
        /*!
            Get basic information from a MSMMovieSearchResult
            \return a queryId
        */
        virtual uint getBasicMovieInfo( const Data::MSMovieSearchResult& _rMovieSearchResult ) = 0;
        /*!
            Get, for a MSMovie, associate casting
            \return a queryId
        */
        virtual uint getMovieCast( const Data::MSMovieInfo& _rMovie ) = 0;

        /*!
            Get all persons from a name
            \return aqueryId
        */
        virtual uint getPersonsFromName( const QString& _rstrName ) = 0;
        /*!
            Get basic information from a MSMMovieSearchResult
            \return a queryId
        */
        virtual uint getBasicPersonInfo( const Data::MSPersonSearchResult& _rPersonSearchResult ) = 0;


        /*!
            Get a data image
            \return a queryId
        */
        virtual uint getDataImageFrom( const Data::MSData& _rMSData ) = 0;
        /*!
            Get an image
            \return a queryId
        */
        virtual uint getImage( const QString& _rstrImageName, eImageType _eImageType ) = 0;
        //------------------------------------------------------//

    signals :
        //------------------------------------------------------//
        // Signals
        /*! Signal emitted when get movies from title is completed */
        void sigMoviesFromTitleFound( uint _uiQueryID, QList< Data::MSMovieSearchResult* > _lpResults );
        /*! Signal emitted when get basic movie info is completed */
        void sigMovieBasicInfoFound( uint _uiQueryID, Data::MSMovieInfo* _pMovie );
        /*! Signal emitted when get movie cast is completed */
        void sigMovieCastFound( uint _uiQueryID, QList< Data::MSMovieCast* > _lpMovie );

        /*! Signal emitted when get persons from name is completed */
        void sigPersonsFromNameFound( uint _uiQueryID, QList< Data::MSPersonSearchResult* > _lpResults );
        /*! Signal emitted when get basic movie info is completed */
        void sigPersonBasicInfoFound( uint _uiQueryID, Data::MSPersonInfo* _pMovie );

        /*! Signal emitted when get data image is completed */
        void sigDataImagesFound( uint _uiQueryID, QList< Data::MSDataImage* > _lpDataImage );

        /*! Signal emitted when get image is completed */
        void sigImageFound( uint _uiQueryID, QPixmap* _pPixmap );
        //------------------------------------------------------//

    protected :
        /*! Constructor */
        MSSearchEngine();
        /*! Destructor */
        ~MSSearchEngine();

        //------------------------------------------------------//
        // Attributs
        QString     m_strName;
        QString     m_strPixIconName;
        QPixmap*    m_pPixIcon;
        //------------------------------------------------------//
    private :
    };

    class MSSearchEngineManager
    {
    public :
        /*! \brief Load all available search engine (plugins) */
        static void loadAllSearchEngines();
        static void unloadSearchEngines();

        /*! \return All search engine */
        static QList< MSSearchEngine* > getAllSearchEngine();

    private :
        static QList< MSSearchEngine* > s_lpSearchEngine;
    };
}

#endif // MSSEARCHENGINE_H
