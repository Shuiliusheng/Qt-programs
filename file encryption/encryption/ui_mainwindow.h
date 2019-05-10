/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Sat Apr 4 22:13:29 2015
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
    QPushButton *btn1;
    QPushButton *btn2;
    QLineEdit *line1;
    QLineEdit *line2;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *line3;
    QLabel *label_3;
    QLabel *label_4;
    QPushButton *lock;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(410, 455);
        MainWindow->setMinimumSize(QSize(410, 455));
        MainWindow->setMaximumSize(QSize(410, 455));
        QFont font;
        font.setPointSize(12);
        MainWindow->setFont(font);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        btn1 = new QPushButton(centralWidget);
        btn1->setObjectName(QString::fromUtf8("btn1"));
        btn1->setGeometry(QRect(30, 140, 81, 51));
        QFont font1;
        font1.setPointSize(24);
        btn1->setFont(font1);
        btn1->setLayoutDirection(Qt::LeftToRight);
        btn2 = new QPushButton(centralWidget);
        btn2->setObjectName(QString::fromUtf8("btn2"));
        btn2->setGeometry(QRect(30, 320, 81, 50));
        btn2->setBaseSize(QSize(0, 4));
        QFont font2;
        font2.setPointSize(20);
        btn2->setFont(font2);
        line1 = new QLineEdit(centralWidget);
        line1->setObjectName(QString::fromUtf8("line1"));
        line1->setGeometry(QRect(90, 30, 181, 31));
        line2 = new QLineEdit(centralWidget);
        line2->setObjectName(QString::fromUtf8("line2"));
        line2->setGeometry(QRect(90, 90, 181, 31));
        line2->setFont(font);
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 30, 61, 31));
        QFont font3;
        font3.setPointSize(13);
        label->setFont(font3);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(30, 90, 54, 21));
        label_2->setFont(font3);
        line3 = new QLineEdit(centralWidget);
        line3->setObjectName(QString::fromUtf8("line3"));
        line3->setGeometry(QRect(60, 250, 291, 31));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 250, 54, 21));
        label_3->setFont(font3);
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(70, 290, 261, 21));
        label_4->setFont(font3);
        lock = new QPushButton(centralWidget);
        lock->setObjectName(QString::fromUtf8("lock"));
        lock->setGeometry(QRect(220, 320, 81, 51));
        QFont font4;
        font4.setPointSize(22);
        lock->setFont(font4);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 410, 27));
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
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "lock", 0, QApplication::UnicodeUTF8));
        btn1->setText(QApplication::translate("MainWindow", "sure", 0, QApplication::UnicodeUTF8));
        btn2->setText(QApplication::translate("MainWindow", "input", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "\347\224\250\346\210\267 :", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "\345\257\206\347\240\201 \357\274\232", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MainWindow", "\346\226\207\344\273\266 :", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("MainWindow", "(\350\257\267\350\276\223\345\205\245\345\256\214\346\225\264\350\267\257\345\276\204\346\210\226\350\200\205\347\233\270\345\257\271\350\267\257\345\276\204\357\274\211", 0, QApplication::UnicodeUTF8));
        lock->setText(QApplication::translate("MainWindow", "exit", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
