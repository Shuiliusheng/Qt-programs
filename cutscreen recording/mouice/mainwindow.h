#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include<iostream>
#include<D:/Opencv2_3/opencv23_mingw/include/opencv2/opencv.hpp>
#include <QDesktopWidget>
#include<D:/Opencv2_3/opencv23_mingw/include/opencv2/core/core.hpp>
#include<D:/Opencv2_3/opencv23_mingw/include/opencv2/imgproc/imgproc.hpp>
#include<D:/Opencv2_3/opencv23_mingw/include/opencv2/highgui/highgui.hpp>
#include<QImage>
#include<QPixmap>

using namespace cv;
using namespace std;
class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    void mouse();
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
};

#endif // MAINWINDOW_H
