#include <MovieSearchWindow.h>

MovieSearchWindow::MovieSearchWindow(QWidget *parent)
	:	QMainWindow(parent)
{
	resize( 500, 300 );

	m_pSearchText = new QLabel( "Type your search : ", this );
	m_pSearchText->move( 10, 10 );

	m_pLaunchSearchButton = new QPushButton( "Launch Search!!", this );
	m_pLaunchSearchButton->move( 390, 40 );
	m_pLaunchSearchButton->resize( 100, 25 );

	m_pSearchEdit = new QTextEdit( "Your Search", this );
	m_pSearchEdit->move( 10, 40 );
	m_pSearchEdit->resize( 300, 25 );

	m_pSearchResultList = new QListWidget( this );
	m_pSearchResultList->move( 10, 85 );
	m_pSearchResultList->resize( 480, 205 );

    QObject::connect( m_pLaunchSearchButton , SIGNAL( pressed () ), this, SLOT(launchButtonPressed()));
}

MovieSearchWindow::~MovieSearchWindow()
{
	delete m_pLaunchSearchButton;
	delete m_pSearchText;
	delete m_pSearchResultList;
}


void MovieSearchWindow::launchButtonPressed()
{
    emit requestLaunch( "Avatar" );
}

void MovieSearchWindow::screenSearchResult( const QStringList & _lResults )
{
    for( int i = 0; i<_lResults.size(); ++i )
        qDebug("=> %s", _lResults[i].toStdString().c_str() );
}

