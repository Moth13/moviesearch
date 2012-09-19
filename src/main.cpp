/*
 * main.cpp
 *
 * Author(s):
 * - Jeremie GUERINEL 
 *
 * Created 2012-9-17
 */

#include <QtGui/QApplication>
#include "MSMainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MSMainWindow w;
    w.show();

    return a.exec();
}
