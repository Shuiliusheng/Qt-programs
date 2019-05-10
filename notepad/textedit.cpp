#include "textedit.h"
#include<iostream>
#define BACKSPACE 16777219
using namespace std;
TextEdit::TextEdit(QWidget *parent):QTextEdit(parent)
{
    connect(this,SIGNAL(cursorPositionChanged()),this,SLOT(cursorpositionchanged()));
    connect(this,SIGNAL(textChanged()),this,SLOT(textchanged()));
    flag1=0;
    flag=0;
    last=0;
    useflag=false;
}

void TextEdit::cursorpositionchanged()
{
    if(!useflag)
        return ;
    QTextCursor cur=this->textCursor();
    int place=cur.position();
    if(place>last)
        flag=1;
    else
        flag=0;
    last=place;
}

void TextEdit::keyPressEvent(QKeyEvent *event)
{
    if(!useflag)
        return ;
    QTextCursor cur;
    char *str2;
    QString temp;
    char c;
    if(event->key()==BACKSPACE)
    {
        temp=this->toPlainText();
        str2=temp.toLatin1().data();
        cur=this->textCursor();
        int place=cur.position();
        if(place==0)
        {
            c=0;
        }
        else
            c=str2[place-1];
    }
    QTextEdit::keyPressEvent(event);
    if(event->key()==BACKSPACE)
    {
        temp=this->toPlainText();
        str2=temp.toLatin1().data();
        cur=this->textCursor();
        int place=cur.position();
        if(c=='\"'||c=='<'||c=='>'||c=='\'')
        {
            int s=find_char(place-1,10);
            int e=find_char_forward(place-1,10);
            s+=1;
            if(e==-1)
                e=temp.length();
            e=e-s;
            char str[1000]={0};
            int i=0;
            for(i=0;i<=e;i++)
                str[i]=str2[i+s];
            flag1=1;
            cur.setPosition(s);
            for(i=0;i<e;i++)
            {
                cur.deleteChar();
            }
            flag1=0;
            for(i=0;i<e;i++)
            {
                cur.insertText(QString(QChar(str[i])));
            }
            cur.setPosition(place);
            this->setTextCursor(cur);
        }
    }
}

int TextEdit::getblock(char *str,int place)
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

bool TextEdit::detect_str(char *str)
{
    char temp[100][20]={"#include","int","double","return","char",
                        "struct","typedef","#define","long","for",
                        "while","if","else","class","public",
                        "bool","void","private","protected","extern",
                        "ifdef","endif","static","const","using",
                        "namespace","std"};
    int num=27;
    for(int i=0;i<num;i++)
        if(strcmp(str,temp[i])==0)
            return true;
    return false;
}

bool TextEdit::over_char(char c)
{
    char over[100]=" \n\r()*{}\"<>";
    int length=strlen(over);
    for(int i=0;i<length;i++)
        if(c==over[i]||c==' ')
        {
            return true;
        }
    return false;
}

void TextEdit::find_str(int &place,int &max,char str1[])
{
    int i=0,j=0;
    char *str=this->toPlainText().toLatin1().data();
    max=strlen(str);
    for(i=place;i>=0;i--)
    {
        if(over_char(str[i]))
        {
            break;
        }
    }
    for(j=place;j<max;j++)
    {
        if(over_char(str[j]))
        {
            break;
        }
    }
    int num=0;
    place=i+1;
    for(i=i+1;i<j;i++)
    {
        str1[num++]=str[i];
    }
    max=num;
}

int TextEdit::find_char(int place,char c)
{
    int i=0;
    char *str=this->toPlainText().toLatin1().data();
    for(i=place;i>=0;i--)
    {
        if(str[i]==c)
            return i;
        if(str[i]=='\n'||str[i]=='\r')
            return -1;
    }
    return -1;
}
int TextEdit::find_char_forward(int place,char c)
{
    int i=0;
    char *str=this->toPlainText().toLatin1().data();
    int max=strlen(str);
    for(i=place;i<max;i++)
    {

        if(str[i]==c)
            return i;
        if(str[i]=='\n'||str[i]=='\r')
            return -1;
    }
    return -1;
}

void TextEdit::color_str_back(char str[],char backc,int rawplace, QColor color)
{
    if(flag1==1)
        return;
    QTextCursor cur=this->textCursor();
    int place=cur.position();
    QTextCharFormat charformat=cur.charFormat();
    if(charformat.foreground().color()!=color)
    {
        flag1=1;
        char str1[1000]={0};
        int t=find_char(place-2,backc);
        int i=0;
        if(t!=-1)
        {
            for(i=t;i<place;i++)
                str1[i-t]=str[i];
            cur.setPosition(t);
            for(i=t;i<place;i++)
                cur.deleteChar();
            QTextCharFormat textchar=cur.charFormat();
            textchar.setForeground(QBrush(color));
            cur.insertText(tr(str1),textchar);
            cur.setPosition(rawplace);
            cur.setCharFormat(charformat);
            this->setTextCursor(cur);
            format=charformat;
        }
        flag1=0;
    }
}
void TextEdit::color_str_fore(char str[],char nextc,int rawplace, QColor color)
{
    if(flag1==1)
        return;
    QTextCursor cur=this->textCursor();
    int place=cur.position();
    QTextCharFormat charformat=cur.charFormat();
    if(charformat.foreground().color()!=color)
    {
        flag1=1;
        char str1[1000]={0};
        int t=find_char_forward(place,nextc);
        int i=0;
        if(t!=-1)
        {
            for(i=place-1;i<=t;i++)
                str1[i-place+1]=str[i];
            cur.setPosition(rawplace-1);
            for(i=place-1;i<=t;i++)
                cur.deleteChar();
            QTextCharFormat textchar=cur.charFormat();;
            textchar.setForeground(QBrush(color));
            cur.insertText(tr(str1),textchar);
            cur.setPosition(rawplace);
            cur.setCharFormat(charformat);
            this->setTextCursor(cur);
            format=charformat;
        }
        flag1=0;
    }
}

void TextEdit::color_str(char str[],char backc, char nextc,int rawplace, QColor color)
{
    if(flag1==1)
        return;
    QTextCursor cur=this->textCursor();
    int place=cur.position();
    QTextCharFormat charformat=cur.charFormat();
    if(charformat.foreground().color()!=color)
    {
        flag1=1;
        char str1[1000]={0};
        int t=find_char(place-2,backc);
        int i=0;
        if(t!=-1)
        {
            for(i=t;i<place;i++)
                str1[i-t]=str[i];
            cur.setPosition(t);
            for(i=t;i<place;i++)
                cur.deleteChar();
            QTextCharFormat textchar=cur.charFormat();;
            textchar.setForeground(QBrush(color));
            cur.insertText(tr(str1),textchar);
            cur.setPosition(rawplace);
            cur.setCharFormat(charformat);
            this->setTextCursor(cur);
        }
        else
        {
            t=find_char_forward(place,nextc);
            if(t!=-1)
            {
                for(i=place-1;i<=t;i++)
                    str1[i-place+1]=str[i];
                cur.setPosition(rawplace-1);
                for(i=place-1;i<=t;i++)
                    cur.deleteChar();
                QTextCharFormat textchar=cur.charFormat();;
                textchar.setForeground(QBrush(color));
                cur.insertText(tr(str1),textchar);
                cur.setPosition(rawplace);
                cur.setCharFormat(charformat);
                this->setTextCursor(cur);
            }
        }
        flag1=0;
    }
}

void TextEdit::textchanged()
{
    if(!useflag)
        return ;
    QString temp=this->toPlainText();
    char *str2=temp.toLatin1().data();
    char str[1000000]={0};
    strcpy(str,str2);
    QTextCursor cur=this->textCursor();
    int place=cur.position();
    int place1=cur.position();

    if(str[place-1]=='\t')
    {
        cur.deletePreviousChar();
        cur.insertText(tr("    "));
        this->setTextCursor(cur);

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
        this->setTextCursor(cur);
    }
    else if((str[place-1]=='\n'||str[place-1]=='\r')&&flag==1)
    {
        int n=getblock(str,place-2);
        if((place-2)>=0&&str[place-2]=='{')
        {
            for(int i=0;i<n+4;i++)
                cur.insertText(tr(" "));
            this->setTextCursor(cur);
        }
        else
        {
            for(int i=0;i<n;i++)
                cur.insertText(tr(" "));
            this->setTextCursor(cur);
        }
    }
    else if(str[place1-1]=='\"')
    {
        if(flag1==1)
            return;
        color_str(str,'\"','\"',place1,QColor(136,198,96));
    }
    else if(str[place1-1]=='\'')
    {
        if(flag1==1)
            return;
        color_str(str,'\'','\'',place1,QColor(227,182,87));
    }
    else if(str[place1-1]=='<')
    {
        if(flag1==1)
            return;
        color_str_fore(str,'>',place1,QColor(191,75,241));
    }
    else if(str[place1-1]=='>')
    {
        if(flag1==1)
            return;
        color_str_back(str,'<',place1,QColor(191,75,241));
    }
    else if(str[place1-1]=='/'&&str[place1-2]=='*'||str[place1-1]=='*'&&str[place1]=='/')
    {
        if(flag1==1)
            return ;
        flag1=1;
        if(str[place1-1]=='*'&&str[place1]=='/')
           place+=1;
        cur.setPosition(place);
        int length=temp.length()-place;
        char str1[10000]={0};
        int i=0;
        for(i=0;i<length;i++)
            str1[i]=str[place+i];
        for(i=0;i<length;i++)
        {
            cur.deleteChar();
        }
        QTextCharFormat textchar=cur.charFormat();;
        textchar.setForeground(QBrush(QColor(123,207,114)));
        cur.insertText(tr(str1), textchar);
        cur.setPosition(place);
        this->setTextCursor(cur);
        flag=0;
    }
    else
    {
        if(flag1==1)
            return ;
        QTextCharFormat charformat=cur.charFormat();
        if(charformat.foreground().color()!=QColor(0,154,205))
        {
            flag1=1;
            int length=temp.length();
            place-=1;
            char str1[200]={0};
            find_str(place,length,str1);
            if(detect_str(str1))
            {
                QTextCharFormat textchar=cur.charFormat();;
                textchar.setForeground(QBrush(QColor(0,154,205)));
                cur.setPosition(place);
                for(int i=0;i<length;i++)
                {
                    cur.deleteChar();
                }
                cur.insertText(tr(str1), textchar);
                this->setTextCursor(cur);
                cur.setCharFormat(charformat);
                format=charformat;
                cur.setPosition(place1);
                this->setTextCursor(cur);
            }
            flag1=0;
        }
        else
        {
            flag1=1;
            int length=temp.length();
            place-=1;
            char str1[200]={0};
            find_str(place,length,str1);
            if(!detect_str(str1))
            {
                cur.setPosition(place);
                for(int i=0;i<length;i++)
                {
                    cur.deleteChar();
                }
                cur.insertText(tr(str1), format);
                cur.setPosition(place1);
                this->setTextCursor(cur);
            }
            flag1=0;
        }
    }
}

void TextEdit::set_use(bool flag)
{
    useflag=flag;
}
