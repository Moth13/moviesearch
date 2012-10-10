/*
 * MSDataPerson.h
 *
 * Author(s):
 * - Jeremie GUERINEL 
 *
 * Created 2012-10-5
 */

#ifndef MSDATAPERSON_H
#define MSDATAPERSON_H

#include <MSData.h>
#include <MSEngineExport.h>

namespace Data
{
    /*! \class Describing search result movie*/
    class MSEngine_EXPORT MSPersonSearchResult : public MSData
    {
        public:
            explicit MSPersonSearchResult( QObject* parent = NULL ) : MSData( parent ){ m_strClassName = "MSPersonSearchResult"; }
            MSPersonSearchResult( const MSPersonSearchResult& _rMSPersonSearchResult ) : MSData( _rMSPersonSearchResult.parent() )
            {
                m_strClassName  = "MSPersonSearchResult";
                m_strName       = _rMSPersonSearchResult.getName();
                m_strPoster     = _rMSPersonSearchResult.getPoster();
                m_iPersonID      = _rMSPersonSearchResult.getPersonID();
            }
            ~MSPersonSearchResult(){}

            // setFunction
            inline void setName( const QString& _rstrName ){ m_strName = _rstrName; }
            inline void setPoster( const QString& _rstrPoster ){ m_strPoster = _rstrPoster; }
            inline void setPersonID( int _iPersonID ){ m_iPersonID = _iPersonID; }

            // getFunction
            inline const QString& getName() const { return m_strName; }
            inline const QString& getPoster() const { return m_strPoster; }
            inline int getPersonID() const { return m_iPersonID; }

            // tools
            virtual bool isValid() const { return true; }
            virtual QString toString() const
            {
                QString strReturn;
                strReturn += m_strName + "; ";
                strReturn += m_strPoster + "; ";
                strReturn += QString::number( m_iPersonID ) + "; ";

                return strReturn;
            }

            inline MSPersonSearchResult& operator=( const MSPersonSearchResult& _rMSPersonSearchResult )
            {
                Q_ASSERT( m_strClassName == _rMSPersonSearchResult.getType() );
                m_strName = _rMSPersonSearchResult.getName();
                return *this;
            }
            inline bool operator==( const MSPersonSearchResult& _rMSPersonSearchResult )
            {
                return m_strClassName == _rMSPersonSearchResult.getName();
            }

            static bool lesser( MSPersonSearchResult* _p1, MSPersonSearchResult* _p2 )
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
            int     m_iPersonID;
    };

    /*! \class Describing basic person info*/
    class MSEngine_EXPORT MSPersonInfo : public MSData
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

    /*! \class Describing filmography*/
    class MSEngine_EXPORT MSPersonCredits: public MSData
    {
        public:
            explicit MSPersonCredits( QObject* parent = NULL ) : MSData( parent ) { m_strClassName = "MSPersonCredits"; }
            MSPersonCredits( const MSPersonCredits& _rMSPersonCredits ) : MSData( _rMSPersonCredits.parent() )
            {
                m_strClassName          = _rMSPersonCredits.getType();
                m_strCharacterName      = _rMSPersonCredits.getCharacterName();
                m_strMovieTitle         = _rMSPersonCredits.getMovieTitle();
                m_strMovieOriTitle      = _rMSPersonCredits.getMovieOriTitle();
                m_strMoviePosterPath    = _rMSPersonCredits.getMoviePosterPath();
                m_dMovieReleaseDate     = _rMSPersonCredits.getMovieReleaseDate();
                m_iMovieID              = _rMSPersonCredits.getMovieID();
            }
            ~MSPersonCredits(){}

            // setFunction
            inline void setCharacterName( const QString& _rstrCharaterName ){ m_strCharacterName = _rstrCharaterName; }
            inline void setMovieTitle( const QString& _strMovieTitle ){ m_strMovieTitle = _strMovieTitle; }
            inline void setMovieOriTitle( const QString& _strMovieOriTitle ){ m_strMovieOriTitle = _strMovieOriTitle; }
            inline void setMovePosterPath( const QString& _strMoviePosterPath ){ m_strMoviePosterPath = _strMoviePosterPath; }
            inline void setMovieReleaseDate( const QDate& _dMovieReleaseDate  ){ m_dMovieReleaseDate = _dMovieReleaseDate; }
            inline void setMovieID( int _iMovieID  ){ m_iMovieID = _iMovieID; }

            // getFunction
            inline const QString& getCharacterName() const { return m_strCharacterName; }
            inline const QString& getMovieTitle() const { return m_strMovieTitle; }
            inline const QString& getMovieOriTitle() const { return m_strMovieOriTitle; }
            inline const QString& getMoviePosterPath() const { return m_strMoviePosterPath; }
            inline const QDate& getMovieReleaseDate() const { return m_dMovieReleaseDate; }
            inline int getMovieID() const { return m_iMovieID; }

            // tools
            virtual bool isValid() const { return m_iMovieID != -1; }
            virtual QString toString() const
            {
                QString strReturn;
                strReturn += m_strCharacterName + "; ";
                strReturn += m_strMovieTitle + "; ";
                strReturn += m_strMovieOriTitle + "; ";
                strReturn += m_strMoviePosterPath + "; ";
                strReturn += m_dMovieReleaseDate.toString() + "; ";
                strReturn += QString::number( m_iMovieID ) + "; ";

                return strReturn;
            }

            inline MSPersonCredits& operator=( const MSPersonCredits& _rMSPersonCredits )
            {
                Q_ASSERT( m_strClassName == _rMSPersonCredits.getType() );

                m_strCharacterName      = _rMSPersonCredits.getCharacterName();
                m_strMovieTitle         = _rMSPersonCredits.getMovieTitle();
                m_strMovieOriTitle      = _rMSPersonCredits.getMovieOriTitle();
                m_strMoviePosterPath    = _rMSPersonCredits.getMoviePosterPath();
                m_dMovieReleaseDate     = _rMSPersonCredits.getMovieReleaseDate();
                m_iMovieID              = _rMSPersonCredits.getMovieID();

                return *this;
            }
            inline bool operator==( const MSPersonCredits& _rMSPersonCredits )
            {
                return m_strClassName           == _rMSPersonCredits.getType()
                        && m_strCharacterName   == _rMSPersonCredits.getCharacterName()
                        && m_strMovieTitle      == _rMSPersonCredits.getMovieTitle()
                        && m_strMovieOriTitle   == _rMSPersonCredits.getMovieOriTitle()
                        && m_strMoviePosterPath == _rMSPersonCredits.getMoviePosterPath()
                        && m_dMovieReleaseDate  == _rMSPersonCredits.getMovieReleaseDate()
                        && m_iMovieID           == _rMSPersonCredits.getMovieID();
            }

            static bool reclentlier( MSPersonCredits* _p1, MSPersonCredits* _p2 )
            {
                bool bValue = false;
                if ( NULL != _p1
                     && NULL != _p2 )
                {
                    bValue = _p1->getMovieReleaseDate() > _p2->getMovieReleaseDate();
                }
                return bValue;
            }

        private:
            QString m_strCharacterName;
            QString m_strMovieTitle;
            QString m_strMovieOriTitle;
            QString m_strMoviePosterPath;
            QDate m_dMovieReleaseDate;
            int m_iMovieID;
    };
}

#endif // MSDATAPERSONN_H
