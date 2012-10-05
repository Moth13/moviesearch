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
}

#endif // MSDATAMOVIE_H
