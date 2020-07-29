#include "mainwindow.h"
#include "checkerboard.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Checkerboard c;
    c.show();
    return a.exec();
}
