#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<stdio.h>
#include<iostream>
#include<io.h>
#include<stdlib.h>
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

void MainWindow::rllock(char str[],char str1[])
{
    int length=200;
    int a=0,b=0;
    for(int i=0;i<length;i+=2)
    {
        if(a>=30)
            a%=30;
        char s=str[i];
        char s1=str[i+1];
        if(s1=='#')
        {
            str1[b++]=s+(char)lock[a++];
        }
        else if(s1=='%')
            str1[b++]=s-(char)lock[a++];
    }
    str1[b]='\0';
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


void MainWindow::chargename()
{
    QString name;
    name=ui->line1->text();
    QByteArray ba = name.toLatin1();
    char *str=ba.data();///用户名

    FILE *p;
    char s[80]="C:\\Windows\\security\\protected\\";
    strcat(s,str);
    p=fopen(s,"rb");
    if(p==NULL)
    {
        QString temp("the User is not exit");
        ui->line1->setText(temp);
    }
    else
    {
        QString name1;
        name1=ui->line2->text();
        QByteArray ba1 = name1.toLatin1();
        char *str1=ba1.data();///密码

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
        if(strcmp(str1,temp)==0)//登陆成功
        {
            QString tempx("success");
            ui->line2->setText(tempx);
            this->temp=1;
            fclose(p);
        }
        if(strcmp(str1,temp)!=0)//登陆失败
        {
            cout <<temp<<endl;
            QString tempy("wrong");
            ui->line2->setText(tempy);
            this->temp=0;
            fclose(p);
        }
    }
}

void MainWindow::chargefile()
{
    QString name;
    name=ui->line1->text();
    QByteArray ba = name.toLatin1();
    char *str=ba.data();///用户名

    QString name1;
    name1=ui->line3->text();
    QByteArray ba1 = name1.toLatin1();
    char *f=ba1.data();///file name


    FILE *p;
    p=fopen(f,"rb");
    if(p==NULL)
    {
        QString temp("Can not find the file");
        ui->line3->setText(temp);
    }
    else
    {
        char temp[62],temp1[31];
        int i=fgetc(p);
        fread(temp,sizeof(char),2*i,p);
        temp[2*i]='\0';
        prorl(temp,temp1);
        if(strcmp(temp1,str)!=0)
        {
            QString temp("the file isn't locked by this User");
            ui->line3->setText(temp);
        }
        else
        {
            char tlock[24],tlock1[12];
            fread(tlock,sizeof(char),20,p);
            tlock[20]='\0';
            prorl(tlock,tlock1);

            for(int i=0;i<10;i++)
            {
                lock[i+20]=(int)tlock1[i];
            }
            if(_access("relockfile",0)==-1)//表示不存在
                system("mkdir relockfile");

            int ia=0;
            char s[100]="relockfile\\relock-",tempq[60];//str是加锁后的文件名
            int lengtha=strlen(f);
            while(f[--lengtha]!=':'&&lengtha>=0&&f[lengtha]!='\\'&&f[lengtha]!='/'&&f[lengtha]!='k')
                tempq[ia++]=f[lengtha];
            int ca=0;
            int ea=0;
            for(ca=ia-1;ca>=0;ca--,ea++)
                s[18+ea]=tempq[ca];
            s[18+ea]='\0';

            FILE *q;
            q=fopen(s,"wb");
            char temp1[101];
            while(!feof(p))
            {

                int a=fread(temp1,sizeof(char),100,p);
                if(a==100)
                {
                    rllock1(temp1);
                    fwrite(temp1,sizeof(char),100,q);
                }
                else
                    fwrite(temp1,sizeof(char),a,q);
            }

            fclose(p);
            fclose(q);

            QString temp("relock success");
            ui->line3->setText(temp);
        }
    }

}


void MainWindow::on_pushButton_2_clicked()
{
    QApplication::exit();
}

void MainWindow::on_pushButton_clicked()
{
    if(temp==0)
        chargename();

}

void MainWindow::on_pushButton_3_clicked()
{
    if(this->temp==1)
        chargefile();
    else
    {
        QString temp("please land");
        ui->line3->setText(temp);
    }
}
