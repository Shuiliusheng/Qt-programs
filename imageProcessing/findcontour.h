#ifndef FINDCONTOUR_H
#define FINDCONTOUR_H

#include<iostream>
#include<opencv2/opencv.hpp>

#include<opencv2/core/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<QImage>
#include<QPixmap>

using namespace cv;
using namespace std;

class Findcontour{
public:
    explicit Findcontour();
    void unclearandgray(Mat &src, Mat &contours, Mat &con);
    void findcontours(Mat &contour);
    void findconvexhull(Mat &con);
    void getRec_Circleinformation(Mat &src);
    void tail2(Mat &srcc,Mat &back);

private:
    Mat src_gray;
    int thresh;
    int max_thresh;
    RNG rng;
};

#endif // FINDCONTOUR_H
