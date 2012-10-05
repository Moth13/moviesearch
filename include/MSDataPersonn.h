/*
 * MSDataPersonn.h
 *
 * Author(s):
 * - Jeremie GUERINEL 
 *
 * Created 2012-10-5
 */

#ifndef MSDATAPERSONN_H
#define MSDATAPERSONN_H

#include <MSData.h>

namespace Data
{
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

#endif // MSDATAPERSONN_H
