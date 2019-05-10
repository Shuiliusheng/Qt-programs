#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<string.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),flag(0),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::data()
{
    Mat src=imread("f://1.jpg");
    pl=src.cols;//x
    pw=src.rows;//y
    QString x1;
    x1=ui->xmax->text();
    xmax=x1.toDouble();
    QString x2;
    x2=ui->xmin->text();
    xmin=x2.toDouble();
    QString y1;
    y1=ui->ymax->text();
    ymax=y1.toDouble();
    QString y2;
    y2=ui->ymin->text();
    ymin=y2.toDouble();
}

void MainWindow::getcenter()
{
    if(xmin>=0)
    {
        bx=(pl-10)/xmax;
        cx=10;
    }
    else if(xmax<=0)
    {
        bx=(pl-10)/(-1*xmin);
        cx=pl-10;
    }
    else
    {
        bx=pl/(xmax-xmin);
        cx=(int)(bx*(-1)*xmin);
    }
    if(ymin>=0)
    {
        by=(pw-10)/ymax;
        cy=pw-10;
    }
    else if(ymax<=0)
    {
        by=(pw-10)/(-1*ymin);
        cy=10;
    }
    else
    {
        by=pw/(ymax-ymin);
        cy=(int)(by*ymax);
    }
}
void MainWindow::drawline(Mat &src)
{
    Point x1(0,cy),x2(pl,cy);
    Point y1(cx,0),y2(cx,pw);
    line(src,x1,x2,Scalar(255,0,0),3,8,0);
    line(src,y1,y2,Scalar(0,255,0),3,8,0);
}

void MainWindow::getxy(int &x, int &y)
{
    x=x+cx;
    y=cy-y;
}
void MainWindow::draw(Mat &src)
{
    QString name;
    name=ui->filename->text();
    QByteArray ba = name.toLatin1();
    char *str=ba.data();

    QString namex;
    namex=ui->xname->text();
    QByteArray bax = namex.toLatin1();
    strx=bax.data();

    QString namey;
    namey=ui->yname->text();
    QByteArray bay = namey.toLatin1();
    stry=bay.data();

    FILE *p;
    p=fopen(str,"rb");
    if(p==NULL)
    {
        QString temp("the file is not exit");
        ui->filename->setText(temp);
    }
    else
    {
        Point n;
        Point l(0,0);
        int i=0;
        int r=0;
        double tempx,tempy;
        while(!feof(p))
        {
            fscanf(p,"%lf,%lf*",&tempx,&tempy);

            n.x=(int)(bx*tempx);
            n.y=(int)(by*tempy);
            if(tempx==1000)
            {
                i=0;
                r+=78;
                r%=255;
                continue;
            }
            getxy(n.x,n.y);;

            if(n.x>pl||n.x<0||n.y>pw||n.y<0)
                continue;
            if(i==0)
            {
                i++;
                l=n;
                continue;
            }
            else
            {
                line(src,n,l,Scalar(0,r,0),2,8,0);
                l=n;
            }
        }
        fclose(p);

        drawtext(src);


        imshow("src",src);
    }
}

void MainWindow::drawtext(Mat &src)
{
    CvFont font,font1;
    cvInitFont(&font,CV_FONT_HERSHEY_SCRIPT_SIMPLEX,0.5,0.5,0,1,8);
    cvInitFont(&font1,CV_FONT_HERSHEY_TRIPLEX,0.8,0.8,0,1,8);
    CvMat cvMat = src;
    cvPutText(&cvMat,strx,cvPoint(pl-40,cy-16),&font1,cvScalar(0,0,0));
    cvPutText(&cvMat,stry,cvPoint(cx+16,20),&font1,cvScalar(0,0,0));
    Point n;
    char str[15];
    double t=0;
    int flag=0;

    if(ymin>=0)
        t=ymax/10.0,flag=1;
    else if(ymax<=0)
        t=ymin/10.0,flag=2;
    else t=(ymax-ymin)/10.0,flag=3;
    for(int i=1;i<=10&&(flag==1||flag==2);i++)
    {
        n.x=0;
        n.y=t*i*by;

        getxy(n.x,n.y);

        sprintf(str,"%0.2lf",t*i);
        line(src,Point(n.x-2,n.y),Point(n.x+3,n.y),Scalar(0,0,255),2,8,0);
        cvPutText(&cvMat,str,cvPoint(n.x+5,n.y),&font,cvScalar(200,0,0));
    }
    if(flag==3)
    {
        int t1,t2;
        t1=ymax/t;
        t2=fabs(ymin)/t;
        for(int i=1;i<=t1;i++)
        {
            n.x=0;
            n.y=t*i*by;
            getxy(n.x,n.y);
            sprintf(str,"%0.2lf",t*i);
            line(src,Point(n.x-2,n.y),Point(n.x+3,n.y),Scalar(0,0,255),2,8,0);
            cvPutText(&cvMat,str,cvPoint(n.x+5,n.y),&font,cvScalar(200,0,0));
        }
        for(int i=1;i<=t2;i++)
        {
            n.x=0;
            n.y=-1*t*i*by;
            getxy(n.x,n.y);
            sprintf(str,"%0.2lf",-1*t*i);
            line(src,Point(n.x-2,n.y),Point(n.x+3,n.y),Scalar(0,0,255),2,8,0);
            cvPutText(&cvMat,str,cvPoint(n.x+5,n.y),&font,cvScalar(200,0,0));
        }
    }

    if(xmin>=0)
        t=xmax/22.0,flag=1;
    else if(xmax<=0)
        t=xmin/22.0,flag=2;
    else t=(xmax-xmin)/22.0,flag=3;
    for(int i=1;i<=22&&(flag==1||flag==2);i++)
    {
        n.x=t*i*bx;
        n.y=0;

        getxy(n.x,n.y);

        sprintf(str,"%0.2lf",t*i);
        line(src,Point(n.x,n.y-2),Point(n.x,n.y+3),Scalar(0,0,255),2,8,0);
        cvPutText(&cvMat,str,cvPoint(n.x,n.y-5),&font,cvScalar(200,0,0));
    }
    if(flag==3)
    {
        int t1,t2;
        t1=xmax/t;
        t2=fabs(xmin)/t;
        for(int i=1;i<=t1;i++)
        {
            n.x=t*i*bx;
            n.y=0;
            getxy(n.x,n.y);
            sprintf(str,"%0.2lf",t*i);
            line(src,Point(n.x,n.y-2),Point(n.x,n.y+3),Scalar(0,0,255),2,8,0);
            cvPutText(&cvMat,str,cvPoint(n.x,n.y-5),&font,cvScalar(200,0,0));
        }
        for(int i=1;i<=t2;i++)
        {
            n.x=-1*t*i*bx;
            n.y=0;
            getxy(n.x,n.y);
            sprintf(str,"%0.2lf",-1*t*i);
            line(src,Point(n.x,n.y-2),Point(n.x,n.y+3),Scalar(0,0,255),2,8,0);
            cvPutText(&cvMat,str,cvPoint(n.x,n.y-5),&font,cvScalar(200,0,0));
        }
    }
}

void MainWindow::draw1(Mat &src)
{
    QString name;
    name=ui->filename->text();
    QByteArray ba = name.toLatin1();
    char *str=ba.data();
    FILE *p;
    p=fopen(str,"rb");
    if(p==NULL)
    {
        QString temp("the file is not exit");
        ui->filename->setText(temp);
    }
    else
    {
        int x=0,y=0;
        double tempx,tempy;
        while(!feof(p))
        {
            fscanf(p,"%lf,%lf*",&tempx,&tempy);
            x=(int)(bx*tempx);
            y=(int)(by*tempy);
            getxy(x,y);

            if(x>pl||x<0||y>pw||y<0)
                continue;
            src.at<Vec3b>(y,x)[0]=0;
            src.at<Vec3b>(y,x)[1]=0;
            src.at<Vec3b>(y,x)[2]=0;
            if(y<pw-10&&x<pl-10)
            {
                src.at<Vec3b>(y+1,x+1)[0]=0;
                src.at<Vec3b>(y+1,x+1)[1]=0;
                src.at<Vec3b>(y+1,x+1)[2]=0;
            }
            if(y>10&&x>10)
            {
                src.at<Vec3b>(y-1,x-1)[0]=0;
                src.at<Vec3b>(y-1,x-1)[1]=0;
                src.at<Vec3b>(y-1,x-1)[2]=0;
            }
            if(x>10)
            {
                src.at<Vec3b>(y,x-1)[0]=0;
                src.at<Vec3b>(y,x-1)[1]=0;
                src.at<Vec3b>(y,x-1)[2]=0;
            }
            if(x<pl-10)
            {
                src.at<Vec3b>(y,x+1)[0]=0;
                src.at<Vec3b>(y,x+1)[1]=0;
                src.at<Vec3b>(y,x+1)[2]=0;
            }
        }
        fclose(p);
        drawtext(src);
        imshow("src",src);
    }

}

void MainWindow::drawfuc()
{

     Mat src=imread("f://1.jpg");
     this->drawline(src);
     if(flag==0)
        draw(src);
     else if(flag==1)
         draw1(src);

}

void MainWindow::on_pushButton_clicked()
{
    this->data();
    this->getcenter();
    this->flag=0;
    this->drawfuc();


}

void MainWindow::on_pushButton_2_clicked()
{
    this->data();
    this->getcenter();
    if(by>bx)
        by=bx;
    else
        bx=by;//0.8415
    this->drawfuc();
}

void MainWindow::on_pushButton_3_clicked()
{
    this->data();
    this->getcenter();
    this->flag=1;
    this->drawfuc();
}
