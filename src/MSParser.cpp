/*
 * MSParser.cpp
 *
 * Author(s):
 * - Jeremie GUERINEL 
 *
 * Created 2012-9-17
 */

#include <MSParser.h>

#include <resources/qjson/include/qjson/parser.h>
#include <resources/qjson/include/qjson/qobjecthelper.h>

#include <MSData.h>

QHash< int, QString > MSParser::parseContentToResultList( const QByteArray& _rstrContent )
{
    QHash< int, QString > hContent;

    QJson::Parser parser;
    bool bOk;

    qDebug() << _rstrContent;

    QVariantMap res = parser.parse( _rstrContent, &bOk ).toMap();
    if( bOk )
    {
        int i = 0;
        foreach( QVariant result, res[ "results" ].toList() )
        {
            hContent.insert( i, result.toMap()[ "original_title" ].toString() );
            ++i;
            hContent.insert( i, QString( "http://cf2.imgobject.com/t/p/w185" ) + result.toMap()[ "poster_path" ].toString() );
            ++i;
            hContent.insert( i, result.toMap()[ "id" ].toString() );
            ++i;

            qDebug() << result.toMap()[ "original_title" ].toString().toUtf8().constData();
        }
    }
    else
    {
        qDebug( "parsing failed" );
    }

    return hContent;
}

MSMovieInfo* MSParser::parseContentToMovie( const QByteArray& _rstrContent )
{
    qDebug( "parsing movie" );

    MSMovieInfo*        pMovie  = new MSMovieInfo();
    QJson::Parser   parser;
    bool            bOk;

    QVariantMap res = parser.parse( _rstrContent, &bOk ).toMap();
    QJson::QObjectHelper::qvariant2qobject( res, pMovie );

    qDebug( "parsing done" );

    return pMovie;
}

MSParser::MSParser()
{

}

MSParser::~MSParser()
{

}
