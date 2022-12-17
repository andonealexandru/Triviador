#include "mainwindow.h"
#include "Map.h"
#include <QtWidgets/QApplication>
#include <fstream>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    Map map;
    //w.show();
    map.show();
    return a.exec();
}
