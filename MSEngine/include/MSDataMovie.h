/*
 * MSDataMovie.h
 *
 * Author(s):
 * - Jeremie GUERINEL
 *
 * Created 2012-10-5
 */

#ifndef MSDATAMOVIE_H
#define MSDATAMOVIE_H

#include <MSData.h>

namespace Data
{
    /*! \class Describing search result movie*/
    class MSMovieSearchResult : public MSData
    {
        public:
            explicit MSMovieSearchResult( QObject* parent = NULL ) : MSData( parent ){ m_strClassName = "MSMovieSearchResult"; }
            MSMovieSearchResult( const MSMovieSearchResult& _rMSMovieSearchResult ) : MSData( _rMSMovieSearchResult.parent() )
            {
                m_strClassName  = "MSMovieSearchResult";
                m_strName       = _rMSMovieSearchResult.getName();
                m_strPoster     = _rMSMovieSearchResult.getPoster();
                m_iMovieID      = _rMSMovieSearchResult.getMovieID();
            }
            ~MSMovieSearchResult(){}

            // setFunction
            inline void setName( const QString& _rstrName ){ m_strName = _rstrName; }
            inline void setPoster( const QString& _rstrPoster ){ m_strPoster = _rstrPoster; }
            inline void setMovieID( int _iMovieID ){ m_iMovieID = _iMovieID; }

            // getFunction
            inline const QString& getName() const { return m_strName; }
            inline const QString& getPoster() const { return m_strPoster; }
            inline int getMovieID() const { return m_iMovieID; }

            // tools
            virtual bool isValid() const { return true; }
            virtual QString toString() const
            {
                QString strReturn;
                strReturn += m_strName + "; ";
                strReturn += m_strPoster + "; ";
                strReturn += QString::number( m_iMovieID ) + "; ";

                return strReturn;
            }

            inline MSMovieSearchResult& operator=( const MSMovieSearchResult& _rMSMovieSearchResult )
            {
                Q_ASSERT( m_strClassName == _rMSMovieSearchResult.getType() );
                m_strName = _rMSMovieSearchResult.getName();
                return *this;
            }
            inline bool operator==( const MSMovieSearchResult& _rMSMovieSearchResult )
            {
                return m_strClassName == _rMSMovieSearchResult.getName();
            }

            static bool lesser( MSMovieSearchResult* _p1, MSMovieSearchResult* _p2 )
            {
                bool bValue = false;
                if ( NULL != _p1
                     && NULL != _p2 )
                {
                    bValue = _p1->getName() < _p2->getName();
                }
                return bValue;
            }

        private:
            QString m_strName;
            QString m_strPoster;
            int     m_iMovieID;
    };

    /*! \class Describing basic movie info*/
    class MSMovieInfo: public MSData
    {
        public:
            explicit MSMovieInfo( QObject* parent = NULL ) : MSData( parent ) { m_strClassName = "MSMovieInfo"; }
            MSMovieInfo( const MSMovieInfo& _rMSMovieInfo ) : MSData( _rMSMovieInfo.parent() )
            {
                m_strClassName  = _rMSMovieInfo.getType();
                m_strTitle      = _rMSMovieInfo.getTitle();
                m_strOriTitle   = _rMSMovieInfo.getOrignalTitle();
                m_strTagline    = _rMSMovieInfo.getTagline();
                m_strOverview   = _rMSMovieInfo.getOverview();
                m_urlHomepage   = _rMSMovieInfo.getHomepage();
                m_releaseDate   = _rMSMovieInfo.getReleaseDate();
                m_fVoteAverage  = _rMSMovieInfo.getVoteAverage();
                m_iVoteCount    = _rMSMovieInfo.getVoteCount();
                m_strPosterPath = _rMSMovieInfo.getPosterPath();
                m_iImdbId       = _rMSMovieInfo.getImdbId();
                m_iID           = _rMSMovieInfo.getId();
            }
            ~MSMovieInfo(){}

            // setFunction
            inline void setTitle( const QString& _rstrTitle ){ m_strTitle = _rstrTitle; }
            inline void setOriTitle( const QString& _rstrOriTitle ){ m_strOriTitle = _rstrOriTitle; }
            inline void setTagline( const QString& _rstrTagline ){ m_strTagline = _rstrTagline; }
            inline void setOverview( const QString& _rstrOverview ){ m_strOverview = _rstrOverview; }
            inline void setHomepage( const QUrl& _rurlHomepage ){ m_urlHomepage = _rurlHomepage; }
            inline void setReleaseDate( const QDate& _rReleaseDate ){ m_releaseDate = _rReleaseDate; }
            inline void setVoteAverage( float _fVoteAverage ){ m_fVoteAverage = _fVoteAverage; }
            inline void setVoteCount( int _iVoteCount ){ m_iVoteCount = _iVoteCount; }
            inline void setPosterPath( const QString& _rstrPosterPath ){ m_strPosterPath = _rstrPosterPath; }
            inline void setImdbId( int _iImdbId ){ m_iImdbId = _iImdbId; }
            inline void setId( int _iID ){ m_iID = _iID; }

            // getFunction
            inline const QString& getTitle() const { return m_strTitle; }
            inline const QString& getOrignalTitle() const { return m_strOriTitle; }
            inline const QString& getTagline() const { return m_strTagline; }
            inline const QString& getOverview() const { return m_strOverview; }
            inline const QUrl& getHomepage() const { return m_urlHomepage; }
            inline const QDate& getReleaseDate() const { return m_releaseDate; }
            inline float getVoteAverage() const { return m_fVoteAverage; }
            inline int getVoteCount() const { return m_iVoteCount; }
            inline const QString& getPosterPath() const { return m_strPosterPath; }
            inline int getImdbId() const { return m_iImdbId; }
            inline int getId() const { return m_iID; }

            // tools
            virtual bool isValid() const { return m_iID != -1; }
            virtual QString toString() const
            {
                QString strReturn;
                strReturn += m_strTitle + "; ";
                strReturn += m_strOriTitle + "; ";
                strReturn += m_strTagline + "; ";
                strReturn += m_strOverview + "; ";
                strReturn += m_urlHomepage.toString() + "; ";
                strReturn += m_releaseDate.toString() + "; ";
                strReturn += QString::number( m_fVoteAverage ) + "; ";
                strReturn += QString::number( m_iVoteCount ) + "; ";
                strReturn += m_strPosterPath + "; ";
                strReturn += QString::number( m_iImdbId ) + "; ";
                strReturn += QString::number( m_iID ) + "; ";

                return strReturn;
            }

            inline MSMovieInfo& operator=( const MSMovieInfo& _rMSMovieInfo )
            {
                Q_ASSERT( m_strClassName == _rMSMovieInfo.getType() );

                m_strTitle      = _rMSMovieInfo.getTitle();
                m_strOriTitle   = _rMSMovieInfo.getOrignalTitle();
                m_strTagline    = _rMSMovieInfo.getTagline();
                m_strOverview   = _rMSMovieInfo.getOverview();
                m_urlHomepage   = _rMSMovieInfo.getHomepage();
                m_releaseDate   = _rMSMovieInfo.getReleaseDate();
                m_fVoteAverage  = _rMSMovieInfo.getVoteAverage();
                m_iVoteCount    = _rMSMovieInfo.getVoteCount();
                m_strPosterPath = _rMSMovieInfo.getPosterPath();
                m_iImdbId       = _rMSMovieInfo.getImdbId();
                m_iID           = _rMSMovieInfo.getId();

                return *this;
            }
            inline bool operator==( const MSMovieInfo& _rMSMovieInfo )
            {
                return m_strClassName       == _rMSMovieInfo.getType()
                        && m_strTitle       == _rMSMovieInfo.getTitle()
                        && m_strOriTitle    == _rMSMovieInfo.getOrignalTitle()
                        && m_strTagline     == _rMSMovieInfo.getTagline()
                        && m_strOverview    == _rMSMovieInfo.getOverview()
                        && m_urlHomepage    == _rMSMovieInfo.getHomepage()
                        && m_releaseDate    == _rMSMovieInfo.getReleaseDate()
                        && m_fVoteAverage   == _rMSMovieInfo.getVoteAverage()
                        && m_iVoteCount     == _rMSMovieInfo.getVoteCount()
                        && m_strPosterPath  == _rMSMovieInfo.getPosterPath()
                        && m_iImdbId        == _rMSMovieInfo.getImdbId()
                        && m_iID            == _rMSMovieInfo.getId();
            }

        private:
            QString m_strTitle;
            QString m_strOriTitle;
            QString m_strTagline;
            QString m_strOverview;
            QUrl m_urlHomepage;
            QDate m_releaseDate;
            float m_fVoteAverage;
            int m_iVoteCount;
            QString m_strPosterPath;
            int m_iID;
            int m_iImdbId;
    };

    /*! \class Describing movie cast*/
    class MSMovieCast: public MSData
    {
        public:
            explicit MSMovieCast( QObject* parent = NULL ) : MSData( parent ) { m_strClassName = "MSMovieCast"; }
            MSMovieCast( const MSMovieCast& _rMSMovieCast ) : MSData( _rMSMovieCast.parent() )
            {
                m_strClassName      = _rMSMovieCast.getType();
                m_strCharacterName  = _rMSMovieCast.getCharacterName();
                m_strActorName      = _rMSMovieCast.getActorName();
                m_strActorImage     = _rMSMovieCast.getActorImage();
                m_iActorID          = _rMSMovieCast.getActorID();
                m_iCastPos          = _rMSMovieCast.getCastPos();
            }
            ~MSMovieCast(){}

            // setFunction
            inline void setCharacterName( const QString& _rstrCharaterName ){ m_strCharacterName = _rstrCharaterName; }
            inline void setActorName( const QString& _rstrActorName ){ m_strActorName = _rstrActorName; }
            inline void setActorImage( const QString& _rstrActorImage ){ m_strActorImage = _rstrActorImage; }
            inline void setActorID( int _iActorID ){ m_iActorID = _iActorID; }
            inline void setCastPos( int _iCastPos  ){ m_iCastPos = _iCastPos; }

            // getFunction
            inline const QString& getCharacterName() const { return m_strCharacterName; }
            inline const QString& getActorName() const { return m_strActorName; }
            inline const QString& getActorImage() const { return m_strActorImage; }
            inline int getActorID() const { return m_iActorID; }
            inline int getCastPos() const { return m_iCastPos; }

            // tools
            virtual bool isValid() const { return m_iActorID != -1; }
            virtual QString toString() const
            {
                QString strReturn;
                strReturn += m_strCharacterName + "; ";
                strReturn += m_strActorName + "; ";
                strReturn += m_strActorImage + "; ";
                strReturn += QString::number( m_iActorID ) + "; ";
                strReturn += QString::number( m_iCastPos ) + "; ";

                return strReturn;
            }

            inline MSMovieCast& operator=( const MSMovieCast& _rMSMovieCast )
            {
                Q_ASSERT( m_strClassName == _rMSMovieCast.getType() );

                m_strCharacterName  = _rMSMovieCast.getCharacterName();
                m_strActorName      = _rMSMovieCast.getActorName();
                m_strActorImage     = _rMSMovieCast.getActorImage();
                m_iActorID          = _rMSMovieCast.getActorID();
                m_iCastPos          = _rMSMovieCast.getCastPos();

                return *this;
            }
            inline bool operator==( const MSMovieCast& _rMSMovieCast )
            {
                return m_strClassName           == _rMSMovieCast.getType()
                        && m_strCharacterName   == _rMSMovieCast.getCharacterName()
                        && m_strActorName       == _rMSMovieCast.getActorName()
                        && m_strActorImage      == _rMSMovieCast.getActorImage()
                        && m_iActorID           == _rMSMovieCast.getActorID()
                        && m_iCastPos           == _rMSMovieCast.getCastPos();
            }

        private:
            QString m_strCharacterName;
            QString m_strActorName;
            QString m_strActorImage;
            int m_iActorID;
            int m_iCastPos;
    };
}

#endif // MSDATAMOVIE_H
