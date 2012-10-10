/*
 * main.cpp
 *
 * Author(s):
 * - Jeremie GUERINEL 
 *
 * Created 2012-9-17
 */

#include <QtGui/QApplication>
#include <MSMainWindow.h>

#include <MSSearchEngine.h>

int main(int argc, char *argv[])
{
    Tools::MSSearchEngineManager::loadAllSearchEngines();

    QApplication a(argc, argv);
    UI::MSMainWindow w;
    w.show();

    return a.exec();
}
