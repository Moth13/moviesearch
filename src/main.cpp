#include <QtGui/QApplication>
#include "MovieSearchApp.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MovieSearchApp search;

    return a.exec();
}
