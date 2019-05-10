#include"findcontour.h"
#include<QTime>


//���캯��
Findcontour::Findcontour()
   :thresh(70),
    max_thresh(255),
    rng(12345)
{

}
//��ͼƬ���б����ģ������Ӷ�Ѱ�ұ�Ե
void Findcontour::unclearandgray(Mat &src,Mat &contours,Mat &con)
{

    cvtColor(src,src_gray,CV_BGR2GRAY);//���
    blur(src_gray,src_gray,Size(5,5));//ģ������


    this->findcontours(contours);//���û�ȡ�߽纯��
    this->findconvexhull(con);//���û�ȡ͹������
    this->getRec_Circleinformation(src);//���û�ȡԲ�ο�����ο�ĺ���
}



//ͨ����Եʹ��findContours���������߽�
void Findcontour::findcontours(Mat &contour)
{
    Mat canny_output;
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;

    //Ѱ�ұ�Ե
    Canny(src_gray,canny_output,thresh,thresh*2,3);

    //Ѱ�ұ߽�
    findContours(canny_output,contours,hierarchy,CV_RETR_TREE,CV_CHAIN_APPROX_SIMPLE,Point(0,0));

    ///�γɱ߽�
    Mat drawing=Mat::zeros(canny_output.size(),CV_8UC3);//��ʼ��mat����洢�߽�

    for(int i=0;i<contours.size();i++)
    {
        Scalar color=Scalar(23,200,23);
        drawContours(drawing ,contours,i,color,2,8,hierarchy,2,Point());

    }
    drawing.copyTo(contour);
}



//ͨ�������Ķ�λͼ��ı߽����convexHull����Ѱ�ұ߽��е�͹������߽�һ���ӡ����
void Findcontour::findconvexhull(Mat &con)
{
    Mat threshold_output;
    vector<vector<Point> > contours1;
    vector<Vec4i> hierarchy1;

    //�ѻ�ɫͼ��ת��Ϊ�ڰ׶�λͼ��
    threshold(src_gray,threshold_output,thresh,255,THRESH_BINARY);

    //Ѱ�Ҷ�λͼ��ı߽�
    findContours(threshold_output,contours1,hierarchy1,CV_RETR_TREE,CV_CHAIN_APPROX_SIMPLE,Point(0,0));

    //Ѱ�ұ߽��е�͹�����洢��һ���µ�hull��
    vector<vector<Point> > hull(contours1.size());
    for(int i=0;i<contours1.size();i++)
    {
        convexHull(Mat(contours1[i]),hull[i],false);//�ú�������Ѱ�ұ߽��е�͹��
    }


    Mat drawing=Mat::zeros(threshold_output.size(),CV_8UC3);//��ʼ��һ��mat�������ڴ洢͹��

    for(int i=0;i<contours1.size();i++)
    {
        //�趨�����ɫ��Χ��155��255
        Scalar color=Scalar(244,23,23);

        //�γɱ߽�ͼ��
        drawContours(drawing ,contours1,i,color,1,8,vector<Vec4i>(),0,Point());

        //�γ�͹��ͼ�񣨿�����������һ��
        drawContours(drawing ,hull,i,color,1,8,vector<Vec4i>(),0,Point());

    }
    drawing.copyTo(con);


}



//ͨ����ֵͼ��ı߽�Ķ���ν���ͼ��Ѱ�Ұ��������С���ο���Բ�ο����Ϣ
void Findcontour::getRec_Circleinformation(Mat &src)
{
    Mat threshold_output1;
    vector<vector<Point> > contours2;//���ڴ洢�߽���Ϣ
    vector<Vec4i> hierarchy2;


    threshold(src_gray,threshold_output1,150,200,THRESH_BINARY);
    //threshΪ��ֵ����ɫ�ص�ĻҶ�ֵ�������߱��趨Ϊ200������Ϊ��ɫ
    //src_grayΪ����Ļ�ɫͼ��threshold_output1Ϊ�����ֵͼ��



    findContours(threshold_output1,contours2,hierarchy2,CV_RETR_TREE,CV_CHAIN_APPROX_SIMPLE,Point(0,0));
    //Ѱ�Ҷ�ֵͼ��ı߽�

    vector<vector<Point> > contours_poly(contours2.size());//�洢�߽���ƺ������


    vector<Rect> boundRect(contours2.size());//�洢���α߽���Ϣ


    vector<Point2f> center(contours2.size());//�洢Բ��λ��

    vector<float> radius(contours2.size());//�洢Բ�뾶

    for(int i=0;i<contours2.size();i++)
    {
        approxPolyDP(Mat(contours2[i]),contours_poly[i],5,true);

        boundRect[i]=boundingRect(Mat(contours_poly[i]));
        //���㲢���ذ�Χ�����㼯����С����

        minEnclosingCircle(contours_poly[i],center[i],radius[i]);
        //���㲢���ذ�Χ�����㼯����СԲ�μ���뾶
    }

    for(int i=0;i<contours2.size();i++)//contours.size������ʾ�߽����
    {
        Scalar color1=Scalar(23,244,244),color=Scalar(244,244,23);

        //����Բ��
        circle(src,center[i],(int)radius[i],color1,4,8,0);
        //���ƾ���
        rectangle(src,boundRect[i].tl(),boundRect[i].br(),color,2,4,0);

    }
    imshow("findcontours",src);

}
void Findcontour::tail2(Mat &srcc,Mat &back)
{
    Mat threshold_output1;
    vector<vector<Point> > contours2;//���ڴ洢�߽���Ϣ
    vector<Vec4i> hierarchy2;

//     Canny(back,back,thresh,thresh*2,3);
     blur(back,back,Size(5,5));
//     GaussianBlur(back,back,Size(5,5),2,2);//ʹ�ø�˹��ʽ�����˲�����

    threshold(back,threshold_output1,235,245,THRESH_BINARY);



    findContours(threshold_output1,contours2,hierarchy2,CV_RETR_TREE,CV_CHAIN_APPROX_SIMPLE,Point(0,0));
    //Ѱ�Ҷ�ֵͼ��ı߽�

    vector<vector<Point> > contours_poly(contours2.size());//�洢�߽���ƺ������


    vector<Rect> boundRect(contours2.size());//�洢���α߽���Ϣ

    for(int i=0;i<contours2.size();i++)
    {
        approxPolyDP(Mat(contours2[i]),contours_poly[i],5,true);
        boundRect[i]=boundingRect(Mat(contours_poly[i]));
        //���㲢���ذ�Χ�����㼯����С����

    }
    int a=0,b=0;
    for(int i=0;i<contours2.size();i++)//contours.size������ʾ�߽����
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



