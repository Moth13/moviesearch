#ifndef MOVIESEARCHAPP_H
#define MOVIESEARCHAPP_H

#include <QtCore>

class MovieSearchWindow;
class MovieSearchRequest;

class MovieSearchApp : public QObject
{
    Q_OBJECT

    public :
        MovieSearchApp( QObject* _pParent = 0 );

        ~MovieSearchApp( );

    private :
        MovieSearchWindow*      m_pGUI;
        MovieSearchRequest*     m_pNetwork;

};

#endif // MOVIESEARCHAPP_H
