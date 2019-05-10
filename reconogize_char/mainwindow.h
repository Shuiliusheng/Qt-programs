#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    MainWindow(QWidget *parent = 0);
    int binary(Mat &src,int th,int flag);//21
    void weight_gray(Mat &src);//3
    int get_threshold_2(Mat src);//30
    int cal_t(Mat src,int t);

    void getpostion(Mat src,Point &l,Point &r1,int color);
    void setFeature(Mat src,double temp[],int color,Point l);
    double cal(Mat src,int color,Point s,Point e);

    void write_file(char i, double temp[]);
    int detect(double temp[]);
    double getmin(double temp[],int i);

    void study(Mat src,Mat src1, char num);
    void test(Mat src,Mat src1);

    void test1();
    void sleep();
    void test_main();
    ~MainWindow();
private:
    int h,w;
    int n_w;
};

#endif // MAINWINDOW_H
