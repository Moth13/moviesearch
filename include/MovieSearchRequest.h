#ifndef MOVIESEARCHREQUEST_H
#define MOVIESEARCHREQUEST_H


#include <QtCore>
#include <QtNetwork>

class MovieSearchRequest : public QObject
{
    Q_OBJECT

    public :
        MovieSearchRequest( );

        ~MovieSearchRequest( );

    public slots :
        void        searchMovie( const QString& _strSearch );

    signals :
        void        searchMovieResult( const QStringList& _lStrResult );

    private slots :
        void        replyFromNetwork( QNetworkReply* _reply );

    private :
       QNetworkAccessManager*      m_pNetworkAccesManager;
};


#endif // MOVIESEARCHREQUEST_H
