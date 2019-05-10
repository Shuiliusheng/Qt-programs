#ifndef HUOFUTRANS_H
#define HUOFUTRANS_H
#include<iostream>
#include<opencv2/opencv.hpp>

#include<opencv2/core/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<QImage>
#include<QPixmap>
#include<stdlib.h>

using namespace cv;
using namespace std;
class HoufuTrans{
public:
    HoufuTrans():length(100){}
    void start(Mat &src,Mat &res, Mat &res1);
    void houghlinp(Mat &res, Mat &src);
    void detectedCircle(Mat &res1);
private:
    int length;
    Mat dst;
    Mat src2;
    Mat src1;
};


#endif // HUOFUTRANS_H
