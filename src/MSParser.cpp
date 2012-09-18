/* iFeelSmart CONFIDENTIAL
 *
 * Copyright © 2012, iFeelSmart.
 * All Rights Reserved.
 *
 * The source code contained or described herein and all documents
 * related to the source code ("Material") are owned by iFeelSmart
 * or its suppliers or licensors. Title to the Material remains
 * with iFeelSmart or its suppliers and licensors.
 * The Material contains trade secrets, proprietary code and confidential
 * information of iFeelSmart or its suppliers and licensors. The Material is
 * protected by worldwide copyright and trade secret laws and treaty
 * provisions. No part of the Material may be used, copied, reproduced,
 * modified, published, uploaded, posted, transmitted, distributed, or
 * disclosed in any way without iFeelSmart's prior express written permission.
 *
 * No license under any patent, copyright, trade secret or other
 * intellectual property right is granted to or conferred upon you by
 * disclosure or delivery of the Materials, either expressly, by
 * implication, inducement, estoppel or otherwise. Any license under
 * such intellectual property rights must be express and approved by
 * iFeelSmart in writing.
 *
 * MSParser.cpp
 *
 * Author(s):
 * - Jeremie GUERINEL 
 *
 * Created 2012-9-17
 */

#include <MSParser.h>

#include <resources/qjson/include/qjson/parser.h>

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

QHash< int, QString > MSParser::parseContentToMovie( const QByteArray& _rstrContent )
{
    QHash< int, QString > hContent;

    QJson::Parser parser;
    bool bOk;

    qDebug() << _rstrContent;

    QVariantMap res = parser.parse( _rstrContent, &bOk ).toMap();
    if( bOk )
    {
        int i = 0;
        hContent.insert( i, res[ "original_title" ].toString() );
        ++i;
        hContent.insert( i, QString( "http://cf2.imgobject.com/t/p/w185" ) + res[ "poster_path" ].toString() );
        ++i;
        hContent.insert( i, res[ "tagline" ].toString() );
        ++i;
        hContent.insert( i, res[ "overview" ].toString() );
        ++i;
    }
    else
    {
        qDebug( "parsing failed" );
    }

    return hContent;
}

MSParser::MSParser()
{

}

MSParser::~MSParser()
{

}
