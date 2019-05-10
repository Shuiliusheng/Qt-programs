/********************************************************************************
** Form generated from reading UI file 'login1.ui'
**
** Created: Thu Dec 29 16:13:44 2016
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN1_H
#define UI_LOGIN1_H

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
#include <QtGui/QTableView>
#include <QtGui/QTextEdit>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_login1
{
public:
    QWidget *centralwidget;
    QLabel *stext;
    QTableView *result;
    QLabel *f11l1;
    QComboBox *f11chose;
    QLabel *f11l2;
    QLabel *f11l3;
    QLabel *date;
    QPushButton *f11sure;
    QPushButton *f11sureall;
    QLabel *f11l4;
    QLabel *f11l5;
    QPushButton *f11bback1;
    QPushButton *f11bsure1;
    QPushButton *f11bsure;
    QPushButton *f11bback;
    QLabel *f12l1;
    QComboBox *f12method;
    QComboBox *f12grade;
    QComboBox *f12college;
    QLineEdit *f12input;
    QLabel *f12l2;
    QPushButton *f12sure;
    QLabel *f12l3;
    QLabel *f12l4;
    QPushButton *f12delete1;
    QPushButton *f12delete;
    QPushButton *f12b1;
    QPushButton *f12b2;
    QPushButton *f12b3;
    QLabel *f21l1;
    QLabel *f21l2;
    QLabel *f21l3;
    QLabel *f21l4;
    QLineEdit *f21in1;
    QTextEdit *f21in3;
    QLineEdit *f21in2;
    QComboBox *f21in4;
    QPushButton *f21b1;
    QPushButton *f22b1;
    QPushButton *f22b2;
    QPushButton *f21b2;
    QPushButton *f21b3;
    QComboBox *f22c1;
    QLineEdit *f22in1;
    QComboBox *f22c2;
    QLabel *f22l1;
    QLabel *f22l2;
    QPushButton *f22b1_2;
    QLineEdit *f3in1;
    QLabel *f3l1;
    QLabel *f3l3;
    QLineEdit *f3in3;
    QLabel *f3l2;
    QPushButton *f3b;
    QLineEdit *f3in2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *login1)
    {
        if (login1->objectName().isEmpty())
            login1->setObjectName(QString::fromUtf8("login1"));
        login1->resize(999, 554);
        centralwidget = new QWidget(login1);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        stext = new QLabel(centralwidget);
        stext->setObjectName(QString::fromUtf8("stext"));
        stext->setGeometry(QRect(120, 120, 381, 231));
        QFont font;
        font.setPointSize(17);
        font.setBold(true);
        font.setWeight(75);
        stext->setFont(font);
        stext->setStyleSheet(QString::fromUtf8("color: rgb(0, 170, 255);color: rgb(255, 155, 170);"));
        result = new QTableView(centralwidget);
        result->setObjectName(QString::fromUtf8("result"));
        result->setGeometry(QRect(20, 70, 461, 351));
        QFont font1;
        font1.setPointSize(11);
        result->setFont(font1);
        result->setStyleSheet(QString::fromUtf8("color: rgb(0, 170, 255);color: rgb(255, 155, 170);\n"
"\n"
"background-image: url(:/new/prefix1/xingkong2.JPG);"));
        f11l1 = new QLabel(centralwidget);
        f11l1->setObjectName(QString::fromUtf8("f11l1"));
        f11l1->setGeometry(QRect(130, 10, 231, 31));
        QFont font2;
        font2.setPointSize(19);
        f11l1->setFont(font2);
        f11l1->setStyleSheet(QString::fromUtf8("color: rgb(131, 255, 255);"));
        f11chose = new QComboBox(centralwidget);
        f11chose->setObjectName(QString::fromUtf8("f11chose"));
        f11chose->setGeometry(QRect(511, 40, 111, 22));
        f11chose->setFont(font1);
        f11l2 = new QLabel(centralwidget);
        f11l2->setObjectName(QString::fromUtf8("f11l2"));
        f11l2->setGeometry(QRect(370, 30, 141, 41));
        QFont font3;
        font3.setPointSize(14);
        f11l2->setFont(font3);
        f11l2->setStyleSheet(QString::fromUtf8("color: rgb(131, 255, 255);"));
        f11l3 = new QLabel(centralwidget);
        f11l3->setObjectName(QString::fromUtf8("f11l3"));
        f11l3->setGeometry(QRect(20, 40, 141, 31));
        f11l3->setFont(font3);
        f11l3->setStyleSheet(QString::fromUtf8("color: rgb(131, 255, 255);\n"
"color: rgb(0, 255, 255);"));
        date = new QLabel(centralwidget);
        date->setObjectName(QString::fromUtf8("date"));
        date->setGeometry(QRect(520, 0, 91, 31));
        QFont font4;
        font4.setPointSize(12);
        date->setFont(font4);
        date->setStyleSheet(QString::fromUtf8("color: rgb(131, 255, 255);"));
        f11sure = new QPushButton(centralwidget);
        f11sure->setObjectName(QString::fromUtf8("f11sure"));
        f11sure->setGeometry(QRect(510, 180, 101, 41));
        f11sure->setFont(font4);
        f11sureall = new QPushButton(centralwidget);
        f11sureall->setObjectName(QString::fromUtf8("f11sureall"));
        f11sureall->setGeometry(QRect(510, 240, 101, 41));
        f11sureall->setFont(font1);
        f11l4 = new QLabel(centralwidget);
        f11l4->setObjectName(QString::fromUtf8("f11l4"));
        f11l4->setGeometry(QRect(500, 90, 111, 61));
        f11l4->setFont(font3);
        f11l4->setStyleSheet(QString::fromUtf8("color: rgb(131, 255, 255);"));
        f11l5 = new QLabel(centralwidget);
        f11l5->setObjectName(QString::fromUtf8("f11l5"));
        f11l5->setGeometry(QRect(500, 300, 121, 61));
        QFont font5;
        font5.setPointSize(13);
        f11l5->setFont(font5);
        f11l5->setStyleSheet(QString::fromUtf8("color: rgb(131, 255, 255);"));
        f11bback1 = new QPushButton(centralwidget);
        f11bback1->setObjectName(QString::fromUtf8("f11bback1"));
        f11bback1->setGeometry(QRect(500, 240, 51, 41));
        f11bback1->setFont(font5);
        f11bsure1 = new QPushButton(centralwidget);
        f11bsure1->setObjectName(QString::fromUtf8("f11bsure1"));
        f11bsure1->setGeometry(QRect(570, 240, 51, 41));
        f11bsure1->setFont(font5);
        f11bsure = new QPushButton(centralwidget);
        f11bsure->setObjectName(QString::fromUtf8("f11bsure"));
        f11bsure->setGeometry(QRect(570, 180, 51, 41));
        f11bsure->setFont(font5);
        f11bback = new QPushButton(centralwidget);
        f11bback->setObjectName(QString::fromUtf8("f11bback"));
        f11bback->setGeometry(QRect(500, 180, 51, 41));
        f11bback->setFont(font5);
        f12l1 = new QLabel(centralwidget);
        f12l1->setObjectName(QString::fromUtf8("f12l1"));
        f12l1->setGeometry(QRect(120, 10, 101, 51));
        QFont font6;
        font6.setPointSize(16);
        f12l1->setFont(font6);
        f12l1->setStyleSheet(QString::fromUtf8("color: rgb(131, 255, 255);"));
        f12method = new QComboBox(centralwidget);
        f12method->setObjectName(QString::fromUtf8("f12method"));
        f12method->setGeometry(QRect(230, 21, 111, 31));
        f12method->setFont(font3);
        f12grade = new QComboBox(centralwidget);
        f12grade->setObjectName(QString::fromUtf8("f12grade"));
        f12grade->setGeometry(QRect(220, 20, 111, 31));
        f12grade->setFont(font3);
        f12college = new QComboBox(centralwidget);
        f12college->setObjectName(QString::fromUtf8("f12college"));
        f12college->setGeometry(QRect(220, 20, 111, 31));
        QFont font7;
        font7.setPointSize(10);
        f12college->setFont(font7);
        f12input = new QLineEdit(centralwidget);
        f12input->setObjectName(QString::fromUtf8("f12input"));
        f12input->setGeometry(QRect(220, 20, 111, 31));
        f12input->setFont(font4);
        f12l2 = new QLabel(centralwidget);
        f12l2->setObjectName(QString::fromUtf8("f12l2"));
        f12l2->setGeometry(QRect(130, 20, 81, 31));
        f12l2->setFont(font3);
        f12l2->setStyleSheet(QString::fromUtf8("color: rgb(131, 255, 255);"));
        f12sure = new QPushButton(centralwidget);
        f12sure->setObjectName(QString::fromUtf8("f12sure"));
        f12sure->setGeometry(QRect(340, 20, 71, 31));
        QFont font8;
        font8.setPointSize(15);
        f12sure->setFont(font8);
        f12l3 = new QLabel(centralwidget);
        f12l3->setObjectName(QString::fromUtf8("f12l3"));
        f12l3->setGeometry(QRect(500, 90, 111, 61));
        f12l3->setFont(font3);
        f12l3->setStyleSheet(QString::fromUtf8("color: rgb(131, 255, 255);"));
        f12l4 = new QLabel(centralwidget);
        f12l4->setObjectName(QString::fromUtf8("f12l4"));
        f12l4->setGeometry(QRect(500, 300, 121, 61));
        f12l4->setFont(font5);
        f12l4->setStyleSheet(QString::fromUtf8("color: rgb(131, 255, 255);"));
        f12delete1 = new QPushButton(centralwidget);
        f12delete1->setObjectName(QString::fromUtf8("f12delete1"));
        f12delete1->setGeometry(QRect(510, 240, 101, 41));
        f12delete1->setFont(font1);
        f12delete = new QPushButton(centralwidget);
        f12delete->setObjectName(QString::fromUtf8("f12delete"));
        f12delete->setGeometry(QRect(510, 180, 101, 41));
        f12delete->setFont(font4);
        f12b1 = new QPushButton(centralwidget);
        f12b1->setObjectName(QString::fromUtf8("f12b1"));
        f12b1->setGeometry(QRect(510, 260, 101, 41));
        f12b1->setFont(font6);
        f12b2 = new QPushButton(centralwidget);
        f12b2->setObjectName(QString::fromUtf8("f12b2"));
        f12b2->setGeometry(QRect(510, 200, 101, 41));
        f12b2->setFont(font6);
        f12b3 = new QPushButton(centralwidget);
        f12b3->setObjectName(QString::fromUtf8("f12b3"));
        f12b3->setGeometry(QRect(510, 150, 101, 41));
        f12b3->setFont(font6);
        f21l1 = new QLabel(centralwidget);
        f21l1->setObjectName(QString::fromUtf8("f21l1"));
        f21l1->setGeometry(QRect(160, 110, 101, 21));
        f21l1->setFont(font3);
        f21l1->setStyleSheet(QString::fromUtf8("color: rgb(131, 255, 255);"));
        f21l2 = new QLabel(centralwidget);
        f21l2->setObjectName(QString::fromUtf8("f21l2"));
        f21l2->setGeometry(QRect(160, 150, 101, 21));
        f21l2->setFont(font3);
        f21l2->setStyleSheet(QString::fromUtf8("color: rgb(131, 255, 255);"));
        f21l3 = new QLabel(centralwidget);
        f21l3->setObjectName(QString::fromUtf8("f21l3"));
        f21l3->setGeometry(QRect(160, 200, 101, 21));
        f21l3->setFont(font3);
        f21l3->setStyleSheet(QString::fromUtf8("color: rgb(131, 255, 255);"));
        f21l4 = new QLabel(centralwidget);
        f21l4->setObjectName(QString::fromUtf8("f21l4"));
        f21l4->setGeometry(QRect(160, 280, 101, 21));
        f21l4->setFont(font3);
        f21l4->setStyleSheet(QString::fromUtf8("color: rgb(131, 255, 255);"));
        f21in1 = new QLineEdit(centralwidget);
        f21in1->setObjectName(QString::fromUtf8("f21in1"));
        f21in1->setGeometry(QRect(260, 109, 151, 31));
        f21in1->setFont(font4);
        f21in3 = new QTextEdit(centralwidget);
        f21in3->setObjectName(QString::fromUtf8("f21in3"));
        f21in3->setGeometry(QRect(260, 200, 151, 61));
        f21in3->setFont(font4);
        f21in2 = new QLineEdit(centralwidget);
        f21in2->setObjectName(QString::fromUtf8("f21in2"));
        f21in2->setGeometry(QRect(260, 149, 151, 31));
        f21in2->setFont(font4);
        f21in4 = new QComboBox(centralwidget);
        f21in4->setObjectName(QString::fromUtf8("f21in4"));
        f21in4->setGeometry(QRect(280, 280, 111, 31));
        f21in4->setFont(font4);
        f21b1 = new QPushButton(centralwidget);
        f21b1->setObjectName(QString::fromUtf8("f21b1"));
        f21b1->setGeometry(QRect(280, 330, 101, 41));
        f21b1->setFont(font6);
        f22b1 = new QPushButton(centralwidget);
        f22b1->setObjectName(QString::fromUtf8("f22b1"));
        f22b1->setGeometry(QRect(510, 180, 101, 41));
        f22b1->setFont(font8);
        f22b2 = new QPushButton(centralwidget);
        f22b2->setObjectName(QString::fromUtf8("f22b2"));
        f22b2->setGeometry(QRect(510, 230, 101, 41));
        f22b2->setFont(font8);
        f21b2 = new QPushButton(centralwidget);
        f21b2->setObjectName(QString::fromUtf8("f21b2"));
        f21b2->setGeometry(QRect(400, 330, 101, 41));
        f21b2->setFont(font3);
        f21b3 = new QPushButton(centralwidget);
        f21b3->setObjectName(QString::fromUtf8("f21b3"));
        f21b3->setGeometry(QRect(160, 330, 101, 41));
        f21b3->setFont(font3);
        f22c1 = new QComboBox(centralwidget);
        f22c1->setObjectName(QString::fromUtf8("f22c1"));
        f22c1->setGeometry(QRect(210, 20, 101, 31));
        f22c1->setFont(font3);
        f22in1 = new QLineEdit(centralwidget);
        f22in1->setObjectName(QString::fromUtf8("f22in1"));
        f22in1->setGeometry(QRect(210, 20, 111, 31));
        f22in1->setFont(font4);
        f22c2 = new QComboBox(centralwidget);
        f22c2->setObjectName(QString::fromUtf8("f22c2"));
        f22c2->setGeometry(QRect(210, 20, 111, 31));
        f22c2->setFont(font4);
        f22l1 = new QLabel(centralwidget);
        f22l1->setObjectName(QString::fromUtf8("f22l1"));
        f22l1->setGeometry(QRect(110, 20, 91, 31));
        f22l1->setFont(font3);
        f22l1->setStyleSheet(QString::fromUtf8("color: rgb(131, 255, 255);"));
        f22l2 = new QLabel(centralwidget);
        f22l2->setObjectName(QString::fromUtf8("f22l2"));
        f22l2->setGeometry(QRect(110, 20, 91, 31));
        f22l2->setFont(font3);
        f22l2->setStyleSheet(QString::fromUtf8("color: rgb(131, 255, 255);"));
        f22b1_2 = new QPushButton(centralwidget);
        f22b1_2->setObjectName(QString::fromUtf8("f22b1_2"));
        f22b1_2->setGeometry(QRect(330, 20, 71, 31));
        f22b1_2->setFont(font8);
        f3in1 = new QLineEdit(centralwidget);
        f3in1->setObjectName(QString::fromUtf8("f3in1"));
        f3in1->setGeometry(QRect(270, 120, 131, 21));
        f3in1->setFont(font7);
        f3in1->setEchoMode(QLineEdit::Normal);
        f3l1 = new QLabel(centralwidget);
        f3l1->setObjectName(QString::fromUtf8("f3l1"));
        f3l1->setGeometry(QRect(190, 120, 81, 21));
        QFont font9;
        font9.setPointSize(11);
        font9.setBold(true);
        font9.setWeight(75);
        f3l1->setFont(font9);
        f3l1->setStyleSheet(QString::fromUtf8("color: rgb(131, 255, 255);"));
        f3l3 = new QLabel(centralwidget);
        f3l3->setObjectName(QString::fromUtf8("f3l3"));
        f3l3->setGeometry(QRect(190, 200, 71, 20));
        f3l3->setFont(font9);
        f3l3->setStyleSheet(QString::fromUtf8("color: rgb(131, 255, 255);"));
        f3in3 = new QLineEdit(centralwidget);
        f3in3->setObjectName(QString::fromUtf8("f3in3"));
        f3in3->setGeometry(QRect(270, 200, 131, 21));
        f3in3->setFont(font7);
        f3in3->setEchoMode(QLineEdit::Normal);
        f3in3->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        f3l2 = new QLabel(centralwidget);
        f3l2->setObjectName(QString::fromUtf8("f3l2"));
        f3l2->setGeometry(QRect(210, 160, 61, 20));
        f3l2->setFont(font9);
        f3l2->setStyleSheet(QString::fromUtf8("color: rgb(131, 255, 255);"));
        f3b = new QPushButton(centralwidget);
        f3b->setObjectName(QString::fromUtf8("f3b"));
        f3b->setGeometry(QRect(270, 240, 111, 31));
        f3b->setFont(font8);
        f3in2 = new QLineEdit(centralwidget);
        f3in2->setObjectName(QString::fromUtf8("f3in2"));
        f3in2->setGeometry(QRect(270, 160, 131, 21));
        f3in2->setFont(font7);
        f3in2->setEchoMode(QLineEdit::Normal);
        f3in2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        login1->setCentralWidget(centralwidget);
        stext->raise();
        result->raise();
        f11l1->raise();
        f11chose->raise();
        f11l2->raise();
        f11l3->raise();
        date->raise();
        f11sure->raise();
        f11sureall->raise();
        f11l4->raise();
        f11l5->raise();
        f11bback1->raise();
        f11bsure1->raise();
        f11bsure->raise();
        f11bback->raise();
        f12l1->raise();
        f12method->raise();
        f12grade->raise();
        f12college->raise();
        f12input->raise();
        f12l2->raise();
        f12sure->raise();
        f12l3->raise();
        f12l4->raise();
        f12delete->raise();
        f12delete1->raise();
        f12b1->raise();
        f12b2->raise();
        f12b3->raise();
        f21l1->raise();
        f21l2->raise();
        f21l3->raise();
        f21l4->raise();
        f21in1->raise();
        f21in3->raise();
        f21in2->raise();
        f21in4->raise();
        f21b1->raise();
        f22b1->raise();
        f22b2->raise();
        f21b2->raise();
        f21b3->raise();
        f22c1->raise();
        f22in1->raise();
        f22c2->raise();
        f22l1->raise();
        f22l2->raise();
        f22b1_2->raise();
        f3in1->raise();
        f3l1->raise();
        f3l3->raise();
        f3in3->raise();
        f3l2->raise();
        f3b->raise();
        f3in2->raise();
        menubar = new QMenuBar(login1);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 999, 22));
        login1->setMenuBar(menubar);
        statusbar = new QStatusBar(login1);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        login1->setStatusBar(statusbar);

        retranslateUi(login1);

        QMetaObject::connectSlotsByName(login1);
    } // setupUi

    void retranslateUi(QMainWindow *login1)
    {
        login1->setWindowTitle(QApplication::translate("login1", "\347\256\241\347\220\206\345\221\230\344\275\277\347\224\250\344\270\255\343\200\202\343\200\202\343\200\202", 0, QApplication::UnicodeUTF8));
        stext->setText(QString());
        f11l1->setText(QApplication::translate("login1", "\345\244\204\347\220\206\347\224\250\346\210\267\350\257\267\346\261\202\343\200\202\343\200\202\343\200\202", 0, QApplication::UnicodeUTF8));
        f11chose->clear();
        f11chose->insertItems(0, QStringList()
         << QApplication::translate("login1", "\345\200\237\344\271\246\350\257\267\346\261\202", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("login1", "\347\273\255\345\200\237\350\257\267\346\261\202", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("login1", "\345\275\222\350\277\230\350\257\267\346\261\202", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("login1", "\347\274\264\350\264\271\350\257\267\346\261\202", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("login1", "\346\263\250\345\206\214\350\257\267\346\261\202", 0, QApplication::UnicodeUTF8)
        );
        f11l2->setText(QApplication::translate("login1", "\350\257\267\346\261\202\347\261\273\345\236\213\351\200\211\346\213\251\357\274\232", 0, QApplication::UnicodeUTF8));
        f11l3->setText(QString());
        date->setText(QString());
        f11sure->setText(QApplication::translate("login1", "\347\241\256\350\256\244\346\255\244\350\257\267\346\261\202", 0, QApplication::UnicodeUTF8));
        f11sureall->setText(QApplication::translate("login1", "\347\241\256\350\256\244\345\205\250\351\203\250\350\257\267\346\261\202", 0, QApplication::UnicodeUTF8));
        f11l4->setText(QString());
        f11l5->setText(QString());
        f11bback1->setText(QApplication::translate("login1", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
        f11bsure1->setText(QApplication::translate("login1", "\347\241\256\350\256\244", 0, QApplication::UnicodeUTF8));
        f11bsure->setText(QApplication::translate("login1", "\347\241\256\350\256\244", 0, QApplication::UnicodeUTF8));
        f11bback->setText(QApplication::translate("login1", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
        f12l1->setText(QApplication::translate("login1", "\346\237\245\350\257\242\346\226\271\345\274\217\357\274\232", 0, QApplication::UnicodeUTF8));
        f12method->clear();
        f12method->insertItems(0, QStringList()
         << QApplication::translate("login1", "\345\255\246\345\217\267", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("login1", "\345\247\223\345\220\215", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("login1", "\345\255\246\351\231\242", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("login1", "\347\272\247\345\210\253", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("login1", "\345\205\245\345\255\246\345\271\264\344\273\275", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("login1", "\347\273\223\346\235\237\346\227\266\351\227\264", 0, QApplication::UnicodeUTF8)
        );
        f12grade->clear();
        f12grade->insertItems(0, QStringList()
         << QApplication::translate("login1", "\346\234\254\347\247\221\347\224\237", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("login1", "\347\240\224\347\251\266\347\224\237", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("login1", "\345\215\232\345\243\253", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("login1", "\350\200\201\345\270\210", 0, QApplication::UnicodeUTF8)
        );
        f12college->clear();
        f12college->insertItems(0, QStringList()
         << QApplication::translate("login1", "\350\256\241\347\256\227\346\234\272\345\255\246\351\231\242", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("login1", "\347\224\265\345\255\220\344\277\241\346\201\257\345\255\246\351\231\242", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("login1", "\350\207\252\345\212\250\345\214\226\345\255\246\351\231\242", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("login1", "\346\234\272\347\224\265\345\255\246\351\231\242", 0, QApplication::UnicodeUTF8)
        );
        f12input->setText(QString());
        f12l2->setText(QString());
        f12sure->setText(QApplication::translate("login1", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
        f12l3->setText(QString());
        f12l4->setText(QString());
        f12delete1->setText(QApplication::translate("login1", "\345\210\240\351\231\244\346\257\225\344\270\232\345\255\246\347\224\237", 0, QApplication::UnicodeUTF8));
        f12delete->setText(QApplication::translate("login1", "\345\210\240\351\231\244\345\255\246\347\224\237", 0, QApplication::UnicodeUTF8));
        f12b1->setText(QApplication::translate("login1", "\345\210\240\351\231\244", 0, QApplication::UnicodeUTF8));
        f12b2->setText(QApplication::translate("login1", "\347\241\256\350\256\244\344\277\256\346\224\271", 0, QApplication::UnicodeUTF8));
        f12b3->setText(QApplication::translate("login1", "\346\217\222\345\205\245", 0, QApplication::UnicodeUTF8));
        f21l1->setText(QApplication::translate("login1", "\345\233\276\344\271\246\347\274\226\345\217\267\357\274\232", 0, QApplication::UnicodeUTF8));
        f21l2->setText(QApplication::translate("login1", "\345\233\276\344\271\246\345\220\215\347\247\260\357\274\232", 0, QApplication::UnicodeUTF8));
        f21l3->setText(QApplication::translate("login1", "\345\233\276\344\271\246\347\256\200\344\273\213\357\274\232", 0, QApplication::UnicodeUTF8));
        f21l4->setText(QApplication::translate("login1", "\345\275\222\345\261\236\345\255\246\347\247\221\357\274\232", 0, QApplication::UnicodeUTF8));
        f21in2->setText(QString());
        f21in4->clear();
        f21in4->insertItems(0, QStringList()
         << QApplication::translate("login1", "\350\256\241\347\256\227\346\234\272", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("login1", "\350\210\252\347\251\272", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("login1", "\344\272\272\346\226\207", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("login1", "\350\210\252\346\265\267", 0, QApplication::UnicodeUTF8)
        );
        f21b1->setText(QApplication::translate("login1", "\347\241\256\350\256\244\346\267\273\345\212\240", 0, QApplication::UnicodeUTF8));
        f22b1->setText(QApplication::translate("login1", "\347\241\256\350\256\244\345\210\240\351\231\244", 0, QApplication::UnicodeUTF8));
        f22b2->setText(QApplication::translate("login1", "\345\205\250\351\203\250\345\210\240\351\231\244", 0, QApplication::UnicodeUTF8));
        f21b2->setText(QApplication::translate("login1", "\346\226\207\344\273\266\344\270\255\346\267\273\345\212\240", 0, QApplication::UnicodeUTF8));
        f21b3->setText(QApplication::translate("login1", "\344\271\246\347\233\256\345\257\274\345\207\272", 0, QApplication::UnicodeUTF8));
        f22c1->clear();
        f22c1->insertItems(0, QStringList()
         << QApplication::translate("login1", "\345\233\276\344\271\246\347\274\226\345\217\267", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("login1", "\345\233\276\344\271\246\345\220\215\347\247\260", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("login1", "\345\205\245\345\272\223\346\227\266\351\227\264", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("login1", "\345\275\222\345\261\236\345\255\246\347\247\221", 0, QApplication::UnicodeUTF8)
        );
        f22c2->clear();
        f22c2->insertItems(0, QStringList()
         << QApplication::translate("login1", "\350\256\241\347\256\227\346\234\272", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("login1", "\350\210\252\347\251\272", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("login1", "\344\272\272\346\226\207", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("login1", "\350\210\252\346\265\267", 0, QApplication::UnicodeUTF8)
        );
        f22l1->setText(QApplication::translate("login1", "\346\237\245\350\257\242\346\226\271\345\274\217\357\274\232", 0, QApplication::UnicodeUTF8));
        f22l2->setText(QString());
        f22b1_2->setText(QApplication::translate("login1", "\347\241\256\350\256\244", 0, QApplication::UnicodeUTF8));
        f3l1->setText(QApplication::translate("login1", "\347\256\241\347\220\206\345\221\230\345\217\267\357\274\232", 0, QApplication::UnicodeUTF8));
        f3l3->setText(QApplication::translate("login1", "\347\231\273\351\231\206\345\257\206\347\240\201\357\274\232", 0, QApplication::UnicodeUTF8));
        f3l2->setText(QApplication::translate("login1", "\345\247\223 \345\220\215\357\274\232", 0, QApplication::UnicodeUTF8));
        f3b->setText(QApplication::translate("login1", "\347\241\256\350\256\244\344\277\256\346\224\271", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class login1: public Ui_login1 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN1_H
