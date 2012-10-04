#ifndef MSSEARCHENGINE_TMDB_H
#define MSSEARCHENGINE_TMDB_H

#include <QtNetwork>
#include <MSSearchEngine.h>

namespace Tools
{
    typedef QPair< uint, int > PQT;

    /*! \class Describing tmdb search engine */
    class MSSearchEngine_TMDB : public MSSearchEngine
    {
        friend class MSSearchEngineManager;
        Q_OBJECT
    public :
        //------------------------------------------------------//
        // Search functions
        /*!
            Get all movie from a title
            \return a queryId
        */
        virtual uint getMoviesFromTitle( const QString& _rstrTitle );
        /*!
            Get basic information from a MSMMovieSearchResult
            \return a queryId
        */
        virtual uint getBasicMovieInfo( const Data::MSMovieSearchResult& _rMovieSearchResult );
        //------------------------------------------------------//
    protected :
        /*! Constructor */
        MSSearchEngine_TMDB();
        /*! Destructor */
        ~MSSearchEngine_TMDB();
    private :
        //------------------------------------------------------//
        // Attributs
        QNetworkAccessManager *         m_pNetworkManager;      ///< Network request manager
        QMap< QNetworkReply*, PQT >     m_mQuery;               ///< Map of research
        //------------------------------------------------------//

        //------------------------------------------------------//
        // Tools

        //------------------------------------------------------//
    private slots :
        //------------------------------------------------------//
        // Query slots
        void onNetworkManagerReply( QNetworkReply* _pReply );
        //------------------------------------------------------//
    };
}
#endif // MSSEARCHENGINE_TMDB_H
