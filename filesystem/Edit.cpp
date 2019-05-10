#include"Edit.h"

Edit::Edit()
{

}

Edit::~Edit()
{

}


bool Edit::init_data(Mat show_dst,Mat dst,char show_text[],char filename[],Scalar back1, Scalar fore1)
{
    strcpy(show_text1,show_text);
    strcpy(open_buf,filename);
    show_src=show_dst;
    src=dst;
    h=src.rows;
    w=src.cols;
    back=back1;
    fore=fore1;

    char_h=16;
    char_w=11;

    max_w=(w-60)/13;
    max_h=h/char_h-3;

    if(max_w>70)
    {
        valid=false;
        return false;
    }
    memset(buf_x,0,50000);
    buf_y=0;
    memset(flag,0,50000);

    x=0;
    y=0;
    last_x=0;
    last_y=0;

    find_str_flag=0;
    find_str_num=0;
    find_x=0,find_y=0;

    replace_str_flag=0;
    replace_str_num=0;
    replace_x=0,replace_y=0;

    copy_flag=0;
    copy_x=-1,copy_y=-1;
    last_copy_x=0,last_copy_y=0;

    cut_flag=0;
    cut_x=-1,cut_y=-1;
    last_cut_x=0,last_cut_y=0;

    save_name_flag=0;
    save_name_num=0;

    open_flag=1;
    open_num=0;

    start_y=0;

    t=(max_h+2)*char_h;
    l.x=0,l.y=t+3;
    r.x=w-1,r.y=t+char_h+4;

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


void Edit::run()
{

    if(!valid)
        return ;

    if(!start())
    {
        char temp[100];
        strcpy(temp,"the file ");
        strcat(temp,open_buf);
        strcat(temp," is not exist!");
        show_str(src,max_h+2,strlen(temp),temp);
        return ;
    }

    while(1)
    {
        int input=waitKey(10);
        if(input==CTRL_O)
        {

        }
        else if(input==F5)
        {
            help_show(src);
            waitKey(0);
            show_buf(src);
        }
        else if(input==PGUP)
        {
            start_y-=(max_h-1);
            start_y=std::max(0,start_y);
            show_buf(src);
        }
        else if(input==PGDOWN)
        {
            start_y+=(max_h-1);
            start_y=std::min(buf_y,start_y);
            show_buf(src);
        }
        else if(input!=-1&&save_name_flag==1)
        {
            if(input==ENTER)
            {
                if(save_name_num!=0)
                {
                    save_name_flag=0;
                    save_now(save_name_buf);
                    dispear_area(src,l,r);
                    show_str(src,max_h+2,strlen("save successfully"),"save successfully");
                }
                else
                {
                    save_name_num=0;
                }
                continue;
            }
            else
            {
                input_str(src,save_name_num,save_name_buf,input);
            }
            char open[240]="save file: ";
            strcat(open,save_name_buf);
            show_str(src,max_h+2,strlen(open),open);
        }
        else if(input==F3)
        {
            if(replace_str_num>0)
            {
                int t=strlen(replace_dst_buf);
                replace_x=0;
                replace_y=0;
                replace_str(src,replace_src_buf,replace_dst_buf,replace_x,replace_y);
                while(1)
                {
                    if(replace_x==0&&replace_y==0)
                        break;
                    replace_x+=t;
                    replace_str(src,replace_src_buf,replace_dst_buf,replace_x,replace_y);
                }
            }
        }
        else if(input==F4)
        {
            show_buf(src);
        }
        else if(input==F2)
        {
            if(replace_str_num>0)
            {
                char temp[100]="src: ";
                strcat(temp,replace_src_buf);
                strcat(temp,"   dst: ");
                strcat(temp,replace_dst_buf);
                dispear_area(src,l,r);
                show_str(src,max_h+2,strlen(temp),temp);
                if(replace_x!=x-strlen(replace_dst_buf))
                    replace_x=x,replace_y=y;
                replace_str(src,replace_src_buf,replace_dst_buf,replace_x,replace_y);
                draw_line(src,replace_x,replace_y);
                x=replace_x;
                y=replace_y;
                replace_x+=strlen(replace_dst_buf);
            }
        }
        else if(input==F1)
        {
            if(find_str_num>0)
            {
                char temp[100]="search: ";
                strcat(temp,find_str_buf);
                dispear_area(src,l,r);
                show_str(src,max_h+2,strlen(temp),temp);
                if(find_x!=x-1)
                    find_x=x,find_y=y;
                find_str(find_x,find_y);
                draw_line(src,find_x,find_y);
                x=find_x;
                y=find_y;
                find_x++;
            }
        }
        else if(input!=-1&&replace_str_flag==2)
        {
            if(input==ENTER)
            {
                replace_str_flag=0;
                replace_x=x;
                replace_y=y;
                replace_str(src,replace_src_buf,replace_dst_buf,replace_x,replace_y);
                draw_line(src,replace_x,replace_y);
                x=replace_x;
                y=replace_y;
                replace_x+=strlen(replace_dst_buf);
            }
            else
            {
                input_str(src,replace_str_num,replace_dst_buf,input);
            }
            char temp[100]="destine: ";
            strcat(temp,replace_dst_buf);

            show_str(src,max_h+2,strlen(temp),temp);
        }
        else if(input!=-1&&replace_str_flag==1)
        {
            if(input==ENTER)
            {
                replace_str_flag=2;
                replace_str_num=0;
                dispear_area(src,l,r);
                show_str(src,max_h+2,9,"destine: ");
                continue;
            }
            else
            {
                input_str(src,replace_str_num,replace_src_buf,input);
            }
            char temp[100]="source: ";
            strcat(temp,replace_src_buf);

            show_str(src,max_h+2,strlen(temp),temp);
        }
        else if(input!=-1&&find_str_flag==1)
        {
            if(input==ENTER)
            {
                find_str_flag=2;
                find_x=x;
                find_y=y;
                find_str(find_x,find_y);
                draw_line(src,find_x,find_y);
                x=find_x;
                y=find_y;
                find_x++;
                continue;
            }
            else
            {
                input_str(src,find_str_num,find_str_buf,input);
            }
            char temp[100]="input: ";
            strcat(temp,find_str_buf);
            show_str(src,max_h+2,strlen(temp),temp);
        }
        else if(input==UP)//shang
        {
            if(y!=0)
            {
                y--;
                if(y<start_y)
                {
                    start_y--;
                    show_buf(src);
                }
                draw_line(src,x,y);
            }
        }
        else if(input==DOWN)//xia
        {
            y++;
            if(y-start_y>=max_h)
            {
                start_y++;
                show_buf(src);
            }
            draw_line(src,x,y);
        }
        else if(input==LEFT)//zuo
        {
            if(x!=0)
            {
                x--;
                draw_line(src,x,y);
            }
        }
        else if(input==RIGHT)//you
        {
            if(x<=max_w)
            {
                x++;
                draw_line(src,x,y);
            }
        }
        else if(input==HOME)
        {
            x=0;
            if(y>=buf_y)
                y=buf_y-1;
            draw_line(src,x,y);
        }
        else if(input==END)
        {
            if(y>=buf_y)
                y=buf_y-1;
            x=buf_x[y];
            draw_line(src,x,y);
        }
        else if(input==CTRL_S)
        {
            char temp[100];
            save_now(open_buf);
            strcpy(temp,"save ");
            strcat(temp,open_buf);
            strcat(temp," sucessfully!");
            dispear_area(src,l,r);
            show_str(src,max_h+2,strlen(temp),temp);
        }
        else if(input==CTRL_V)
        {
            for(int i=0;i<strlen(copy_buf);i++)
            {
                input_char(src,copy_buf[i]);
            }
        }
        else if(input==CTRL_C)
        {
            cut_flag=0;
            if(copy_flag==0)
            {
                copy_x=x;
                copy_y=y;
                copy_flag=1;
                draw_line(src,copy_x,copy_y);
                last_copy_x=last_x;
                last_copy_y=y;
            }
            else if(copy_flag==1)
            {
                if(y>copy_y||(y==copy_y&&x>copy_x))
                {
                    copy_str(src,copy_x,copy_y,x,y);
                }
                else if(copy_y==y&&copy_x==x)
                {
                    dispear_area(src,l,r);
                    show_str(src,max_h,15,"nothing to copy");
                }
                else
                {
                    copy_str(src,x,y,copy_x,copy_y);
                }
                copy_flag=0;
                copy_x=-1;
                copy_y=-1;
                int last_copy_y1=(last_copy_y-start_y)*char_h;
                if(last_copy_y1+6>=0&&last_copy_y1+char_h>=0)
                    line1(last_copy_x,last_copy_y1+6,last_copy_x,last_copy_y1+char_h,Scalar(0,255,0));
                draw_line(src,x,y);
                imshow(show_text1,show_src);
            }
        }
        else if(input==CTRL_X)
        {
            copy_flag=0;
            if(cut_flag==0)
            {
                cut_x=x;
                cut_y=y;
                cut_flag=1;
                draw_line(src,cut_x,cut_y);
                last_cut_x=last_x;
                last_cut_y=y;
            }
            else if(cut_flag==1)
            {
                if(y>cut_y||(y==cut_y&&x>cut_x))
                {
                    cut_str(src,cut_x,cut_y,x,y);
                }
                else if(cut_y==y&&cut_x==x)
                {
                    dispear_area(src,l,r);
                    show_str(src,max_h,15,"nothing to copy");
                }
                else
                {
                    cut_str(src,x,y,cut_x,cut_y);
                }
                cut_flag=0;
                cut_x=-1;
                cut_y=-1;
                int last_cut_y1=(last_cut_y-start_y)*char_h;
                if(last_cut_y1+6>=0&&last_cut_y1+char_h>=0)
                    line1(last_cut_x,last_cut_y1+6,last_cut_x,last_cut_y1+char_h,Scalar(0,255,0));
                draw_line(src,x,y);
                imshow(show_text1,show_src);
            }
        }
        else if(input==CTRL_R)
        {
            dispear_area(src,l,r);
            replace_str_flag=1;
            replace_str_num=0;
            show_str(src,max_h+2,8,"source: ");
        }
        else if(input==CTRL_E)
        {
            start_y=std::max(0,buf_y-max_h);
            y=start_y+max_h-1;
            x=buf_x[y];
            show_buf(src);
            draw_line(src,x,y);
        }
        else if(input==CTRL_B)
        {
            y=0;
            x=0;
            start_y=0;
            show_buf(src);
            draw_line(src,x,y);
        }
        else if(input==CTRL_D)
        {
            del_line(src,y);
            for(int i=y;i<buf_y;i++)
            {
                dispear_char_line(src,i);
                show_line(src,i);
            }
            draw_line(src,x,y);
        }
        else if(input==CTRL_F)
        {
            dispear_area(src,l,r);
            find_str_flag=1;
            find_str_num=0;
            show_str(src,max_h+2,6,"input: ");
        }
        else if(input!=-1)
        {
            input_char(src,input);
        }

        if(input!=-1&&copy_flag==1)
        {
            int last_copy_y1=(last_copy_y-start_y)*char_h;
            if(last_copy_y1+6>=0&&last_copy_y1+char_h>=0)
                line1(last_copy_x,last_copy_y1+6,last_copy_x,last_copy_y1+char_h,Scalar(0,255,0));
            dispear_area(src,l,r);
            show_str(src,max_h+2,17,"---copy operation");
            continue;
        }
        else if(input!=-1&&cut_flag==1)
        {
            int last_cut_y1=(last_cut_y-start_y)*char_h;
            if(last_cut_y1+6>=0&&last_cut_y1+char_h>=0)
                line1(last_cut_x,last_cut_y1+6,last_cut_x,last_cut_y1+char_h,Scalar(0,255,0));
            dispear_area(src,l,r);
            show_str(src,max_h+2,17,"---cut operation");
            continue;
        }
        if(input==27)
            break;
    }
    return ;
}

void Edit::line1(int sx,int sy,int ex,int ey,Scalar color)
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


void Edit::dispear_area(Mat dst,Point lp,Point rp)
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
            for(int c=0;c<dst.channels();c++)
                dst.data[y * dst.step + x * dst.channels() + c]=0;
        }
    }
}

void Edit::dispear_line(Mat dst)
{
    int tx=last_x;
    line1(tx,last_y+6,tx,last_y+char_h,back);
    imshow(show_text1,show_src);
}

void Edit::draw_line(Mat dst,int x,int y)
{
    dispear_line(dst);
    int tx=1;
    for(int i=0;i<x;i++)
    {
        tx+=get_wide(buf[y][i]);
    }
    last_x=tx;
    last_y=(y-start_y)*char_h;
    if(last_y<0||last_y>=w)
        return ;
    line1(tx,last_y+6,tx,last_y+char_h,Scalar(0,255,0,255));
    imshow(show_text1,show_src);
}

int Edit::get_wide(char c)
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

void Edit::show_text(Mat dst,int x,int y,char c)
{
    char temp[2]={0};
    temp[0]=c;
    putText(dst,temp,Point(x,y),FONT_HERSHEY_SIMPLEX,0.5,fore,1,8);
}

void Edit::show_str(Mat dst,int y,int num,char str[])
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
}

void Edit::show_line(Mat dst,int y)
{
    int x=char_w*-1+2;
    int ty=(y+1-start_y)*char_h;
    if(y+1-start_y>max_h||y+1-start_y<0)
        return ;
    for(int i=0;i<buf_x[y];i++)
    {
        x+=char_w;
        show_text(dst,x,ty,buf[y][i]);
        if(buf[y][i]=='m')
            x+=5;
        else if(buf[y][i]=='f'||buf[y][i]=='i'||buf[y][i]=='I'||buf[y][i]=='j'||buf[y][i]=='t'||buf[y][i]=='l')
            x-=3;
        else if(buf[y][i]=='r'||buf[y][i]=='J')
            x-=2;

        else if(buf[y][i]=='W'||buf[y][i]=='U'||buf[y][i]=='V'||buf[y][i]=='X'||buf[y][i]=='Q'||buf[y][i]=='O'||buf[y][i]=='M')
            x+=2;
        else if(buf[y][i]>='A'&&buf[y][i]<='Z'||buf[y][i]=='w')
            x+=1;
    }
    char temp[20];
    sprintf(temp,"|%04d",y);
//    dispear_area(dst,Point(w-50,ty-char_h),Point(w-1,ty));
    putText(dst,temp,Point(w-50,ty),FONT_HERSHEY_SIMPLEX,0.5,fore,1,8);
    imshow(show_text1,show_src);
}

void Edit::show_buf(Mat dst)
{
    int e=std::min(buf_y,start_y+max_h);
    dispear_area(dst,Point(0,0),Point(w-1,(max_h+1)*char_h));
    for(int i=start_y;i<e;i++)
    {
        show_line(dst,i);
    }
}

void Edit::dispear_char_line(Mat dst,int y)
{
    int t=(y-start_y)*char_h;
    Point l(0,t+3);
    Point r(w-1,t+char_h+4);
    dispear_area(dst,l,r);
}


void Edit::add_char(int x,int y,char c,char flag[])
{
    if(y>=buf_y)
        buf_y=y+1;
    for(int i=buf_x[y]-1;i>=x;i--)
        buf[y][i+1]=buf[y][i];
    buf[y][x]=c;
    if(x>buf_x[y])
    {
        for(int i=buf_x[y];i<x;i++)
            buf[y][i]=' ';
        buf_x[y]=x+1;
    }
    else
        buf_x[y]++;
    flag[y]=1;
    if(buf_x[y]>max_w+1)
    {
        add_char(0,y+1,buf[y][buf_x[y]-1],flag);
        buf_x[y]=max_w+1;
    }
}

void Edit::del_line(Mat dst,int y)
{
    for(int i=y;i<buf_y;i++)
    {
        if(buf_x[i+1]>70)
            buf_x[i+1]=0;
        for(int c=0;c<buf_x[i+1];c++)
        {
            buf[i][c]=buf[i+1][c];
        }
        buf_x[i]=buf_x[i+1];
        buf_x[i+1]=0;
    }
    buf_y--;
    if(buf_y<0)
        buf_y=0;
    dispear_char_line(dst,buf_y);
}

int Edit::del_char(Mat dst)
{
    if(x>buf_x[y])
    {
        x=buf_x[y];
        return 2;
    }
    if(y>=buf_y)
    {
        x=buf_x[buf_y-1];
        y=buf_y-1;
        return 2;
    }
    if(x==0&&y==0)
        return 0;
    int flag=0;
    if(x==0&&y!=0)
    {
        int i=0;
        int d=buf_x[y-1];
        for(i=0;i<buf_x[y]&&d<=max_w;i++)
        {
            buf[y-1][d++]=buf[y][i];
        }
        x=buf_x[y-1];
        buf_x[y-1]=d;
        buf_x[y]-=i;
        for(d=0;d<buf_x[y];d++)
            buf[y][d]=buf[y][i++];
        y--;
        if(y-start_y<0)
        {
            start_y--;
            show_buf(dst);
        }

        flag=1;
        if(buf_x[y+1]==0)
        {
            dispear_char_line(dst,y+1);
            del_line(dst,y+1);
            for(int i=y;i<buf_y;i++)
            {
                dispear_char_line(dst,i);
                show_line(dst,i);
            }
            return 0;
        }
    }
    else
    {
        for(int i=x;i<buf_x[y];i++)
        {
            buf[y][i-1]=buf[y][i];
        }
        buf_x[y]--;
        x--;
        dispear_char_line(dst,y);
        show_line(dst,y);
    }
    if(flag==1)
    {
        for(int i=y;i<=y+1;i++)
        {
            dispear_char_line(dst,i);
            show_line(dst,i);
        }
    }
}

void Edit::add_line(Mat dst)
{
    int i=0;
    for(i=buf_y-1;i>y;i--)
    {
        for(int c=0;c<buf_x[i];c++)
        {
            buf[i+1][c]=buf[i][c];
        }
        buf_x[i+1]=buf_x[i];
    }

    buf_y=buf_y+1;

    buf_x[y+1]=0;
    for(i=x;i<buf_x[y];i++)
    {
        buf[y+1][buf_x[y+1]++]=buf[y][i];
    }
    buf_x[y]=x;
    int e=std::min(buf_y,start_y+max_h);
    for(int i=y;i<e;i++)
    {
        dispear_char_line(dst,i);
        show_line(dst,i);
    }
    x=0;
    y++;
    if(y-start_y>=max_h)
    {
        start_y=y-max_h+1;
        show_buf(dst);
    }
    draw_line(dst,x,y);
}

int Edit::find_str(int &x,int &y)
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
    return 0;
}

void Edit::input_str(Mat src,int &num,char buf[],int input)
{
    if(input==BACKSPACE&&num>0)
    {
        buf[num-1]='\0';
        num--;
        dispear_area(src,l,r);
    }
    else if(input==CTRL_V)
    {
        for(int i=0;i<strlen(copy_buf);i++)
        {
            if(copy_buf[i]==ENTER)
                break;
            buf[num++]=copy_buf[i];
        }
    }
    else if(input!=BACKSPACE&&input<160&&input>27)
    {
        buf[num++]=input;
        buf[num]='\0';
    }
}

void Edit::replace_str(Mat src1,char src[],char dst[],int x1,int y1)
{
    char temp[1000]={0};
    int num=0;

    int ls=strlen(src);
    int ld=strlen(dst);

    int i=0,j=0,c=0,n=0;

    for(n=y1;n<buf_y;n++)
    {
        num=0;
        i=0;
        int flag=0;
        if(n==y1)
        {
            for(i=0;i<x1;i++)
                temp[num++]=buf[n][i];
            i=x1;
        }
        for(;i<buf_x[n];i++)
        {
            if(flag==0)
            {
                for(j=0;j<ls;j++)
                {
                    if(src[j]!=buf[n][i+j])
                        break;
                }
                if(j==ls)
                {
                    replace_x=i;
                    replace_y=n;
                    for(c=0;c<ld;c++)
                        temp[num++]=dst[c];
                    i=i+j-1;
                    flag=1;
                    continue;
                }
            }
            temp[num++]=buf[n][i];
        }
        if(flag==1)
        {
            if(num-1<=max_w)
            {
                for(i=0;i<num;i++)
                    buf[n][i]=temp[i];
                buf_x[n]=num;
            }
            else
            {
                for(i=0;i<=max_w;i++)
                    buf[n][i]=temp[i];
                buf_x[n]=max_w;
                x=0;
                y=n+1;
                for(i;i<num;i++)
                {
                    input_char(src1,temp[i]);
                }
                input_char(src1,13);
            }
            dispear_char_line(src1,n);
            show_line(src1,n);
            break;
        }
    }
    if(n==buf_y)
    {
        replace_x=0;
        replace_y=0;
    }
}

void Edit::input_char(Mat dst,char c)
{
    if(c>255)
        return ;
    switch(c){
        case BACKSPACE:{
            del_char(dst);
            draw_line(dst,x,y);
            break;
        }
        case ESC:break;
        case ENTER:
            add_line(dst);
            break;
        case TAB:
            for(int i=0;i<4;i++)
            {
                input_char(dst,' ');
            }
            break;
        default:
            add_char(x,y,c,flag);
            x++;
            if(x>max_w)
                x=0,y++;
            for(int i=0;i<buf_y;i++)
            {
                if(flag[i]==1)
                {
                    dispear_char_line(dst,i);
                    show_line(dst,i);
                    flag[i]=0;
                }
            }
            draw_line(dst,x,y);
    }
}
void Edit::cut_str(Mat dst,int sx,int sy,int ex,int ey)
{
    char temp[50];
    int i=0,j=0,n=0;
    sprintf(temp,"cut  x:%d y:%d -->x:%d y:%d",sx,sy,ex,ey);
    dispear_area(dst,l,r);
    show_str(dst,max_h+2,strlen(temp),temp);

    ey=std::min(ey,buf_y-1);
    ex=std::min(ex,buf_x[ey]);
    int num=0;
    for(i=sy;i<=ey;i++)
    {
        j=0;
        n=buf_x[i];
        if(i==sy)
            j=sx;
        else if(i==ey)
            n=ex;
        for(j;j<n;j++)
        {
            copy_buf[num++]=buf[i][j];
        }
        if(i!=ey&&(buf_x[i]<max_w+1))
            copy_buf[num++]=ENTER;
    }
    x=ex,y=ey;
    while(1)
    {
        if(x==sx&&y==sy)
            break;
        del_char(dst);
    }

    copy_buf[num]='\0';
}

void Edit::copy_str(Mat dst,int sx,int sy,int ex,int ey)
{
    char temp[50];
    int i=0,j=0,n=0;
    sprintf(temp,"copy  x:%d y:%d -->x:%d y:%d",sx,sy,ex,ey);
    dispear_area(dst,l,r);
    show_str(dst,max_h+2,strlen(temp),temp);

    ey=std::min(ey,buf_y-1);
    ex=std::min(ex,buf_x[ey]);
    int num=0;
    for(i=sy;i<=ey;i++)
    {
        j=0;
        n=buf_x[i];
        if(i==sy)
            j=sx;
        else if(i==ey)
            n=ex;
        for(j;j<n;j++)
        {
            copy_buf[num++]=buf[i][j];
        }
        if(i!=ey&&(buf_x[i]<max_w+1))
            copy_buf[num++]=ENTER;
    }
    copy_buf[num]='\0';
}
void Edit::save_now(char name[])
{
    FILE *p=fopen(name,"w+");
    for(int i=0;i<buf_y;i++)
    {
        buf[i][buf_x[i]]='\0';
        if(buf_x[i]==max_w+1)
        {
            fprintf(p,"%s",buf[i]);
        }
        else
        {
            fprintf(p,"%s\n",buf[i]);
        }
    }
    fclose(p);
}

bool Edit::start()
{
    FILE *p=NULL;
    p=fopen(open_buf,"r+");
    if(p==NULL)
        return false;

    char temp[500];
    char temp1[500];
    int num=0;
    int num1=0;
    while(!feof(p)&&buf_y<50000)
    {
        memset(temp1,0,200);
        num=0;
        fgets(temp1,200,p);
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
    fclose(p);
    show_buf(src);
    draw_line(src,0,0);
    return true;
}

void Edit::help_show(Mat dst)
{
    char help[21][100]={
        "up|down|left|right : choose direction button",
        "end : move to the line end",
        "home : move to the line begin",
        "pgup : move to the last page",
        "pgdn : move to the next page",
        "ctrl_b : move to the begin of file",
        "ctrl_e : move to the end of file",
        "ctrl_d : delete the line which cursor place",
        "ctrl_s : save file operation",
        "ctrl_f : find operation,input the src and dst",
        "ctrl_r : replace operation,input the src and dst",
        "ctrl_c : copy operation,first push start,second push end",
        "ctrl_x : cut operation,first push start,second push end",
        "ctrl_v : after the copy/cut operation,paste string",
        "ctrl_o : close now file without save,open other file",
        "f1 : after the find operation,find next",
        "f2 : after the replace operation,replace single",
        "f3 : after the replace operation,replace all",
        "f4 : flush the screen",
        "f5 : help information",
        "support enter|tab|backspace button"
    };
    dispear_area(src,Point(0,0),Point(w-1,h-1));
    show_str(dst,0,strlen("*************help information************"),"*************help information************");
    for(int i=1;i<=21;i++)
    {
        show_str(dst,i,strlen(help[i-1]),help[i-1]);
    }
    show_str(dst,22,strlen("*****************************************"),"*****************************************");
}
