#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<windows.h>
#include<stdio.h>
#include<QMessageBox>
int sx,sy,ex,ey;

int now_x=0;
int now_y=0;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    sx=0;
    sy=0;
    ex=GetSystemMetrics(SM_CXSCREEN);
    ey=GetSystemMetrics(SM_CYSCREEN);
    QTextCodec::setCodecForTr(QTextCodec::codecForName("GB2312"));//设置中文显示
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("GB2312"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("GB2312"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

cv::Mat QImage2cvMat(QImage image)
{
    cv::Mat mat;
    switch(image.format())
    {
    case QImage::Format_ARGB32:
    case QImage::Format_RGB32:
    case QImage::Format_ARGB32_Premultiplied:
        mat = cv::Mat(image.height(), image.width(), CV_8UC4, (void*)image.constBits(), image.bytesPerLine());
        break;
    case QImage::Format_RGB888:
        mat = cv::Mat(image.height(), image.width(), CV_8UC3, (void*)image.constBits(), image.bytesPerLine());
        cv::cvtColor(mat, mat, CV_BGR2RGB);
        break;
    case QImage::Format_Indexed8:
        mat = cv::Mat(image.height(), image.width(), CV_8UC1, (void*)image.constBits(), image.bytesPerLine());
        break;
    }
    return mat;
}

void on_mouse(int event,int x,int y,int flags,void *ustc)//event鼠标事件代号，x,y鼠标坐标，flags拖拽和键盘操作的代号
{
    if(event==CV_EVENT_LBUTTONDOWN)
    {
        now_x=x*2;
        now_y=y*2;
    }
}
void MainWindow::cut()
{
    QPixmap fullScreen;
    fullScreen = QPixmap::grabWindow(QApplication::desktop()->winId(),sx,sy,ex-sx,ey-sy);
    QImage src=fullScreen.toImage();
    Mat frame=QImage2cvMat(src);
    cv::resize(frame,frame,Size(frame.cols/2,frame.rows/2),(0,0),(0,0),3);
    imshow("test",frame);
    setMouseCallback("test",on_mouse,0);
}


void MainWindow::on_pushButton_13_clicked()
{
    cut();
}

void MainWindow::on_pushButton_14_clicked()
{
    ui->x_label->setText("X:"+QString::number(now_x));
    ui->y_label->setText("Y:"+QString::number(now_y));
}

void MainWindow::on_pushButton_9_clicked()
{
    char temp[100];
    sprintf(temp,"move %d %d",now_x,now_y);
    ui->textEdit->append(tr(temp));
}

void MainWindow::on_pushButton_clicked()
{
    char temp[100];
    sprintf(temp,"lclick %d %d",now_x,now_y);
    ui->textEdit->append(tr(temp));
}

void MainWindow::on_pushButton_2_clicked()
{
    char temp[100];
    sprintf(temp,"lup %d %d",now_x,now_y);
    ui->textEdit->append(tr(temp));
}

void MainWindow::on_pushButton_3_clicked()
{
    char temp[100];
    sprintf(temp,"ldown %d %d",now_x,now_y);
    ui->textEdit->append(tr(temp));
}

void MainWindow::on_pushButton_8_clicked()
{
    char temp[100];
    sprintf(temp,"dlclick %d %d",now_x,now_y);
    ui->textEdit->append(tr(temp));
}

void MainWindow::on_pushButton_5_clicked()
{
    char temp[100];
    sprintf(temp,"rclick %d %d",now_x,now_y);
    ui->textEdit->append(tr(temp));
}

void MainWindow::on_pushButton_6_clicked()
{
    char temp[100];
    sprintf(temp,"rup %d %d",now_x,now_y);
    ui->textEdit->append(tr(temp));
}

void MainWindow::on_pushButton_4_clicked()
{
    char temp[100];
    sprintf(temp,"rdown %d %d",now_x,now_y);
    ui->textEdit->append(tr(temp));
}

void MainWindow::on_pushButton_7_clicked()
{
    char temp[100];
    sprintf(temp,"drclick %d %d",now_x,now_y);
    ui->textEdit->append(tr(temp));
}

void MainWindow::on_pushButton_10_clicked()
{
    char temp[100];
    sprintf(temp,"input ");
    if(!ui->lineEdit->text().isEmpty())
        ui->textEdit->append(tr(temp)+ui->lineEdit->text());
}

void MainWindow::on_choose_currentIndexChanged(const QString &arg1)
{

}

void MainWindow::on_pushButton_11_clicked()
{
    ui->textEdit->append(tr("DOWN ")+ui->choose->currentText());
}

void MainWindow::on_pushButton_12_clicked()
{
    ui->textEdit->append(tr("UP ")+ui->choose->currentText());
}

void MainWindow::on_pushButton_15_clicked()
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

        out <<ui->textEdit->toPlainText();
        QMessageBox::information(this,tr("保存成功"),fname,QMessageBox::Yes);
        file.close();
    }
}

void MainWindow::on_pushButton_16_clicked()
{
    if(!ui->line_sleep->text().isEmpty())
    {
        int t=ui->line_sleep->text().toInt();
        char temp[100];
        sprintf(temp,"sleep %d",t);
        ui->textEdit->append(tr(temp));
    }
}

void MainWindow::on_pushButton_17_clicked()
{
    if(!ui->line_circle->text().isEmpty())
    {
        int t=ui->line_circle->text().toInt();
        char temp[100];
        sprintf(temp,"begin %d",t);
        ui->textEdit->append(tr(temp));
    }
}

void MainWindow::on_pushButton_18_clicked()
{
    ui->textEdit->append(tr("end"));
}

void MainWindow::on_middown_clicked()
{
    char temp[100];
    sprintf(temp,"middown %d %d",now_x,now_y);
    ui->textEdit->append(tr(temp));
}

void MainWindow::on_midup_clicked()
{
    char temp[100];
    sprintf(temp,"midup %d %d",now_x,now_y);
    ui->textEdit->append(tr(temp));
}

void MainWindow::on_mid_clicked()
{
    char temp[100];
    sprintf(temp,"middown %d %d",now_x,now_y);
    ui->textEdit->append(tr(temp));
    sprintf(temp,"midup %d %d",now_x,now_y);
    ui->textEdit->append(tr(temp));
}
