/*
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
    ui->History_View->clear();

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

void MSMainWindow::on_History_View_itemDoubleClicked(QListWidgetItem *item)
{
    MSTabInfo* pTab = new MSTabInfo();
    pTab->searchFor( m_mMovieByID[ item->text() ] );

    ui->lTabInfo_Widget->addTab( pTab, item->text() );
    ui->lTabInfo_Widget->setCurrentIndex( m_lpTabsInfo.size() );
    m_lpTabsInfo.push_back( pTab );
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
            m_mMovieByID.insert( content[ i ], content[ i + 2 ].toInt() );
            ++i;
            ++i;
        }
    }
}
