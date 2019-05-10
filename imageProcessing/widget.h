#ifndef WIDGET_H
#define WIDGET_H

#include <QtGui/QWidget>
#include<QLabel>
#include<QPushButton>
#include<QLineEdit>
#include<QGridLayout>
#include<QComboBox>
#include<QWidget>

#include<iostream>
#include<QImage>
#include<QPixmap>
#include<stdlib.h>

#include<opencv2/opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>

#include"outedge.h"
#include"backpro.h"
#include"findcontour.h"
#include"huofuTrans.h"

using namespace cv;
using namespace std;

class Widget : public QWidget
{
    Q_OBJECT
    
public:
    Widget(QWidget *parent = 0);
    ~Widget();void window();
    void task11(Mat &mat);
    void task22(Mat &mat, Mat &backpro, Mat &dst);
    void task33(Mat &src);
    void task44(Mat &src);
    void tail1(Mat &src);
private slots:
    void camerss();
    void stopc();
    void task1c();
    void task2c();
    void task3c();
    void task4c();
    void taill();

private:
    QLabel *wind;
    QLabel *name;
    QLabel *exp;
    QPushButton *stop;
    QPushButton *task1;
    QPushButton *task2;
    QPushButton *task3;
    QPushButton *task4;
    QPushButton *cramer;
    QPushButton *tail;
    QLineEdit *jpg;
    Outedge out;
    Backpro back;
    Findcontour find;
    HoufuTrans hough;
    int a;
    int t;
};

#endif // WIDGET_H
