#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<iostream>
#include<D:/Opencv2_3/opencv23_mingw/include/opencv2/opencv.hpp>
#include<D:/Opencv2_3/opencv23_mingw/include/opencv2/core/core.hpp>
#include<D:/Opencv2_3/opencv23_mingw/include/opencv2/imgproc/imgproc.hpp>
#include<D:/Opencv2_3/opencv23_mingw/include/opencv2/highgui/highgui.hpp>
#include<QImage>
#include<QPixmap>
#include<math.h>
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
    void getdata();
    void getdata1();
    void drawline(Mat &src);
    void drawline1(Mat &src);
    void drawline2(Mat &src,Point O,Point q,Point w,Point e);
    void drawline3(Mat &src);
    void drawline4(Mat &src);
    int calZ(int r,int g,int b);
    int calZ1(int r,int g,int b);
    int calX(int x2,int y);
    int calX1(int x2,int y);
    int calY(int y, int z);
    int calY1(int y, int z);
    void rolate(int xi,int yi,int zi, int &X0, int &Y0);
    void rolate1(int &xi,int &yi,int &zi);
    void insertcol(Mat &src);
    void insertcol1(Mat &src);
    void insertrow(Mat &src);

    void result();
    void result1();
    void drawfuction();
    void result2();   
    void fuction(int x,int y,double &z,int &flag);
    void drawfuction1();

private slots:
    void on_add_clicked();

    void on_cut_clicked();

    void on_add1_clicked();

    void on_cut2_clicked();

    void on_X1_clicked();

    void on_x2_clicked();

    void on_y1_clicked();

    void on_y2_clicked();

    void on_z1_clicked();

    void on_z2_clicked();

    void on_reset_clicked();

    void on_lengthadd_clicked();

    void on_lengthcut_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_8_clicked();

private:
    Ui::MainWindow *ui;
    int choose;
    int length;
    int ctx;
    int cty;
    int ctz;
    double bei;
    double bei1;
    double bei2;
    int h;
    int x;
    int Ox;
    int Oy;
    Point O,q,w,e;
    int h1;
    int x1;
    int Ox1;
    int Oy1;
    Point O1,q1,w1,e1;
};

#endif // MAINWINDOW_H
