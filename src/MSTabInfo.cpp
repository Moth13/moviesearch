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
 * MSTabInfo.cpp
 *
 * Author(s):
 * - Jeremie GUERINEL 
 *
 * Created 2012-9-17
 */

#include "include/MSTabInfo.h"
#include "ui_MSTabInfo.h"
#include <MSParser.h>

MSTabInfo::MSTabInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MSTabInfo)
{
    ui->setupUi(this);

    ui->TabInfo_Image_Label->setPixmap( QPixmap( "../../../resources/simpson_Me.jpg" ) );
    ui->TabInfo_Title_Label->setText( "J. Guerinel" );

    m_pNetworkManager = new QNetworkAccessManager( this );

    bool bIsConnected = QObject::connect( m_pNetworkManager
                      , SIGNAL( finished( QNetworkReply* ) )
                      , this
                      , SLOT( onReplyFinished( QNetworkReply* ) )
                      , Qt::QueuedConnection );

    if( bIsConnected )
    {
        qDebug( "Network manager successfully connected" );
    }
    else
    {
        qFatal( "Network manager failed to be connected" );
    }
}

MSTabInfo::~MSTabInfo()
{
    delete ui;
    delete m_pNetworkManager;
}

void MSTabInfo::searchFor( int iID )
{
    QNetworkRequest request;
    request.setRawHeader( "Accept","application/json" );
    request.setUrl( QUrl( "http://api.themoviedb.org/3/movie/" + QString::number( iID ) + "?api_key=dc005c14d5fdaa914da77a1855473768" ) );
    m_pQueriesMap.insert( m_pNetworkManager->get( request ), 0 );
}

void MSTabInfo::setContent( const QHash< int, QString >& _rhContent )
{
    ui->TabInfo_Title_Label->setText( _rhContent[ 0 ] );
    ui->TabInfo_TagLine_Label->setText( _rhContent[ 2 ] );
    ui->TabInfo_Overview_Label->setText( _rhContent[ 3 ] );

    QNetworkRequest request;
    request.setRawHeader( "Accept","application/json" );
    request.setUrl( QUrl( _rhContent[ 1 ] ) );
    m_pQueriesMap.insert( m_pNetworkManager->get( request ), 1 );
}

void MSTabInfo::onReplyFinished( QNetworkReply* _pReply )
{
    if( m_pQueriesMap[ _pReply ] == 1 )
    {
        m_pQueriesMap.take( _pReply );
        const QByteArray data( _pReply->readAll() );

        QPixmap pixmap;
        pixmap.loadFromData(data);

        ui->TabInfo_Image_Label->setPixmap( pixmap );
    }
    else
    {
        MSParser parser;
        QHash< int, QString > content = parser.parseContentToMovie( _pReply->readAll() );
        setContent( content );
    }
}
