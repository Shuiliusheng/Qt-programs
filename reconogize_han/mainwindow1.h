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
    int binary(Mat &src,int th,int flag);//21
    void weight_gray(Mat &src);//3
    int get_threshold_2(Mat src);//30
    int cal_t(Mat src,int t);

    void getpostion(Mat src,Point &l,Point &r1,int color);
    void setFeature(Mat src,double temp[],int color,Point l);
    void detect_t(int temp[],int n,double t[], int color);
    void setFeature1(Mat src,double temp[],int color,Point l,Point r);
    double cal(Mat src,int color,Point s,Point e);

    void write_file(int i, double temp[], double temp1[]);
    int detect(double temp[],double temp2[]);
    double getmin(double temp[],double temp2[], int i);

    void study(Mat src,Mat src1, int num);
    void test(Mat src,Mat src1);

    void test_main();
    ~MainWindow1();
private:
    int h,w;
    int h1,w1;
    int n_w;
};

#endif // MAINWINDOW1_H
