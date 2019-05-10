#include"huofuTrans.h"

void HoufuTrans::start(Mat &src,Mat &res,Mat &res1)
{

    src.copyTo(src2);
    cvtColor(src,src1,CV_RGB2GRAY);//进行初始准备，将图像变灰，并进行边缘检测得到边缘图像（一张二值图像）用于霍夫变换
    Canny(src1,dst,50,200,3);//得到边缘为白色底为黑的二值图像

    houghlinp(res,src);

    detectedCircle(res1);
}


void HoufuTrans::houghlinp(Mat &res,Mat &src)
{
    vector<Vec4i> lines;

    HoughLinesP(dst,lines,1,CV_PI/90,100,100,10);

    for(size_t i=0;i<lines.size();i++)
    {
        Vec4i l=lines[i];//便于表示，利于计算

        line(src,Point(l[0],l[1]),Point(l[2],l[3]),Scalar(11,200,111),3,CV_AA);

    }
    src.copyTo(res);
}


void HoufuTrans::detectedCircle(Mat &res1)
{

    Canny(src1,src1,50,200,3);//得到边缘为白色底为黑的二值图像
    blur(src1,src1,Size(5,5));
    vector<Vec3f> circles;//定义一个容器可以存储多个三组flaot数据的对象用于存储圆心坐标与圆半径


    HoughCircles(src1,circles,CV_HOUGH_GRADIENT,1,src1.rows/8,150,70,0,0);
    //霍夫圆变换得到图形中满足条件的圆的圆心坐标与圆半径数据

    for(size_t a=0;a<circles.size();a++)
    {
        Point center(cvRound(circles[a][0]),cvRound(circles[a][1]));//得到圆中心坐标点

        int radius=cvRound(circles[a][2]);//得到整数型圆半径的值

        circle(src2,center,3,Scalar(23,222,155),-1,8,0);//根据数据画出实心圆心

        circle(src2,center,radius,Scalar(255,23,178),3,8,0);//根据数据（圆心与半径）在原图中画出圆形
    }
    src2.copyTo(res1);

}
