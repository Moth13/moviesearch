#include <MovieSearchRequest.h>


MovieSearchRequest::MovieSearchRequest( )
    :   m_pNetworkAccesManager      ( NULL )
{

    m_pNetworkAccesManager = new QNetworkAccessManager(this);
    QObject::connect(m_pNetworkAccesManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFromNetwork(QNetworkReply* )) );
}

MovieSearchRequest::~MovieSearchRequest( )
{
    delete m_pNetworkAccesManager;
}

void MovieSearchRequest::searchMovie( const QString& _strSearch )
{
    m_pNetworkAccesManager->get( QNetworkRequest( QUrl( "http://api.themoviedb.org/2.1/Movie.search/en/xml/dc005c14d5fdaa914da77a1855473768/Avatar") ) );
}

void MovieSearchRequest::replyFromNetwork( QNetworkReply* _reply )
{
    QStringList _result;
    _result.push_back( "Avatar ");
    _result.push_back( "Avatar1 ");
    _result.push_back( "Avatar2 ");
    _result.push_back( "Avatar3 ");

    emit searchMovieResult( _result );
}


