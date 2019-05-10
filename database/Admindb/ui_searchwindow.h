/********************************************************************************
** Form generated from reading UI file 'searchwindow.ui'
**
** Created: Thu Dec 29 16:13:44 2016
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SEARCHWINDOW_H
#define UI_SEARCHWINDOW_H

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
#include <QtGui/QPlainTextEdit>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QTableView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SearchWindow
{
public:
    QWidget *centralwidget;
    QComboBox *choose;
    QLabel *l3;
    QComboBox *subject;
    QPushButton *bsearch;
    QPlainTextEdit *intro;
    QLabel *l1;
    QLabel *label_2;
    QLabel *l2;
    QLineEdit *bookname;
    QTableView *result;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *SearchWindow)
    {
        if (SearchWindow->objectName().isEmpty())
            SearchWindow->setObjectName(QString::fromUtf8("SearchWindow"));
        SearchWindow->resize(800, 600);
        centralwidget = new QWidget(SearchWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        choose = new QComboBox(centralwidget);
        choose->setObjectName(QString::fromUtf8("choose"));
        choose->setGeometry(QRect(290, 90, 101, 21));
        QFont font;
        font.setPointSize(12);
        choose->setFont(font);
        l3 = new QLabel(centralwidget);
        l3->setObjectName(QString::fromUtf8("l3"));
        l3->setGeometry(QRect(110, 90, 81, 20));
        QFont font1;
        font1.setPointSize(11);
        font1.setBold(true);
        font1.setWeight(75);
        l3->setFont(font1);
        l3->setStyleSheet(QString::fromUtf8("color: rgb(0, 170, 255);"));
        subject = new QComboBox(centralwidget);
        subject->setObjectName(QString::fromUtf8("subject"));
        subject->setGeometry(QRect(230, 90, 101, 22));
        subject->setFont(font);
        bsearch = new QPushButton(centralwidget);
        bsearch->setObjectName(QString::fromUtf8("bsearch"));
        bsearch->setGeometry(QRect(341, 90, 75, 23));
        bsearch->setFont(font);
        bsearch->setCheckable(false);
        bsearch->setAutoRepeat(false);
        bsearch->setAutoDefault(false);
        bsearch->setDefault(true);
        bsearch->setFlat(false);
        intro = new QPlainTextEdit(centralwidget);
        intro->setObjectName(QString::fromUtf8("intro"));
        intro->setGeometry(QRect(470, 160, 221, 271));
        QPalette palette;
        QBrush brush(QColor(255, 155, 170, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush);
        intro->setPalette(palette);
        QFont font2;
        font2.setPointSize(12);
        font2.setBold(false);
        font2.setWeight(50);
        intro->setFont(font2);
        intro->setLayoutDirection(Qt::LeftToRight);
        intro->setAutoFillBackground(true);
        intro->setStyleSheet(QString::fromUtf8("color: rgb(0, 170, 255);color: rgb(255, 155, 170);\n"
"background-image: url(:/new/prefix1/xingkong2.JPG);\n"
""));
        intro->setFrameShadow(QFrame::Raised);
        intro->setTextInteractionFlags(Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);
        l1 = new QLabel(centralwidget);
        l1->setObjectName(QString::fromUtf8("l1"));
        l1->setGeometry(QRect(190, 30, 291, 41));
        QFont font3;
        font3.setPointSize(18);
        font3.setBold(true);
        font3.setWeight(75);
        l1->setFont(font3);
        l1->setStyleSheet(QString::fromUtf8("color: rgb(0, 170, 255);"));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(470, 130, 111, 20));
        QFont font4;
        font4.setPointSize(12);
        font4.setBold(true);
        font4.setWeight(75);
        label_2->setFont(font4);
        label_2->setStyleSheet(QString::fromUtf8("color: rgb(0, 170, 255);"));
        l2 = new QLabel(centralwidget);
        l2->setObjectName(QString::fromUtf8("l2"));
        l2->setGeometry(QRect(170, 90, 111, 21));
        l2->setFont(font4);
        l2->setStyleSheet(QString::fromUtf8("color: rgb(0, 170, 255);"));
        bookname = new QLineEdit(centralwidget);
        bookname->setObjectName(QString::fromUtf8("bookname"));
        bookname->setGeometry(QRect(200, 90, 131, 21));
        result = new QTableView(centralwidget);
        result->setObjectName(QString::fromUtf8("result"));
        result->setGeometry(QRect(10, 130, 451, 321));
        QFont font5;
        font5.setPointSize(10);
        font5.setBold(true);
        font5.setWeight(75);
        result->setFont(font5);
        result->setStyleSheet(QString::fromUtf8("color: rgb(0, 170, 255);color: rgb(255, 155, 170);\n"
"background-image: url(:/new/prefix1/xingkong2.JPG);\n"
"\n"
"\n"
""));
        result->setFrameShadow(QFrame::Raised);
        SearchWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(SearchWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 22));
        SearchWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(SearchWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        SearchWindow->setStatusBar(statusbar);

        retranslateUi(SearchWindow);

        QMetaObject::connectSlotsByName(SearchWindow);
    } // setupUi

    void retranslateUi(QMainWindow *SearchWindow)
    {
        SearchWindow->setWindowTitle(QApplication::translate("SearchWindow", "\344\271\246\347\261\215\346\237\245\350\257\242", 0, QApplication::UnicodeUTF8));
        choose->clear();
        choose->insertItems(0, QStringList()
         << QApplication::translate("SearchWindow", "\346\227\240", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SearchWindow", "\345\233\276\344\271\246\347\274\226\345\217\267", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SearchWindow", "\345\233\276\344\271\246\345\220\215\347\247\260", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SearchWindow", "\345\275\222\345\261\236\345\255\246\347\247\221", 0, QApplication::UnicodeUTF8)
        );
        l3->setText(QString());
        subject->clear();
        subject->insertItems(0, QStringList()
         << QApplication::translate("SearchWindow", "\350\256\241\347\256\227\346\234\272", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SearchWindow", "\350\210\252\347\251\272", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SearchWindow", "\350\210\252\346\265\267", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SearchWindow", "\351\251\254\345\205\213\346\200\235", 0, QApplication::UnicodeUTF8)
        );
        bsearch->setText(QApplication::translate("SearchWindow", "\346\237\245\350\257\242", 0, QApplication::UnicodeUTF8));
        l1->setText(QApplication::translate("SearchWindow", "\345\233\276\344\271\246\346\237\245\350\257\242\350\277\233\350\241\214\344\270\255\343\200\202\343\200\202\343\200\202", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("SearchWindow", "\344\271\246\347\261\215\347\256\200\344\273\213\357\274\232", 0, QApplication::UnicodeUTF8));
        l2->setText(QApplication::translate("SearchWindow", "\351\200\211\346\213\251\346\237\245\350\257\242\346\226\271\345\274\217\357\274\232", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SearchWindow: public Ui_SearchWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SEARCHWINDOW_H
