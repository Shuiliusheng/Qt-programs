#include"findcontour.h"
#include<QTime>


//构造函数
Findcontour::Findcontour()
   :thresh(70),
    max_thresh(255),
    rng(12345)
{

}
//对图片进行变灰与模糊处理从而寻找边缘
void Findcontour::unclearandgray(Mat &src,Mat &contours,Mat &con)
{

    cvtColor(src,src_gray,CV_BGR2GRAY);//变灰
    blur(src_gray,src_gray,Size(5,5));//模糊处理


    this->findcontours(contours);//调用获取边界函数
    this->findconvexhull(con);//调用获取凸包函数
    this->getRec_Circleinformation(src);//调用获取圆形框与矩形框的函数
}



//通过边缘使用findContours函数产生边界
void Findcontour::findcontours(Mat &contour)
{
    Mat canny_output;
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;

    //寻找边缘
    Canny(src_gray,canny_output,thresh,thresh*2,3);

    //寻找边界
    findContours(canny_output,contours,hierarchy,CV_RETR_TREE,CV_CHAIN_APPROX_SIMPLE,Point(0,0));

    ///形成边界
    Mat drawing=Mat::zeros(canny_output.size(),CV_8UC3);//初始化mat对象存储边界

    for(int i=0;i<contours.size();i++)
    {
        Scalar color=Scalar(23,200,23);
        drawContours(drawing ,contours,i,color,2,8,hierarchy,2,Point());

    }
    drawing.copyTo(contour);
}



//通过产生的二位图像的边界调用convexHull函数寻找边界中的凸包并与边界一起打印出来
void Findcontour::findconvexhull(Mat &con)
{
    Mat threshold_output;
    vector<vector<Point> > contours1;
    vector<Vec4i> hierarchy1;

    //把灰色图像转化为黑白二位图像
    threshold(src_gray,threshold_output,thresh,255,THRESH_BINARY);

    //寻找二位图像的边界
    findContours(threshold_output,contours1,hierarchy1,CV_RETR_TREE,CV_CHAIN_APPROX_SIMPLE,Point(0,0));

    //寻找边界中的凸包并存储在一个新的hull中
    vector<vector<Point> > hull(contours1.size());
    for(int i=0;i<contours1.size();i++)
    {
        convexHull(Mat(contours1[i]),hull[i],false);//该函数用于寻找边界中的凸包
    }


    Mat drawing=Mat::zeros(threshold_output.size(),CV_8UC3);//初始化一个mat对象用于存储凸包

    for(int i=0;i<contours1.size();i++)
    {
        //设定随机颜色范围是155到255
        Scalar color=Scalar(244,23,23);

        //形成边界图像
        drawContours(drawing ,contours1,i,color,1,8,vector<Vec4i>(),0,Point());

        //形成凸包图像（可以两者置于一起）
        drawContours(drawing ,hull,i,color,1,8,vector<Vec4i>(),0,Point());

    }
    drawing.copyTo(con);


}



//通过二值图像的边界的多边形近似图像寻找包含其的最小矩形框与圆形框的信息
void Findcontour::getRec_Circleinformation(Mat &src)
{
    Mat threshold_output1;
    vector<vector<Point> > contours2;//用于存储边界信息
    vector<Vec4i> hierarchy2;


    threshold(src_gray,threshold_output1,150,200,THRESH_BINARY);
    //thresh为阈值，当色素点的灰度值大于它者被设定为200，否则为黑色
    //src_gray为输入的灰色图像，threshold_output1为输出二值图像



    findContours(threshold_output1,contours2,hierarchy2,CV_RETR_TREE,CV_CHAIN_APPROX_SIMPLE,Point(0,0));
    //寻找二值图像的边界

    vector<vector<Point> > contours_poly(contours2.size());//存储边界近似后的数据


    vector<Rect> boundRect(contours2.size());//存储矩形边界信息


    vector<Point2f> center(contours2.size());//存储圆点位置

    vector<float> radius(contours2.size());//存储圆半径

    for(int i=0;i<contours2.size();i++)
    {
        approxPolyDP(Mat(contours2[i]),contours_poly[i],5,true);

        boundRect[i]=boundingRect(Mat(contours_poly[i]));
        //计算并返回包围轮廓点集的最小矩形

        minEnclosingCircle(contours_poly[i],center[i],radius[i]);
        //计算并返回包围轮廓点集的最小圆形及其半径
    }

    for(int i=0;i<contours2.size();i++)//contours.size（）表示边界个数
    {
        Scalar color1=Scalar(23,244,244),color=Scalar(244,244,23);

        //绘制圆形
        circle(src,center[i],(int)radius[i],color1,4,8,0);
        //绘制矩形
        rectangle(src,boundRect[i].tl(),boundRect[i].br(),color,2,4,0);

    }
    imshow("findcontours",src);

}
void Findcontour::tail2(Mat &srcc,Mat &back)
{
    Mat threshold_output1;
    vector<vector<Point> > contours2;//用于存储边界信息
    vector<Vec4i> hierarchy2;

//     Canny(back,back,thresh,thresh*2,3);
     blur(back,back,Size(5,5));
//     GaussianBlur(back,back,Size(5,5),2,2);//使用高斯公式进行滤波处理

    threshold(back,threshold_output1,235,245,THRESH_BINARY);



    findContours(threshold_output1,contours2,hierarchy2,CV_RETR_TREE,CV_CHAIN_APPROX_SIMPLE,Point(0,0));
    //寻找二值图像的边界

    vector<vector<Point> > contours_poly(contours2.size());//存储边界近似后的数据


    vector<Rect> boundRect(contours2.size());//存储矩形边界信息

    for(int i=0;i<contours2.size();i++)
    {
        approxPolyDP(Mat(contours2[i]),contours_poly[i],5,true);
        boundRect[i]=boundingRect(Mat(contours_poly[i]));
        //计算并返回包围轮廓点集的最小矩形

    }
    int a=0,b=0;
    for(int i=0;i<contours2.size();i++)//contours.size（）表示边界个数
    {
        int c=(boundRect[i].tl().x-boundRect[i].br().x)*(boundRect[i].tl().y-boundRect[i].br().y);
        if(c<0)
            c=-c;
        if(c>b)
         {
            b=c;
            a=i;
         }
    }
    Scalar color=Scalar(244,244,23);
    rectangle(srcc,boundRect[a].tl(),boundRect[a].br(),color,2,4,0);
    imshow("tail",srcc);
}



