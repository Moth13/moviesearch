/*
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

namespace Ui
{
    class MSTabInfo;
}

class MSData;

class MSTabInfo : public QWidget
{
        Q_OBJECT

    public:
        explicit MSTabInfo(QWidget *parent = 0);
        ~MSTabInfo();

        void searchFor( int iID );

        bool hasData() const;
        const MSData& getCurrentData() const;

    private slots :
        void onReplyFinished( QNetworkReply* );

    private:
        Ui::MSTabInfo*              m_pUI;
        QNetworkAccessManager*      m_pNetworkManager;
        QMap< QNetworkReply*, int > m_pQueriesMap;
        MSData*                     m_pData;

        void setContent( const MSData& rMSData );
};

#endif // MSTABINFO_H
