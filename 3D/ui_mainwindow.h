/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Sun Mar 15 01:24:40 2015
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *add;
    QPushButton *cut;
    QLabel *label;
    QLabel *label_2;
    QPushButton *add1;
    QPushButton *cut2;
    QPushButton *X1;
    QPushButton *x2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QPushButton *y1;
    QPushButton *z1;
    QPushButton *y2;
    QPushButton *z2;
    QPushButton *reset;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QPushButton *lengthadd;
    QPushButton *lengthcut;
    QLabel *label_9;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label_12;
    QLabel *label_13;
    QLabel *label_14;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QPushButton *pushButton_8;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(739, 484);
        QFont font;
        font.setPointSize(8);
        MainWindow->setFont(font);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        add = new QPushButton(centralWidget);
        add->setObjectName(QString::fromUtf8("add"));
        add->setGeometry(QRect(0, 80, 81, 51));
        QFont font1;
        font1.setPointSize(23);
        add->setFont(font1);
        cut = new QPushButton(centralWidget);
        cut->setObjectName(QString::fromUtf8("cut"));
        cut->setGeometry(QRect(90, 80, 81, 51));
        cut->setFont(font1);
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(0, 40, 171, 31));
        QFont font2;
        font2.setPointSize(17);
        label->setFont(font2);
        label->setFrameShape(QFrame::WinPanel);
        label->setFrameShadow(QFrame::Raised);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(0, 140, 171, 31));
        label_2->setFont(font2);
        label_2->setFrameShape(QFrame::WinPanel);
        label_2->setFrameShadow(QFrame::Raised);
        add1 = new QPushButton(centralWidget);
        add1->setObjectName(QString::fromUtf8("add1"));
        add1->setGeometry(QRect(0, 190, 81, 51));
        QFont font3;
        font3.setPointSize(22);
        add1->setFont(font3);
        cut2 = new QPushButton(centralWidget);
        cut2->setObjectName(QString::fromUtf8("cut2"));
        cut2->setGeometry(QRect(90, 190, 81, 51));
        cut2->setFont(font1);
        X1 = new QPushButton(centralWidget);
        X1->setObjectName(QString::fromUtf8("X1"));
        X1->setGeometry(QRect(500, 10, 81, 51));
        QFont font4;
        font4.setPointSize(15);
        X1->setFont(font4);
        x2 = new QPushButton(centralWidget);
        x2->setObjectName(QString::fromUtf8("x2"));
        x2->setGeometry(QRect(600, 10, 81, 51));
        QFont font5;
        font5.setPointSize(14);
        x2->setFont(font5);
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(440, 10, 61, 41));
        QFont font6;
        font6.setPointSize(25);
        label_3->setFont(font6);
        label_3->setLineWidth(10);
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(440, 80, 61, 41));
        label_4->setFont(font6);
        label_4->setLineWidth(10);
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(440, 150, 61, 41));
        label_5->setFont(font6);
        label_5->setLineWidth(10);
        y1 = new QPushButton(centralWidget);
        y1->setObjectName(QString::fromUtf8("y1"));
        y1->setGeometry(QRect(500, 80, 81, 51));
        y1->setFont(font4);
        z1 = new QPushButton(centralWidget);
        z1->setObjectName(QString::fromUtf8("z1"));
        z1->setGeometry(QRect(500, 150, 81, 51));
        z1->setFont(font4);
        y2 = new QPushButton(centralWidget);
        y2->setObjectName(QString::fromUtf8("y2"));
        y2->setGeometry(QRect(600, 80, 81, 51));
        y2->setFont(font5);
        z2 = new QPushButton(centralWidget);
        z2->setObjectName(QString::fromUtf8("z2"));
        z2->setGeometry(QRect(600, 150, 81, 51));
        z2->setFont(font5);
        reset = new QPushButton(centralWidget);
        reset->setObjectName(QString::fromUtf8("reset"));
        reset->setGeometry(QRect(500, 220, 181, 51));
        reset->setFont(font3);
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(690, 10, 51, 41));
        QFont font7;
        font7.setPointSize(18);
        label_6->setFont(font7);
        label_6->setLineWidth(5);
        label_6->setMidLineWidth(7);
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(690, 80, 51, 41));
        label_7->setFont(font4);
        label_7->setLineWidth(5);
        label_7->setMidLineWidth(7);
        label_8 = new QLabel(centralWidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(690, 150, 51, 41));
        label_8->setFont(font7);
        label_8->setLineWidth(5);
        label_8->setMidLineWidth(7);
        lengthadd = new QPushButton(centralWidget);
        lengthadd->setObjectName(QString::fromUtf8("lengthadd"));
        lengthadd->setGeometry(QRect(10, 360, 51, 41));
        lengthadd->setFont(font7);
        lengthcut = new QPushButton(centralWidget);
        lengthcut->setObjectName(QString::fromUtf8("lengthcut"));
        lengthcut->setGeometry(QRect(80, 360, 51, 41));
        lengthcut->setFont(font7);
        label_9 = new QLabel(centralWidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(10, 330, 121, 21));
        label_9->setFont(font4);
        label_9->setFrameShape(QFrame::Box);
        label_9->setFrameShadow(QFrame::Raised);
        label_9->setLineWidth(1);
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(510, 350, 81, 51));
        QFont font8;
        font8.setPointSize(26);
        pushButton->setFont(font8);
        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(610, 350, 81, 51));
        QFont font9;
        font9.setPointSize(27);
        pushButton_2->setFont(font9);
        label_10 = new QLabel(centralWidget);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(510, 300, 181, 41));
        label_10->setFont(font4);
        label_10->setFrameShape(QFrame::WinPanel);
        label_10->setFrameShadow(QFrame::Raised);
        label_11 = new QLabel(centralWidget);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(10, 40, 151, 41));
        label_12 = new QLabel(centralWidget);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(20, 10, 131, 21));
        label_12->setFont(font4);
        label_13 = new QLabel(centralWidget);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(180, 90, 61, 31));
        QFont font10;
        font10.setPointSize(11);
        label_13->setFont(font10);
        label_14 = new QLabel(centralWidget);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(0, 300, 161, 21));
        label_14->setFont(font4);
        pushButton_3 = new QPushButton(centralWidget);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(280, 40, 81, 31));
        pushButton_3->setFont(font7);
        pushButton_4 = new QPushButton(centralWidget);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setGeometry(QRect(280, 100, 81, 31));
        QFont font11;
        font11.setPointSize(16);
        pushButton_4->setFont(font11);
        pushButton_5 = new QPushButton(centralWidget);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        pushButton_5->setGeometry(QRect(280, 150, 81, 31));
        pushButton_5->setFont(font11);
        pushButton_6 = new QPushButton(centralWidget);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));
        pushButton_6->setGeometry(QRect(270, 240, 111, 41));
        pushButton_6->setFont(font10);
        pushButton_8 = new QPushButton(centralWidget);
        pushButton_8->setObjectName(QString::fromUtf8("pushButton_8"));
        pushButton_8->setGeometry(QRect(270, 300, 111, 41));
        pushButton_8->setFont(font10);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 739, 22));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        add->setText(QApplication::translate("MainWindow", "add", 0, QApplication::UnicodeUTF8));
        cut->setText(QApplication::translate("MainWindow", "cut", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", " r e s u l t", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "r e s u l t 1", 0, QApplication::UnicodeUTF8));
        add1->setText(QApplication::translate("MainWindow", "add1", 0, QApplication::UnicodeUTF8));
        cut2->setText(QApplication::translate("MainWindow", "cut1", 0, QApplication::UnicodeUTF8));
        X1->setText(QApplication::translate("MainWindow", "\351\241\272\346\227\266\351\222\210", 0, QApplication::UnicodeUTF8));
        x2->setText(QApplication::translate("MainWindow", "\351\200\206\346\227\266\351\222\210", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MainWindow", " X:", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("MainWindow", " Y:", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("MainWindow", " Z:", 0, QApplication::UnicodeUTF8));
        y1->setText(QApplication::translate("MainWindow", "\351\241\272\346\227\266\351\222\210", 0, QApplication::UnicodeUTF8));
        z1->setText(QApplication::translate("MainWindow", "\351\241\272\346\227\266\351\222\210", 0, QApplication::UnicodeUTF8));
        y2->setText(QApplication::translate("MainWindow", "\351\200\206\346\227\266\351\222\210", 0, QApplication::UnicodeUTF8));
        z2->setText(QApplication::translate("MainWindow", "\351\200\206\346\227\266\351\222\210", 0, QApplication::UnicodeUTF8));
        reset->setText(QApplication::translate("MainWindow", "\350\277\230   \345\216\237", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("MainWindow", "blue", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("MainWindow", "green", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("MainWindow", "red", 0, QApplication::UnicodeUTF8));
        lengthadd->setText(QApplication::translate("MainWindow", "add", 0, QApplication::UnicodeUTF8));
        lengthcut->setText(QApplication::translate("MainWindow", "cut", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("MainWindow", "  length", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("MainWindow", "add", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("MainWindow", "cut", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("MainWindow", "\346\224\271\345\217\230\345\207\275\346\225\260x y\347\232\204\345\244\247\345\260\217", 0, QApplication::UnicodeUTF8));
        label_11->setText(QString());
        label_12->setText(QApplication::translate("MainWindow", "Z\347\232\204\351\253\230\345\272\246\347\232\204\345\217\230\345\214\226", 0, QApplication::UnicodeUTF8));
        label_13->setText(QApplication::translate("MainWindow", "\345\214\205\346\213\254\346\227\213\350\275\254", 0, QApplication::UnicodeUTF8));
        label_14->setText(QApplication::translate("MainWindow", "\346\227\213\350\275\254\344\275\223\347\232\204\350\275\264\351\225\277\345\217\230\345\214\226", 0, QApplication::UnicodeUTF8));
        pushButton_3->setText(QApplication::translate("MainWindow", "result", 0, QApplication::UnicodeUTF8));
        pushButton_4->setText(QApplication::translate("MainWindow", "result1", 0, QApplication::UnicodeUTF8));
        pushButton_5->setText(QApplication::translate("MainWindow", "drawfuc", 0, QApplication::UnicodeUTF8));
        pushButton_6->setText(QApplication::translate("MainWindow", "\345\256\236\351\231\205\345\233\276\345\203\217\347\232\204\346\227\213\350\275\254", 0, QApplication::UnicodeUTF8));
        pushButton_8->setText(QApplication::translate("MainWindow", "\345\207\275\346\225\260\345\233\276\345\203\217\347\232\204\346\227\213\350\275\254", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
