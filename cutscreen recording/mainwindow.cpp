#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QPixmap>
#include <QDesktopWidget>
#include<stdio.h>
#include<opencv2/opencv.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<iostream>
#include<QThread>
#include <windows.h>
using namespace std;

extern MainWindow w;
Mat frame1;
int choose_flag=0;
int sx,sy,ex,ey;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),flag(1)
{
//     setAttribute(Qt::WA_TranslucentBackground);//背景透明
//    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint |Qt::WindowStaysOnTopHint);
    ui->setupUi(this);
    ui->start->setText("choose");
    sx=0;
    sy=0;
    ex=GetSystemMetrics(SM_CXSCREEN);
    ey=GetSystemMetrics(SM_CYSCREEN);
}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::test()
{
    Mat src;
    Size frameSize(ex-sx,ey-sy);

    VideoWriter oVideoWriter(name,-1, 19, frameSize);
    //CV_FOURCC('D', 'I', 'V', 'X')
    if (!oVideoWriter.isOpened())
    {
        cout << "初始化VideoWriter失败！" << endl;
        return ;
    }


    while(flag)
    {
        cut(src,oVideoWriter);
        if(waitKey(5)>=0)
            break;
    }
}


void MainWindow::paintmouse(Mat &frame)
{
    char str[10];
    sprintf(str,"%x",GetCursor());
    if(str[4]=='9')
    {
        Point temp1[4];
        QPoint temp;
        temp=QCursor::pos();
        temp.setX(temp.x()-sx);
        temp.setY(temp.y()-sy);
        temp1[0].x=temp.x();
        temp1[0].y=temp.y()+10;
        temp1[1].x=temp.x();
        temp1[1].y=temp.y()-10;
        temp1[2].x=temp.x()-10;
        temp1[2].y=temp.y();
        temp1[3].x=temp.x()+10;
        temp1[3].y=temp.y();
        line(frame,temp1[0],temp1[1],Scalar(233,233,233),4,8,0);
        line(frame,temp1[2],temp1[3],Scalar(233,233,233),4,8,0);
        line(frame,temp1[0],temp1[1],Scalar(0,0,0),2,8,0);
        line(frame,temp1[2],temp1[3],Scalar(0,0,0),2,8,0);
    }
    else
    {
        QPoint temp(0,0);
        Point temp1[5];
        temp=QCursor::pos();
        temp.setX(temp.x()-sx);
        temp.setY(temp.y()-sy);
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
    }
//    imshow("12",frame);
    return ;
}
cv::Mat QImage2cvMat(QImage image)
{
    cv::Mat mat;
    switch(image.format())
    {
    case QImage::Format_ARGB32:
    case QImage::Format_RGB32:
    case QImage::Format_ARGB32_Premultiplied:
        mat = cv::Mat(image.height(), image.width(), CV_8UC4, (void*)image.constBits(), image.bytesPerLine());
        break;
    case QImage::Format_RGB888:
        mat = cv::Mat(image.height(), image.width(), CV_8UC3, (void*)image.constBits(), image.bytesPerLine());
        cv::cvtColor(mat, mat, CV_BGR2RGB);
        break;
    case QImage::Format_Indexed8:
        mat = cv::Mat(image.height(), image.width(), CV_8UC1, (void*)image.constBits(), image.bytesPerLine());
        break;
    }
    return mat;
}


void MainWindow::cut(Mat &frame,VideoWriter videowrite)
{
    QPixmap fullScreen;
    fullScreen = QPixmap::grabWindow(QApplication::desktop()->winId(),sx,sy,ex-sx,ey-sy);
    QImage src=fullScreen.toImage();
    frame=QImage2cvMat(src);
    paintmouse(frame);

    videowrite.write(frame);
//    imshow("asdf",frame);
//    cv::resize(frame,frame,Size(frame.cols,frame.rows),(0,0),(0,0),3);
}
void line1(Mat src,int sx,int sy,int ex,int ey,Scalar color)
{
    for(int y=sy;y<=ey+3;++y)
    {
        for(int x=sx;x<=ex+3;++x)
        {
            for(int c=0;c<src.channels();c++)
                src.data[y * src.step + x * src.channels() + c]=color(c);
        }
    }
}

void on_mouse(int event,int x,int y,int flags,void *ustc)//event鼠标事件代号，x,y鼠标坐标，flags拖拽和键盘操作的代号
{
    if(event==CV_EVENT_LBUTTONDOWN)
    {
        if(choose_flag==0)
        {
            sx=x;
            sy=y;
            choose_flag++;

            int h=frame1.rows/2;
            int w=frame1.cols/3;

            int r=(255-frame1.at<Vec3b>(w,h)[0]+30)%256;
            int g=(255-frame1.at<Vec3b>(w,h)[1])%256;
            int b=(255-frame1.at<Vec3b>(w,h)[2]+30)%256;

            putText(frame1,"choose the next point",Point(w,h),FONT_HERSHEY_SIMPLEX,1,Scalar(b,g,r,255),1,8);
            imshow("screen choosing",frame1);
        }
        else if(choose_flag==1)
        {
            ex=x;
            ey=y;

            int tx=std::min(sx,ex);
            int ty=std::min(sy,ey);
            ex=std::max(sx,ex);
            ey=std::max(sy,ey);
            sx=tx;
            sy=ty;

            line1(frame1,sx,sy,sx,ey,Scalar(255,155,155));
            line1(frame1,sx,ey,ex,ey,Scalar(255,155,155));
            line1(frame1,ex,sy,ex,ey,Scalar(255,155,155));
            line1(frame1,sx,sy,ex,sy,Scalar(255,155,155));

            sx=sx*1.5;
            sy=sy*1.5;
            ex=ex*1.5;
            ey=ey*1.5;

            int h=frame1.rows/2+30;
            int w=frame1.cols/3;

            int r=(255-frame1.at<Vec3b>(w,h)[0]+30)%256;
            int g=(255-frame1.at<Vec3b>(w,h)[1])%256;
            int b=(255-frame1.at<Vec3b>(w,h)[2]+30)%256;
            putText(frame1,"enter start button to start",Point(w,h),FONT_HERSHEY_SIMPLEX,1,Scalar(b,g,r,255),1,8);
            imshow("screen choosing",frame1);
            choose_flag=-1;
        }
    }
}


void MainWindow::on_start_clicked()
{
    if(ui->input->text().isEmpty())
        ui->input->setText("input a file name to save");
    else
    {       
        if(ui->start->text().compare(tr("choose"))==0)
        {
            sx=0;
            sy=0;
            ex=GetSystemMetrics(SM_CXSCREEN);
            ey=GetSystemMetrics(SM_CYSCREEN);
            this->hide();

            QPixmap fullScreen;
            fullScreen = QPixmap::grabWindow(QApplication::desktop()->winId(),sx,sy,ex,ey);
            QImage src=fullScreen.toImage();
            frame1=QImage2cvMat(src);
            paintmouse(frame1);
            cv::resize(frame1,frame1,Size(frame1.cols/1.5,frame1.rows/1.5),(0,0),(0,0),3);
            imshow("screen choosing",frame1);
            setMouseCallback("screen choosing",on_mouse,0);
            ui->start->setText("start");
            this->show();
        }
        else if(ui->start->text().compare(tr("start"))==0)
        {
            name=ui->input->text().toStdString()+".avi";
            test();
            ui->start->setText("choose");
        }
        //
    }
}





void MainWindow::on_pushButton_clicked()
{
    flag=0;
    this->close();
}
