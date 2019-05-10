#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include<opencv2/opencv.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>

#include<time.h>
#include<stdio.h>
#include<string.h>
#include<iostream>
using namespace std;
using namespace cv;

typedef struct{
    Point2i leftup;
    Point2i rightdown;
    char name[100];
    int type;
    int label;
}RFile;


class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    bool init();

private:

};


#endif // MAINWINDOW_H
