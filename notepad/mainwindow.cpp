#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include<QTextCodec>
#include<QDebug> 
#include<QTextEdit>
#include<QPushButton>
#include<QVBoxLayout>
using namespace std;

int n=0;
int light=0;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->statusBar()->hide();
    ui->setupUi(this);
    draw_toolbar();
    QTextCodec::setCodecForTr(QTextCodec::codecForName("GB2312"));//设置中文显示
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("GB2312"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("GB2312"));

    press=false;

    findDlg = new QDialog(this);
    findDlg->setWindowTitle(tr("查找"));
    findLineEdit = new QLineEdit(findDlg);
    replaceLineEdit = new QLineEdit(findDlg);
    btn= new QPushButton(tr("查找下一个"), findDlg);
    btn1= new QPushButton(tr("查找前一个"), findDlg);
    btn2= new QPushButton(tr("全部替换"), findDlg);
    QVBoxLayout *layout= new QVBoxLayout(findDlg);
    layout->addWidget(findLineEdit);
    layout->addWidget(replaceLineEdit);
    layout->addWidget(btn);
    QHBoxLayout *layout2=new QHBoxLayout();
    check1=new QCheckBox("区分大小写",findDlg);
    check2=new QCheckBox("全词匹配",findDlg);
    layout2->addWidget(check1);
    layout2->addWidget(check2);
    QHBoxLayout *layout1=new QHBoxLayout();
    layout1->addWidget(btn);
    layout1->addWidget(btn1);
    layout1->addWidget(btn2);
    layout->addLayout(layout2);
    layout->addLayout(layout1);
    connect(btn2, SIGNAL(clicked()), this, SLOT(replace_all()));
    read_temp();

}

MainWindow::~MainWindow()
{
    save_temp();
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    ui->tabWidget->setGeometry(0,0,this->width(),this->height()-45);
    resize_btn();
    int index=ui->tabWidget->currentIndex();
    if(index!=ui->tabWidget->count()-1)
    {
        Text *text=(Text*)ui->tabWidget->currentWidget();
        text->resize_ui(0,0,ui->tabWidget->width(),ui->tabWidget->height());
    }
}

void MainWindow::resize_btn()
{
    ui->addfile->setGeometry(this->width()/2-90,this->height()/2-90,181,71);
    ui->newfile->setGeometry(this->width()/2-90,this->height()/2-10,181,71);
}

void MainWindow::on_addfile_clicked()
{
    QString fname=QFileDialog::getOpenFileName(this,tr("打开文件"),"",tr("*"));
    QFile file(fname);
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        QMessageBox::warning(this,tr("打开"),tr("文件打开失败!"),QMessageBox::Yes);
        return;
    }

    Text *text=new Text(ui->tabWidget);
    text->init(0,0,ui->tabWidget->width(),ui->tabWidget->height(),fname);
    ui->tabWidget->insertTab(ui->tabWidget->count()-1,(QWidget *)text,tr("new")+QString::number(n++));

    connect(text->close,SIGNAL(clicked()),this,SLOT(close_tab()));
    connect(text,SIGNAL(nameChanged(QString)),this,SLOT(change_tab_name(QString)));

    if(light==1)
    {
        QPalette palette;
        palette.setBrush(this->backgroundRole(),QBrush(QColor(0,0,0)));
        text->setAutoFillBackground(true);
        text->setPalette(palette);
        palette.setBrush(QPalette::Base,QBrush(QColor(0,0,0,255)));
        palette.setColor(QPalette::Text,QColor(235,235,235));
        text->edit->setPalette(palette);
        text->edit->setTextColor(QColor(240,240,240));
    }

    QString str;
    QTextStream in(&file);
    str=in.readAll();
    text->edit->setText(str);
    file.close();
    ui->tabWidget->setCurrentIndex(ui->tabWidget->count()-2);
    change_tab_name(QFileInfo(fname).fileName());
}

void MainWindow::draw_toolbar()
{
    QToolBar *tool;
    tool=addToolBar(tr("tool"));
    tool->setGeometry(0,0,this->width(),25);
    tool->setFloatable(false);
    tool->setFixedHeight(25);
    tool->setIconSize(QSize(25,25));
    tool->setMovable(false);
    QAction *save=new QAction(QIcon("save.ico"),tr("Save"),this);
    save->setStatusTip(tr("Save file"));
    tool->addAction(save);

    QAction *saveas=new QAction(QIcon("saveas.ico"),tr("Save As"),this);
    saveas->setStatusTip(tr("Save file As"));
    tool->addAction(saveas);

    QAction *Find=new QAction(QIcon("find.ico"),tr("Find"),this);
    Find->setStatusTip(tr("Find text"));
    tool->addAction(Find);

    QAction *Replace=new QAction(QIcon("replace.ico"),tr("Replace"),this);
    Replace->setStatusTip(tr("Replace text"));
    tool->addAction(Replace);

    QAction *big=new QAction(QIcon("big.ico"),tr("Big"),this);
    big->setStatusTip(tr("Big text"));
    tool->addAction(big);

    QAction *small=new QAction(QIcon("small.ico"),tr("Small"),this);
    small->setStatusTip(tr("Small text"));
    tool->addAction(small);

    QAction *background=new QAction(QIcon("back.ico"),tr("background"),this);
    background->setStatusTip(tr("background"));
    tool->addAction(background);


    QAction *light=new QAction(QIcon("light.ico"),tr("light"),this);
    light->setStatusTip(tr("light"));
    tool->addAction(light);

    QAction *fontlight=new QAction(QIcon("fontlight.ico"),tr("font light"),this);
    fontlight->setStatusTip(tr("font light"));
    tool->addAction(fontlight);

    QAction *code=new QAction(QIcon("code.ico"),tr("code"),this);
    code->setStatusTip(tr("code"));
    tool->addAction(code);


    connect(save,SIGNAL(triggered()),this,SLOT(save_file()));
    connect(Find,SIGNAL(triggered()),this,SLOT(find_text()));
    connect(Replace,SIGNAL(triggered()),this,SLOT(replace_text()));
    connect(big,SIGNAL(triggered()),this,SLOT(big_text()));
    connect(small,SIGNAL(triggered()),this,SLOT(small_text()));
    connect(saveas,SIGNAL(triggered()),this,SLOT(save_as()));
    connect(background,SIGNAL(triggered()),this,SLOT(set_background()));
    connect(light,SIGNAL(triggered()),this,SLOT(open_light()));
    connect(fontlight,SIGNAL(triggered()),this,SLOT(fontlight()));
    connect(code,SIGNAL(triggered()),this,SLOT(codeing()));
}

void MainWindow::codeing()
{
    int index=ui->tabWidget->currentIndex();
    if(index!=ui->tabWidget->count()-1)
    {
        Text *text=(Text*)ui->tabWidget->currentWidget();
        text->coding=!text->coding;
        text->set_coding(text->coding);
    }
}

void MainWindow::fontlight()
{
    int index=ui->tabWidget->currentIndex();
    if(index!=ui->tabWidget->count()-1)
    {
        Text *text=(Text*)ui->tabWidget->currentWidget();
        QColor color=text->edit->textColor();
        int c=color.red();
        c+=40;
        c%=256;
        text->edit->setTextColor(QColor(c,c,c));
        QString temp=text->edit->toPlainText();
        text->edit->setText(temp);
    }
}

void MainWindow::open_file()
{

}

void MainWindow::close_tab()
{
    ui->tabWidget->removeTab(ui->tabWidget->currentIndex());
    ui->tabWidget->repaint();
}

void MainWindow::on_newfile_clicked()
{
    Text *text=new Text(ui->tabWidget);
    text->init(0,0,ui->tabWidget->width(),ui->tabWidget->height(),tr("new")+QString::number(n));
    ui->tabWidget->insertTab(ui->tabWidget->count()-1,(QWidget *)text,tr("new")+QString::number(n++));
    connect(text->close,SIGNAL(clicked()),this,SLOT(close_tab()));
    connect(text,SIGNAL(nameChanged(QString)),this,SLOT(change_tab_name(QString)));
    ui->tabWidget->setCurrentIndex(ui->tabWidget->count()-2);
    if(light==1)
    {
        QPalette palette;
        palette.setBrush(this->backgroundRole(),QBrush(QColor(0,0,0)));
        text->setAutoFillBackground(true);
        text->setPalette(palette);
        palette.setBrush(QPalette::Base,QBrush(QColor(0,0,0,255)));
        palette.setColor(QPalette::Text,QColor(235,235,235));
        text->edit->setPalette(palette);
        text->edit->setTextColor(QColor(240,240,240));
    }


}

void MainWindow::change_tab_name(QString name)
{
    int index=ui->tabWidget->currentIndex();
    ui->tabWidget->setTabText(index,name);
}

void MainWindow::save_file()
{
    int index=ui->tabWidget->currentIndex();
    if(index!=ui->tabWidget->count()-1)
    {
        Text *text=(Text*)ui->tabWidget->currentWidget();
        QString fname(text->windowTitle());
        QFile file(fname);
        if(!file.open(QIODevice::WriteOnly|QIODevice::Text))
        {
            QMessageBox::warning(this,tr("创建文件"),tr("文件创建失败!"),QMessageBox::Yes);
            return;
        }
        QTextStream out(&file);

        out <<text->edit->toPlainText();
        QMessageBox::information(this,tr("保存成功"),fname,QMessageBox::Yes);
        file.close();
    }
}

void MainWindow::save_as()
{
    int index=ui->tabWidget->currentIndex();
    if(index!=ui->tabWidget->count()-1)
    {
        Text *text=(Text*)ui->tabWidget->currentWidget();
        QString fname=QFileDialog::getSaveFileName(this,tr("选择文件目录及文件名称"),"",tr("*"));
        QFile file(fname);
        if(!file.open(QIODevice::WriteOnly|QIODevice::Text))
        {
            QMessageBox::warning(this,tr("创建文件"),tr("文件创建失败!"),QMessageBox::Yes);
            return;
        }
        QTextStream out(&file);

        out <<text->edit->toPlainText();
        QMessageBox::information(this,tr("保存成功"),fname,QMessageBox::Yes);
        file.close();
    }
}

void MainWindow::find_text()
{
    int index=ui->tabWidget->currentIndex();
    if(index!=ui->tabWidget->count()-1)
    {
        findDlg->show();
        replaceLineEdit->hide();
        btn2->hide();
        Text *text=(Text*)ui->tabWidget->currentWidget();
        findLineEdit->setText(text->edit->textCursor().selectedText());

        btn->setText(tr("查找下一个"));
        btn1->setText(tr("查找前一个"));

        connect(btn, SIGNAL(clicked()), this, SLOT(find_str()));
        connect(btn1, SIGNAL(clicked()), this, SLOT(find_str1()));

    }
}

void MainWindow::find_str()
{
    int index=ui->tabWidget->currentIndex();
    if(index!=ui->tabWidget->count()-1)
    {
        Text *text=(Text*)ui->tabWidget->currentWidget();
        QString findtext=findLineEdit->text();//获得对话框的内容
        if(find_method(text->edit,findtext,1))
        {
            // 查找到后高亮显示
            QPalette palette = text->edit->palette();
            palette.setColor(QPalette::Highlight,palette.color(QPalette::Active,QPalette::Highlight));
            text->edit->setPalette(palette);
        }
        else
        {
            QMessageBox::information(this,tr("注意"),tr("没有找到内容"),QMessageBox::Ok);
        }
    }
}

void MainWindow::find_str1()
{
    int index=ui->tabWidget->currentIndex();
    if(index!=ui->tabWidget->count()-1)
    {
        Text *text=(Text*)ui->tabWidget->currentWidget();
        QString findtext=findLineEdit->text();//获得对话框的内容
        if(find_method(text->edit,findtext,2))
        {
            // 查找到后高亮显示
            QPalette palette = text->edit->palette();
            palette.setColor(QPalette::Highlight,palette.color(QPalette::Active,QPalette::Highlight));
            text->edit->setPalette(palette);

        }
        else
        {
            QMessageBox::information(this,tr("注意"),tr("没有找到内容"),QMessageBox::Ok);
        }
    }
}

bool MainWindow::find_method(QTextEdit *edit,QString findtext,int method)
{
    if(method==1)//down
    {
        if(check2->isChecked())//whole
        {
            if(check1->isChecked())
                edit->find(findtext,QTextDocument::FindWholeWords|QTextDocument::FindCaseSensitively);
            return edit->find(findtext,QTextDocument::FindWholeWords);
        }
        else if(check1->isChecked())//sentitive
        {
            return edit->find(findtext,QTextDocument::FindCaseSensitively);
        }
        else
            return edit->find(findtext);
    }
    else
    {
        if(check2->isChecked())//whole
        {
            if(check1->isChecked())
                edit->find(findtext,QTextDocument::FindWholeWords|QTextDocument::FindCaseSensitively|QTextDocument::FindBackward);
            return edit->find(findtext,QTextDocument::FindWholeWords|QTextDocument::FindBackward);
        }
        else if(check1->isChecked())//sentitive
        {
            return edit->find(findtext,QTextDocument::FindCaseSensitively|QTextDocument::FindBackward);
        }
        else
            return edit->find(findtext,QTextDocument::FindBackward);
    }
}

int size1=9;

void MainWindow::big_text()
{
    int index=ui->tabWidget->currentIndex();
    if(index!=ui->tabWidget->count()-1)
    {
        Text *text=(Text*)ui->tabWidget->currentWidget();
        size1++;
        size1=std::min(50,size1);
        text->edit->setFontPointSize(size1);
        QString temp=text->edit->toPlainText();
        text->edit->setPlainText(temp);
    }
}

void MainWindow::small_text()
{
    int index=ui->tabWidget->currentIndex();
    if(index!=ui->tabWidget->count()-1)
    {
        Text *text=(Text*)ui->tabWidget->currentWidget();
        size1--;
        size1=std::max(5,size1);
        text->edit->setFontPointSize(size1);
        QString temp=text->edit->toPlainText();
        text->edit->setPlainText(temp);
    }
}

void MainWindow::replace_text()
{
    int index=ui->tabWidget->currentIndex();
    if(index!=ui->tabWidget->count()-1)
    {
        findDlg->show();
        replaceLineEdit->setVisible(true);
        Text *text=(Text*)ui->tabWidget->currentWidget();
        findLineEdit->setText(text->edit->textCursor().selectedText());
        replaceLineEdit->setText(text->edit->textCursor().selectedText());
        btn->setText("替换下一个");
        btn1->setText("替换上一个");
        btn2->show();
        connect(btn, SIGNAL(clicked()), this, SLOT(replace_str_down()));
        connect(btn1, SIGNAL(clicked()), this, SLOT(replace_str_up()));
    }
}

void MainWindow::replace_str_down()
{
    int index=ui->tabWidget->currentIndex();
    if(index!=ui->tabWidget->count()-1)
    {
        Text *text=(Text*)ui->tabWidget->currentWidget();
        QString findtext=findLineEdit->text();//获得对话框的内容
        QString replacetext=replaceLineEdit->text();
        if(find_method(text->edit,findtext,1))
        {
            text->edit->textCursor().removeSelectedText();
            text->edit->textCursor().insertText(replacetext);

            if(text->edit->find(replacetext,QTextDocument::FindBackward))
            {
                // 查找到后高亮显示
                QPalette palette = text->edit->palette();
                palette.setColor(QPalette::Highlight,palette.color(QPalette::Active,QPalette::Highlight));
                text->edit->setPalette(palette);
            }
        }
        else
        {
            QMessageBox::information(this,tr("注意"),tr("没有找到内容"),QMessageBox::Ok);
        }
    }
}

void MainWindow::replace_str_up()
{
    int index=ui->tabWidget->currentIndex();
    if(index!=ui->tabWidget->count()-1)
    {
        Text *text=(Text*)ui->tabWidget->currentWidget();
        QString findtext=findLineEdit->text();//获得对话框的内容
        QString replacetext=replaceLineEdit->text();
        if(find_method(text->edit,findtext,2))
        {
            text->edit->textCursor().removeSelectedText();
            text->edit->textCursor().insertText(replacetext);

            if(text->edit->find(replacetext,QTextDocument::FindBackward))
            {
                // 查找到后高亮显示
                QPalette palette = text->edit->palette();
                palette.setColor(QPalette::Highlight,palette.color(QPalette::Active,QPalette::Highlight));
                text->edit->setPalette(palette);
            }
        }
        else
        {
            QMessageBox::information(this,tr("注意"),tr("没有找到内容"),QMessageBox::Ok);
        }
    }
}

void MainWindow::replace_all()
{
    int index=ui->tabWidget->currentIndex();
    if(index!=ui->tabWidget->count()-1)
    {
        Text *text=(Text*)ui->tabWidget->currentWidget();
        QString findtext=findLineEdit->text();//获得对话框的内容
        QString replacetext=replaceLineEdit->text();
        QString temp=text->edit->toPlainText();
        if(check1->isChecked())
            temp.replace(findtext,replacetext,Qt::CaseSensitive);
        else
            temp.replace(findtext,replacetext);
        text->edit->setText(temp);
    }
}


int last_key=0;

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==CTRL)
    {
        last_key=CTRL;
        return ;
    }
    if(last_key==CTRL)
    {
        int key=event->key();
        if(key==EXIT)
        {
            this->close();
        }
        else if(key==QUIT)
        {
            this->close();
        }
        else if(key==SAVE)
        {
            save_file();
        }
        else if(key=='r'||key=='R')
        {
            replace_text();
        }
        else if(key=='f'||key=='F')
        {
            find_text();
        }
        else if(key=='d'||key=='D')
        {
            save_as();
        }
        else if(key=='b'||key=='B')
        {
            big_text();
        }
        else if(key=='l'||key=='L')
        {
            small_text();
        }
    }
}

void MainWindow::set_background()
{
    int index=ui->tabWidget->currentIndex();
    if(index!=ui->tabWidget->count()-1)
    {
        QString fname=QFileDialog::getOpenFileName(this,tr("打开文件"),"",tr("Images (*.png *.bmp *.jpg)"));
        Text *text=(Text*)ui->tabWidget->currentWidget();
        text->setAutoFillBackground(true);
        QPalette palette;
        palette.setBrush(this->backgroundRole(),QBrush(QImage(fname).scaled(text->width(), text->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));
        text->setPalette(palette);
        palette.setBrush(QPalette::Base,QBrush(QColor(255,255,255,25)));
        text->edit->setPalette(palette);
    }
}


void MainWindow::open_light()
{
    if(light==0)
    {
        setWindowFlags( Qt::FramelessWindowHint);
        this->show();
        QPalette palette;
        palette.setBrush(this->backgroundRole(),QBrush(QColor(0,0,0)));
        this->setPalette(palette);
        int i=0;
        for(i=0;i<ui->tabWidget->count()-1;i++)
        {
            Text *text=(Text*)ui->tabWidget->widget(i);
            text->setAutoFillBackground(true);
            text->setPalette(palette);
            palette.setBrush(QPalette::Base,QBrush(QColor(0,0,0,255)));
            palette.setColor(QPalette::Text,QColor(235,235,235));
            text->edit->setPalette(palette);
            text->edit->setTextColor(QColor(240,240,240));
            QString temp=text->edit->toPlainText();
            text->edit->setText(temp);
        }
        ui->tabWidget->widget(i)->setAutoFillBackground(true);
        ui->tabWidget->widget(i)->setPalette(palette);

        light++;
    }
    else
    {
        light=0;
        setWindowFlags( Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);
        this->show();
        QPalette palette;
        palette.setBrush(this->backgroundRole(),QBrush(QColor(230,230,230)));
        this->setPalette(palette);
        int i=0;
        for(i=0;i<ui->tabWidget->count()-1;i++)
        {
            Text *text=(Text*)ui->tabWidget->widget(i);
            text->setAutoFillBackground(true);
            palette.setBrush(this->backgroundRole(),QBrush(QColor(240,240,240)));
            text->setPalette(palette);
            palette.setBrush(QPalette::Base,QBrush(QColor(245,245,245,25)));
            text->edit->setPalette(palette);
            text->edit->setTextColor(QColor(0,0,0));
            QString temp=text->edit->toPlainText();
            text->edit->setText(temp);
        }
        ui->tabWidget->widget(i)->setAutoFillBackground(true);
        ui->tabWidget->widget(i)->setPalette(palette);
    }
}
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::RightButton)
    {
        oldPos = event->globalPos();
        press = true;
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(press)
    {
        this->move(this->pos() + event->globalPos() - oldPos);
        oldPos = event->globalPos();
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    press = false;
}

void MainWindow::save_temp()
{
    QString fname(tr("tempfile"));
    QFile file(fname);
    if(!file.open(QIODevice::WriteOnly|QIODevice::Text))
    {
        QMessageBox::warning(this,tr("创建文件"),tr("文件创建失败!"),QMessageBox::Yes);
        return;
    }
    QTextStream out(&file);
    for(int i=0;i<ui->tabWidget->count()-1;i++)
    {
        Text *text=(Text*)ui->tabWidget->widget(i);//text->windowTitle()
        out <<"begin"<<endl;
        out <<text->windowTitle()<<endl;
        out <<text->edit->toPlainText()<<endl;
        out <<"end"<<endl;
    }
    file.close();
}

void MainWindow::read_temp()
{
    QString fname(tr("tempfile"));
    QFile file(fname);
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        QMessageBox::warning(this,tr("打开文件"),tr("打开文件失败!"),QMessageBox::Yes);
        return;
    }
    QTextStream in(&file);
    QString temp;
    while(!in.atEnd())
    {
        temp=in.readLine();
        if(temp.compare(tr("begin"))==0)
        {
            temp=in.readLine();

            Text *text=new Text(ui->tabWidget);
            text->init(0,0,ui->tabWidget->width(),ui->tabWidget->height(),temp);
            ui->tabWidget->insertTab(ui->tabWidget->count()-1,(QWidget *)text,QFileInfo(temp).fileName());
            connect(text->close,SIGNAL(clicked()),this,SLOT(close_tab()));
            connect(text,SIGNAL(nameChanged(QString)),this,SLOT(change_tab_name(QString)));
            ui->tabWidget->setCurrentIndex(ui->tabWidget->count()-2);

            while(!in.atEnd())
            {
                temp=in.readLine();
                if(temp.compare(tr("end"))==0)
                    break;
                text->edit->append(temp);
            }
        }
    }
    file.close();
}
