/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Wed Dec 7 00:13:29 2016
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
#include <QtGui/QTextEdit>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QTextEdit *show;
    QPushButton *start;
    QPushButton *save;
    QLabel *label;
    QPushButton *save_2;
    QPushButton *save_3;
    QPushButton *use;
    QMenuBar *menuBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(413, 395);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(413, 395));
        MainWindow->setMaximumSize(QSize(413, 395));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        show = new QTextEdit(centralWidget);
        show->setObjectName(QString::fromUtf8("show"));
        show->setGeometry(QRect(0, 0, 421, 311));
        show->setMaximumSize(QSize(421, 311));
        start = new QPushButton(centralWidget);
        start->setObjectName(QString::fromUtf8("start"));
        start->setGeometry(QRect(0, 310, 61, 41));
        QFont font;
        font.setPointSize(15);
        start->setFont(font);
        save = new QPushButton(centralWidget);
        save->setObjectName(QString::fromUtf8("save"));
        save->setGeometry(QRect(60, 310, 61, 41));
        save->setFont(font);
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(305, 310, 101, 41));
        QFont font1;
        font1.setPointSize(14);
        label->setFont(font1);
        save_2 = new QPushButton(centralWidget);
        save_2->setObjectName(QString::fromUtf8("save_2"));
        save_2->setGeometry(QRect(120, 310, 61, 41));
        save_2->setFont(font);
        save_3 = new QPushButton(centralWidget);
        save_3->setObjectName(QString::fromUtf8("save_3"));
        save_3->setGeometry(QRect(180, 310, 61, 41));
        save_3->setFont(font);
        use = new QPushButton(centralWidget);
        use->setObjectName(QString::fromUtf8("use"));
        use->setGeometry(QRect(240, 310, 61, 41));
        use->setFont(font);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 413, 23));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        start->setText(QApplication::translate("MainWindow", "start", 0, QApplication::UnicodeUTF8));
        save->setText(QApplication::translate("MainWindow", "show", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "F12: stop", 0, QApplication::UnicodeUTF8));
        save_2->setText(QApplication::translate("MainWindow", "save", 0, QApplication::UnicodeUTF8));
        save_3->setText(QApplication::translate("MainWindow", "run", 0, QApplication::UnicodeUTF8));
        use->setText(QApplication::translate("MainWindow", "use", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
