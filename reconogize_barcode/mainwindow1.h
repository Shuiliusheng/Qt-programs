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
    void cut(Mat src, Mat src1);
    Mat check(Mat src, int color);
    void get_num(Mat src, int color);
    void check1(int n,int temp[]);

    void test_main();


    void draw_bar();
    void check2(int number[]);
    void get_se(int nu[],int se[]);
    void get_oe(int n,int temp[]);
    ~MainWindow1();
private:
    int hs,he;
    int fw;
};

#endif // MAINWINDOW1_H
