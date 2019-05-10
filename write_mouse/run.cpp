#include "run.h"

HHOOK keyHook1=NULL;
void static unHook1();
static int flag=0;

Run::Run()
{
    x=0;
    y=0;
    p1=NULL;
}


LRESULT CALLBACK keyProc1(int nCode,WPARAM wParam,LPARAM lParam )
{
    KBDLLHOOKSTRUCT *pkbhs = (KBDLLHOOKSTRUCT *) lParam;
    if(pkbhs->vkCode==VK_F12)
    {
        unHook1();
        flag=1;
    }
    return CallNextHookEx(keyHook1, nCode, wParam, lParam);
}

void static unHook1()
{
    UnhookWindowsHookEx(keyHook1);
}

void static setHook1()
{
    keyHook1 =SetWindowsHookEx( WH_KEYBOARD_LL,keyProc1,GetModuleHandle(NULL),0);
}



int Run::special_key(char str[])
{
    if(strcmp(str,"CTRL")==0)
    {
        return 17;
    }
    else if(strcmp(str,"SHIFT")==0)
    {
        return 16;
    }
    else if(strcmp(str,"ENTER")==0)
    {
        return 13;
    }
    else if(strcmp(str,"TAB")==0)
    {
        return 9;
    }
    else if(strcmp(str,"BACKSPACE")==0)
    {
        return 8;
    }
    else if(strcmp(str,"ALT")==0)
    {
        return 18;
    }
    else if(strcmp(str,"UP")==0)
    {
        return 38;
    }
    else if(strcmp(str,"DOWN")==0)
    {
        return 40;
    }
    else if(strcmp(str,"LEFT")==0)
    {
        return 37;
    }
    else if(strcmp(str,"RIGHT")==0)
    {
        return 39;
    }
    else if(strcmp(str,"HOME")==0)
    {
        return 36;
    }
    else if(strcmp(str,"PGUP")==0)
    {
        return 33;
    }
    else if(strcmp(str,"PGDN")==0)
    {
        return 34;
    }
    else if(strcmp(str,"END")==0)
    {
        return 35;
    }
    else if(strcmp(str,"ESC")==0)
    {
        return 27;
    }
    else if(strcmp(str,"CAPSLOCK")==0)
    {
        return 20;
    }
    else if(strcmp(str,"DEL")==0)
    {
        return 46;
    }
    else if(strcmp(str,"F1")==0)
    {
        return 112;
    }
    else if(strcmp(str,"F2")==0)
    {
        return 113;
    }
    else if(strcmp(str,"F3")==0)
    {
        return 114;
    }
    else if(strcmp(str,"F4")==0)
    {
        return 115;
    }
    else if(strcmp(str,"F5")==0)
    {
        return 116;
    }
    else if(strcmp(str,"F6")==0)
    {
        return 117;
    }
    else if(strcmp(str,"F7")==0)
    {
        return 118;
    }
    else if(strcmp(str,"F8")==0)
    {
        return 119;
    }
    else if(strcmp(str,"F9")==0)
    {
        return 120;
    }
    else if(strcmp(str,"F10")==0)
    {
        return 121;
    }
    else if(strcmp(str,"F11")==0)
    {
        return 122;
    }
    else if(strcmp(str,"F12")==0)
    {
        return 123;
    }
    else
    {
        return -1;
    }
}


int Run::change(char &c)
{
    switch(c){
        case '!':c='1';break;
        case '@':c='2';break;
        case '#':c='3';break;
        case '$':c='4';break;
        case '%':c='5';break;
        case '^':c='6';break;
        case '&':c='7';break;
        case '*':c='8';break;
        case '(':c='9';break;
        case ')':c='0';break;
        case '_':c='-';break;
        case '+':c='=';break;
        case '{':c='[';break;
        case '}':c=']';break;
        case '|':c='\\';break;
        case '"':c='\'';break;
        case ':':c=';';break;
        case '<':c=',';break;
        case '>':c='.';break;
        case '?':c='?';break;
        default:
            return 0;
    }
    return 1;
}

void Run::change1(char &c)
{
    if(c==';')
        c=0XBA;
    else if(c=='.')
        c=0XBE;
    else if(c==',')
        c=0xbc;
    else if(c=='/')
        c=0XBF;
    else if(c=='[')
        c=0xdb;
    else if(c==']')
        c=0xdd;
    else if(c=='\\')
        c=0xdc;
    else if(c=='\'')
        c=0xde;
    else if(c=='`')
        c=0xc0;
}


void Run::output_key(char c)
{
    if(change(c)==1)
    {
        change1(c);
        keybd_event(16,0, 0, 0);
        keybd_event((BYTE)c,0, 0, 0);
        keybd_event((BYTE)c,0, KEYEVENTF_KEYUP, 0);
        keybd_event(16, 0, KEYEVENTF_KEYUP, 0);
    }
    else
    {
        change1(c);
        keybd_event((BYTE)c,0, 0, 0);
        keybd_event((BYTE)c,0, KEYEVENTF_KEYUP, 0);
    }
// 	keybd_event((BYTE)str[i],0, 0, 0);
//	keybd_event((BYTE)str[i], 0, KEYEVENTF_KEYUP, 0);
}

int Run::runcmd(char cmd[])
{
    char temp[100];
    sscanf(cmd,"%s",temp);
    if(strcmp(temp,"move")==0||strcmp(temp,MOVE)==0)
    {
        sscanf(cmd,"%s %d %d",temp,&x,&y);
        point.x=x;
        point.y=y;
        ::SetCursorPos(point.x, point.y);
    }
    else if(strcmp(temp,"lclick")==0)
    {
        sscanf(cmd,"%s %d %d",temp,&x,&y);
        point.x=x;
        point.y=y;
        ::mouse_event(MOUSEEVENTF_LEFTDOWN, point.x, point.y, 0, 0);
        ::mouse_event(MOUSEEVENTF_LEFTUP, point.x, point.y, 0, 0);

    }
    else if(strcmp(temp,LCLICK)==0)
    {
        ::mouse_event(MOUSEEVENTF_LEFTDOWN, point.x, point.y, 0, 0);
        ::mouse_event(MOUSEEVENTF_LEFTUP, point.x, point.y, 0, 0);
    }
    else if(strcmp(temp,"lup")==0)
    {
        sscanf(cmd,"%s %d %d",temp,&x,&y);
        point.x=x;
        point.y=y;
        ::mouse_event(MOUSEEVENTF_LEFTUP, point.x, point.y, 0, 0);
    }
    else if(strcmp(temp,LUP)==0)
    {
        ::mouse_event(MOUSEEVENTF_LEFTUP, point.x, point.y, 0, 0);
    }
    else if(strcmp(temp,"ldown")==0)
    {
        sscanf(cmd,"%s %d %d",temp,&x,&y);
        point.x=x;
        point.y=y;
        ::mouse_event(MOUSEEVENTF_LEFTDOWN, point.x, point.y, 0, 0);
    }
    else if(strcmp(temp,LDOWN)==0)
    {
        ::mouse_event(MOUSEEVENTF_LEFTDOWN, point.x, point.y, 0, 0);
    }
    else if(strcmp(temp,"dlclick")==0)
    {
        sscanf(cmd,"%s %d %d",temp,&x,&y);
        point.x=x;
        point.y=y;
        ::mouse_event(MOUSEEVENTF_LEFTDOWN, point.x, point.y, 0, 0);
        ::mouse_event(MOUSEEVENTF_LEFTUP, point.x, point.y, 0, 0);
        ::mouse_event(MOUSEEVENTF_LEFTDOWN, point.x, point.y, 0, 0);
        ::mouse_event(MOUSEEVENTF_LEFTUP, point.x, point.y, 0, 0);
    }
    else if(strcmp(temp,DLCLICK)==0)
    {
        ::mouse_event(MOUSEEVENTF_LEFTDOWN, point.x, point.y, 0, 0);
        ::mouse_event(MOUSEEVENTF_LEFTUP, point.x, point.y, 0, 0);
        ::mouse_event(MOUSEEVENTF_LEFTDOWN, point.x, point.y, 0, 0);
        ::mouse_event(MOUSEEVENTF_LEFTUP, point.x, point.y, 0, 0);
    }
    else if(strcmp(temp,"rclick")==0)
    {
        sscanf(cmd,"%s %d %d",temp,&x,&y);
        point.x=x;
        point.y=y;
        ::mouse_event(MOUSEEVENTF_RIGHTDOWN, point.x, point.y, 0, 0);
        ::mouse_event(MOUSEEVENTF_RIGHTUP, point.x, point.y, 0, 0);
    }
    else if(strcmp(temp,RCLICK)==0)
    {
        ::mouse_event(MOUSEEVENTF_RIGHTDOWN, point.x, point.y, 0, 0);
        ::mouse_event(MOUSEEVENTF_RIGHTUP, point.x, point.y, 0, 0);
    }
    else if(strcmp(temp,"rup")==0)
    {
        sscanf(cmd,"%s %d %d",temp,&x,&y);
        point.x=x;
        point.y=y;
        ::mouse_event(MOUSEEVENTF_RIGHTUP, point.x, point.y, 0, 0);
    }
    else if(strcmp(temp,RUP)==0)
    {
        ::mouse_event(MOUSEEVENTF_RIGHTUP, point.x, point.y, 0, 0);
    }
    else if(strcmp(temp,"rdown")==0)
    {
        sscanf(cmd,"%s %d %d",temp,&x,&y);
        point.x=x;
        point.y=y;
        ::mouse_event(MOUSEEVENTF_RIGHTDOWN, point.x, point.y, 0, 0);
    }
    else if(strcmp(temp,RDOWN)==0)
    {
        ::mouse_event(MOUSEEVENTF_RIGHTDOWN, point.x, point.y, 0, 0);
    }
    else if(strcmp(temp,"drclick")==0)
    {
        sscanf(cmd,"%s %d %d",temp,&x,&y);
        point.x=x;
        point.y=y;
        ::mouse_event(MOUSEEVENTF_RIGHTDOWN, point.x, point.y, 0, 0);
        ::mouse_event(MOUSEEVENTF_RIGHTUP, point.x, point.y, 0, 0);
        ::mouse_event(MOUSEEVENTF_RIGHTDOWN, point.x, point.y, 0, 0);
        ::mouse_event(MOUSEEVENTF_RIGHTUP, point.x, point.y, 0, 0);
    }
    else if(strcmp(temp,DRCLICK)==0)
    {
        ::mouse_event(MOUSEEVENTF_RIGHTDOWN, point.x, point.y, 0, 0);
        ::mouse_event(MOUSEEVENTF_RIGHTUP, point.x, point.y, 0, 0);
        ::mouse_event(MOUSEEVENTF_RIGHTDOWN, point.x, point.y, 0, 0);
        ::mouse_event(MOUSEEVENTF_RIGHTUP, point.x, point.y, 0, 0);
    }
    else if(strcmp(temp,"middown")==0)
    {
        sscanf(cmd,"%s %d %d",temp,&x,&y);
        point.x=x;
        point.y=y;
        ::mouse_event(MOUSEEVENTF_MIDDLEDOWN, point.x, point.y, 0, 0);
    }
    else if(strcmp(temp,MDOWN)==0)
    {
        ::mouse_event(MOUSEEVENTF_MIDDLEDOWN, point.x, point.y, 0, 0);
    }
    else if(strcmp(temp,"midup")==0)
    {
        sscanf(cmd,"%s %d %d",temp,&x,&y);
        point.x=x;
        point.y=y;
        ::mouse_event(MOUSEEVENTF_MIDDLEUP, point.x, point.y, 0, 0);
    }
    else if(strcmp(temp,MUP)==0)
    {
        ::mouse_event(MOUSEEVENTF_MIDDLEUP, point.x, point.y, 0, 0);
    }
    else if(strcmp(temp,"wheel")==0||strcmp(temp,WHEEL)==0)
    {
        int num=0;
        sscanf(cmd,"%s %d",temp,&num);
        ::mouse_event(MOUSEEVENTF_WHEEL, point.x, point.y, num, 0);
    }
    else if(strcmp(temp,"inputn_down")==0||strcmp(temp,IDOWN)==0)
    {
        int c=0;
        sscanf(cmd,"%s %d",temp,&c);
        keybd_event(c,0,0,0);
    }
    else if(strcmp(temp,"inputn_up")==0||strcmp(temp,IUP)==0)
    {
        int c=0;
        sscanf(cmd,"%s %d",temp,&c);
        keybd_event(c,0,KEYEVENTF_KEYUP,0);
    }
    else if(strcmp(temp,"input")==0||strcmp(temp,IINPUT)==0)
    {
        char str[100];
        strcpy(str,&cmd[6]);
        for(int i=0;i<strlen(str);i++)
        {
            if(str[i]<='z'&&str[i]>='a')
            {
                keybd_event(20,0,0,0);
                keybd_event(20,0,KEYEVENTF_KEYUP,0);
                keybd_event(20,0,0,0);
                keybd_event(20,0,KEYEVENTF_KEYUP,0);
                str[i]=str[i]-32;
                keybd_event((BYTE)str[i],0, 0, 0);
                keybd_event((BYTE)str[i], 0, KEYEVENTF_KEYUP, 0);
            }
            else if(str[i]<='Z'&&str[i]>='A'||str[i]<='9'&&str[i]>='0')
            {
                keybd_event((BYTE)str[i],0, 0, 0);
                keybd_event((BYTE)str[i], 0, KEYEVENTF_KEYUP, 0);
            }
            else
            {
                output_key(str[i]);
            }
        }
    }
    else if(strcmp(temp,"DOWN")==0||strcmp(temp,DDOWN)==0)
    {
        char Key[20];
        sscanf(cmd,"%s %s",temp,Key);
        int key=special_key(Key);
        if(key==-1)
            cout <<Key<<" "<<key<<endl;
        else
            ::keybd_event((BYTE)key,0, 0, 0);
    }
    else if(strcmp(temp,"UP")==0||strcmp(temp,UUP)==0)
    {
        char Key[20];
        sscanf(cmd,"%s %s",temp,Key);
        int key=special_key(Key);
        if(key==-1)
            cout <<Key<<" "<<key<<endl;
        else
            ::keybd_event((BYTE)key,0, KEYEVENTF_KEYUP, 0);
    }
    else if(strcmp(temp,"sleep")==0||strcmp(temp,SSLEEP)==0)
    {
        int time=0;
        sscanf(cmd,"%s %d",temp,&time);
        Sleep(time);
    }
    else if(strcmp(temp,"begin")==0||strcmp(temp,BEGIN)==0)
    {
        int circle=0;
        sscanf(cmd,"%s %d",temp,&circle);
        return circle;
    }
    else if(strcmp(temp,"end")==0||strcmp(temp,EEND)==0)
    {
        return -1;
    }
    else
    {
        cout <<temp<<endl;
        cout <<"wrong"<<endl;
    }
    return -2;
}

void Run::run_while(unsigned int place,int circle)
{
    unsigned int place1=0;
    int circle1=0;
    char str[200];
    while(circle>0&&!feof(p1))
    {
        fgets(str,200,p1);
        circle1=runcmd(str);
        if(circle1>=0)
        {
            place1=ftell(p1);
            run_while(place1,circle1);
        }
        else if(circle1==-1)
        {
            circle--;
            fseek(p1,place,SEEK_SET);
        }
        if(flag==1)
            break;
    }
}

int Run::run_file(const char name[])
{
    p1=fopen(name,"r");
    if(p1==NULL)
        return 0;
    char str[200];
    unsigned int place=0;
    int circle=0;
    flag=0;
    while(!feof(p1))
    {
        fgets(str,200,p1);
        circle=runcmd(str);
        if(circle>=0)
        {
            place=ftell(p1);
            run_while(place,circle);
        }
        if(flag==1)
            break;
    }
}

void Run::run()
{
    flag=0;
    while(run_flag||circle>0)
    {
        circle--;
        this->run_file(filename);
        if(flag==1)
            return ;
        Sleep(sleep_time);
    }
    unHook1();
}

void Run::set_param(int sleep1, int circle1, char file[], bool run_flag1)
{
    this->sleep_time=sleep1;
    this->circle=circle1;
    this->run_flag=run_flag1;
    strcpy(filename,file);
    setHook1();
}
