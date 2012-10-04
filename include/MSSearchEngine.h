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
    class MSMovieInfo;
    class MSMovieSearchResult;
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
        //------------------------------------------------------//
        // Attributs functions
        /*! \return Search Engine's name */
        inline const QString& getName() const{ return m_strName; }
        /*! \return Search Engine's icon */
//        const QPixmap& getIcon() const { return m_pixIcon ; }
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
        //------------------------------------------------------//

    signals :
        //------------------------------------------------------//
        // Signals
        /*! Signal emitted when get movies from title is completed */
        void sigMoviesFromTitleFound( uint _uiQueryID, QList< Data::MSMovieSearchResult* > _lpResults );
        /*! Signal emitted when get basic moovie info is completed */
        void sigMovieBasicInfoFound( uint _uiQueryID, Data::MSMovieInfo* _pMovie );
        //------------------------------------------------------//

    protected :
        /*! Constructor */
        MSSearchEngine();
        /*! Destructor */
        ~MSSearchEngine();

        //------------------------------------------------------//
        // Attributs
        QString m_strName;
//        QPixmap m_pixIcon;
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
