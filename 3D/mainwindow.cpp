#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),h(0),x(0),Ox(0),Oy(0),bei(1),bei1(1),ctx(0),cty(0),ctz(0),length(140),bei2(1),
    choose(0),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    getdata1();
    getdata();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::getdata()//获取基本的图片数据以用于基本功能的使用
{
    Mat src=imread("source.jpg");
    double a,b;
    int c,d;
    a=src.cols;//行
    c=(int)a;
    b=src.rows;//列
    d=(int)b;
    a=a/1.707;
    b=b-0.707*a;
    this->x=(int)a;
    this->h=(int)b-70;
    this->Oy=h;
    this->Ox=c-this->x;
    O.x=this->Ox;
    O.y=this->Oy;
    q.x=0;
    q.y=d-70;
    w.x=O.x;
    w.y=0;
    e.x=c;
    e.y=O.y;
}
void MainWindow::getdata1()
{
    Mat src=imread("source.jpg");
    double a,b;
    int c,d;
    a=src.cols;//行
    c=(int)a;
    b=src.rows;//列
    d=(int)b;
    x1=(int)(a/1.707);
    h1=d-70;
    Ox1=(int)(0.707*x1);
    Oy1=h1;
    O1.x=Ox1;
    O1.y=Oy1;
    q1.x=0;
    q1.y=(int)(O1.y-0.707*x1);
    w1.x=a;
    w1.y=h1;
    e1.x=O1.x;
    e1.y=0;
}

//绘制坐标轴
void MainWindow::drawline1(Mat &src)//y轴向左
{
    line(src,O1,q1,Scalar(0,0,0),4,8,0);
    line(src,O1,w1,Scalar(0,0,0),4,8,0);
    line(src,O1,e1,Scalar(0,0,0),4,8,0);
}

void MainWindow::drawline(Mat &src)//x轴向右
{
    line(src,O,q,Scalar(0,0,0),4,8,0);
    line(src,O,w,Scalar(0,0,0),4,8,0);
    line(src,O,e,Scalar(0,0,0),4,8,0);

}
void MainWindow::drawline2(Mat &src,Point O,Point q,Point w,Point e)//绘制参数坐标轴
{
    line(src,O,q,Scalar(122,0,0),2,8,0);
    line(src,O,w,Scalar(0,122,0),2,8,0);
    line(src,O,e,Scalar(0,0,122),2,8,0);

}
void MainWindow::drawline3(Mat &src)//绘制旋转单向坐标轴
{
     Point x3,y3,z3;
     rolate(length,0,0,x3.x,x3.y);
     rolate(0,length,0,y3.x,y3.y);
     rolate(0,0,length,z3.x,z3.y);
     drawline2(src,O,x3,y3,z3);
}
void MainWindow::drawline4(Mat &src)//绘制旋转双向坐标轴
{
     Point x3,y3,z3;
     rolate(length,0,0,x3.x,x3.y);
     rolate(0,length,0,y3.x,y3.y);
     rolate(0,0,length,z3.x,z3.y);
     drawline2(src,O,x3,y3,z3);
     rolate(-1*length,0,0,x3.x,x3.y);
     rolate(0,-1*length,0,y3.x,y3.y);
     rolate(0,0,-1*length,z3.x,z3.y);
     drawline2(src,O,x3,y3,z3);
}

//坐标变换
int MainWindow::calZ(int r, int g, int b)//根据灰度，获取高度值，用于result
{
    double temp;
    int Z;
    temp=(0.3*r + 0.59*g + 0.11*b)/255*h/10*bei;
    Z=(int)temp;
    return Z;
}
int MainWindow::calZ1(int r, int g, int b)//根据灰度，获取高度值，用于result1
{
    double temp;
    int Z;
    temp=(0.3*r + 0.59*g + 0.11*b)/255*(q1.y)/10*bei1;
    Z=(int)temp;
    return Z;
}
int MainWindow::calX(int x2, int y)//根据x,y计算平面的x
{
    double temp;
    int temp1;
    temp=y*0.707;
    temp1=this->Ox+x2-(int)temp;
    return temp1;
}
int MainWindow::calX1(int x2, int y)//根据x,y计算平面的x1
{
    double temp;
    int temp1;
    temp=y*0.707;
    temp1=this->Ox1+x2-(int)temp;
    return temp1;
}
int MainWindow::calY(int y,int z)
{
    int temp;
    temp=(int)(y*0.707)+(this->h)-z;
    return temp;
}
int MainWindow::calY1(int y,int z)
{
    int temp;
    temp=(this->h1)-(int)(y*0.707)-z;
    return temp;
}
void MainWindow::rolate(int xi, int yi, int zi,int &X0,int &Y0)//计算旋转坐标，并得到平面对应点
{
    double x,y,z;
    double ct=(double)ctx/180*3.14;
    double ct1=(double)cty/180*3.14;
    double ct2=(double)ctz/180*3.14;

    y=yi*cos(ct)+zi*sin(ct);//x change
    z=-1*yi*sin(ct)+zi*cos(ct);

    x=xi*cos(ct1)-z*sin(ct1);//y change
    z=xi*sin(ct1)+z*cos(ct1);

    x=x*cos(ct2)-y*sin(ct2);//z change
    y=x*sin(ct2)+y*cos(ct2);

    xi=(int)x;
    yi=(int)y;
    zi=(int)z;

    X0=calX(xi,yi);//化为二维坐标
    Y0=calY(yi,zi);
}
void MainWindow::rolate1(int &xi, int &yi, int &zi)//计算旋转坐标
{
    double x,y,z;
    double ct=(double)ctx/180*3.14;
    double ct1=(double)cty/180*3.14;
    double ct2=(double)ctz/180*3.14;

    y=yi*cos(ct)+zi*sin(ct);//x change
    z=-1*yi*sin(ct)+zi*cos(ct);

    x=xi*cos(ct1)-z*sin(ct1);//y change
    z=xi*sin(ct1)+z*cos(ct1);

    x=x*cos(ct2)-y*sin(ct2);//z change
    y=x*sin(ct2)+y*cos(ct2);

    xi=(int)x;
    yi=(int)y;
    zi=(int)z;
}

//线性插值，补全图像
void MainWindow::insertcol(Mat &src)
{
    int x1,y1;
    int r1=255,g1=255,b1=255;
    x1=src.cols;
    y1=src.rows;
    for(int n=0;n<x1;n++)
        for(int m=0;m<y1;m++)
        {
            int r,g,b;
            b=src.at<Vec3b>(m,n)[0];
            g=src.at<Vec3b>(m,n)[1];
            r=src.at<Vec3b>(m,n)[2];
            if(b>=203&&g>203&&r>203)
            {
                src.at<Vec3b>(m,n)[0]=b1;
                src.at<Vec3b>(m,n)[1]=g1;
                src.at<Vec3b>(m,n)[2]=r1;
            }
            b1=b;
            r1=r;
            g1=g;
        }
}

void MainWindow::insertcol1(Mat &src)
{
    int x1,y1;
    x1=src.cols;
    y1=src.rows;
    for(int n=0;n<x1;n++)
        for(int m=y1-1;m>0;m--)
        {
            int r,g,b;
            b=src.at<Vec3b>(m,n)[0];
            g=src.at<Vec3b>(m,n)[1];
            r=src.at<Vec3b>(m,n)[2];
            if(b>=253&&g>253&&r>253&&m<y1-1)
            {
                int b1,g1,r1;
                b1=src.at<Vec3b>(m-1,n)[0];
                g1=src.at<Vec3b>(m-1,n)[1];
                r1=src.at<Vec3b>(m-1,n)[2];
                src.at<Vec3b>(m,n)[0]=b1;
                src.at<Vec3b>(m,n)[1]=g1;
                src.at<Vec3b>(m,n)[2]=r1;
            }
        }
}

void MainWindow::insertrow(Mat &src)
{
    int x1,y1;
    int r1=255,g1=255,b1=255;
    x1=src.cols;
    y1=src.rows;
    for(int m=0;m<y1;m++)
        for(int n=0;n<x1;n++)
        {
            int r,g,b;
            b=src.at<Vec3b>(m,n)[0];
            g=src.at<Vec3b>(m,n)[1];
            r=src.at<Vec3b>(m,n)[2];
            if(b>=203&&g>203&&r>200)
            {
                src.at<Vec3b>(m,n)[0]=b1;
                src.at<Vec3b>(m,n)[1]=g1;
                src.at<Vec3b>(m,n)[2]=r1;
            }
            b1=b;
            r1=r;
            g1=g;
        }
}

//绘制实际图片，x轴向右，灰度代表高度
void MainWindow::result()
{
    Mat srcgray;
    srcgray=imread("targetp.jpg");
    int a=srcgray.cols;
    int b=srcgray.rows;
    if(a<x)
        x=a;
    if(b<x)
        x=b;
    Mat src1=imread("source.jpg");
    Mat src2=imread("source1.jpg");

    for(int n=0;n<this->x;n++)
        for(int m=0;m<this->x;m++)
        {
            int r,g,b;
            b=srcgray.at<Vec3b>(n,m)[0];
            g=srcgray.at<Vec3b>(n,m)[1];
            r=srcgray.at<Vec3b>(n,m)[2];
            int Z=calZ(r,g,b);
            int x=calX(m,n);
            int y=calY(n,Z);
            src1.at<Vec3b>(y,x)[0]=b;
            src1.at<Vec3b>(y,x)[1]=g;
            src1.at<Vec3b>(y,x)[2]=r;
        }
    for(int n=0;n<this->x;n++)
        for(int m=0;m<this->x;m++)
        {
            int r,g,b;
            b=srcgray.at<Vec3b>(n,m)[0];
            g=srcgray.at<Vec3b>(n,m)[1];
            r=srcgray.at<Vec3b>(n,m)[2];
            int Z=0;
            int x=calX(m,n);
            int y=calY(n,Z);
            src2.at<Vec3b>(y,x)[0]=b;
            src2.at<Vec3b>(y,x)[1]=g;
            src2.at<Vec3b>(y,x)[2]=r;
        }
    drawline(src2);
    imshow("target",src2);
    if(bei<0.5)
    {
        this->insertcol(src1);
        this->insertrow(src1);
    }
    else if(bei>2.0)
    {
        this->insertcol(src1);
        this->insertrow(src1);
        this->insertcol(src1);
        this->insertrow(src1);
        this->insertcol(src1);
        this->insertrow(src1);
        this->insertcol(src1);
        this->insertrow(src1);
        this->insertcol(src1);
        this->insertrow(src1);
    }
    else
    {
        this->insertcol(src1);
        this->insertrow(src1);
        this->insertcol(src1);
        this->insertrow(src1);
    }
    this->drawline(src1);
    imshow("result",src1);
}

//绘制图片，y轴向左，灰度代表高度
void MainWindow::result1()
{
    Mat srcgray=imread("targetp.jpg");
    Mat src1=imread("source2.jpg");
    Mat src2=imread("source3.jpg");
    int a=srcgray.cols;
    int b=srcgray.rows;
    if(a<x1)
        x1=a;
    if(b<x1)
        x1=b;
    for(int n=0;n<x1;n++)
        for(int m=0;m<x1;m++)
        {
            int r,g,b;
            b=srcgray.at<Vec3b>(n,m)[0];
            g=srcgray.at<Vec3b>(n,m)[1];
            r=srcgray.at<Vec3b>(n,m)[2];
            int Z=calZ1(r,g,b);
            int x=calX1(m,n);
            int y=calY1(n,Z);
            src1.at<Vec3b>(y,x)[0]=b;
            src1.at<Vec3b>(y,x)[1]=g;
            src1.at<Vec3b>(y,x)[2]=r;
        }
    for(int n=0;n<x1;n++)
        for(int m=0;m<x1;m++)
        {
            int r,g,b;
            b=srcgray.at<Vec3b>(n,m)[0];
            g=srcgray.at<Vec3b>(n,m)[1];
            r=srcgray.at<Vec3b>(n,m)[2];
            int Z=0;
            int x=calX1(m,n);
            int y=calY1(n,Z);
            src2.at<Vec3b>(y,x)[0]=b;
            src2.at<Vec3b>(y,x)[1]=g;
            src2.at<Vec3b>(y,x)[2]=r;
        }
    drawline1(src2);
    imshow("target1",src2);
    this->insertcol(src1);
    this->insertrow(src1);
    this->insertcol(src1);
    this->insertrow(src1);
    this->drawline1(src1);
    imshow("result1",src1);
}

//绘制单方向的函数图像,不旋转
void MainWindow::drawfuction()
{
    Mat src=imread("source4.jpg");
    drawline(src);
    for(int n=0;n<x;n++)
        for(int m=0;m<x;m++)
        {
            double temp;
            int flag=0;
            fuction(n,m,temp,flag);
            if(temp>=h)
                continue;
            double temp1=temp/h*255;
            int color=(int)temp1;
            int x1=calX(n,m);
            int y=calY(m,(int)temp);
            src.at<Vec3b>(y,x1)[0]=color;
            src.at<Vec3b>(y,x1)[1]=color;
            src.at<Vec3b>(y,x1)[2]=color;
        }
    this->insertcol(src);
    this->insertrow(src);
    this->insertcol(src);
    this->insertrow(src);
    imshow("fuction",src);
}

//绘制旋转的实际图像
void MainWindow::result2()
{
    Mat srcgray;
    srcgray=imread("targetp.jpg");
    int a=srcgray.cols;
    int b=srcgray.rows;
    if(a<length)
        length=a;
    if(b<length)
        length=b;
    Mat src1=imread("source.jpg");
    Mat src2=imread("source1.jpg");

    for(int n=0;n<this->length;n++)
        for(int m=0;m<this->length;m++)
        {
            int r,g,b;
            b=srcgray.at<Vec3b>(n,m)[0];
            g=srcgray.at<Vec3b>(n,m)[1];
            r=srcgray.at<Vec3b>(n,m)[2];
            int tx,ty,tz;
            int Z=calZ(r,g,b);
            tx=m,ty=n,tz=Z;
            rolate1(tx,ty,tz);
            int x=calX(tx,ty);
            int y=calY(ty,tz);
            src1.at<Vec3b>(y,x)[0]=b;
            src1.at<Vec3b>(y,x)[1]=g;
            src1.at<Vec3b>(y,x)[2]=r;
        }
    if(bei<0.5)
    {
        this->insertcol(src1);
        this->insertrow(src1);
    }
    else if(bei>2.0)
    {
        this->insertcol(src1);
        this->insertrow(src1);
        this->insertcol(src1);
        this->insertrow(src1);
        this->insertcol(src1);
        this->insertrow(src1);
        this->insertcol(src1);
        this->insertrow(src1);
        this->insertcol(src1);
        this->insertrow(src1);
    }
    else
    {
        this->insertcol(src1);
        this->insertrow(src1);
        this->insertcol(src1);
        this->insertrow(src1);
        this->insertcol(src1);
        this->insertrow(src1);
    }
    this->drawline3(src1);
    imshow("result",src1);
}

//绘制旋转的函数图像
void MainWindow::drawfuction1()
{
    Mat src=imread("source4.jpg");
    drawline4(src);
    for(int n=length*-1;n<length;n++)
        for(int m=length*-1;m<length;m++)
        {
            double temp;
            int flag=0;
            fuction(n,m,temp,flag);
            if(flag==1)
                continue;
            double temp1=temp/length*255;
            int color=(int)temp1;
            int tx,ty,tz;
            int x1,y;
            tx=n,ty=m,tz=(int)temp;
            rolate(tx,ty,tz,x1,y);
            src.at<Vec3b>(y,x1)[0]=color;
            src.at<Vec3b>(y,x1)[1]=color;
            src.at<Vec3b>(y,x1)[2]=color;
        }
    this->insertcol(src);
    this->insertrow(src);
    this->insertcol(src);
    this->insertrow(src);
    this->insertcol(src);
    this->insertrow(src);
    this->insertcol(src);
    this->insertrow(src);
    imshow("fuction",src);
}
void MainWindow::fuction(int x,int y,double &z,int &flag)//函数
{
    int tx=bei2*x,ty=bei2*y;
    z=sqrt(tx*tx+ty*ty);
    z=z*bei;
    if(z>length-15)
        flag=1;

}

//按钮的消息响应函数
void MainWindow::on_add_clicked()
{
    if(bei>4)
        return;
    else
        bei+=0.1;
    switch(choose)
    {
        case 0:this->result();break;
        case 1:this->result1();break;
        case 2:this->drawfuction();break;
        case 3:this->result2();break;
        case 4:this->drawfuction1();
    }
}

void MainWindow::on_cut_clicked()
{
    if(bei<=0.01)
        return;
    else
    {
        if(bei>0.1)
            bei-=0.1;
        else
            bei-=0.01;
    }
    switch(choose)
    {
        case 0:this->result();break;
        case 1:this->result1();break;
        case 2:this->drawfuction();break;
        case 3:this->result2();break;
        case 4:this->drawfuction1();
    }
}

void MainWindow::on_add1_clicked()
{
    if(bei1>3.5)
        return;
    else
        bei1+=0.1;
    switch(choose)
    {
        case 0:this->result();break;
        case 1:this->result1();break;
        case 2:this->drawfuction();break;
        case 3:this->result2();break;
        case 4:this->drawfuction1();
    }
}

void MainWindow::on_cut2_clicked()
{
    if(bei1<=0.01)
        return;
    else
    {
        if(bei1>0.11)
            bei1-=0.1;
        else
            bei1-=0.01;
    }
    switch(choose)
    {
        case 0:this->result();break;
        case 1:this->result1();break;
        case 2:this->drawfuction();break;
        case 3:this->result2();break;
        case 4:this->drawfuction1();
    }

}


void MainWindow::on_X1_clicked()
{
    ctx-=10;
    switch(choose)
    {
        case 0:this->result();break;
        case 1:this->result1();break;
        case 2:this->drawfuction();break;
        case 3:this->result2();break;
        case 4:this->drawfuction1();
    }
}

void MainWindow::on_x2_clicked()
{
    ctx+=10;
    switch(choose)
    {
        case 0:this->result();break;
        case 1:this->result1();break;
        case 2:this->drawfuction();break;
        case 3:this->result2();break;
        case 4:this->drawfuction1();
    }
}

void MainWindow::on_y1_clicked()
{
    cty-=10;
    switch(choose)
    {
        case 0:this->result();break;
        case 1:this->result1();break;
        case 2:this->drawfuction();break;
        case 3:this->result2();break;
        case 4:this->drawfuction1();
    }
}

void MainWindow::on_y2_clicked()
{
    cty+=10;
    switch(choose)
    {
        case 0:this->result();break;
        case 1:this->result1();break;
        case 2:this->drawfuction();break;
        case 3:this->result2();break;
        case 4:this->drawfuction1();
    }
}

void MainWindow::on_z1_clicked()
{
    ctz-=10;
    switch(choose)
    {
        case 0:this->result();break;
        case 1:this->result1();break;
        case 2:this->drawfuction();break;
        case 3:this->result2();break;
        case 4:this->drawfuction1();
    }
}

void MainWindow::on_z2_clicked()
{
    ctz+=10;
    switch(choose)
    {
        case 0:this->result();break;
        case 1:this->result1();break;
        case 2:this->drawfuction();break;
        case 3:this->result2();break;
        case 4:this->drawfuction1();
    }
}

void MainWindow::on_reset_clicked()
{
    ctz=0;
    ctx=0;
    cty=0;
    bei=1;
    bei1=1;
    bei2=1;
    length=140;
    switch(choose)
    {
        case 0:this->result();break;
        case 1:this->result1();break;
        case 2:this->drawfuction();break;
        case 3:this->result2();break;
        case 4:this->drawfuction1();
    }
}

void MainWindow::on_lengthadd_clicked()
{
    this->length+=5;
    switch(choose)
    {
        case 0:this->result();break;
        case 1:this->result1();break;
        case 2:this->drawfuction();break;
        case 3:this->result2();break;
        case 4:this->drawfuction1();
    }
}

void MainWindow::on_lengthcut_clicked()
{
    this->length-=5;
    switch(choose)
    {
        case 0:this->result();break;
        case 1:this->result1();break;
        case 2:this->drawfuction();break;
        case 3:this->result2();break;
        case 4:this->drawfuction1();
    }
}



void MainWindow::on_pushButton_clicked()
{
    if(bei2<4)
        this->bei2+=0.1;
    switch(choose)
    {
        case 0:this->result();break;
        case 1:this->result1();break;
        case 2:this->drawfuction();break;
        case 3:this->result2();break;
        case 4:this->drawfuction1();
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    if(bei2>0.1)
        this->bei2-=0.1;
    switch(choose)
    {
        case 0:this->result();break;
        case 1:this->result1();break;
        case 2:this->drawfuction();break;
        case 3:this->result2();break;
        case 4:this->drawfuction1();
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    destroyAllWindows();
    result();
    choose=0;
}

void MainWindow::on_pushButton_4_clicked()
{
    destroyAllWindows();
    result1();
    choose=1;
}

void MainWindow::on_pushButton_5_clicked()
{
    destroyAllWindows();
    drawfuction();
    choose=2;
}

void MainWindow::on_pushButton_6_clicked()
{
    destroyAllWindows();
    result2();
    choose=3;
}

void MainWindow::on_pushButton_8_clicked()
{
    destroyAllWindows();
    drawfuction1();
    choose=4;
}
