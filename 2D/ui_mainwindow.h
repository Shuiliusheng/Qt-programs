/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Sat Apr 18 18:55:54 2015
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
#include <QtGui/QLineEdit>
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
    QLineEdit *xmax;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLineEdit *xmin;
    QLineEdit *ymin;
    QLineEdit *ymax;
    QPushButton *pushButton;
    QLineEdit *filename;
    QLabel *label_5;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QLineEdit *xname;
    QLineEdit *yname;
    QLabel *label_6;
    QLabel *label_7;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(405, 344);
        QFont font;
        font.setPointSize(14);
        MainWindow->setFont(font);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        xmax = new QLineEdit(centralWidget);
        xmax->setObjectName(QString::fromUtf8("xmax"));
        xmax->setGeometry(QRect(70, 20, 61, 31));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 30, 54, 12));
        QFont font1;
        font1.setPointSize(12);
        label->setFont(font1);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(170, 30, 54, 12));
        QFont font2;
        font2.setPointSize(11);
        label_2->setFont(font2);
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(170, 70, 54, 12));
        label_3->setFont(font1);
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(10, 70, 54, 12));
        label_4->setFont(font1);
        xmin = new QLineEdit(centralWidget);
        xmin->setObjectName(QString::fromUtf8("xmin"));
        xmin->setGeometry(QRect(70, 60, 61, 31));
        ymin = new QLineEdit(centralWidget);
        ymin->setObjectName(QString::fromUtf8("ymin"));
        ymin->setGeometry(QRect(230, 60, 61, 31));
        ymax = new QLineEdit(centralWidget);
        ymax->setObjectName(QString::fromUtf8("ymax"));
        ymax->setGeometry(QRect(230, 20, 61, 31));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(10, 210, 91, 51));
        pushButton->setFont(font);
        filename = new QLineEdit(centralWidget);
        filename->setObjectName(QString::fromUtf8("filename"));
        filename->setGeometry(QRect(90, 150, 211, 31));
        filename->setFont(font);
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(10, 160, 81, 20));
        label_5->setFont(font1);
        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(240, 210, 101, 51));
        pushButton_3 = new QPushButton(centralWidget);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(120, 210, 101, 51));
        xname = new QLineEdit(centralWidget);
        xname->setObjectName(QString::fromUtf8("xname"));
        xname->setGeometry(QRect(70, 100, 61, 31));
        yname = new QLineEdit(centralWidget);
        yname->setObjectName(QString::fromUtf8("yname"));
        yname->setGeometry(QRect(230, 100, 61, 31));
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(10, 100, 51, 20));
        label_6->setFont(font1);
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(170, 100, 54, 20));
        label_7->setFont(font1);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 405, 23));
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
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "fuction picture", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "X MAX:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "Y MAX:", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MainWindow", "Y MIN:", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("MainWindow", "X MIN:", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("MainWindow", "use line", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("MainWindow", "FILE NAME:", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("MainWindow", "x,y\347\255\211\346\257\224\344\276\213", 0, QApplication::UnicodeUTF8));
        pushButton_3->setText(QApplication::translate("MainWindow", "use point", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("MainWindow", "xName:", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("MainWindow", "yName:", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
