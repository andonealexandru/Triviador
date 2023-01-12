#include "mainwindow.h"
#include "Map.h"
#include <QtWidgets/QApplication>
#include "NumericQuestion.h"
#include "MCQuestion.h"
#include "SugestionAnswer.h"
#include "DuelResult.h"
#include "lobby.h"
#include <fstream>
#include <QTimer>
#include <QObject> 

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
  //  Map map;
  //  map.g.ReadMap(2);// TODO: apelez functia de paintevent dupa cr
    //NumericQuestion nq(3, "intrebare", 1, 1, 1);
  //  MCQuestion mcq(2, "intrebare", { "r1","r2","r3","r4" }, 1, 0, 1);
   
    //DuelResult dr({ "Iulian","Eduard","Mihai" });
    //dr.show();
    w.show();
    //mcq.show();
   // map.show();

    return a.exec();
}