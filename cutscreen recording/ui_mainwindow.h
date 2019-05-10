/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Sat Nov 26 15:44:56 2016
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
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *start;
    QPushButton *pushButton;
    QLineEdit *input;
    QLabel *label;
    QLabel *output;
    QMenuBar *menuBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(269, 155);
        MainWindow->setMaximumSize(QSize(269, 155));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        start = new QPushButton(centralWidget);
        start->setObjectName(QString::fromUtf8("start"));
        start->setGeometry(QRect(20, 80, 101, 51));
        QFont font;
        font.setPointSize(24);
        font.setBold(false);
        font.setItalic(false);
        font.setUnderline(false);
        font.setWeight(50);
        font.setStrikeOut(false);
        font.setKerning(false);
        font.setStyleStrategy(QFont::PreferAntialias);
        start->setFont(font);
        start->setCursor(QCursor(Qt::ArrowCursor));
        start->setMouseTracking(true);
        start->setFocusPolicy(Qt::ClickFocus);
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(150, 80, 101, 51));
        QFont font1;
        font1.setPointSize(29);
        pushButton->setFont(font1);
        input = new QLineEdit(centralWidget);
        input->setObjectName(QString::fromUtf8("input"));
        input->setGeometry(QRect(10, 40, 241, 31));
        QFont font2;
        font2.setPointSize(12);
        input->setFont(font2);
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 10, 91, 21));
        QFont font3;
        font3.setPointSize(11);
        label->setFont(font3);
        output = new QLabel(centralWidget);
        output->setObjectName(QString::fromUtf8("output"));
        output->setGeometry(QRect(140, 10, 151, 21));
        output->setMinimumSize(QSize(151, 21));
        output->setFont(font3);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 269, 23));
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
        pushButton->setText(QApplication::translate("MainWindow", "exit", 0, QApplication::UnicodeUTF8));
        input->setText(QApplication::translate("MainWindow", "test.avi", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "videoname:", 0, QApplication::UnicodeUTF8));
        output->setText(QApplication::translate("MainWindow", "time: ", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
