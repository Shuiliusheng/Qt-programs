#ifndef BACKPRO_H
#define BACKPRO_H

#include<iostream>

#include<opencv2/opencv.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>

#include<QImage>
#include<QPixmap>


using namespace cv;
using namespace std;
class Backpro{
public:
    Backpro() :bins(25),histSize(2){}
    QImage imag;
    QImage imag1;
    void change1(Mat &src,Mat &backpro, Mat &dst);
    void change2(Mat &src1,Mat &src, Mat &backproj);
    void mattoQImage(cv::Mat &mat,QImage &img);
    void Histt(Mat &histImg);
    void BackProjj(Mat &backpro);

private:
    Mat hsv,hsv1;
    Mat hue,hue1;
    int bins;
    int histSize;
    MatND hist;
};





#endif // BACKPRO_H
