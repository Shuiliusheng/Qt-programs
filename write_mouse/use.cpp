#include "use.h"
#include "ui_use.h"
#include<QFileDialog>
#include<QByteArray>
#include<windows.h>
Use::Use(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Use)
{
    ui->setupUi(this);
    sleep=0;
    circle=0;
}

Use::~Use()
{
    delete ui;
}



void Use::on_pushButton_clicked()
{
    QString fname=QFileDialog::getOpenFileName(this,tr("打开文件"),"",tr("*"));
    char *name=fname.toLatin1().data();
    strcpy(filename,name);
}

void Use::on_start_clicked()
{
    sleep=ui->sleeptime->text().toInt();
    circle=ui->times->text().toInt();

    bool run_flag=false;
    FILE *p=NULL;
    p=fopen(filename,"r");
    if(p==NULL)
        return;
    fclose(p);
    if(circle==-1)
        run_flag=true;
    runfile.set_param(sleep,circle,filename,run_flag);
    runfile.start();
}
