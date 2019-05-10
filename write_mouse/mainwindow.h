#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <Windows.h>
#include <windows.h>
#include <string.h>
#include <iostream>
#include <QTime>
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include "use.h"
using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    Use use;
    Run runfile;

    void reduce_cmd(char cmd[],FILE *p);

private slots:
    void on_start_clicked();

    void on_save_clicked();

    void on_save_2_clicked();

    void on_save_3_clicked();

    void on_use_clicked();

    void reduce_file();

    void exit()
    {
        this->close();
    }

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
