#include <MovieSearchApp.h>
#include <MovieSearchWindow.h>
#include <MovieSearchRequest.h>


MovieSearchApp::MovieSearchApp( QWidget* _pParent )
    :   m_pGUI          ( NULL )
    ,   m_pNetwork      ( NULL )
{
    m_pGUI = new MovieSearchWindow( _pParent );
    m_pNetwork = new MovieSearchRequest( );


    QObject::connect( m_pGUI, SIGNAL( requestLaunch( const QString& ) ), m_pNetwork, SLOT( searchMovie( const QString & ) ) );
    QObject::connect( m_pNetwork, SIGNAL( searchMovieResult( const QStringList& ) ), m_pGUI, SLOT( screenSearchResult( const QStringList & ) ) );

    m_pGUI->show();
}

MovieSearchApp::~MovieSearchApp( )
{
    delete m_pGUI;
    delete m_pNetwork;
}
