#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<stdio.h>
#include<iostream>
#include<ctime>
using namespace std;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    number=7;
    times[0]=0;times[1]=0;times[2]=0;
    x0=7;
    y0=7;
    init();
    setsrc1();
    showbtn();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::copy(int ex,int ey,int sx,int sy)
{
    for(int n=0;n<x0;n++)
        for(int m=0;m<y0;m++)
            source1[n][m]=source[n][m];
    source1[ex][ey]=0;
    source1[sx][sy]=1;
}

void MainWindow::init()
{
    int n=0,m=0;
    for(n;n<x0;n++)
        for(m;m<y0;m++)
            source[n][m]=12;
    btn[0][0]=(ui->btn1);
    btn[0][1]=(ui->btn2);
    btn[0][2]=(ui->btn3);
    btn[0][3]=(ui->btn4);
    btn[0][4]=(ui->btn04);
    btn[0][5]=(ui->btn05);
    btn[0][6]=(ui->btn06);

    btn[1][0]=(ui->btn5);
    btn[1][1]=(ui->btn6);
    btn[1][2]=(ui->btn7);
    btn[1][3]=(ui->btn8);
    btn[1][4]=(ui->btn141);
    btn[1][5]=(ui->btn151);
    btn[1][6]=(ui->btn161);

    btn[2][0]=(ui->btn9);
    btn[2][1]=(ui->btn10);
    btn[2][2]=(ui->btn11);
    btn[2][3]=(ui->btn12);
    btn[2][4]=(ui->btn24);
    btn[2][5]=(ui->btn25);
    btn[2][6]=(ui->btn26);

    btn[3][0]=(ui->btn13);
    btn[3][1]=(ui->btn14);
    btn[3][2]=(ui->btn15);
    btn[3][3]=(ui->btn16);
    btn[3][4]=(ui->btn34);
    btn[3][5]=(ui->btn35);
    btn[3][6]=(ui->btn36);

    btn[4][0]=(ui->btn40);
    btn[4][1]=(ui->btn41);
    btn[4][2]=(ui->btn42);
    btn[4][3]=(ui->btn43);
    btn[4][4]=(ui->btn44);
    btn[4][5]=(ui->btn45);
    btn[4][6]=(ui->btn46);

    btn[5][0]=(ui->btn50);
    btn[5][1]=(ui->btn51);
    btn[5][2]=(ui->btn52);
    btn[5][3]=(ui->btn53);
    btn[5][4]=(ui->btn54);
    btn[5][5]=(ui->btn55);
    btn[5][6]=(ui->btn56);

    btn[6][0]=(ui->btn60);
    btn[6][1]=(ui->btn61);
    btn[6][2]=(ui->btn62);
    btn[6][3]=(ui->btn63);
    btn[6][4]=(ui->btn64);
    btn[6][5]=(ui->btn65);
    btn[6][6]=(ui->btn66);

}

void MainWindow::setsrc()
{
    int sr[7][7]={
        11,11,12,14,13,11,12,
        13,12,13,11,13,12,13,
        11,14,13,12,11,12,13,
        11,12,13,14,11,11,12,
        12,13,11,13,12,12,11,
        11,14,13,12,11,12,12,
        12,11,12,13,14,13,11
    };
    for(int n=0;n<x0;n++)
        for(int m=0;m<y0;m++)
            source[n][m]=sr[n][m];
}
void MainWindow::setsrc1()
{
    srand(time(0));
    rand();
    int temp=0;
    int temp1=0;
    temp1=rand()%(26-number);
    for(int n=0;n<x0;n++)
        for(int m=0;m<y0;m++)
        {
            temp=rand()%number;
            if(temp==0)
                temp++;
            if(temp+temp1<=22)
                source[n][m]=temp+temp1;
            else
                source[n][m]=22;
        }
}
//加载图片资源，在按钮上显示
void MainWindow::showbtn()
{
    QPixmap *pixmap = NULL;
    pixmap = new QPixmap();
    int n,m;
    for(n=0;n<x0;n++)
        for(m=0;m<y0;m++)
        {
            char str[15];
            sprintf(str,"\src\\s%d.jpg",source[n][m]);//图片资源的位置
            pixmap->load(str);
            btn[n][m]->setIcon(*pixmap);
            btn[n][m]->setIconSize(QSize((int)(pixmap->width()/2),(int)(pixmap->height()/2)));
            btn[n][m]->setFixedSize((int)(pixmap->width()/2),(int)(pixmap->height()/2));
        }
}
//加载消除后的图片资源
void MainWindow::delpicture1(int x1, int y1, int x2, int y2)
{
    char str[15];
    QPixmap *pixmap = NULL;
    pixmap = new QPixmap();
    sprintf(str,"\src\\m%d.jpg",source[x1][y1]);//图片资源的位置
    pixmap->load(str);
    btn[x1][y1]->setIcon(*pixmap);
    btn[x1][y1]->setIconSize(QSize((int)(pixmap->width()/2),(int)(pixmap->height()/2)));
    btn[x1][y1]->setFixedSize((int)(pixmap->width()/2),(int)(pixmap->height()/2));
    btn[x2][y2]->setIcon(*pixmap);
    btn[x2][y2]->setIconSize(QSize((int)(pixmap->width()/2),(int)(pixmap->height()/2)));
    btn[x2][y2]->setFixedSize((int)(pixmap->width()/2),(int)(pixmap->height()/2));

}

void MainWindow::delpicture(int x1, int y1, int x2, int y2)
{
    QPixmap *pixmap = NULL;
    pixmap = new QPixmap();
    pixmap->load("src\\00.jpg");
    btn[x1][y1]->setIcon(*pixmap);
    btn[x1][y1]->setIconSize(QSize((int)(pixmap->width()/2),(int)(pixmap->height()/2)));
    btn[x1][y1]->setFixedSize((int)(pixmap->width()/2),(int)(pixmap->height()/2));
    btn[x2][y2]->setIcon(*pixmap);
    btn[x2][y2]->setIconSize(QSize((int)(pixmap->width()/2),(int)(pixmap->height()/2)));
    btn[x2][y2]->setFixedSize((int)(pixmap->width()/2),(int)(pixmap->height()/2));

}
void MainWindow::charge(int sx, int sy, int ex, int ey, int &flag)
{

    if(sx==ex&&sy==ey)
    {
        flag=1;
        return ;
    }
    if(sx+1<x0&&source1[sx+1][sy]==0)
    {
        source1[sx+1][sy]=1;
        charge(sx+1,sy,ex,ey,flag);
    }
    if(flag==1)
        return;
    if(sx-1>=0&&source1[sx-1][sy]==0)
    {
        source1[sx-1][sy]=1;
        charge(sx-1,sy,ex,ey,flag);
    }
    if(flag==1)
        return;
    if(sy+1<y0&&source1[sx][sy+1]==0)
    {
        source1[sx][sy+1]=1;
        charge(sx,sy+1,ex,ey,flag);
    }
    if(flag==1)
        return;
    if(sy-1>=0&&source1[sx][sy-1]==0)
    {
        source1[sx][sy-1]=1;
        charge(sx,sy-1,ex,ey,flag);
    }
    return ;
}

void MainWindow::btnfuc(int x, int y)
{
    times[0]++;
    if(times[0]==1)
        times[1]=x,times[2]=y;
    else
    {
        if(times[1]==x&&times[2]==y)
            times[0]=0;
        else if(source[times[1]][times[2]]==source[x][y])
        {
            int flag=0;
            copy(times[1],times[2],x,y);
            charge(x,y,times[1],times[2],flag);
            if(flag==1)
            {
                delpicture1(times[1],times[2],x,y);
                source[times[1]][times[2]]=0;
                source[x][y]=0;
            }
        }
        times[0]=0;
    }
}

void MainWindow::on_btn1_clicked()
{
    btnfuc(0,0);
}

void MainWindow::on_btn2_clicked()
{
    btnfuc(0,1);
}

void MainWindow::on_btn3_clicked()
{
    btnfuc(0,2);
}

void MainWindow::on_btn4_clicked()
{
    btnfuc(0,3);
}

void MainWindow::on_btn5_clicked()
{
    btnfuc(1,0);
}

void MainWindow::on_btn6_clicked()
{
    btnfuc(1,1);
}

void MainWindow::on_btn7_clicked()
{
    btnfuc(1,2);
}

void MainWindow::on_btn8_clicked()
{
    btnfuc(1,3);
}

void MainWindow::on_btn9_clicked()
{
    btnfuc(2,0);
}

void MainWindow::on_btn10_clicked()
{
    btnfuc(2,1);
}

void MainWindow::on_btn11_clicked()
{
    btnfuc(2,2);
}

void MainWindow::on_btn12_clicked()
{
    btnfuc(2,3);
}

void MainWindow::on_btn13_clicked()
{
    btnfuc(3,0);
}

void MainWindow::on_btn14_clicked()
{
    btnfuc(3,1);
}

void MainWindow::on_btn15_clicked()
{
    btnfuc(3,2);
}

void MainWindow::on_btn16_clicked()
{
    btnfuc(3,3);
}

void MainWindow::on_btn04_clicked()
{
    btnfuc(0,4);
}

void MainWindow::on_btn05_clicked()
{
    btnfuc(0,5);
}

void MainWindow::on_btn06_clicked()
{
    btnfuc(0,6);
}

void MainWindow::on_btn141_clicked()
{
    btnfuc(1,4);
}

void MainWindow::on_btn151_clicked()
{
    btnfuc(1,5);
}

void MainWindow::on_btn161_clicked()
{
    btnfuc(1,6);
}

void MainWindow::on_btn24_clicked()
{
    btnfuc(2,4);
}

void MainWindow::on_btn25_clicked()
{
    btnfuc(2,5);
}

void MainWindow::on_btn26_clicked()
{
    btnfuc(2,6);
}

void MainWindow::on_btn34_clicked()
{
    btnfuc(3,4);
}

void MainWindow::on_btn35_clicked()
{
    btnfuc(3,5);
}

void MainWindow::on_btn36_clicked()
{
    btnfuc(3,6);
}

void MainWindow::on_btn40_clicked()
{
    btnfuc(4,0);
}

void MainWindow::on_btn41_clicked()
{
    btnfuc(4,1);
}

void MainWindow::on_btn42_clicked()
{
    btnfuc(4,2);
}

void MainWindow::on_btn43_clicked()
{
    btnfuc(4,3);
}

void MainWindow::on_btn44_clicked()
{
    btnfuc(4,4);
}

void MainWindow::on_btn45_clicked()
{
    btnfuc(4,5);
}

void MainWindow::on_btn46_clicked()
{
    btnfuc(4,6);
}

void MainWindow::on_btn50_clicked()
{
    btnfuc(5,0);
}

void MainWindow::on_btn51_clicked()
{
    btnfuc(5,1);
}

void MainWindow::on_btn52_clicked()
{
    btnfuc(5,2);
}

void MainWindow::on_btn53_clicked()
{
    btnfuc(5,3);
}

void MainWindow::on_btn54_clicked()
{
    btnfuc(5,4);
}

void MainWindow::on_btn55_clicked()
{
    btnfuc(5,5);
}

void MainWindow::on_btn56_clicked()
{
    btnfuc(5,6);
}

void MainWindow::on_btn60_clicked()
{
    btnfuc(6,0);
}

void MainWindow::on_btn61_clicked()
{
    btnfuc(6,1);
}

void MainWindow::on_btn62_clicked()
{
    btnfuc(6,2);
}

void MainWindow::on_btn63_clicked()
{
    btnfuc(6,3);
}

void MainWindow::on_btn64_clicked()
{
    btnfuc(6,4);
}

void MainWindow::on_btn65_clicked()
{
    btnfuc(6,5);
}

void MainWindow::on_btn66_clicked()
{
    btnfuc(6,6);
}

void MainWindow::on_cut_clicked()
{
    if(number>7)
    {
        number--;
        times[0]=0;times[1]=0;times[2]=0;
        setsrc1();
        showbtn();
    }
}

void MainWindow::on_add_clicked()
{
    if(number<16)
    {
        number++;
        times[0]=0;times[1]=0;times[2]=0;
        setsrc1();
        showbtn();
    }
}
