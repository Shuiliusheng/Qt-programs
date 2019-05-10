#include "text.h"
#include<QFileDialog>
#include<QTextCodec>
#include<QMessageBox>
Text::Text(QWidget *parent):
    QWidget(parent) 
{
    QTextCodec::setCodecForTr(QTextCodec::codecForName("GB2312"));//设置中文显示
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("GB2312"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("GB2312"));
    flag=0;
    last=0;
    coding=0;
}

void Text::resize_ui(int x, int y, int w, int h)
{
    this->setGeometry(x,y,w,h);
    edit->setGeometry(x,y,w,h-55);
    w=w/2;
    h=h-54;
    close->setGeometry(w+3,h,70,30);
    open->setGeometry(w-73,h,70,30);
}

void Text::init(int x, int y, int w, int h,QString filename)
{
    this->setGeometry(x,y,w,h);
    edit=new TextEdit(this);

    edit->setGeometry(x,y,w,h-55);
    close=new QPushButton(tr("Close"),this);
    open=new QPushButton(tr("Open"),this);
    w=w/2;
    h=h-54;
    close->setGeometry(w+3,h,70,30);
    open->setGeometry(w-73,h,70,30);
    connect(close,SIGNAL(clicked()),this,SLOT(close_tab1()));
    connect(open,SIGNAL(clicked()),this,SLOT(open_file1()));
    this->setWindowTitle(filename);
//    connect(edit,SIGNAL(textChanged()),this,SLOT(text_change()));
//    connect(edit,SIGNAL(cursorPositionChanged()),this,SLOT(cursor_change()));
}

void Text::open_file1()
{
    QString fname=QFileDialog::getOpenFileName(this,tr("打开文件"),"",tr("*"));
    QFile file(fname);
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        QMessageBox::warning(this,tr("打开"),tr("文件打开失败!"),QMessageBox::Yes);
        return;
    }

    QString str;
    QTextStream in(&file);
    str=in.readAll();
    edit->setText(str);
    file.close();
    this->setWindowTitle(fname);

    emit nameChanged(QFileInfo(fname).fileName());
}

void Text::close_tab1()
{

}

void Text::text_change()
{
    if(coding==0)
        return;
    QString temp=edit->toPlainText();
    char *str=temp.toLatin1().data();
    QTextCursor cur=edit->textCursor();
    int place=cur.position();
    if(str[place-1]=='\t')
    {
        cur.deletePreviousChar();
        cur.insertText(tr("    "));
        edit->setTextCursor(cur);

    }
    else if(str[place-1]=='}'&&flag==1)
    {
        int n=getblock(str,place-1);
        if(n>4)
            n=4;
        for(int i=0;i<=n;i++)
            cur.deletePreviousChar();
        cur.insertText("} ");
        cur.deletePreviousChar();
        edit->setTextCursor(cur);
    }
    else if((str[place-1]=='\n'||str[place-1]=='\r')&&flag==1)
    {
        int n=getblock(str,place-2);
        if((place-2)>=0&&str[place-2]=='{')
        {
            for(int i=0;i<n+4;i++)
                cur.insertText(tr(" "));
            edit->setTextCursor(cur);
        }
        else
        {
            for(int i=0;i<n;i++)
                cur.insertText(tr(" "));
            edit->setTextCursor(cur);
        }
    }
}

void Text::cursor_change()
{
    QTextCursor cur=edit->textCursor();
    int place=cur.position();
    if(place>last)
        flag=1;
    else
        flag=0;
    last=place;
}

int Text::getblock(char *str,int place)
{
    int i=0;
    for(i=place;i>=0;i--)
    {
        if(str[i]==10)
            break;
    }
    int num=0;
    i=i+1;
    for(i;i<place;i++)
    {
        if(str[i]==' ')
            num++;
        if(str[i]!=' ')
            break;
    }
    return num;
}

void Text::set_coding(bool flag)
{
    edit->set_use(flag);
}
