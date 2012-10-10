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
#include <MSEngineExport.h>

namespace Data
{
    /*! \class Describing main MSData*/
    class MSEngine_EXPORT MSData : public QObject
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
    /*! \class Describing image*/
    class MSEngine_EXPORT MSDataImage: public MSData
    {
        public:
            enum eImageType
            {   INVALID     = -1
            ,   POSTER      = 0
            ,   BACKDROP
            ,   PROFILES
            };

            explicit MSDataImage( QObject* parent = NULL ) : MSData( parent ), m_eImageType ( INVALID ) { m_strClassName = "MSDataImage"; }
            MSDataImage( const MSDataImage& _rMSDataImage ) : MSData( _rMSDataImage.parent() )
            {
                m_strClassName  = _rMSDataImage.getType();
                m_strImageFile  = _rMSDataImage.getImageFile();
                m_strIso        = _rMSDataImage.getIso();
                m_fAspectRatio  = _rMSDataImage.getAspectRatio();
                m_iHeight       = _rMSDataImage.getHeight();
                m_iWidth        = _rMSDataImage.getWidth();
                m_eImageType    = _rMSDataImage.getImageType();
            }
            ~MSDataImage(){}

            // setFunction
            inline void setImageFile( const QString& _rstrImageFile ){ m_strImageFile = _rstrImageFile; }
            inline void setIso( const QString& _rstrIso ){ m_strIso = _rstrIso; }
            inline void setAspectRatio( float _fAspectRatio ){ m_fAspectRatio = _fAspectRatio; }
            inline void setHeight( int _iHeight ){ m_iHeight = _iHeight; }
            inline void setWidth( int _iWidth ){ m_iWidth = _iWidth; }
            inline void setImageType( eImageType _eImageType ){ m_eImageType = _eImageType; }

            // getFunction
            inline const QString& getImageFile() const { return m_strImageFile; }
            inline const QString& getIso() const { return m_strIso; }
            inline float getAspectRatio() const { return m_fAspectRatio; }
            inline int getHeight() const { return m_iHeight; }
            inline int getWidth() const { return m_iWidth; }
            inline eImageType getImageType() const { return m_eImageType ; }

            // tools
            virtual bool isValid() const { return m_eImageType != INVALID; }
            virtual QString toString() const
            {
                QString strReturn;
                strReturn += m_strImageFile + "; ";
                strReturn += m_strIso + "; ";
                strReturn += QString::number( m_fAspectRatio ) + "; ";
                strReturn += QString::number( m_iHeight ) + "; ";
                strReturn += QString::number( m_iWidth ) + "; ";
                strReturn += QString::number( m_eImageType ) + "; ";

                return strReturn;
            }

            inline MSDataImage& operator=( const MSDataImage& _rMSDataImage )
            {
                Q_ASSERT( m_strClassName == _rMSDataImage.getType() );

                m_strImageFile  = _rMSDataImage.getImageFile();
                m_strIso        = _rMSDataImage.getIso();
                m_fAspectRatio  = _rMSDataImage.getAspectRatio();
                m_iHeight       = _rMSDataImage.getHeight();
                m_iWidth        = _rMSDataImage.getWidth();
                m_eImageType    = _rMSDataImage.getImageType();

                return *this;
            }
            inline bool operator==( const MSDataImage& _rMSDataImage )
            {
                return m_strClassName       == _rMSDataImage.getType()
                        && m_strImageFile   == _rMSDataImage.getImageFile()
                        && m_strIso         == _rMSDataImage.getIso()
                        && m_fAspectRatio   == _rMSDataImage.getAspectRatio()
                        && m_iHeight        == _rMSDataImage.getHeight()
                        && m_iWidth         == _rMSDataImage.getWidth()
                        && m_eImageType     == _rMSDataImage.getImageType();
            }

        private:
            QString m_strImageFile;
            QString m_strIso;
            float m_fAspectRatio;
            int m_iHeight;
            int m_iWidth;
            eImageType m_eImageType;
    };
}

#endif // MSDATA_H
