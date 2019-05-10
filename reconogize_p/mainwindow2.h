#ifndef MAINWINDOW2_H
#define MAINWINDOW2_H

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
class MainWindow2 : public QMainWindow
{
    Q_OBJECT
    
public:
    MainWindow2(QWidget *parent = 0);

    void delete_back(Mat src, int t[]);
    void delete_back1(Mat src, int t[]);
    int binary(Mat &src,int th,int flag);//21
    void weight_gray(Mat &src);//3
    int get_threshold_2(Mat src);//30
    int cal_t(Mat src,int t);

    bool find_nosing(Mat src,int r,int c);
    Mat de_longly_nosing(Mat src);//14
    void cut(Mat src,int color, int num);

    void detect1(Mat src,int color);
    void detect_eye(Mat src,int h1,int h2,int color);
    void detect_mouth(Mat src,int h1,int h2,int w1,int w2);
    int find_bottom(int temp[],int n,int num, int s);

    int find_eye1(Mat src,int h1,int h2,int w1,int w2);

    void get_postion(Mat src1);
    void setFeature(double temp[]);

    void study(Mat src,int i);
    void write_file(double temp[],int i);
    double getmin(double temp[],int i,double l);
    int charge(double temp[]);
    int detect(Mat src);
    void test_main();

    ~MainWindow2();
private:
    Point el,er,el1,er1;
    Point ml,mr;
};

#endif // MAINWINDOW2_H
