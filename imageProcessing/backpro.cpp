#include"backpro.h"
#include<stdlib.h>

void Backpro::BackProjj(Mat &backpro)
{

    this->histSize = MAX( bins, 2 );
    float hue_range[] = { 0, 180 };
    const float* ranges = { hue_range };

    calcHist( &hue, 1, 0, Mat(), hist, 1, &histSize, &ranges, true, false );//产生直方图的数据

    normalize( hist, hist, 0, 255, NORM_MINMAX, -1, Mat() );//把直方图中的bins值转化为0到255之间的值以便产生直方图的图像

    calcBackProject( &hue, 1, 0, hist, backpro, &ranges, 1, true );//产生投影图
    this->mattoQImage(backpro,imag);

}
void Backpro::Histt(Mat &histImg)
{
    int w = 400;
    int h = 400;
    int bin_w = cvRound( (double) w / this->histSize );
    histImg = Mat::zeros( w, h, CV_8UC3 );

    for( int i = 0; i < bins; i ++ )
    {
        rectangle( histImg, Point( i*bin_w, h ), Point( (i+1)*bin_w, h - cvRound( hist.at<float>(i)*h/255.0 ) ), Scalar( 45, 0, 56 ), -1 );
    }
}



void Backpro::change1(Mat &src, Mat &backpro,Mat &dst)
{
    cvtColor( src, hsv, CV_BGR2HSV );//原图
    hue.create( hsv.size(), hsv.depth() );
    int ch[] = { 0, 0 };
    mixChannels( &hsv, 1, &hue, 1, ch, 1 );
    BackProjj(backpro);
    Histt(dst);
}




void Backpro::change2(Mat &src1,Mat &src,Mat &backproj)
{

    cvtColor( src, hsv, CV_BGR2HSV );//原图
    cvtColor( src1, hsv1, CV_BGR2HSV );//模板


    hue.create( hsv.size(), hsv.depth() );
    hue1.create( hsv1.size(), hsv1.depth() );
    int ch[] = { 0, 0 };
    mixChannels( &hsv, 1, &hue, 1, ch, 1 );
    mixChannels( &hsv1, 1, &hue1, 1, ch, 1 );


    this->histSize = MAX( 12, 2 );
    float hue_range[] = { 0, 180 };
    const float* ranges = { hue_range };
    calcHist( &hue1, 1, 0, Mat(), hist, 1, &histSize, &ranges, true, false );//产生直方图的数据
    normalize( hist, hist, 0, 255, NORM_MINMAX, -1, Mat() );//把直方图中的bins值转化为0到255之间的值以便产生直方图的图像
    calcBackProject( &hue, 1, 0, hist, backproj, &ranges, 1, true );//产生投影图
    equalizeHist(backproj,backproj);
}

void Backpro::mattoQImage(cv::Mat &mat,QImage &img)
{
    int nChannel=mat.channels();

    if(nChannel==3)//判断通道数，选择图片格式
    {
        cv::cvtColor(mat,mat,CV_RGB2BGR);
        img = QImage((const unsigned char*)mat.data,mat.cols,mat.rows,mat.step,QImage::Format_RGB888);

      }
    else if(nChannel==4||nChannel==1)
    {
        img = QImage((const unsigned char*)mat.data,mat.cols,mat.rows,mat.step,QImage::Format_Indexed8);
    }
}


