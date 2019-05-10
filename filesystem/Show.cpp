#include"Show.h"

Show::Show()
{

}

Show::~Show()
{

}

void Show::diretect_show(char filename[])
{
    directect=true;
    strcpy(open_buf,filename);
}

bool Show::init_data(Mat show_dst,Mat dst,const char show_text[],Scalar back1, Scalar fore1)
{
    strcpy(show_text1,show_text);
    show_src=show_dst;
    src=dst;
    h=src.rows;
    w=src.cols;
    back=back1;
    fore=fore1;

    directect=false;
    memset(buf_x,0,80);
    buf_y=0;

    x=0;
    y=0;
    last_x=0;
    last_y=0;

    char_h=16;
    char_w=11;

    max_w=(w-60)/13;
    max_h=h/char_h-3;

    if(max_h>75)
    {
        valid=false;
        return false;
    }

    find_str_flag=0;
    find_str_num=0;
    find_x=0,find_y=0;

    open_flag=1;
    open_num=0;
    num_place=0;
    now_place=0;


    t=(max_h+2)*char_h;
    l.x=0,l.y=t+3;
    r.x=w-1,r.y=t+char_h+4;
    p=NULL;

    for(int y=0;y<src.rows;++y)
    {
        for(int x=0;x<src.cols;++x)
        {
            for(int c=0;c<src.channels();c++)
                src.data[y * src.step + x * src.channels() + c]=back(c);
        }
    }

    valid=true;
    return true;
}

void Show::run()
{
    if(!valid)
        return;
    open_flag=1;
    open_num=0;

    if(!directect)
    {
        show_str(src,0,strlen("------------help infomation-----------"),"------------help infomation-----------");
        show_str(src,1,strlen("----ctrl+o : open the file to look"),"----ctrl+o : open the file to look");
        show_str(src,2,strlen("----ctrl+f : find the string "),"----ctrl+f : find the string ");
        show_str(src,3,strlen("----ctrl+e : exit"),"----ctrl+e : exit");
        show_str(src,4,strlen("----f1     : find the next dst string "),"----f1     : find the next dst string ");
        show_str(src,5,strlen("----f2     : help infomation "),"----f2     : help infomation ");

        show_str(src,max_h+2,11,"open file: ");
    }
    else
    {
        char temp[100]="file: ";
        if(!start())
        {
            strcpy(temp,"the file ");
            strcat(temp,open_buf);
            strcat(temp," is not exist!");
            show_str(src,max_h+2,strlen(temp),temp);
            return ;
        }
        open_flag=0;
        strcat(temp,open_buf);
        dispear_area(src,l,r);
        show_str(src,max_h+2,strlen(temp),temp);
        show_buf(src);
        set_cursor(src,0,0);
    }

    while(1)
    {
        int input=waitKey(10);
        if(!directect&&input!=-1&&open_flag==1)
        {
            if(p!=NULL)
                fclose(p);
            p=NULL;
            if(input==ENTER)
            {
                if(!start()||open_num==0)
                {
                    dispear_area(src,l,r);
                    show_str(src,max_h+2,10,"open file: ");
                    open_num=0;
                }
                else
                {
                    open_flag=0;
                    char temp[100]="file: ";
                    strcat(temp,open_buf);
                    dispear_area(src,l,r);
                    show_str(src,max_h+2,strlen(temp),temp);
                    show_buf(src);
                }
                continue;

            }
            else
            {
                input_str(open_num,open_buf,input);
            }
            char open[240]="open file: ";
            strcat(open,open_buf);
            show_str(src,max_h+2,strlen(open),open);
        }
        else if(input==CTRL_F)
        {
            find_str_flag=1;
            find_str_num=0;
            dispear_area(src,l,r);
            show_str(src,max_h+2,6,"input: ");
        }
        else if(input!=-1&&find_str_flag==1)
        {
            if(input==ENTER)
            {
                find_str_flag=0;
                find_x=x;
                find_y=y;
                find_str(src,find_x,find_y);
                x=find_x;
                y=find_y;
                set_cursor(src,x,y);
                find_x++;
                continue;
            }
            else
            {
                input_str(find_str_num,find_str_buf,input);
            }
            char temp[100]="input: ";
            strcat(temp,find_str_buf);
            show_str(src,max_h+2,strlen(temp),temp);
        }
        else if(input==UP)
        {
            if(y>0)
                y--;
            else if(now_place>0)
            {
                now_place--;
                fseek(p,place_flag[now_place],SEEK_SET);
                buf_y=0;
                add_to_buf(p);
                show_buf(src);
                x=0,y=max_h+1;
                set_cursor(src,x,y);
            }
            set_cursor(src,x,y);
        }
        else if(input==DOWN)
        {
            if(y<=max_h)
                y++;
            else if(now_place<num_place-1)
            {
                now_place++;
                fseek(p,place_flag[now_place],SEEK_SET);
                buf_y=0;
                add_to_buf(p);
                show_buf(src);
                x=0,y=0;
                set_cursor(src,x,y);
            }
            set_cursor(src,x,y);
        }
        else if(input==LEFT)
        {
            if(x>0)
                x--;
            set_cursor(src,x,y);
        }
        else if(input==RIGHT)
        {
            if(x<=max_w)
                x++;
            set_cursor(src,x,y);
        }
        else if(input==PGUP)
        {
            if(now_place>0)
            {
                now_place--;
                fseek(p,place_flag[now_place],SEEK_SET);
                buf_y=0;
                add_to_buf(p);
                show_buf(src);
                x=0,y=0;
                set_cursor(src,x,y);
            }

        }
        else if(input==PGDOWN)
        {
            if(now_place<num_place-1)
            {
                now_place++;
                fseek(p,place_flag[now_place],SEEK_SET);
                buf_y=0;
                add_to_buf(p);
                show_buf(src);
                x=0,y=0;
                set_cursor(src,x,y);
            }
        }
        else if(input==END)
        {
            if(now_place!=num_place-1)
            {
                now_place=num_place-1;
                fseek(p,place_flag[now_place],SEEK_SET);
                buf_y=0;
                add_to_buf(p);
                show_buf(src);

                y=buf_y-1;
                x=buf_x[y];
                set_cursor(src,x,y);
            }
        }
        else if(input==HOME)
        {
            if(now_place!=0)
            {
                now_place=0;
                fseek(p,place_flag[now_place],SEEK_SET);
                buf_y=0;
                add_to_buf(p);
                show_buf(src);

                x=0,y=0;
                set_cursor(src,x,y);
            }
        }
        else if(!directect&&input==CTRL_O)
        {
            open_flag=1;
            open_num=0;
            x=0,y=0;
            last_x=0,last_y=0;
            num_place=0;
            find_str_flag=0;
            now_place=0;
            dispear_screen(src);
            show_str(src,max_h+2,11,"open file: ");
        }
        else if(input==CTRL_E)
        {
            break;
        }
        else if(input==F1)
        {
            if(find_str_num>0)
            {
                char temp[100]="search: ";
                strcat(temp,find_str_buf);
                dispear_area(src,l,r);
                show_str(src,max_h+2,strlen(temp),temp);
                if(find_x!=x+1)
                    find_x=x,find_y=y;
                find_str(src,find_x,find_y);
                x=find_x;
                y=find_y;
                set_cursor(src,x,y);
                find_x++;
            }
        }
        else if(input==F2)
        {
            dispear_screen(src);
            show_str(src,0,strlen("------------help infomation-----------"),"------------help infomation-----------");
            show_str(src,1,strlen("----ctrl+o : open the file to look"),"----ctrl+o : open the file to look");
            show_str(src,2,strlen("----ctrl+f : find the string "),"----ctrl+f : find the string ");
            show_str(src,3,strlen("----ctrl+e : exit"),"----ctrl+e : exit");
            show_str(src,4,strlen("----f1     : find the next dst string "),"----f1     : find the next dst string ");
            show_str(src,5,strlen("----f2     : help infomation "),"----f2     : help infomation ");
            waitKey(0);
            dispear_screen(src);
            show_buf(src);
        }
        else if(input==ESC)
        {
            break;
        }
    }

    return ;
}


void Show::add_to_buf(FILE *p)
{
    char temp[800];
    char temp1[800];
    int num=0;
    int num1=0;
    while(!feof(p)&&buf_y<=max_h)
    {
        memset(temp1,0,800);
        num=0;
        fgets(temp1,800,p);
        num1=strlen(temp1)-1;
        if(temp1[num1]=='\n')
            temp1[num1]='\0';
        else
            num1++;
        for(int c=0;c<num1;c++)
        {
            if(temp1[c]=='\t')
            {
                for(int j=0;j<4;j++)
                    temp[num++]=' ';
                continue;
            }
            temp[num++]=temp1[c];
        }
        for(int i=0;i<num;i++)
        {
            int c=0;
            for(c=i;c<=i+max_w&&c<num;c++)
                buf[buf_y][c-i]=temp[c];
            buf_x[buf_y]=c-i;
            buf_y++;
            i=c-1;
        }
    }
}

bool Show::start()
{
    p=fopen(open_buf,"r+");
    if(p==NULL)
        return false;
    while(!feof(p)&&num_place<100000)
    {
        place_flag[num_place++]=ftell(p);
        buf_y=0;
        add_to_buf(p);
    }
    fseek(p,0,SEEK_SET);
    buf_y=0;
    add_to_buf(p);
    return true;
}

int Show::get_wide(char c)
{
    int x=0;
    if(c=='m')
        x+=5;
    else if(c=='f'||c=='i'||c=='I'||c=='j'||c=='t'||c=='l')
        x-=3;
    else if(c=='r'||c=='J')
        x-=2;
    else if(c=='W'||c=='U'||c=='V'||c=='X'||c=='Q'||c=='O'||c=='M')
        x+=2;
    else if(c>='A'&&c<='Z'||c=='w')
        x=1;

    return x+char_w;
}

void Show::line1(int sx,int sy,int ex,int ey,Scalar color)
{
    for(int y=sy;y<=ey;++y)
    {
        for(int x=sx;x<=ex+1;++x)
        {
            for(int c=0;c<src.channels();c++)
                src.data[y * src.step + x * src.channels() + c]=color(c);
        }
    }
}

void Show::dispear_area(Mat dst,Point lp,Point rp)
{
    if(rp.y>=h)
        rp.y=h-1;
    if(rp.x>=w)
        rp.x=w-1;
    if(lp.y<0)
        lp.y=0;
    if(lp.x<0)
        lp.x=0;
    for(int y=lp.y;y<=rp.y;++y)
    {
        for(int x=lp.x;x<=rp.x;++x)
        {
            for(int c=0;c<src.channels();c++)
                src.data[y * src.step + x * src.channels() + c]=0;
        }
    }
}

void Show::dispear_line(Mat dst)
{
    int tx=last_x;
    line1(tx,last_y+6,tx,last_y+char_h,back);
    imshow(show_text1,show_src);
}

void Show::set_cursor(Mat dst,int x,int y)
{
    dispear_line(dst);
    int tx=1;
    for(int i=0;i<x;i++)
    {
        tx+=get_wide(buf[y][i]);
    }
    last_x=tx;
    last_y=y*char_h;
    line1(tx,last_y+6,tx,last_y+char_h,Scalar(0,255,0,255));
//    line(dst,Point(tx,last_y+6),Point(tx,last_y+char_h),Scalar(0,255,0,255),2,8,0);
    imshow(show_text1,show_src);
}

void Show::show_text(Mat dst,int x,int y,char c)
{
    char temp[2]={0};
    temp[0]=c;
    putText(dst,temp,Point(x,y),FONT_HERSHEY_SIMPLEX,0.5,fore,1,8);
}

void Show::dispear_char_line(Mat dst,int y)
{
    int t=(y)*char_h;
    Point l(0,t+3);
    Point r(w-1,t+char_h+4);
    dispear_area(dst,l,r);
}


int Show::show_str(Mat dst,int y,int num,char str[])
{
    int x=char_w*-1+2;
    int ty=(y+1)*char_h;
    for(int i=0;i<num;i++)
    {
        x+=char_w;
        show_text(dst,x,ty,str[i]);
        if(str[i]=='m')
            x+=5;
        else if(str[i]=='f'||str[i]=='i'||str[i]=='I'||str[i]=='j'||str[i]=='t'||str[i]=='l')
            x-=3;
        else if(str[i]=='r'||str[i]=='J')
            x-=2;

        else if(str[i]=='W'||str[i]=='U'||str[i]=='V'||str[i]=='X'||str[i]=='Q'||str[i]=='O'||str[i]=='M')
            x+=2;
        else if(str[i]>='A'&&str[i]<='Z'||str[i]=='w')
            x+=1;
    }
    imshow(show_text1,show_src);
    return ty;
}


void Show::show_buf(Mat dst)
{
    dispear_screen(dst);
    int t=now_place*(max_h+1);
    int n=min(max_h+1,buf_y);
    for(int i=0;i<n;i++)
    {
        int ty=show_str(dst,i,buf_x[i],buf[i]);
        char temp[20];
        sprintf(temp,"|%04d",i+t);
        dispear_area(dst,Point(w-50,ty-char_h+3),Point(w-1,ty));
        putText(dst,temp,Point(w-50,ty),FONT_HERSHEY_SIMPLEX,0.5,fore,1,8);
        imshow(show_text1,show_src);

    }
    char temp[20];
    sprintf(temp,"Page: %d",now_place+1);
    show_str(dst,max_h+2,strlen(temp),temp);
}

void Show::input_str(int &num,char buf[],int input)
{
    if(input==BACKSPACE&&num>0)
    {
        buf[num-1]='\0';
        num--;
        dispear_area(src,l,r);
    }
    else if(input!=BACKSPACE&&input<160&&input>27)
    {
        buf[num++]=input;
        buf[num]='\0';
    }
}

void Show::dispear_screen(Mat dst)
{
    dispear_area(dst,Point(0,0),Point(w-1,h-1));
}

int Show::find_str(Mat dst,int &x,int &y)
{
    int l=strlen(find_str_buf);
    if(l==0)
        return 0;

    int i=0,j=0,n=0;

    for(n=y;n<buf_y;n++)
    {
        if(n==y)
            i=x;
        else
            i=0;
        for(;i<buf_x[n];i++)
        {
            for(j=0;j<l;j++)
            {
                if(find_str_buf[j]!=buf[n][i+j])
                    break;
            }
            if(j==l)
            {
                x=i;
                y=n;
                return 1;
            }
        }
    }
    x=0;
    y=0;

    now_place=(now_place+1)%num_place;
    fseek(p,place_flag[now_place],SEEK_SET);
    buf_y=0;
    add_to_buf(p);
    show_buf(dst);

    find_str(dst,x,y);

    return 0;
}
