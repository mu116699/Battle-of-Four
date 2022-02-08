#include "checkerboard.h"
#include "checkerboardpc.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    CheckerBoardPC cpc;
//    cpc.show();

    Checkerboard c;
    c.show();


    return a.exec();
}
