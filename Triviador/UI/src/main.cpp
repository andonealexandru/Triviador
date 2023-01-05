#include "mainwindow.h"
#include "Map.h"
#include <QtWidgets/QApplication>
#include "NumericQuestion.h"
#include "MCQuestion.h"
#include <fstream>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    Map map;
    NumericQuestion nq;
    MCQuestion mcq(2, "intrebare", { "r1","r2","r3","r4" },1,0,1);
    mcq.setQuestion();
    //w.show();
    //map.show();
    //nq.show();
    mcq.show();

    return a.exec();
}
