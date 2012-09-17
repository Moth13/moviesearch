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

MSMainWindow::MSMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MSMainWindow)
{
    ui->setupUi(this);
}

MSMainWindow::~MSMainWindow()
{
    delete ui;

    while( !m_lpTabsInfo.isEmpty() )
    {
        delete m_lpTabsInfo.takeLast();
    }
}

void MSMainWindow::on_SearchFor_TextEdit_returnPressed()
{
    QString strResearch = ui->SearchFor_TextEdit->text();

    if( !strResearch.isEmpty() )
    {
        MSTabInfo* pTab = new MSTabInfo();

        ui->lTabInfo_Widget->addTab( pTab, strResearch );
        m_lpTabsInfo.push_back( pTab );
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
