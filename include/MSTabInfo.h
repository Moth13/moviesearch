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
 * MSTabInfo.h
 *
 * Author(s):
 * - Jeremie GUERINEL
 *
 * Created 2012-9-17
 */

#ifndef MSTABINFO_H
#define MSTABINFO_H

#include <QtCore>
#include <QWidget>
#include <QtNetwork>

namespace Ui {
    class MSTabInfo;
}

class MSTabInfo : public QWidget
{
        Q_OBJECT

    public:
        explicit MSTabInfo(QWidget *parent = 0);
        ~MSTabInfo();

        void setContent( const QHash< int, QString >& _rhContent );
    private slots :
        void onReplyFinished( QNetworkReply* );
    private:
        Ui::MSTabInfo *ui;
        QNetworkAccessManager * m_pNetworkManager;
};

#endif // MSTABINFO_H
