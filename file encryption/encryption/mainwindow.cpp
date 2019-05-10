#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<stdio.h>
#include<iostream>
#include<ctime>
#include<string.h>
#include <stdlib.h>
#include<io.h>
using namespace std;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),temp(0),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setplock();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::setplock()//设定程序自身的锁
{
    plock[0]=23;
    plock[1]=45;
    plock[2]=12;
    plock[3]=1;
    plock[4]=56;
    plock[5]=47;
    plock[6]=33;
    plock[7]=31;
    plock[8]=15;
    plock[9]=40;
}

void MainWindow::prolock(char str[],char str1[])//程序上锁
{
    int length=strlen(str);
    int a=0,b=0;
    for(int i=0;i<length;i++)
    {
        if(a>9)
            a%=10;
        int temp=(int)str[i]+plock[a++];
        if(temp>120)
        {
            str1[b++]=(char)(temp-2*plock[a-1]);
            str1[b++]='#';//是减
        }
        else
        {
            str1[b++]=(char)temp;
            str1[b++]='%';//是加
        }
    }
    str1[b]='\0';
}
void MainWindow::prorl(char str[], char str1[])//程序结锁
{
    int length=strlen(str);
    int a=0,b=0;
    for(int i=0;i<length;i+=2)
    {
        if(a>9)
            a%=10;
        char s=str[i];
        char s1=str[i+1];
        if(s1=='#')
        {
            str1[b++]=s+(char)plock[a++];
        }
        else if(s1=='%')
            str1[b++]=s-(char)plock[a++];
    }
    str1[b]='\0';
}
void MainWindow::prorl1(char &str, char str1, int a)//程序解锁
{
    if(a>9)
        a%=10;
    if(str1=='#')
        str=str+(char)plock[a++];
    else if(str1=='%')
        str=str-(char)plock[a++];
}

void MainWindow::llock1(char str[])
{
    int i=0;
    char temp;
    for(i=0;i<30;i+=2)
    {
        temp=str[lock[i]];
        str[lock[i]]=str[lock[i+1]];
        str[lock[i+1]]=temp;
    }
}

void MainWindow::rllock1(char str[])
{
    int i=28;
    char temp;
    for(i=28;i>=0;i-=2)
    {
        temp=str[lock[i]];
        str[lock[i]]=str[lock[i+1]];
        str[lock[i+1]]=temp;
    }
}

void MainWindow::data()//获取数据
{
    QString name;
    name=ui->line1->text();
    QByteArray ba = name.toLatin1();
    char *str=ba.data();
    QString name1;
    name1=ui->line2->text();
    QByteArray ba1 = name1.toLatin1();
    char *str1=ba1.data();
    if(str[1]=='\0'||str[2]=='\0')
    {
        QString temp("at least three");
        ui->line1->setText(temp);
        this->temp=0;
    }
    else if(str1[0]=='\0'||str1[1]=='\0'||str1[2]=='\0')
    {
        QString temp("at least three");
        ui->line2->setText(temp);
        this->temp=0;
    }   
    else
    {
        ////判断是否存在，存在则判断密码是否正确
        int length1=strlen(str);
        int length2=strlen(str1);
        if(length1>30||length2>30)
        {
            QString temp("too long");
            ui->line2->setText(temp);
            this->temp=0;
        }
        FILE *p;
        char s[80]="C:\\Windows\\security\\protected\\";
        strcat(s,str);
        p=fopen(s,"rb");
        if(p!=NULL)//有这个文件存在
        {
            char s=0,s1=0,str3[70];
            for(int i=0;i<20;i++)//获取锁
            {
                fscanf(p,"%c%c",&s,&s1);
                prorl1(s,s1,i);
                lock[i]=(int)s;
            }
            fscanf(p,"%s",str3);
            char temp[40];
            prorl(str3,temp);
            cout <<temp<<endl;
            cout <<str1<<endl;
            if(strcmp(str1,temp)==0)//登陆成功
            {
                QString tempx("success");
                ui->line2->setText(tempx);
                fclose(p);
            }
            if(strcmp(str1,temp)!=0)//登陆失败
            {

                QString tempx("wrong");
                ui->line2->setText(tempx);
                this->temp=0;
                fclose(p);
                return ;
            }
        }
        else
        {
            start(str,str1);//没有这个文件就开始创建
            QString tempx("build success");
            ui->line2->setText(tempx);

        }
    }
}


void MainWindow::start(char str[], char str1[])
{
    srand(time(0));//设定随机数由时间随意产生
    int length1=strlen(str);
    int length2=strlen(str1);

    for(int i=0;i<3;i++)
        lockplace[i]=rand()%length1;//三个来源于名字
    for(int i=3;i<10;i++)
        lockplace[i]=rand()%length2;//七个来源于密码

    for(int i=0;i<10;i++)
        lock[i]=rand()%100;//十个来源于随机
    for(int i=10;i<13;i++)
        lock[i]=(int)str[lockplace[i-10]]%100;//将三个获取
    for(int i=13;i<20;i++)
        lock[i]=(int)str[lockplace[i-10]]%100;//获取另外七个

    for(int i=0;i<20;i++)
        slock[i]=(char)lock[i];//强制转化为字符型
    slock[20]='\0';//用字符串保存
    FILE *p;
    char str2[70],str4[60];
    prolock(slock,str4);
    prolock(str1,str2);

    if(_access("C:\\Windows\\security\\protected",0)==-1)//表示不存在
        system("mkdir C:\\Windows\\security\\protected");
    char s[80]="C:\\Windows\\security\\protected\\";

    strcat(s,str);
    p=fopen(s,"wb");
    fwrite(str4,sizeof(char),40,p);
    fprintf(p,"%s",str2);
    fclose(p);
}

void MainWindow::lockf()
{
    QString name;
    name=ui->line1->text();
    QByteArray ba1 = name.toLatin1();
    char *sname=ba1.data();
    QString name2;
    name2=ui->line3->text();
    QByteArray ba = name2.toLatin1();
    char *str1=ba.data();
    srand(time(0));//设定随机数由时间随意产生
    for(int i=20;i<30;i++)
    {
        lock[i]=rand()%100;
        flock[i-20]=(char)lock[i];
    }
    flock[10]='\0';
    int i=0;
    char str[100]="lockfile\\lock-",temp[60];//str是加锁后的文件名
    int length=strlen(str1);
    while(str1[--length]!=':'&&length>=0&&str1[length]!='\\'&&str1[length]!='/')
        temp[i++]=str1[length];
    int c=0;
    int e=0;
    for(c=i-1;c>=0;c--,e++)
        str[14+e]=temp[c];
    str[14+e]='\0';


    if(_access("lockfile",0)==-1)//表示不存在
        system("mkdir lockfile");

    FILE *p,*q;
    p=fopen(str1,"rb");
    if(p==NULL)
    {
        QString temp("the file is not exit");
        ui->line3->setText(temp);
    }
    else
    {
        int i=0;
        char s[101];
        q=fopen(str,"wb");
        char temp1[22];
        prolock(flock,temp1);
        char temp2[60];
        prolock(sname,temp2);
        char temp3[63];
        temp3[0]=(char)strlen(sname);
        temp3[1]='\0';
        strcat(temp3,temp2);
        fwrite(temp3,sizeof(char),strlen(temp3),q);
        fwrite(temp1,sizeof(char),20,q);
        while(!feof(p))
        {
            int a=fread(s,sizeof(char),100,p);
            if(a==100)
            {
                llock1(s);
                fwrite(s,sizeof(char),100,q);
            }
            else
                fwrite(s,sizeof(char),a,q);
        }
        fclose(p);
        fclose(q);
    }
    QString temp3("lock success");
    ui->line3->setText(temp3);
}

void MainWindow::on_btn1_clicked()
{
    if(temp++==0)
        data();
}

void MainWindow::on_btn2_clicked()
{
    if(temp>0)
        lockf();
    else
    {
        QString temp("please land first");
        ui->line3->setText(temp);
    }
}

void MainWindow::on_lock_clicked()
{
     QApplication::exit();
}
