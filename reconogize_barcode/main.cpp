#include <QtGui/QApplication>
#include "mainwindow1.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow1 w;
    w.show();
    
    return a.exec();
}
