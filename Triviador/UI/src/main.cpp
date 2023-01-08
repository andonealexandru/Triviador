#include "mainwindow.h"
#include "Map.h"
#include "NumericQuestion.h"
#include "MCQuestion.h"
#include "Profile.h"
#include <QtWidgets/QApplication>
#include <fstream>
#include <Qstring>
#include"Register.h"

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    Map map;
   // NumericQuestion nq;
    Profile profile;
    MCQuestion mcq(2, "intrebare", { "r1","r2","r3","r4" },1,0,1);
    mcq.setQuestion();
    //w.show();
    //map.show();
    //nq.show();
    //mcq.show();
    //profile.show();
   Register r;
    r.show();
   

    return a.exec();
}
