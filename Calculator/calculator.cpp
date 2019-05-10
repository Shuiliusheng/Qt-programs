#include "calculator.h"
#include "ui_calculator.h"
#include<QDebug>
Calculator::Calculator(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Calculator),
    result(0.0),
    a(0),b(0),c(0)
{
    ui->setupUi(this);
    QTimer *timer=new QTimer(this);
    connect(ui->exitBtn,SIGNAL(clicked()),this,SLOT(eexit()));
    connect(ui->resultBtn,SIGNAL(clicked()),this,SLOT(showarea()));
    connect(ui->addBtn,SIGNAL(clicked()),this,SLOT(add()));
    connect(ui->reduceBtn,SIGNAL(clicked()),this,SLOT(reduce()));
    connect(ui->multyBtn,SIGNAL(clicked()),this,SLOT(multy()));
    connect(ui->divideBtn,SIGNAL(clicked()),this,SLOT(divide()));
    connect(ui->systimeBtn,SIGNAL(clicked()),this,SLOT(systemTime()));
    connect(timer,SIGNAL(timeout()),this,SLOT(showTime()));
    connect(ui->changBtn,SIGNAL(clicked()),this,SLOT(changeTime()));
    timer->start(1000);
}

Calculator::~Calculator()
{
    delete ui;
}
void Calculator::eexit()
{
    this->close();
}
void Calculator::add()
{
    QString tempt;
    QString s1=ui->inputLine1->text();
    bool ok;
    QString s2=ui->inputLine2->text();
    double a=s1.toDouble(&ok);
    double b=s2.toDouble(&ok);
    this->result=a+b;
}
void Calculator::reduce()
{
    QString tempt;
    QString s1=ui->inputLine1->text();
    bool ok;
    QString s2=ui->inputLine2->text();
    double a=s1.toDouble(&ok);
    double b=s2.toDouble(&ok);
    this->result=a-b;
}
void Calculator::multy()
{
    QString tempt;
    QString s1=ui->inputLine1->text();
    bool ok;
    QString s2=ui->inputLine2->text();
    double a=s1.toDouble(&ok);
    double b=s2.toDouble(&ok);
    this->result=a*b;
}
void Calculator::divide()
{
    QString tempt;
    QString s1=ui->inputLine1->text();
    bool ok;
    QString s2=ui->inputLine2->text();
    double a=s1.toDouble(&ok);
    double b=s2.toDouble(&ok);
    if(b!=0)
        this->result=a/b;
}
void Calculator::showarea()
{
    QString tempt;
    double a;
    a=this->result;
    ui->resultLabel->setText(tempt.setNum(a));
    this->result=0.0;
}
void Calculator:: showTime()
{
    QString temp;
    int &n=this->a,&m=this->b,&p=this->c;
    ui->secondLabel->setText(temp.setNum(n));
    ui->minuteLabel->setText(temp.setNum(m));
    ui->hourLabel->setText(temp.setNum(p));
    if(n>=59&&m>=59&&p>=23)
    {
        n=0;
        m=0;
        p=0;
    }
    else
    {
        if(n>=59&&m>=59)
        {
            n=0;
            m=0;
            p++;
        }
        else
        {
            if(n>=59)
            {
                n=0;
                m++;
            }
            else
                n++;
        }
    }
    qDebug()<<tr("123")<<endl;
}
void Calculator::changeTime()
{
    bool ok;
    QString temp;
    QString s1=ui->hourEdit->text();
    QString s2=ui->minuteEdit->text();
    QString s3=ui->secondEdit->text();
    int s=s3.toInt(&ok);
    int m=s2.toInt(&ok);
    int h=s1.toInt(&ok);
    this->a=s;
    if(m<=59)
    {
        this->b=m;
    }
    if(h<=59)
    {
        this->c=h;
    }
}
void Calculator::systemTime()
{
    ui->timeEdit->setTime(QTime::currentTime());
}
