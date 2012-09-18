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
 * MSMainwindow.h
 *
 * Author(s):
 * - Jeremie GUERINEL 
 *
 * Created 2012-9-17
 */

#ifndef MSMAINWINDOW_H
#define MSMAINWINDOW_H

#include <QtGui>
#include <QtNetwork>

namespace Ui
{
    class MSMainWindow;
}

class MSTabInfo;

class MSMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MSMainWindow(QWidget *parent = 0);
    ~MSMainWindow();

    private slots:
        void on_SearchFor_TextEdit_returnPressed();

        void on_lTabInfo_Widget_tabCloseRequested(int index);

        void on_actionClose_triggered();

        void on_actionAbout_MovieSearch_triggered();

        void onReplyFinished( QNetworkReply* );

        void on_History_View_itemDoubleClicked(QListWidgetItem *item);

    private:
        Ui::MSMainWindow *      ui;
        QList< MSTabInfo* >     m_lpTabsInfo;
        QMap< QString, int >    m_mMovieByID;
        QNetworkAccessManager * m_pNetworkManager;
};

#endif // MSMAINWINDOW_H
