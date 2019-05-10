#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<stdio.h>
#include<string.h>
#include<iostream>
#include<opencv2/opencv.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<QImage>
#include<QPixmap>
using namespace cv;
using namespace std;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void data();
    void drawtext(Mat &src);
    void getcenter();
    void drawline(Mat &src);
    void drawfuc();
    void getxy(int &x,int &y);
    void draw(Mat &src);
    void draw1(Mat &src);
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
    int flag;
    double xmax,xmin,ymax,ymin;
    int pw,pl;
    int cx,cy;
    char *strx,*stry;
    double bx,by;
};

#endif // MAINWINDOW_H
