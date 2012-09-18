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
        foreach( QVariant result, res[ "results" ].toList() )
        {
            qDebug() << result.toMap()[ "original_title" ].toString().toUtf8().constData();
        }
    }
    else
    {
        qDebug( "parsing failed" );
    }

    return hContent;

//    result to parse :
//    {
//        "page":1
//        ,"results":
//        [
//            {
//                "adult":false,"backdrop_path":"/5XPPB44RQGfkBrbJxmtdndKz05n.jpg","id":19995,"original_title":"Avatar","release_date":"2009-12-18","poster_path":"/s66l83fTQp0FAJsJqY0xUmkamcx.jpg","popularity":21569094.172,"title":"Avatar","vote_average":7.9,"vote_count":516
//            },
//            {
//                "adult":false,"backdrop_path":null,"id":76600,"original_title":"Avatar 2","release_date":"2014-12-01","poster_path":null,"popularity":0.727,"title":"Avatar 2","vote_average":0.0,"vote_count":0
//            },
//            {
//                "adult":false,"backdrop_path":null,"id":116126,"original_title":"Avatar The Last Air Bender Book 2 Volume 1","release_date":"2005-02-21","poster_path":"/2MQKa1C3HN99hOqXP2e0fACl6fb.jpg","popularity":0.157,"title":"Avatar The Last Air Bender Book 2 Volume 1","vote_average":0.0,"vote_count":0
//            },
//            {
//                "adult":false,"backdrop_path":"/9NULdZaUSmrFdjLfhP8ZdZ3RCqF.jpg","id":111332,"original_title":"Avatar: Creating the World of Pandora","release_date":"2010-02-07","poster_path":"/Ar4QELb2FvpBE9oSvidlclcCIdc.jpg","popularity":0.233,"title":"Avatar: Creating the World of Pandora","vote_average":8.5,"vote_count":1
//            },
//            {
//                "adult":false,"backdrop_path":null,"id":83533,"original_title":"Avatar 3","release_date":"2015-12-01","poster_path":null,"popularity":0.2,"title":"Avatar 3","vote_average":0.0,"vote_count":0
//            },
//            {
//                "adult":false,"backdrop_path":null,"id":100287,"original_title":"My Avatar and Me","release_date":"2010-11-17","poster_path":"/1DRS1iHoIKQ3ZKVmuFeIsjRd6Gr.jpg","popularity":0.38,"title":"My Avatar and Me","vote_average":0.0,"vote_count":0
//            },
//            {
//                "adult":false,"backdrop_path":"/swoBS9uLdYyzoyMdk7FPGD7GuMB.jpg","id":79582,"original_title":"Aliens vs. Avatars","release_date":"2011-09-20","poster_path":"/9ntgW9dwg5imLfbcQDoAO3Z9L4X.jpg","popularity":0.06,"title":"Aliens vs. Avatars","vote_average":0.0,"vote_count":0
//            }
//        ]
//        ,"total_pages":1
//        ,"total_results":7
//    }
}

MSParser::MSParser()
{

}

MSParser::~MSParser()
{

}
