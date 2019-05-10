#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<opencv2/opencv.hpp>

#include<opencv2/core/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<QImage>
#include<QPixmap>
#include<iostream>
using namespace std;
using namespace cv;
#include <windows.h>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void paintmouse(Mat &frame);
    void cut(Mat &frame, VideoWriter videowrite);
    void test();
    void pic(Mat &src);
private slots:
    void on_start_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    int flag;
    string name;
};

#endif // MAINWINDOW_H
