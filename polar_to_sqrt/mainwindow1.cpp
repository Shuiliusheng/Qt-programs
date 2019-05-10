#include "mainwindow1.h"
const int rolate=180;
MainWindow1::MainWindow1(QWidget *parent)
    : QMainWindow(parent)
{
    this->test_main();
}

MainWindow1::~MainWindow1()
{
    
}
void MainWindow1::test_main()
{
    Mat src=imread("f:/num\\px.jpg");
    imshow("1",src);
    s_p(p_s1(src));
}
//变换后长高为原高
Mat MainWindow1::p_s(Mat src)
{
    Mat src1(src.rows,src.rows,src.type());
    for(int m=0;m<src1.rows;m++)
        for(int n=0;n<src1.cols;n++)
            for(int i=0;i<3;i++)
                src1.at<Vec3b>(m,n)[i]=255;

    int r=src.rows,c=src.cols;
    double t=(360.0)/c;
    for(int m=0;m<2*src1.rows;m++)
        for(int n=0;n<2*src1.cols;n++)
        {
            double di=sqrt((m-r)*(m-r)+(n-r)*(n-r));
            if(di<r)
            {
                double x=n-r,y=r-m;
                double sita=180*(atan(y/x)/3.141593);
                if(x==0&&y>0)sita=90;
                if(x==0&&y<0)sita=270;
                if(x<0&&y!=0)sita+=180;
                if(x<0&&y==0)sita=180;
                if(x>0&&y<0)sita+=360;
                sita+=rolate;
                if(sita>360)
                    sita-=360;
                int m1=(int)di,n1=(int)(sita/t);
                if(m1<r&&n1<c&&m1>=0&&n1>=0)
                    for(int i=0;i<3;i++)
                        src1.at<Vec3b>(m/2,n/2)[i]=src.at<Vec3b>(m1,n1)[i];
            }
        }
    imshow("21",src1);
    return src1;
}

//变为二倍,转换后长宽均为原高的二倍
Mat MainWindow1::p_s1(Mat src)
{
    Mat src1(src.rows*2,src.rows*2,src.type());
    for(int m=0;m<src1.rows;m++)
        for(int n=0;n<src1.cols;n++)
            for(int i=0;i<3;i++)
                src1.at<Vec3b>(m,n)[i]=255;
    int r=src.rows,c=src.cols;
    double t=(360.0)/c;
    for(int m=0;m<src1.rows;m++)
        for(int n=0;n<src1.cols;n++)
        {
            double di=sqrt((m-r)*(m-r)+(n-r)*(n-r));
            if(di<r)
            {
                double x=n-r,y=r-m;
                double sita=180*(atan(y/x)/3.141593);
                if(x==0&&y>0)sita=90;
                if(x==0&&y<0)sita=270;
                if(x<0&&y!=0)sita+=180;
                if(x<0&&y==0)sita=180;
                if(x>0&&y<0)sita+=360;
                sita+=rolate;
                if(sita>360)
                    sita-=360;
                int m1=(int)di,n1=(int)(sita/t);
                if(m1<r&&n1<c&&m1>=0&&n1>=0)
                    for(int i=0;i<3;i++)
                        src1.at<Vec3b>(m,n)[i]=src.at<Vec3b>(m1,n1)[i];
            }
        }
    imshow("2",src1);
    return src1;
}

void MainWindow1::s_p(Mat src1)
{
    int cx=src1.rows/2,cy=src1.cols/2;

    if(cx>cy)
        cx=cy;
    else
        cy=cx;
    Mat src(cx*2,cy*2,src1.type());
    double t=3.141593/cx;
    for(int m=0;m<cx*2;m++)
        for(int n=0;n<cx*2;n++)
        {
            int x=cx+m*cos(n*t)/2;
            int y=cy-m*sin(n*t)/2;
            for(int i=0;i<3;i++)
                src.at<Vec3b>(m,n)[i]=src1.at<Vec3b>(y,x)[i];
        }
    imshow("src",src);

}

void MainWindow1::s_p1(Mat src1)
{
    int cx=src1.rows/2,cy=src1.cols/2;

    if(cx>cy)
        cx=cy;
    else
        cy=cx;
    Mat src(cx,cy,src1.type());
    double t=2*3.141593/cx;
    for(int m=0;m<cx;m++)
        for(int n=0;n<cx;n++)
        {
            int x=cx+m*cos(n*t);
            int y=cy-m*sin(n*t);
            if(x<src1.cols&&x>=0&&y<src1.rows&&y>=0)
                for(int i=0;i<3;i++)
                    src.at<Vec3b>(m,n)[i]=src1.at<Vec3b>(y,x)[i];
        }
    imshow("srcz",src);

}
