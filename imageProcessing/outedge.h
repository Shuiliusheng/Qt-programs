#ifndef OUTEDGE_H
#define OUTEDGE_H


#include<iostream>
#include<QImage>
#include<QPixmap>
#include<opencv2/opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<stdlib.h>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

class Outedge{
public:
//    explicit Outedge(QWidget *parent = 0);
    Outedge() : kernel_size(3), lowThreshold(50),ratio(2) {}

    void print(cv::Mat &dst);

    void toGray(QImage &im);

    void mattoQImage(cv::Mat &dst,QImage &img);
    void outedge(Mat &src, Mat &dst);

private:
    int kernel_size;
    int lowThreshold;
    int ratio;
};
#endif // OUTEDGE_H
