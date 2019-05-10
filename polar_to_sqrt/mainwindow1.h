#ifndef MAINWINDOW1_H
#define MAINWINDOW1_H

#include <QtGui/QMainWindow>
#include<opencv2/opencv.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<QImage>
#include<QPixmap>
#include<iostream>
#include<stdio.h>
#include<string.h>
using namespace std;
using namespace cv;
class MainWindow1 : public QMainWindow
{
    Q_OBJECT
    
public:
    MainWindow1(QWidget *parent = 0);
    void test_main();
    Mat p_s(Mat src);
    Mat p_s1(Mat src);
    void s_p(Mat src1);
    void s_p1(Mat src1);
    ~MainWindow1();
};

#endif // MAINWINDOW1_H
