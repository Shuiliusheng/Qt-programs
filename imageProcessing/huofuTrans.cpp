#include"huofuTrans.h"

void HoufuTrans::start(Mat &src,Mat &res,Mat &res1)
{

    src.copyTo(src2);
    cvtColor(src,src1,CV_RGB2GRAY);//���г�ʼ׼������ͼ���ң������б�Ե���õ���Եͼ��һ�Ŷ�ֵͼ�����ڻ���任
    Canny(src1,dst,50,200,3);//�õ���ԵΪ��ɫ��Ϊ�ڵĶ�ֵͼ��

    houghlinp(res,src);

    detectedCircle(res1);
}


void HoufuTrans::houghlinp(Mat &res,Mat &src)
{
    vector<Vec4i> lines;

    HoughLinesP(dst,lines,1,CV_PI/90,100,100,10);

    for(size_t i=0;i<lines.size();i++)
    {
        Vec4i l=lines[i];//���ڱ�ʾ�����ڼ���

        line(src,Point(l[0],l[1]),Point(l[2],l[3]),Scalar(11,200,111),3,CV_AA);

    }
    src.copyTo(res);
}


void HoufuTrans::detectedCircle(Mat &res1)
{

    Canny(src1,src1,50,200,3);//�õ���ԵΪ��ɫ��Ϊ�ڵĶ�ֵͼ��
    blur(src1,src1,Size(5,5));
    vector<Vec3f> circles;//����һ���������Դ洢�������flaot���ݵĶ������ڴ洢Բ��������Բ�뾶


    HoughCircles(src1,circles,CV_HOUGH_GRADIENT,1,src1.rows/8,150,70,0,0);
    //����Բ�任�õ�ͼ��������������Բ��Բ��������Բ�뾶����

    for(size_t a=0;a<circles.size();a++)
    {
        Point center(cvRound(circles[a][0]),cvRound(circles[a][1]));//�õ�Բ���������

        int radius=cvRound(circles[a][2]);//�õ�������Բ�뾶��ֵ

        circle(src2,center,3,Scalar(23,222,155),-1,8,0);//�������ݻ���ʵ��Բ��

        circle(src2,center,radius,Scalar(255,23,178),3,8,0);//�������ݣ�Բ����뾶����ԭͼ�л���Բ��
    }
    src2.copyTo(res1);

}
