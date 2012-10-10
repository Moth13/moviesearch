/*
 * MSImage.h
 *
 * Author(s):
 * - Jeremie GUERINEL
 *
 * Created 2012-10-5
 */

#ifndef MSIMAGE_H
#define MSIMAGE_H

#include <QtCore>
#include <QLabel>

class QMovie;

class MSImage : public QLabel
{
        Q_OBJECT
    public :
        /*! Constructor, coming from QLabel */
        explicit MSImage( QWidget * parent = 0, Qt::WindowFlags f = 0 );
        explicit MSImage( const QString & text, QWidget * parent = 0, Qt::WindowFlags f = 0 );

        /*! Destructor */
        virtual ~MSImage();

    public slots :
        /*! Start waiting animation */
        void onStartAnimation();
        /*! Stop current wainting animation and set Pixmap */
        void onPixmapReceived( const QPixmap& _rPixmap );

    private :
        //------------------------------------------------------//
        // Attributs
        static QMovie*  s_pQMovie;
        static int      s_iNbUsed;
        //------------------------------------------------------//
};

#endif // MSIMAGE_H
