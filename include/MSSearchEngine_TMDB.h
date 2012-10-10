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
        /*!
            Get, for a MSMovie, associate casting
            \return a queryId
        */
        virtual uint getMovieCast( const Data::MSMovieInfo& _rMovie ) ;

        /*!
            Get all persons from a name
            \return aqueryId
        */
        virtual uint getPersonsFromName( const QString& _rstrName );
        /*!
            Get basic information from a MSMMovieSearchResult
            \return a queryId
        */
        virtual uint getBasicPersonInfo( const Data::MSPersonSearchResult& _rPersonSearchResult );
        /*!
            Get credits for a personn
            \return a queryId
        */
        virtual uint getPersonCredits( const Data::MSPersonInfo& _rPerson );

        /*!
            Get a data image
            \return a queryId
        */
        virtual uint getDataImageFrom( const Data::MSData& _rMSData );
        /*!
            Get an image
            \return a queryId
        */
        virtual uint getImage( const QString& _rstrImageName, eImageType _eImageType );
        //------------------------------------------------------//
    protected :
        /*! Constructor */
        MSSearchEngine_TMDB();
        /*! Destructor */
        ~MSSearchEngine_TMDB();
    private :
        //------------------------------------------------------//
        // Attributs
        enum eQueryType
        {   Movie_Search = 0
        ,   Movie_Info
        ,   Movie_Cast

        ,   Person_Search
        ,   Person_Info
        ,   Person_Credits

        ,   DataImage_Get
        ,   Image_Get
        };

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
