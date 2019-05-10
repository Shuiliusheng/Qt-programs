/********************************************************************************
** Form generated from reading UI file 'use.ui'
**
** Created: Tue Dec 6 23:05:01 2016
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USE_H
#define UI_USE_H

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
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Use
{
public:
    QWidget *centralwidget;
    QPushButton *pushButton;
    QPushButton *start;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *sleeptime;
    QLineEdit *times;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Use)
    {
        if (Use->objectName().isEmpty())
            Use->setObjectName(QString::fromUtf8("Use"));
        Use->resize(291, 94);
        Use->setMinimumSize(QSize(291, 94));
        Use->setMaximumSize(QSize(291, 94));
        centralwidget = new QWidget(Use);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(210, 10, 71, 31));
        QFont font;
        font.setPointSize(14);
        pushButton->setFont(font);
        start = new QPushButton(centralwidget);
        start->setObjectName(QString::fromUtf8("start"));
        start->setGeometry(QRect(210, 40, 71, 31));
        start->setFont(font);
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 10, 131, 31));
        QFont font1;
        font1.setPointSize(10);
        label->setFont(font1);
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 40, 131, 31));
        label_2->setFont(font1);
        sleeptime = new QLineEdit(centralwidget);
        sleeptime->setObjectName(QString::fromUtf8("sleeptime"));
        sleeptime->setGeometry(QRect(140, 10, 61, 31));
        sleeptime->setFont(font1);
        times = new QLineEdit(centralwidget);
        times->setObjectName(QString::fromUtf8("times"));
        times->setGeometry(QRect(140, 40, 61, 31));
        times->setFont(font1);
        Use->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Use);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 291, 23));
        Use->setMenuBar(menubar);
        statusbar = new QStatusBar(Use);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        Use->setStatusBar(statusbar);

        retranslateUi(Use);

        QMetaObject::connectSlotsByName(Use);
    } // setupUi

    void retranslateUi(QMainWindow *Use)
    {
        Use->setWindowTitle(QApplication::translate("Use", "UseRecord", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("Use", "File", 0, QApplication::UnicodeUTF8));
        start->setText(QApplication::translate("Use", "Start", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Use", "Circle Sleep(ms) :", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("Use", "    Circle Times :", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Use: public Ui_Use {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USE_H
