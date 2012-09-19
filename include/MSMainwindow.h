/*
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

        void onReplyFinished( QNetworkReply* );

        void on_SearchFor_TextEdit_returnPressed();

        void on_lTabInfo_Widget_tabCloseRequested(int index);

        void on_actionClose_triggered();

        void on_actionAbout_MovieSearch_triggered();

        void on_History_View_itemDoubleClicked(QListWidgetItem *item);

    private:
        Ui::MSMainWindow *      ui;
        QList< MSTabInfo* >     m_lpTabsInfo;
        QMap< QString, int >    m_mMovieByID;
        QNetworkAccessManager * m_pNetworkManager;
};

#endif // MSMAINWINDOW_H
