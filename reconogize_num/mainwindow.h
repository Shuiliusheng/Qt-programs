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

    double cal(Mat src,int color,Point s,Point e);
    void setFeature(Mat src,double temp[],int color,Point l);

    void write_file(int i, double temp[]);
    void test(Mat src, Mat src1);
    int detect(double temp[]);
    double getmin(double temp[],int i);

    void study(Mat src,Mat src1, int num);

    void test_main();
    ~MainWindow();
private:
    int h,w;
    int n_w;
};

#endif // MAINWINDOW_H
