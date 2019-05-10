#include "widget.h"
#include "outedge.cpp"
//#include "backpro.cpp"
#include<QTime>
#include <QCoreApplication>


Widget::Widget(QWidget *parent)
    :QWidget(parent),out(),back(),a(1),t(0)
{
    window();
    connect(cramer,SIGNAL(clicked()),this,SLOT(camerss()));
    connect(stop,SIGNAL(clicked()),this,SLOT(stopc()));
    connect(task1,SIGNAL(clicked()),this,SLOT(task1c()));
    connect(task2,SIGNAL(clicked()),this,SLOT(task2c()));
    connect(task3,SIGNAL(clicked()),this,SLOT(task3c()));
    connect(task4,SIGNAL(clicked()),this,SLOT(task4c()));
    connect(tail,SIGNAL(clicked()),this,SLOT(taill()));
}

Widget::~Widget()
{
    
}
void Widget::window()
{
    name=new QLabel();
    name->setFrameStyle(QFrame::WinPanel|QFrame::Raised);
    wind=new QLabel();
    wind->setFrameStyle(QFrame::WinPanel|QFrame::Raised);
    exp=new QLabel(tr("explane"));
    exp->setFrameStyle(QFrame::Panel|QFrame::Sunken);
    task1=new QPushButton(tr("task1"));
    task2=new QPushButton(tr("task2"));
    task3=new QPushButton(tr("task3"));
    task4=new QPushButton(tr("task4"));
    tail=new QPushButton(tr("tail target"));
    cramer=new QPushButton(tr("cramer"));
    stop=new QPushButton(tr("stop"));
    jpg=new QLineEdit();

    QGridLayout *mainlayout=new QGridLayout;
    mainlayout->addWidget(name,0,0,9,4);
    mainlayout->addWidget(wind,0,4,9,4);
    mainlayout->addWidget(exp,9,0,1,8);
    mainlayout->addWidget(task1,10,0,0);
    mainlayout->addWidget(task2,10,2,0);
    mainlayout->addWidget(task3,10,4,0);
    mainlayout->addWidget(task4,10,6,0);
    mainlayout->addWidget(cramer,11,0,1,1);
    mainlayout->addWidget(stop,11,2,1,1);
    mainlayout->addWidget(tail,11,4,1,1);
    mainlayout->addWidget(jpg,11,5,1,2);
    setLayout(mainlayout);
    setWindowTitle(tr("task:"));
}
void Widget::stopc()
{
    this->a=0;
    exp->setText("**�ر�����ͷ**\n**������԰�����������ر�**");
}
void Widget::task1c()
{
    this->t=1;
    exp->setText("**��ͼΪ��Ե����õ���ͼƬ**\n**�밴stop����**\n**�����������������**");
}
void Widget::task2c()
{
    this->t=2;
    exp->setText("**��ͼ��ʾ��ͼ���Լ�Ϊģ�������ֱ��ͼ��������ķ���ͶӰ**\n**��ͼΪ����ֱ��ͼ������**\n**�밴stop��ֹͣ**");
}
void Widget::task3c()
{
    this->t=3;
    exp->setText("**��ͼΪͼ����findcontoursѰ�ҵı߽�**\n��ͼΪͼ��Ѱ�ҵ���͹��**\n**���������ͼƬΪͼ�а��������߽�ľ�����Բ��***�밴stop������");
}
void Widget::task4c()
{
    this->t=4;
    exp->setText("**��ͼΪ����Բ�任������ͼ�е�Բ�α߽�**\n**��ͼΪ����任������ͼ�е��߶Σ����������յ�**\n**�밴stop��ֹͣ");
}
void Widget::taill()
{
    this->t=5;
    exp->setText("**���ڷ���������Ҫ���Ŀ����ɫ�Ľ�ͼ����**");
}

void Widget::camerss()
{
    exp->setText("**������ͷ**");
    VideoCapture cap(0);
    if(!cap.isOpened())
    {
        cout << "23"<<endl;
        return ;
    }
    Mat frame;
//    QImage *img;
    bool stop = false;
    while(!stop)
    {

        cap>>frame;
        imshow("1111",frame);
        if(this->a==0)
           break;
        switch(this->t)
        {
             case 1:
             {
                task11(frame);
                break;
             }
             case 2:
            {
                Mat backpro;
                Mat dst;
                task22(frame,backpro,dst);
                break;
            }
             case 3:
            {
                task33(frame);
                break;
            }
             case 4:
            {
                task44(frame);
                break;
            }
            case 5:
            {
                tail1(frame);
                break;
            }
        }
        if(waitKey(30) >=0)
            stop = true;
    }
    cvDestroyAllWindows();
    this->a=1;
    this->t=0;

}

void Widget::task11(Mat &mat)
{
    Mat dst;
    this->out.outedge(mat,dst);
    cvtColor(dst, dst, CV_BGR2RGB);

    QTime time;       //�ӳ�һ��ʱ����д�ӡ
    while(time.elapsed() <1)
        QCoreApplication::processEvents();

    QImage *img1=new QImage((const unsigned char*)dst.data,dst.cols, dst.rows, dst.step, QImage::Format_RGB888);
    name->setAutoFillBackground(true);
    name->setScaledContents(true);
    name->setPixmap(QPixmap::fromImage(*img1));
}


void Widget::task22(Mat& mat,Mat &backpro,Mat &dst)
{
    this->back.change1(mat,backpro,dst);

    QTime time;       //�ӳ�һ��ʱ����д�ӡ
    while(time.elapsed() <1)
        QCoreApplication::processEvents();

    name->setAutoFillBackground(true);
    name->setScaledContents(true);
    name->setPixmap(QPixmap::fromImage(this->back.imag));

    cvtColor(dst, dst, CV_BGR2RGB);
    QTime time1;       //�ӳ�һ��ʱ����д�ӡ
    while(time1.elapsed() <1)
        QCoreApplication::processEvents();
    QImage *img1=new QImage((const unsigned char*)dst.data,dst.cols, dst.rows, dst.step, QImage::Format_RGB888);
    wind->setAutoFillBackground(true);
    wind->setScaledContents(true);
    wind->setPixmap(QPixmap::fromImage(*img1));
}


void Widget::task33(Mat &src)
{
    Mat contours;
    Mat con;
    this->find.unclearandgray(src,contours,con);

    cvtColor(contours,contours, CV_BGR2RGB);
    QTime time1;       //�ӳ�һ��ʱ����д�ӡ
    while(time1.elapsed() < 1)
        QCoreApplication::processEvents();
    QImage *img1=new QImage((const unsigned char*)contours.data,contours.cols, contours.rows, contours.step, QImage::Format_RGB888);
    wind->setAutoFillBackground(true);
    wind->setScaledContents(true);
    wind->setPixmap(QPixmap::fromImage(*img1));



    cvtColor(con,con, CV_BGR2RGB);
    QTime time;       //�ӳ�һ��ʱ����д�ӡ
    while(time.elapsed() < 10)
        QCoreApplication::processEvents();
    QImage *img=new QImage((const unsigned char*)con.data,con.cols, con.rows, con.step, QImage::Format_RGB888);
    name->setAutoFillBackground(true);
    name->setScaledContents(true);
    name->setPixmap(QPixmap::fromImage(*img));
}
void Widget::task44(Mat &src)
{
    Mat res;
    Mat res1;
    this->hough.start(src,res,res1);
    cvtColor(res,res, CV_BGR2RGB);
    QImage *img1=new QImage((const unsigned char*)res.data,res.cols, res.rows, res.step, QImage::Format_RGB888);
    wind->setAutoFillBackground(true);
    wind->setScaledContents(true);
    wind->setPixmap(QPixmap::fromImage(*img1));


    cvtColor(res1,res1, CV_BGR2RGB);
    QImage *img=new QImage((const unsigned char*)res1.data,res1.cols, res1.rows, res1.step, QImage::Format_RGB888);
    name->setAutoFillBackground(true);
    name->setScaledContents(true);
    name->setPixmap(QPixmap::fromImage(*img));
}

void Widget::tail1(Mat &src)
{
    Mat src1;
    Mat back;
    QString s1=jpg->text();
    string s2=s1.toStdString();
    const char *ch=s2.c_str();
    src1=imread(ch,1);
    if(!src1.data)
        this->t=0;
    else
    {
        this->back.change2(src1,src,back);
        this->find.tail2(src,back);
    }

}
