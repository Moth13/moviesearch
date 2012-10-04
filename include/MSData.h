/*
 * MSData.h
 *
 * Author(s):
 * - Jeremie GUERINEL
 *
 * Created 2012-9-19
 */

#ifndef MSDATA_H
#define MSDATA_H

#include <QtCore>

namespace Data
{
    /*! \class Describing main MSData*/
    class MSData : public QObject
    {
        public:
            explicit MSData( QObject* parent = NULL ) : QObject( parent ), m_strClassName( "MSData" ){}
            MSData( const MSData& _rMSData ) : QObject( _rMSData.parent() ), m_strClassName( "MSData" ){}
            ~MSData(){}

            inline const QString& getType() const { return m_strClassName; }
            inline MSData& operator=( const MSData& _rMSData )
            {
                m_strClassName = _rMSData.getType();
                return *this;
            }
            inline bool operator==( const MSData& _rMSData )
            {
                return m_strClassName == _rMSData.getType();
            }

            virtual bool isValid() const = 0;
            virtual QString toString() const = 0;

        protected :
            QString m_strClassName;
    };

    /*! \class Describing search result movie*/
    class MSMovieSearchResult : public MSData
    {
        public:
            explicit MSMovieSearchResult( QObject* parent = NULL ) : MSData( parent ){ m_strClassName = "MSMovieSearchResult"; }
            MSMovieSearchResult( const MSMovieSearchResult& _rMSMovieSearchResult ) : MSData( _rMSMovieSearchResult.parent() )
            {
                m_strClassName      = "MSMovieSearchResult";
            }
            ~MSMovieSearchResult(){}

            // setFunction
            inline void setName( const QString& _rstrName ){ m_strName = _rstrName; }

            // getFunction
            inline const QString& getName() const { return m_strName; }

            // tools
            virtual bool isValid() const { return true; }
            virtual QString toString() const
            {
                QString strReturn;
                strReturn += m_strName + "; ";

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

    /*! \class Describing basic person info*/
    class MSPersonInfo : public MSData
    {
        public:
            explicit MSPersonInfo( QObject* parent = NULL ) : MSData( parent ){ m_strClassName = "MSPersonInfo"; }
            MSPersonInfo( const MSPersonInfo& _rMSPersonInfo ) : MSData( _rMSPersonInfo.parent() )
            {
                m_strClassName      = "MSPersonInfo";
                m_strName           = _rMSPersonInfo.getName();
                m_urlHomepage       = _rMSPersonInfo.getHomepage();
                m_dateBirth         = _rMSPersonInfo.getBirthday();
                m_dateDead          = _rMSPersonInfo.getDeathday();
                m_strPlaceOfBirth   = _rMSPersonInfo.getPlaceOfBirth();
                m_strImagePath      = _rMSPersonInfo.getProfilePath();
                m_iID               = _rMSPersonInfo.getId();
            }
            ~MSPersonInfo(){}

            // setFunction
            inline void setName( const QString& _rstrName ){ m_strName = _rstrName; }
            inline void setHomepage( const QUrl& _rurlHomepage ){ m_urlHomepage = _rurlHomepage; }
            inline void setBirthday( const QDate& _rdateBirth ){ m_dateBirth = _rdateBirth; }
            inline void setDeathday( const QDate& _rdateDead ){ m_dateDead = _rdateDead; }
            inline void setPlaceOfBirth( const QString& _rstrPlaceOfBirth ){ m_strPlaceOfBirth = _rstrPlaceOfBirth; }
            inline void setProfileImagePath( const QString& _rstrImagePath ){ m_strImagePath = _rstrImagePath; }
            inline void setId( int _iID ){ m_iID = _iID; }

            // getFunction
            inline const QString& getName() const { return m_strName; }
            inline const QUrl& getHomepage() const { return m_urlHomepage; }
            inline const QDate& getBirthday() const { return m_dateBirth; }
            inline const QDate& getDeathday() const { return m_dateDead; }
            inline const QString& getPlaceOfBirth() const { return m_strPlaceOfBirth; }
            inline const QString& getProfilePath() const { return m_strImagePath; }
            inline int getId() const { return m_iID; }

            // tools
            virtual bool isValid() const { return m_iID != -1; }
            virtual QString toString() const
            {
                QString strReturn;
                strReturn += m_strName + "; ";
                strReturn += m_urlHomepage.toString() + "; ";
                strReturn += m_dateBirth.toString() + "; ";
                strReturn += m_dateDead.toString() + "; ";
                strReturn += m_strPlaceOfBirth + "; ";
                strReturn += m_strImagePath + "; ";
                strReturn += QString::number( m_iID ) + "; ";

                return strReturn;
            }

            inline MSPersonInfo& operator=( const MSPersonInfo& _rMSPersonInfo )
            {
                Q_ASSERT( m_strClassName == _rMSPersonInfo.getType() );

                m_strName           = _rMSPersonInfo.getName();
                m_urlHomepage       = _rMSPersonInfo.getHomepage();
                m_dateBirth         = _rMSPersonInfo.getBirthday();
                m_dateDead          = _rMSPersonInfo.getDeathday();
                m_strPlaceOfBirth   = _rMSPersonInfo.getPlaceOfBirth();
                m_strImagePath      = _rMSPersonInfo.getProfilePath();
                m_iID               = _rMSPersonInfo.getId();

                return *this;
            }
            inline bool operator==( const MSPersonInfo& _rMSPersonInfo )
            {
                return m_strClassName           == _rMSPersonInfo.getName()
                        && m_urlHomepage        == _rMSPersonInfo.getHomepage()
                        && m_dateBirth          == _rMSPersonInfo.getBirthday()
                        && m_dateDead           == _rMSPersonInfo.getDeathday()
                        && m_strPlaceOfBirth    == _rMSPersonInfo.getPlaceOfBirth()
                        && m_strImagePath       == _rMSPersonInfo.getProfilePath()
                        && m_iID                == _rMSPersonInfo.getId();
            }

        private:
            QString m_strName;
            QUrl m_urlHomepage;
            QDate m_dateBirth;
            QDate m_dateDead;
            int m_iID;
            QString m_strPlaceOfBirth;
            QString m_strImagePath;
    };
}

#endif // MSDATA_H
