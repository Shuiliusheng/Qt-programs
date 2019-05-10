#include <QtGui/QApplication>
#include "widget.h"
#include<QGridLayout>
#include<QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("GB2312"));
    Widget w;
    w.show();
    
    return a.exec();
}
