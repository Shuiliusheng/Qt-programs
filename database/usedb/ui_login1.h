/********************************************************************************
** Form generated from reading UI file 'login1.ui'
**
** Created: Thu Dec 29 16:17:33 2016
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
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_login1
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QPushButton *f1sure;
    QLabel *f1l1;
    QLineEdit *f1name;
    QLabel *f1l2;
    QPushButton *f1search;
    QPushButton *f1delete;
    QPushButton *f1sure1;
    QLabel *fmoney;
    QLabel *f2l1;
    QTableView *f2info;
    QPushButton *f2xujie;
    QPushButton *f2back;
    QPushButton *f2pay;
    QLabel *stext;
    QLabel *date;
    QLabel *f3l2;
    QLabel *f3l4;
    QLineEdit *f3starttime;
    QLineEdit *f3password;
    QLabel *f3l6;
    QLineEdit *f3name;
    QLabel *f3l3;
    QComboBox *f3college;
    QLabel *f3l5;
    QLineEdit *f3overtime;
    QLabel *f3l7;
    QLineEdit *f3use;
    QLabel *f3l1;
    QPushButton *f3sure;
    QPushButton *f3delete;
    QPushButton *f3change;
    QLineEdit *f3co;
    QLineEdit *f3gra;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *login1)
    {
        if (login1->objectName().isEmpty())
            login1->setObjectName(QString::fromUtf8("login1"));
        login1->resize(695, 510);
        QFont font;
        font.setPointSize(10);
        login1->setFont(font);
        centralwidget = new QWidget(login1);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(21, 0, 31, 31));
        QFont font1;
        font1.setPointSize(20);
        label->setFont(font1);
        label->setStyleSheet(QString::fromUtf8("color: rgb(131, 255, 255);"));
        f1sure = new QPushButton(centralwidget);
        f1sure->setObjectName(QString::fromUtf8("f1sure"));
        f1sure->setGeometry(QRect(180, 190, 81, 41));
        QFont font2;
        font2.setPointSize(13);
        f1sure->setFont(font2);
        f1l1 = new QLabel(centralwidget);
        f1l1->setObjectName(QString::fromUtf8("f1l1"));
        f1l1->setGeometry(QRect(70, 50, 201, 51));
        QFont font3;
        font3.setPointSize(21);
        f1l1->setFont(font3);
        f1l1->setStyleSheet(QString::fromUtf8("color: rgb(131, 255, 255);"));
        f1name = new QLineEdit(centralwidget);
        f1name->setObjectName(QString::fromUtf8("f1name"));
        f1name->setGeometry(QRect(150, 130, 131, 31));
        QFont font4;
        font4.setPointSize(12);
        f1name->setFont(font4);
        f1l2 = new QLabel(centralwidget);
        f1l2->setObjectName(QString::fromUtf8("f1l2"));
        f1l2->setGeometry(QRect(40, 120, 91, 51));
        QFont font5;
        font5.setPointSize(16);
        f1l2->setFont(font5);
        f1l2->setStyleSheet(QString::fromUtf8("color: rgb(131, 255, 255);"));
        f1search = new QPushButton(centralwidget);
        f1search->setObjectName(QString::fromUtf8("f1search"));
        f1search->setGeometry(QRect(60, 190, 81, 41));
        f1search->setFont(font2);
        f1delete = new QPushButton(centralwidget);
        f1delete->setObjectName(QString::fromUtf8("f1delete"));
        f1delete->setGeometry(QRect(170, 190, 51, 41));
        f1delete->setFont(font2);
        f1sure1 = new QPushButton(centralwidget);
        f1sure1->setObjectName(QString::fromUtf8("f1sure1"));
        f1sure1->setGeometry(QRect(230, 190, 51, 41));
        f1sure1->setFont(font2);
        fmoney = new QLabel(centralwidget);
        fmoney->setObjectName(QString::fromUtf8("fmoney"));
        fmoney->setGeometry(QRect(460, 20, 141, 51));
        QFont font6;
        font6.setPointSize(15);
        fmoney->setFont(font6);
        fmoney->setStyleSheet(QString::fromUtf8("color: rgb(131, 255, 255);"));
        f2l1 = new QLabel(centralwidget);
        f2l1->setObjectName(QString::fromUtf8("f2l1"));
        f2l1->setGeometry(QRect(10, 30, 201, 51));
        f2l1->setFont(font3);
        f2l1->setStyleSheet(QString::fromUtf8("color: rgb(131, 255, 255);"));
        f2info = new QTableView(centralwidget);
        f2info->setObjectName(QString::fromUtf8("f2info"));
        f2info->setGeometry(QRect(10, 80, 451, 341));
        QFont font7;
        font7.setPointSize(10);
        font7.setBold(true);
        font7.setWeight(75);
        f2info->setFont(font7);
        f2info->setStyleSheet(QString::fromUtf8("color: rgb(0, 170, 255);color: rgb(255, 155, 170);\n"
"\n"
"background-image: url(:/new/prefix2/xingkong2.JPG);"));
        f2xujie = new QPushButton(centralwidget);
        f2xujie->setObjectName(QString::fromUtf8("f2xujie"));
        f2xujie->setGeometry(QRect(500, 110, 91, 41));
        f2xujie->setFont(font2);
        f2back = new QPushButton(centralwidget);
        f2back->setObjectName(QString::fromUtf8("f2back"));
        f2back->setGeometry(QRect(500, 160, 91, 41));
        f2back->setFont(font2);
        f2pay = new QPushButton(centralwidget);
        f2pay->setObjectName(QString::fromUtf8("f2pay"));
        f2pay->setGeometry(QRect(500, 210, 91, 41));
        f2pay->setFont(font2);
        stext = new QLabel(centralwidget);
        stext->setObjectName(QString::fromUtf8("stext"));
        stext->setGeometry(QRect(120, 120, 381, 231));
        QFont font8;
        font8.setPointSize(17);
        font8.setBold(true);
        font8.setWeight(75);
        stext->setFont(font8);
        stext->setStyleSheet(QString::fromUtf8("color: rgb(0, 170, 255);color: rgb(255, 155, 170);"));
        date = new QLabel(centralwidget);
        date->setObjectName(QString::fromUtf8("date"));
        date->setGeometry(QRect(500, 0, 151, 31));
        QFont font9;
        font9.setPointSize(12);
        font9.setUnderline(true);
        date->setFont(font9);
        date->setStyleSheet(QString::fromUtf8("color: rgb(131, 255, 255);"));
        f3l2 = new QLabel(centralwidget);
        f3l2->setObjectName(QString::fromUtf8("f3l2"));
        f3l2->setGeometry(QRect(130, 90, 61, 20));
        QFont font10;
        font10.setPointSize(11);
        font10.setBold(true);
        font10.setWeight(75);
        f3l2->setFont(font10);
        f3l2->setStyleSheet(QString::fromUtf8("color: rgb(131, 255, 255);"));
        f3l4 = new QLabel(centralwidget);
        f3l4->setObjectName(QString::fromUtf8("f3l4"));
        f3l4->setGeometry(QRect(110, 170, 71, 20));
        f3l4->setFont(font10);
        f3l4->setStyleSheet(QString::fromUtf8("color: rgb(131, 255, 255);"));
        f3starttime = new QLineEdit(centralwidget);
        f3starttime->setObjectName(QString::fromUtf8("f3starttime"));
        f3starttime->setGeometry(QRect(190, 130, 131, 21));
        f3starttime->setFont(font4);
        f3starttime->setEchoMode(QLineEdit::Normal);
        f3starttime->setAlignment(Qt::AlignCenter);
        f3password = new QLineEdit(centralwidget);
        f3password->setObjectName(QString::fromUtf8("f3password"));
        f3password->setGeometry(QRect(190, 210, 131, 21));
        f3password->setFont(font4);
        f3password->setEchoMode(QLineEdit::Normal);
        f3password->setAlignment(Qt::AlignCenter);
        f3l6 = new QLabel(centralwidget);
        f3l6->setObjectName(QString::fromUtf8("f3l6"));
        f3l6->setGeometry(QRect(130, 250, 51, 20));
        f3l6->setFont(font10);
        f3l6->setStyleSheet(QString::fromUtf8("color: rgb(131, 255, 255);"));
        f3name = new QLineEdit(centralwidget);
        f3name->setObjectName(QString::fromUtf8("f3name"));
        f3name->setGeometry(QRect(190, 90, 131, 21));
        f3name->setFont(font4);
        f3name->setEchoMode(QLineEdit::Normal);
        f3name->setAlignment(Qt::AlignCenter);
        f3l3 = new QLabel(centralwidget);
        f3l3->setObjectName(QString::fromUtf8("f3l3"));
        f3l3->setGeometry(QRect(110, 130, 71, 20));
        f3l3->setFont(font10);
        f3l3->setStyleSheet(QString::fromUtf8("color: rgb(131, 255, 255);"));
        f3college = new QComboBox(centralwidget);
        f3college->setObjectName(QString::fromUtf8("f3college"));
        f3college->setGeometry(QRect(190, 250, 101, 22));
        f3l5 = new QLabel(centralwidget);
        f3l5->setObjectName(QString::fromUtf8("f3l5"));
        f3l5->setGeometry(QRect(110, 210, 71, 20));
        f3l5->setFont(font10);
        f3l5->setStyleSheet(QString::fromUtf8("color: rgb(131, 255, 255);"));
        f3overtime = new QLineEdit(centralwidget);
        f3overtime->setObjectName(QString::fromUtf8("f3overtime"));
        f3overtime->setGeometry(QRect(190, 170, 131, 21));
        f3overtime->setFont(font4);
        f3overtime->setEchoMode(QLineEdit::Normal);
        f3overtime->setAlignment(Qt::AlignCenter);
        f3l7 = new QLabel(centralwidget);
        f3l7->setObjectName(QString::fromUtf8("f3l7"));
        f3l7->setGeometry(QRect(130, 290, 51, 20));
        f3l7->setFont(font10);
        f3l7->setStyleSheet(QString::fromUtf8("color: rgb(131, 255, 255);"));
        f3use = new QLineEdit(centralwidget);
        f3use->setObjectName(QString::fromUtf8("f3use"));
        f3use->setGeometry(QRect(190, 60, 131, 21));
        f3use->setFont(font4);
        f3use->setEchoMode(QLineEdit::Normal);
        f3use->setAlignment(Qt::AlignCenter);
        f3l1 = new QLabel(centralwidget);
        f3l1->setObjectName(QString::fromUtf8("f3l1"));
        f3l1->setGeometry(QRect(130, 60, 61, 20));
        f3l1->setFont(font10);
        f3l1->setStyleSheet(QString::fromUtf8("color: rgb(131, 255, 255);"));
        f3sure = new QPushButton(centralwidget);
        f3sure->setObjectName(QString::fromUtf8("f3sure"));
        f3sure->setGeometry(QRect(210, 330, 61, 41));
        QFont font11;
        font11.setPointSize(14);
        f3sure->setFont(font11);
        f3delete = new QPushButton(centralwidget);
        f3delete->setObjectName(QString::fromUtf8("f3delete"));
        f3delete->setGeometry(QRect(280, 330, 61, 41));
        f3delete->setFont(font11);
        f3change = new QPushButton(centralwidget);
        f3change->setObjectName(QString::fromUtf8("f3change"));
        f3change->setGeometry(QRect(140, 330, 61, 41));
        f3change->setFont(font11);
        f3co = new QLineEdit(centralwidget);
        f3co->setObjectName(QString::fromUtf8("f3co"));
        f3co->setGeometry(QRect(190, 250, 131, 21));
        f3co->setFont(font4);
        f3co->setEchoMode(QLineEdit::Normal);
        f3co->setAlignment(Qt::AlignCenter);
        f3gra = new QLineEdit(centralwidget);
        f3gra->setObjectName(QString::fromUtf8("f3gra"));
        f3gra->setGeometry(QRect(190, 290, 131, 21));
        f3gra->setFont(font4);
        f3gra->setEchoMode(QLineEdit::Normal);
        f3gra->setAlignment(Qt::AlignCenter);
        login1->setCentralWidget(centralwidget);
        menubar = new QMenuBar(login1);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 695, 22));
        login1->setMenuBar(menubar);
        statusbar = new QStatusBar(login1);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        login1->setStatusBar(statusbar);

        retranslateUi(login1);

        QMetaObject::connectSlotsByName(login1);
    } // setupUi

    void retranslateUi(QMainWindow *login1)
    {
        login1->setWindowTitle(QApplication::translate("login1", "\344\275\277\347\224\250\344\270\255\343\200\202\343\200\202\343\200\202", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("login1", "\342\230\235", 0, QApplication::UnicodeUTF8));
        f1sure->setText(QApplication::translate("login1", "\345\200\237\351\230\205", 0, QApplication::UnicodeUTF8));
        f1l1->setText(QApplication::translate("login1", "\345\200\237\351\230\205\344\270\255\343\200\202\343\200\202\343\200\202", 0, QApplication::UnicodeUTF8));
        f1name->setText(QApplication::translate("login1", "00000000", 0, QApplication::UnicodeUTF8));
        f1l2->setText(QApplication::translate("login1", "\345\233\276\344\271\246\347\274\226\345\217\267\357\274\232", 0, QApplication::UnicodeUTF8));
        f1search->setText(QApplication::translate("login1", "\346\237\245\350\257\242\344\271\246\347\261\215", 0, QApplication::UnicodeUTF8));
        f1delete->setText(QApplication::translate("login1", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
        f1sure1->setText(QApplication::translate("login1", "\347\241\256\350\256\244", 0, QApplication::UnicodeUTF8));
        fmoney->setText(QString());
        f2l1->setText(QApplication::translate("login1", "\345\267\262\345\200\237\344\271\246\347\261\215\343\200\202\343\200\202\343\200\202", 0, QApplication::UnicodeUTF8));
        f2xujie->setText(QApplication::translate("login1", "\347\224\263\350\257\267\347\273\255\345\200\237", 0, QApplication::UnicodeUTF8));
        f2back->setText(QApplication::translate("login1", "\347\224\263\350\257\267\345\275\222\350\277\230", 0, QApplication::UnicodeUTF8));
        f2pay->setText(QApplication::translate("login1", "\347\274\264 \350\264\271", 0, QApplication::UnicodeUTF8));
        stext->setText(QString());
        date->setText(QString());
        f3l2->setText(QApplication::translate("login1", "\345\247\223 \345\220\215\357\274\232", 0, QApplication::UnicodeUTF8));
        f3l4->setText(QApplication::translate("login1", "\347\273\223\346\235\237\346\227\266\351\227\264\357\274\232", 0, QApplication::UnicodeUTF8));
        f3starttime->setText(QString());
        f3password->setText(QString());
        f3l6->setText(QApplication::translate("login1", "\345\255\246 \351\231\242\357\274\232", 0, QApplication::UnicodeUTF8));
        f3l3->setText(QApplication::translate("login1", "\345\205\245\345\255\246\346\227\266\351\227\264\357\274\232", 0, QApplication::UnicodeUTF8));
        f3college->clear();
        f3college->insertItems(0, QStringList()
         << QApplication::translate("login1", "\350\256\241\347\256\227\346\234\272\345\255\246\351\231\242", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("login1", "\347\224\265\345\255\220\344\277\241\346\201\257\345\255\246\351\231\242", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("login1", "\350\207\252\345\212\250\345\214\226\345\255\246\351\231\242", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("login1", "\346\234\272\347\224\265\345\255\246\351\231\242", 0, QApplication::UnicodeUTF8)
        );
        f3l5->setText(QApplication::translate("login1", "\347\231\273\351\231\206\345\257\206\347\240\201\357\274\232", 0, QApplication::UnicodeUTF8));
        f3overtime->setText(QString());
        f3l7->setText(QApplication::translate("login1", "\345\271\264 \347\272\247\357\274\232", 0, QApplication::UnicodeUTF8));
        f3use->setText(QString());
        f3l1->setText(QApplication::translate("login1", "\345\255\246 \345\217\267\357\274\232", 0, QApplication::UnicodeUTF8));
        f3sure->setText(QApplication::translate("login1", "\347\241\256\350\256\244", 0, QApplication::UnicodeUTF8));
        f3delete->setText(QApplication::translate("login1", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
        f3change->setText(QApplication::translate("login1", "\344\277\256\346\224\271", 0, QApplication::UnicodeUTF8));
        f3co->setText(QString());
        f3gra->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class login1: public Ui_login1 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN1_H
