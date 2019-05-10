/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Thu Dec 29 16:13:43 2016
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
    QLineEdit *usename;
    QLineEdit *name;
    QLabel *welcome;
    QLineEdit *password1;
    QLabel *luse1;
    QLabel *lpass1;
    QLabel *lname1;
    QLabel *luse;
    QPushButton *submit;
    QLineEdit *usename1;
    QLabel *lpass;
    QLineEdit *password;
    QPushButton *login;
    QPushButton *reg;
    QPushButton *search;
    QPushButton *back;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(584, 479);
        QFont font;
        font.setPointSize(9);
        MainWindow->setFont(font);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        usename = new QLineEdit(centralWidget);
        usename->setObjectName(QString::fromUtf8("usename"));
        usename->setGeometry(QRect(140, 130, 131, 21));
        QFont font1;
        font1.setPointSize(10);
        usename->setFont(font1);
        usename->setEchoMode(QLineEdit::Normal);
        name = new QLineEdit(centralWidget);
        name->setObjectName(QString::fromUtf8("name"));
        name->setGeometry(QRect(140, 170, 131, 21));
        name->setFont(font1);
        name->setEchoMode(QLineEdit::Normal);
        name->setAlignment(Qt::AlignCenter);
        welcome = new QLabel(centralWidget);
        welcome->setObjectName(QString::fromUtf8("welcome"));
        welcome->setGeometry(QRect(80, 50, 221, 41));
        QFont font2;
        font2.setPointSize(17);
        font2.setBold(true);
        font2.setWeight(75);
        welcome->setFont(font2);
        welcome->setStyleSheet(QString::fromUtf8("color: rgb(131, 255, 255);"));
        password1 = new QLineEdit(centralWidget);
        password1->setObjectName(QString::fromUtf8("password1"));
        password1->setGeometry(QRect(140, 210, 131, 21));
        password1->setFont(font1);
        password1->setEchoMode(QLineEdit::Normal);
        password1->setAlignment(Qt::AlignCenter);
        luse1 = new QLabel(centralWidget);
        luse1->setObjectName(QString::fromUtf8("luse1"));
        luse1->setGeometry(QRect(60, 130, 81, 21));
        QFont font3;
        font3.setPointSize(11);
        font3.setBold(true);
        font3.setWeight(75);
        luse1->setFont(font3);
        luse1->setStyleSheet(QString::fromUtf8("color: rgb(131, 255, 255);"));
        lpass1 = new QLabel(centralWidget);
        lpass1->setObjectName(QString::fromUtf8("lpass1"));
        lpass1->setGeometry(QRect(60, 210, 71, 20));
        lpass1->setFont(font3);
        lpass1->setStyleSheet(QString::fromUtf8("color: rgb(131, 255, 255);"));
        lname1 = new QLabel(centralWidget);
        lname1->setObjectName(QString::fromUtf8("lname1"));
        lname1->setGeometry(QRect(80, 170, 61, 20));
        lname1->setFont(font3);
        lname1->setStyleSheet(QString::fromUtf8("color: rgb(131, 255, 255);"));
        luse = new QLabel(centralWidget);
        luse->setObjectName(QString::fromUtf8("luse"));
        luse->setGeometry(QRect(60, 130, 81, 20));
        luse->setFont(font3);
        luse->setStyleSheet(QString::fromUtf8("color: rgb(131, 255, 255);"));
        submit = new QPushButton(centralWidget);
        submit->setObjectName(QString::fromUtf8("submit"));
        submit->setGeometry(QRect(170, 260, 101, 41));
        QFont font4;
        font4.setPointSize(14);
        font4.setBold(false);
        font4.setWeight(50);
        submit->setFont(font4);
        submit->setStyleSheet(QString::fromUtf8("border-color: rgb(103, 253, 255);"));
        usename1 = new QLineEdit(centralWidget);
        usename1->setObjectName(QString::fromUtf8("usename1"));
        usename1->setGeometry(QRect(140, 130, 131, 21));
        usename1->setFont(font1);
        usename1->setEchoMode(QLineEdit::Normal);
        usename1->setAlignment(Qt::AlignCenter);
        lpass = new QLabel(centralWidget);
        lpass->setObjectName(QString::fromUtf8("lpass"));
        lpass->setGeometry(QRect(82, 170, 61, 20));
        lpass->setFont(font3);
        lpass->setStyleSheet(QString::fromUtf8("color: rgb(131, 255, 255);"));
        password = new QLineEdit(centralWidget);
        password->setObjectName(QString::fromUtf8("password"));
        password->setGeometry(QRect(140, 170, 131, 21));
        QFont font5;
        font5.setPointSize(8);
        password->setFont(font5);
        password->setEchoMode(QLineEdit::Password);
        login = new QPushButton(centralWidget);
        login->setObjectName(QString::fromUtf8("login"));
        login->setGeometry(QRect(140, 210, 61, 31));
        QFont font6;
        font6.setPointSize(15);
        login->setFont(font6);
        reg = new QPushButton(centralWidget);
        reg->setObjectName(QString::fromUtf8("reg"));
        reg->setGeometry(QRect(210, 210, 61, 31));
        reg->setFont(font6);
        search = new QPushButton(centralWidget);
        search->setObjectName(QString::fromUtf8("search"));
        search->setGeometry(QRect(140, 270, 131, 31));
        QFont font7;
        font7.setPointSize(16);
        search->setFont(font7);
        back = new QPushButton(centralWidget);
        back->setObjectName(QString::fromUtf8("back"));
        back->setGeometry(QRect(70, 260, 71, 41));
        QFont font8;
        font8.setPointSize(32);
        back->setFont(font8);
        MainWindow->setCentralWidget(centralWidget);
        password->raise();
        usename->raise();
        name->raise();
        welcome->raise();
        password1->raise();
        luse1->raise();
        lpass1->raise();
        lname1->raise();
        luse->raise();
        submit->raise();
        usename1->raise();
        lpass->raise();
        login->raise();
        reg->raise();
        search->raise();
        back->raise();
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 584, 22));
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
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "\347\256\241\347\220\206\345\221\230\347\231\273\351\231\206\347\225\214\351\235\242", 0, QApplication::UnicodeUTF8));
        name->setText(QString());
        welcome->setText(QApplication::translate("MainWindow", "Welcome to Use\357\274\201", 0, QApplication::UnicodeUTF8));
        luse1->setText(QApplication::translate("MainWindow", "\347\256\241\347\220\206\345\221\230\345\217\267\357\274\232", 0, QApplication::UnicodeUTF8));
        lpass1->setText(QApplication::translate("MainWindow", "\347\231\273\351\231\206\345\257\206\347\240\201\357\274\232", 0, QApplication::UnicodeUTF8));
        lname1->setText(QApplication::translate("MainWindow", "\345\247\223 \345\220\215\357\274\232", 0, QApplication::UnicodeUTF8));
        luse->setText(QApplication::translate("MainWindow", "\347\256\241\347\220\206\345\221\230\345\217\267\357\274\232", 0, QApplication::UnicodeUTF8));
        submit->setText(QApplication::translate("MainWindow", "\347\241\256\350\256\244\346\217\220\344\272\244", 0, QApplication::UnicodeUTF8));
        usename1->setText(QApplication::translate("MainWindow", "2013302544", 0, QApplication::UnicodeUTF8));
        lpass->setText(QApplication::translate("MainWindow", "\345\257\206 \347\240\201\357\274\232", 0, QApplication::UnicodeUTF8));
        login->setText(QApplication::translate("MainWindow", "\347\231\273\351\231\206", 0, QApplication::UnicodeUTF8));
        reg->setText(QApplication::translate("MainWindow", "\346\263\250\345\206\214", 0, QApplication::UnicodeUTF8));
        search->setText(QApplication::translate("MainWindow", "\346\237\245\350\257\242\344\271\246\347\261\215", 0, QApplication::UnicodeUTF8));
        back->setText(QApplication::translate("MainWindow", "\342\230\234", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
