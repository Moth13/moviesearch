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

MSTabInfo::MSTabInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MSTabInfo)
{
    ui->setupUi(this);

    ui->TabInfo_Image_Label->setPixmap( QPixmap( "../../../resources/simpson_Me.jpg" ) );
    ui->TabInfo_Title_Label->setText( "J. Guerinel" );
}

MSTabInfo::~MSTabInfo()
{
    delete ui;
}
