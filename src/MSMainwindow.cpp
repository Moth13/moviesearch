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
 * MSMainwindow.cpp
 *
 * Author(s):
 * - Jeremie GUERINEL 
 *
 * Created 2012-9-17
 */

#include "MSMainwindow.h"
#include "ui_MSMainwindow.h"

#include "MSTabInfo.h"

#include <QMessageBox>
#include <MSParser.h>

MSMainWindow::MSMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MSMainWindow)
{
    ui->setupUi(this);

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

MSMainWindow::~MSMainWindow()
{
    delete ui;

    while( !m_lpTabsInfo.isEmpty() )
    {
        delete m_lpTabsInfo.takeLast();
    }

    delete m_pNetworkManager;
}

void MSMainWindow::on_SearchFor_TextEdit_returnPressed()
{
    QString strResearch = ui->SearchFor_TextEdit->text();

    if( !strResearch.isEmpty() )
    {
        QNetworkRequest request;

//        request.setUrl( QUrl( "http://api.themoviedb.org/3/authentication/token/new?api_key=dc005c14d5fdaa914da77a1855473768" ) );

        request.setRawHeader( "Accept","application/json" );
        request.setUrl( QUrl( "http://api.themoviedb.org/3/search/movie?api_key=dc005c14d5fdaa914da77a1855473768&query=" + strResearch ) );
        QNetworkReply* reply = m_pNetworkManager->get( request );
    }
}

void MSMainWindow::on_lTabInfo_Widget_tabCloseRequested(int index)
{
    MSTabInfo* pTab = m_lpTabsInfo.takeAt( index );
    ui->lTabInfo_Widget->removeTab( index );

    delete pTab;
}

void MSMainWindow::on_actionClose_triggered()
{
    close();
}

void MSMainWindow::on_actionAbout_MovieSearch_triggered()
{
    QString strMessage  = "Designed by J. Guerinel";
    strMessage          += QString( "/n jeremie.guerinel@gmail.com" );
    strMessage          += QString( "/n Version : " ) + QString( MS_VERSION );
    QMessageBox::about( this, "About Movie search", strMessage );
}

void MSMainWindow::onReplyFinished( QNetworkReply* _pReply )
{
    if( _pReply )
    {
        MSParser parser;
        QHash< int, QString > content = parser.parseContentToResultList( _pReply->readAll() );

        for( int i = 0; i<content.size(); i++ )
        {
            ui->History_View->insertItem( i, content[ i ] );
            ++i;
        }

        MSTabInfo* pTab = new MSTabInfo();
        pTab->setContent( content );

        ui->lTabInfo_Widget->addTab( pTab, content[ 0 ] );
        m_lpTabsInfo.push_back( pTab );
    }
}
