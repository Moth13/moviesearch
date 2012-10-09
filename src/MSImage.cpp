/*
 * MSImage.cpp
 *
 * Author(s):
 * - Jeremie GUERINEL 
 *
 * Created 2012-10-5
 */

#include <MSImage.h>

#include <QMovie>

QMovie* MSImage::s_pQMovie = NULL;
int     MSImage::s_iNbUsed = 0;

MSImage::MSImage( QWidget * parent, Qt::WindowFlags f )
    :   QLabel( parent, f )
{
    onStartAnimation();
}

MSImage::MSImage( const QString & text, QWidget * parent, Qt::WindowFlags f )
    :   QLabel( text, parent, f )
{
    onStartAnimation();
}

MSImage::~MSImage()
{
    --s_iNbUsed;
    if( s_iNbUsed <= 0 )
    {
        s_pQMovie->stop();
        delete s_pQMovie;
    }
}

void MSImage::onStartAnimation()
{
    if( NULL == s_pQMovie )
    {
        s_pQMovie = new QMovie( "../../../resources/waiting.gif" );
        s_pQMovie->start();
    }
    ++s_iNbUsed;

    setMovie( s_pQMovie );
}

void MSImage::onPixmapReceived( const QPixmap& _rPixmap )
{
    setScaledContents( true );
    setPixmap( _rPixmap );
}

