/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Thu Dec 29 16:17:32 2016
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
#include <QtGui/QComboBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLineEdit *usename;
    QLineEdit *password;
    QLabel *luse;
    QLabel *lpass;
    QLabel *welcome;
    QPushButton *getin;
    QPushButton *login;
    QLineEdit *usename1;
    QLabel *luse1;
    QLabel *lname1;
    QLineEdit *name;
    QLabel *lstart;
    QLineEdit *starttime;
    QLabel *lover;
    QLineEdit *overtime;
    QComboBox *college;
    QLabel *lcollege;
    QComboBox *grade;
    QLabel *lgrade;
    QPushButton *submit;
    QPushButton *search;
    QLineEdit *password1;
    QLabel *lpass1;
    QPushButton *back;
    QMenuBar *menuBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->setWindowModality(Qt::WindowModal);
        MainWindow->resize(399, 456);
        QFont font;
        font.setPointSize(10);
        font.setBold(false);
        font.setWeight(50);
        MainWindow->setFont(font);
        MainWindow->setStyleSheet(QString::fromUtf8("border-image:./123.jpg"));
        MainWindow->setUnifiedTitleAndToolBarOnMac(false);
        MainWindow->setProperty("test", QVariant(QPixmap(QString::fromUtf8("../../123.JPG"))));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        usename = new QLineEdit(centralWidget);
        usename->setObjectName(QString::fromUtf8("usename"));
        usename->setGeometry(QRect(140, 110, 131, 21));
        QFont font1;
        font1.setPointSize(10);
        usename->setFont(font1);
        usename->setEchoMode(QLineEdit::Normal);
        password = new QLineEdit(centralWidget);
        password->setObjectName(QString::fromUtf8("password"));
        password->setGeometry(QRect(140, 150, 131, 21));
        QFont font2;
        font2.setPointSize(8);
        password->setFont(font2);
        password->setEchoMode(QLineEdit::Password);
        luse = new QLabel(centralWidget);
        luse->setObjectName(QString::fromUtf8("luse"));
        luse->setGeometry(QRect(80, 110, 61, 20));
        QFont font3;
        font3.setPointSize(11);
        font3.setBold(true);
        font3.setWeight(75);
        luse->setFont(font3);
        luse->setStyleSheet(QString::fromUtf8("color: rgb(131, 255, 255);"));
        lpass = new QLabel(centralWidget);
        lpass->setObjectName(QString::fromUtf8("lpass"));
        lpass->setGeometry(QRect(80, 150, 61, 20));
        lpass->setFont(font3);
        lpass->setStyleSheet(QString::fromUtf8("color: rgb(131, 255, 255);"));
        welcome = new QLabel(centralWidget);
        welcome->setObjectName(QString::fromUtf8("welcome"));
        welcome->setGeometry(QRect(80, 50, 221, 41));
        QFont font4;
        font4.setPointSize(17);
        font4.setBold(true);
        font4.setWeight(75);
        welcome->setFont(font4);
        welcome->setStyleSheet(QString::fromUtf8("color: rgb(131, 255, 255);"));
        getin = new QPushButton(centralWidget);
        getin->setObjectName(QString::fromUtf8("getin"));
        getin->setGeometry(QRect(130, 190, 61, 31));
        QFont font5;
        font5.setPointSize(15);
        getin->setFont(font5);
        login = new QPushButton(centralWidget);
        login->setObjectName(QString::fromUtf8("login"));
        login->setGeometry(QRect(220, 190, 61, 31));
        login->setFont(font5);
        usename1 = new QLineEdit(centralWidget);
        usename1->setObjectName(QString::fromUtf8("usename1"));
        usename1->setGeometry(QRect(160, 50, 131, 21));
        usename1->setFont(font1);
        usename1->setEchoMode(QLineEdit::Normal);
        usename1->setAlignment(Qt::AlignCenter);
        luse1 = new QLabel(centralWidget);
        luse1->setObjectName(QString::fromUtf8("luse1"));
        luse1->setGeometry(QRect(100, 50, 61, 20));
        luse1->setFont(font3);
        luse1->setStyleSheet(QString::fromUtf8("color: rgb(131, 255, 255);"));
        lname1 = new QLabel(centralWidget);
        lname1->setObjectName(QString::fromUtf8("lname1"));
        lname1->setGeometry(QRect(100, 90, 61, 20));
        lname1->setFont(font3);
        lname1->setStyleSheet(QString::fromUtf8("color: rgb(131, 255, 255);"));
        name = new QLineEdit(centralWidget);
        name->setObjectName(QString::fromUtf8("name"));
        name->setGeometry(QRect(160, 90, 131, 21));
        name->setFont(font1);
        name->setEchoMode(QLineEdit::Normal);
        name->setAlignment(Qt::AlignCenter);
        lstart = new QLabel(centralWidget);
        lstart->setObjectName(QString::fromUtf8("lstart"));
        lstart->setGeometry(QRect(78, 130, 71, 20));
        lstart->setFont(font3);
        lstart->setStyleSheet(QString::fromUtf8("color: rgb(131, 255, 255);"));
        starttime = new QLineEdit(centralWidget);
        starttime->setObjectName(QString::fromUtf8("starttime"));
        starttime->setGeometry(QRect(160, 130, 131, 21));
        starttime->setFont(font1);
        starttime->setEchoMode(QLineEdit::Normal);
        starttime->setAlignment(Qt::AlignCenter);
        lover = new QLabel(centralWidget);
        lover->setObjectName(QString::fromUtf8("lover"));
        lover->setGeometry(QRect(80, 170, 71, 20));
        lover->setFont(font3);
        lover->setStyleSheet(QString::fromUtf8("color: rgb(131, 255, 255);"));
        overtime = new QLineEdit(centralWidget);
        overtime->setObjectName(QString::fromUtf8("overtime"));
        overtime->setGeometry(QRect(160, 170, 131, 21));
        overtime->setFont(font1);
        overtime->setEchoMode(QLineEdit::Normal);
        overtime->setAlignment(Qt::AlignCenter);
        college = new QComboBox(centralWidget);
        college->setObjectName(QString::fromUtf8("college"));
        college->setGeometry(QRect(160, 230, 101, 22));
        lcollege = new QLabel(centralWidget);
        lcollege->setObjectName(QString::fromUtf8("lcollege"));
        lcollege->setGeometry(QRect(100, 230, 51, 20));
        lcollege->setFont(font3);
        lcollege->setStyleSheet(QString::fromUtf8("color: rgb(131, 255, 255);"));
        grade = new QComboBox(centralWidget);
        grade->setObjectName(QString::fromUtf8("grade"));
        grade->setGeometry(QRect(160, 270, 101, 22));
        lgrade = new QLabel(centralWidget);
        lgrade->setObjectName(QString::fromUtf8("lgrade"));
        lgrade->setGeometry(QRect(100, 270, 51, 20));
        lgrade->setFont(font3);
        lgrade->setStyleSheet(QString::fromUtf8("color: rgb(131, 255, 255);"));
        submit = new QPushButton(centralWidget);
        submit->setObjectName(QString::fromUtf8("submit"));
        submit->setGeometry(QRect(160, 310, 101, 41));
        QFont font6;
        font6.setPointSize(14);
        font6.setBold(false);
        font6.setWeight(50);
        submit->setFont(font6);
        submit->setStyleSheet(QString::fromUtf8("border-color: rgb(103, 253, 255);"));
        search = new QPushButton(centralWidget);
        search->setObjectName(QString::fromUtf8("search"));
        search->setGeometry(QRect(140, 250, 131, 31));
        QFont font7;
        font7.setPointSize(16);
        search->setFont(font7);
        password1 = new QLineEdit(centralWidget);
        password1->setObjectName(QString::fromUtf8("password1"));
        password1->setGeometry(QRect(160, 200, 131, 21));
        password1->setFont(font2);
        password1->setEchoMode(QLineEdit::Normal);
        password1->setAlignment(Qt::AlignCenter);
        lpass1 = new QLabel(centralWidget);
        lpass1->setObjectName(QString::fromUtf8("lpass1"));
        lpass1->setGeometry(QRect(80, 200, 71, 20));
        lpass1->setFont(font3);
        lpass1->setStyleSheet(QString::fromUtf8("color: rgb(131, 255, 255);"));
        back = new QPushButton(centralWidget);
        back->setObjectName(QString::fromUtf8("back"));
        back->setGeometry(QRect(60, 310, 71, 41));
        QFont font8;
        font8.setPointSize(29);
        font8.setBold(false);
        font8.setWeight(50);
        back->setFont(font8);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 399, 22));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "\345\233\276\344\271\246\346\237\245\350\257\242", 0, QApplication::UnicodeUTF8));
        luse->setText(QApplication::translate("MainWindow", "\345\255\246 \345\217\267\357\274\232", 0, QApplication::UnicodeUTF8));
        lpass->setText(QApplication::translate("MainWindow", "\345\257\206 \347\240\201\357\274\232", 0, QApplication::UnicodeUTF8));
        welcome->setText(QApplication::translate("MainWindow", "Welcome to Use\357\274\201", 0, QApplication::UnicodeUTF8));
        getin->setText(QApplication::translate("MainWindow", "\347\231\273 \351\231\206", 0, QApplication::UnicodeUTF8));
        login->setText(QApplication::translate("MainWindow", "\346\263\250\345\206\214", 0, QApplication::UnicodeUTF8));
        usename1->setText(QApplication::translate("MainWindow", "2013302544", 0, QApplication::UnicodeUTF8));
        luse1->setText(QApplication::translate("MainWindow", "\345\255\246 \345\217\267\357\274\232", 0, QApplication::UnicodeUTF8));
        lname1->setText(QApplication::translate("MainWindow", "\345\247\223 \345\220\215\357\274\232", 0, QApplication::UnicodeUTF8));
        lstart->setText(QApplication::translate("MainWindow", "\345\205\245\345\255\246\346\227\266\351\227\264\357\274\232", 0, QApplication::UnicodeUTF8));
        starttime->setText(QApplication::translate("MainWindow", "201309", 0, QApplication::UnicodeUTF8));
        lover->setText(QApplication::translate("MainWindow", "\347\273\223\346\235\237\346\227\266\351\227\264\357\274\232", 0, QApplication::UnicodeUTF8));
        overtime->setText(QApplication::translate("MainWindow", "201707", 0, QApplication::UnicodeUTF8));
        college->clear();
        college->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "\350\256\241\347\256\227\346\234\272\345\255\246\351\231\242", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "\347\224\265\345\255\220\344\277\241\346\201\257\345\255\246\351\231\242", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "\350\207\252\345\212\250\345\214\226\345\255\246\351\231\242", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "\346\234\272\347\224\265\345\255\246\351\231\242", 0, QApplication::UnicodeUTF8)
        );
        lcollege->setText(QApplication::translate("MainWindow", "\345\255\246 \351\231\242\357\274\232", 0, QApplication::UnicodeUTF8));
        grade->clear();
        grade->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "\346\234\254\347\247\221\347\224\237", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "\347\240\224\347\251\266\347\224\237", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "\345\215\232\345\243\253", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "\350\200\201\345\270\210", 0, QApplication::UnicodeUTF8)
        );
        lgrade->setText(QApplication::translate("MainWindow", "\345\271\264 \347\272\247\357\274\232", 0, QApplication::UnicodeUTF8));
        submit->setText(QApplication::translate("MainWindow", "\347\241\256\350\256\244\346\217\220\344\272\244", 0, QApplication::UnicodeUTF8));
        search->setText(QApplication::translate("MainWindow", "\346\237\245\350\257\242\344\271\246\347\261\215", 0, QApplication::UnicodeUTF8));
        password1->setText(QString());
        lpass1->setText(QApplication::translate("MainWindow", "\347\231\273\351\231\206\345\257\206\347\240\201\357\274\232", 0, QApplication::UnicodeUTF8));
        back->setText(QApplication::translate("MainWindow", "\342\230\234", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
