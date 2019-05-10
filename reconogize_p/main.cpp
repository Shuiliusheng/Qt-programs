#include <QtGui/QApplication>
#include "mainwindow2.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow2 w;
    w.show();
    
    return a.exec();
}
