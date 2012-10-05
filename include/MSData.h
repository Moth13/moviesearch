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
}

#endif // MSDATA_H
