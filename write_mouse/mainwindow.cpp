#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<stdio.h>
#include<QTextCodec>
HHOOK keyHook=NULL;
HHOOK mouseHook=NULL;

void unHook();
QTime raw_time;
QTime t1;
FILE *p;
int flag=0;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QTextCodec::setCodecForTr(QTextCodec::codecForName("GB2312"));//设置中文显示
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("GB2312"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("GB2312"));

    QMenu *first1;
    first1=menuBar()->addMenu(tr("功能"));

    QAction *action1=new QAction(tr("压缩记录文件"),this);
    action1->setStatusTip(tr("压缩记录文件"));
    action1->setWhatsThis(tr("压缩记录文件"));
    connect(action1,SIGNAL(triggered()),this,SLOT(reduce_file()));
    first1->addAction(action1);

    QAction *action2=new QAction(tr("退出"),this);
    action2->setStatusTip(tr("退出"));
    action2->setWhatsThis(tr("退出"));
    connect(action2,SIGNAL(triggered()),this,SLOT(exit()));
    first1->addAction(action2);


}

MainWindow::~MainWindow()
{
    delete ui;
}

LRESULT CALLBACK keyProc(int nCode,WPARAM wParam,LPARAM lParam )
{
    KBDLLHOOKSTRUCT *pkbhs = (KBDLLHOOKSTRUCT *) lParam;
    if(pkbhs->vkCode==VK_F12)
    {
        unHook();
        fclose(p);
        flag=1;
    }
    if(wParam==WM_KEYDOWN)
    {
        t1=t1.currentTime();
        int sleep_time=raw_time.msecsTo(t1);
        raw_time=t1;
        if(sleep_time>10)
        {
            fprintf(p,"sleep %d\n",sleep_time);
        }
        fprintf(p,"inputn_down %d\n",pkbhs->vkCode);
    }
    else if(wParam==WM_KEYUP)
    {
        t1=t1.currentTime();
        int sleep_time=raw_time.msecsTo(t1);
        raw_time=t1;
        if(sleep_time>10)
        {
            fprintf(p,"sleep %d\n",sleep_time);
        }
        fprintf(p,"inputn_up %d\n",pkbhs->vkCode);
    }

    return CallNextHookEx(keyHook, nCode, wParam, lParam);

}

LRESULT CALLBACK mouseProc(int nCode,WPARAM wParam,LPARAM lParam )
{
    if(wParam==WM_MOUSEMOVE)
    {
        MOUSEHOOKSTRUCT *mhookstruct = (MOUSEHOOKSTRUCT*)lParam;
        POINT pt = mhookstruct->pt;
        t1=t1.currentTime();
        int sleep_time=raw_time.msecsTo(t1);
        raw_time=t1;
        if(sleep_time>10)
        {
            fprintf(p,"sleep %d\n",sleep_time);
        }
        fprintf(p,"move %d %d\n",pt.x,pt.y);
    }
    if(wParam == WM_LBUTTONDOWN)        //只处理WM_MOUSEMOVE消息
    {
        MOUSEHOOKSTRUCT *mhookstruct = (MOUSEHOOKSTRUCT*)lParam;
        POINT pt = mhookstruct->pt;
        t1=t1.currentTime();
        int sleep_time=raw_time.msecsTo(t1);
        raw_time=t1;
        if(sleep_time>10)
        {
            fprintf(p,"sleep %d\n",sleep_time);
        }
        //fprintf(p,"move %d %d\n",pt.x,pt.y);
        fprintf(p,"ldown %d %d\n",pt.x,pt.y);
    }
    if(wParam == WM_LBUTTONUP)
    {
        MOUSEHOOKSTRUCT *mhookstruct = (MOUSEHOOKSTRUCT*)lParam;
        POINT pt = mhookstruct->pt;
        t1=t1.currentTime();
        int sleep_time=raw_time.msecsTo(t1);
        raw_time=t1;
        if(sleep_time>10)
        {
            fprintf(p,"sleep %d\n",sleep_time);
        }
        //fprintf(p,"move %d %d\n",pt.x,pt.y);
        fprintf(p,"lup %d %d\n",pt.x,pt.y);
    }
    if(wParam == WM_RBUTTONDOWN)
    {
        MOUSEHOOKSTRUCT *mhookstruct = (MOUSEHOOKSTRUCT*)lParam;
        POINT pt = mhookstruct->pt;
        t1=t1.currentTime();
        int sleep_time=raw_time.msecsTo(t1);
        raw_time=t1;
        if(sleep_time>10)
        {
            fprintf(p,"sleep %d\n",sleep_time);
        }
        //fprintf(p,"move %d %d\n",pt.x,pt.y);
        fprintf(p,"rdown %d %d\n",pt.x,pt.y);
    }
    if(wParam == WM_RBUTTONUP)
    {
        MOUSEHOOKSTRUCT *mhookstruct = (MOUSEHOOKSTRUCT*)lParam;
        POINT pt = mhookstruct->pt;
        t1=t1.currentTime();
        int sleep_time=raw_time.msecsTo(t1);
        raw_time=t1;
        if(sleep_time>10)
        {
            fprintf(p,"sleep %d\n",sleep_time);
        }
        //fprintf(p,"move %d %d\n",pt.x,pt.y);
        fprintf(p,"rup %d %d\n",pt.x,pt.y);
    }
    if(wParam == WM_MBUTTONDOWN)
    {
        MOUSEHOOKSTRUCT *mhookstruct = (MOUSEHOOKSTRUCT*)lParam;
        POINT pt = mhookstruct->pt;
        t1=t1.currentTime();
        int sleep_time=raw_time.msecsTo(t1);
        raw_time=t1;
        if(sleep_time>10)
        {
            fprintf(p,"sleep %d\n",sleep_time);
        }
        fprintf(p,"middown %d %d\n",pt.x,pt.y);
    }
    if(wParam == WM_MBUTTONUP)
    {
        MOUSEHOOKSTRUCT *mhookstruct = (MOUSEHOOKSTRUCT*)lParam;
        POINT pt = mhookstruct->pt;
        t1=t1.currentTime();
        int sleep_time=raw_time.msecsTo(t1);
        raw_time=t1;
        if(sleep_time>10)
        {
            fprintf(p,"sleep %d\n",sleep_time);
        }
        fprintf(p,"midup %d %d\n",pt.x,pt.y);
    }
    if(wParam == WM_MOUSEWHEEL)
    {
        MSLLHOOKSTRUCT *mhookstruct = (MSLLHOOKSTRUCT *)lParam;
        int num = (short)HIWORD(mhookstruct->mouseData);
        t1=t1.currentTime();
        int sleep_time=raw_time.msecsTo(t1);
        raw_time=t1;
        if(sleep_time>10)
        {
            fprintf(p,"sleep %d\n",sleep_time);
        }
        fprintf(p,"wheel %d\n",num);
    }
    else
    {

    }
    return CallNextHookEx(mouseHook, nCode, wParam, lParam);;
}

void unHook()
{
    UnhookWindowsHookEx(keyHook);
    UnhookWindowsHookEx(mouseHook);
}

void setHook()
{
    keyHook =SetWindowsHookEx( WH_KEYBOARD_LL,keyProc,GetModuleHandle(NULL),0);
    mouseHook =SetWindowsHookEx( WH_MOUSE_LL,mouseProc,GetModuleHandle(NULL),0);
}



void MainWindow::on_start_clicked()
{
    QTime time;
    flag=0;
    raw_time=time.currentTime();
    p=fopen("tempfile","w");
    setHook();
}

void MainWindow::on_save_clicked()
{
    if(flag==1)
    {
        QString fname=tr("tempfile");
        QFile file(fname);
        if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
        {
            QMessageBox::warning(this,tr("打开"),tr("文件打开失败!"),QMessageBox::Yes);
            return;
        }
        QString str;
        QTextStream in(&file);
        str=in.readAll();
        ui->show->setPlainText(str);
        file.close();
    }
}

void MainWindow::on_save_2_clicked()
{
    if(QMessageBox::question(this,tr("保存"),tr("保存文件？"),QMessageBox::Save|QMessageBox::Cancel)==QMessageBox::Save)
    {
        QString fname=QFileDialog::getSaveFileName(this,tr("选择文件目录及文件名称"),"",tr("*"));
        QFile file(fname);
        if(!file.open(QIODevice::WriteOnly|QIODevice::Text))
        {
            QMessageBox::warning(this,tr("创建文件"),tr("文件创建失败!"),QMessageBox::Yes);
            return;
        }
        QTextStream out(&file);
        out <<ui->show->toPlainText();
        QMessageBox::information(this,tr("保存成功"),fname,QMessageBox::Yes);
        file.close();

        QFile file1(tr("tempfile"));
        file1.open(QIODevice::WriteOnly|QIODevice::Text);
        QTextStream out1(&file);
        out1 <<ui->show->toPlainText();
        file1.close();

    }
}

void MainWindow::on_save_3_clicked()
{
    ui->label->setText("Running...");
    runfile.set_param(1,1,"tempfile",false);
    runfile.start();
    ui->label->setText("END...");
}


void MainWindow::on_use_clicked()
{
    use.show();
}

void MainWindow::reduce_file()
{
    QString fname=QFileDialog::getOpenFileName(this,tr("打开文件"),"",tr("*"));
    char name[200];
    strcpy(name,fname.toLatin1().data());
    QString fname1=QFileDialog::getSaveFileName(this,tr("选择保存目录及文件名称"),"",tr("*"));
    char *name1=fname1.toLatin1().data();

    FILE *p=fopen(name,"r");
    FILE *p1=fopen(name1,"w");

    if(p==NULL)
        return ;
    char str[200];
    while(!feof(p))
    {
        fgets(str,200,p);
        reduce_cmd(str,p1);
    }
    fclose(p);
    fclose(p1);

}

void MainWindow::reduce_cmd(char cmd[], FILE *p)
{
    char temp[100];
    int x=0,y=0;
    sscanf(cmd,"%s",temp);
    if(strcmp(temp,"move")==0)
    {
        sscanf(cmd,"%s %d %d",temp,&x,&y);
        fprintf(p,"%s %d %d\n",MOVE,x,y);
    }
    else if(strcmp(temp,"lclick")==0)
    {
        fprintf(p,"%s\n",LCLICK);
    }
    else if(strcmp(temp,"lup")==0)
    {
        fprintf(p,"%s\n",LUP);
    }
    else if(strcmp(temp,"ldown")==0)
    {
        fprintf(p,"%s\n",LDOWN);
    }
    else if(strcmp(temp,"dlclick")==0)
    {
        fprintf(p,"%s\n",DLCLICK);
    }
    else if(strcmp(temp,"rclick")==0)
    {
        fprintf(p,"%s\n",RCLICK);
    }
    else if(strcmp(temp,"rup")==0)
    {
        fprintf(p,"%s\n",RUP);
    }
    else if(strcmp(temp,"rdown")==0)
    {
        fprintf(p,"%s\n",RDOWN);
    }
    else if(strcmp(temp,"drclick")==0)
    {
        fprintf(p,"%s\n",DRCLICK);
    }
    else if(strcmp(temp,"middown")==0)
    {
        fprintf(p,"%s\n",MDOWN);
    }
    else if(strcmp(temp,"midup")==0)
    {
        fprintf(p,"%s\n",MUP);
    }
    else if(strcmp(temp,"wheel")==0)
    {
        int num=0;
        sscanf(cmd,"%s %d",temp,&num);
        fprintf(p,"%s %d\n",WHEEL,num);
    }
    else if(strcmp(temp,"inputn_down")==0)
    {
        int c=0;
        sscanf(cmd,"%s %d",temp,&c);
        fprintf(p,"%s %d\n",IDOWN,c);
    }
    else if(strcmp(temp,"inputn_up")==0)
    {
        int c=0;
        sscanf(cmd,"%s %d %d",temp,&c);
        fprintf(p,"%s %d\n",IUP,c);
    }
    else if(strcmp(temp,"input")==0)
    {
        char str[100];
        strcpy(str,&cmd[6]);
        fprintf(p,"%s %s\n",IINPUT,str);
    }
    else if(strcmp(temp,"DOWN")==0)
    {
        char Key[20];
        sscanf(cmd,"%s %s",temp,Key);
        fprintf(p,"%s %s\n",DDOWN,Key);
    }
    else if(strcmp(temp,"UP")==0)
    {
        char Key[20];
        sscanf(cmd,"%s %s",temp,Key);
        fprintf(p,"%s %s\n",UUP,Key);
    }
    else if(strcmp(temp,"sleep")==0)
    {
        int time=0;
        sscanf(cmd,"%s %d",temp,&time);
        fprintf(p,"%s %d\n",SSLEEP,time);
    }
    else if(strcmp(temp,"begin")==0)
    {
        int circle=0;
        sscanf(cmd,"%s %d",temp,&circle);
        fprintf(p,"%s %d\n",BEGIN,circle);
    }
    else if(strcmp(temp,"end")==0)
    {
        fprintf(p,"%s\n",EEND);
    }
    else
    {
        cout <<"wrong"<<endl;
    }
    return ;

}
