#include "mainwindow.h"
#include <QDesktopWidget>
#include<QApplication>
#include<windows.h>
#include<stdio.h>
#include<wingdi.h>
#include<QPoint>
#include<iostream>
#include<D:/Opencv2_3/opencv23_mingw/include/opencv2/core/core.hpp>
#include<D:/Opencv2_3/opencv23_mingw/include/opencv2/imgproc/imgproc.hpp>
#include<D:/Opencv2_3/opencv23_mingw/include/opencv2/highgui/highgui.hpp>
#include<D:/Opencv2_3/opencv23_mingw/include/opencv2/opencv.hpp>
using namespace std;
using namespace cv;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    mouse();
}

MainWindow::~MainWindow()
{
    
}
void MainWindow::mouse()
{
    QPoint temp(0,0);
    Point temp1[5];
    bool stop = false;

    while(!stop)
    {
        Mat frame;
        frame=cv::imread("f://123.jpg",1);
        temp=QCursor::pos();
        temp1[0].x=temp.x();
        temp1[0].y=temp.y();
        temp1[1].x=temp.x();
        temp1[1].y=temp.y()+14;
        temp1[2].x=temp.x()+10;
        temp1[2].y=temp.y()+10;
        temp1[3].x=(temp1[1].x+temp1[2].x)/2+2;
        temp1[3].y=(temp1[1].y+temp1[2].y)/2+5;
        temp1[4].x=(temp1[1].x+temp1[2].x)/2;
        temp1[4].y=(temp1[1].y+temp1[2].y)/2;
        line(frame,temp1[0],temp1[1],Scalar(233,233,233),4,8,0);
        line(frame,temp1[1],temp1[2],Scalar(233,233,233),4,8,0);
        line(frame,temp1[2],temp1[0],Scalar(233,233,233),4,8,0);
        line(frame,temp1[4],temp1[3],Scalar(233,233,233),4,8,0);
        line(frame,temp1[0],temp1[3],Scalar(233,233,233),4,8,0);
        line(frame,temp1[0],temp1[1],Scalar(0,0,0),1,8,0);
        line(frame,temp1[1],temp1[2],Scalar(0,0,0),1,8,0);
        line(frame,temp1[2],temp1[0],Scalar(0,0,0),1,8,0);
        line(frame,temp1[3],temp1[4],Scalar(0,0,0),2,8,0);
//        Qt::CursorShape sha
//        QCursor((Qt::CursorShape)shape1);
//        WORD a = shape1;
//        Qt::CursorShape();
//        cout << shape1 <<endl;
//        imshow("qw",frame);
//        int a=3;
//        polylines(frame,&temp1,&a,3,1,Scalar(255,255,255),1,8,0);
//        if(waitKey(30)>=0)
//            stop = true;

    }
    cvDestroyAllWindows();













}
