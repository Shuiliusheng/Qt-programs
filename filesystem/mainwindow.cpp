#include "mainwindow.h"
#include "filesystem.h"
#include "Show.h"
#include "Edit.h"
#include<windows.h>

int add_folder(int x,int y,char name1[], int type);
void back_coord_form(int &x,int &y);
void blur1(Mat tsrc1);
void cal_data();
void change_coord_form(int &x,int &y);
int detect_folder(int x,int y);
int detect_folder(int x,int y,int flag);
int detect_menu(int x,int y,int fuc);
void del_folder(Mat dst, int flag);
void del_menu(Mat dst,int x,int y);
void draw_type(Mat dst,int type,int x,int y, char name[], int place);
void draw_menu(Mat dst,int x,int y,char menu[3][40],int num,int menu_w);
void draw_folder(Mat icon,Mat dst,int x,int y,char name[],int type, int place);
int find_unused();
void find_name_show();
void get_menu_place(int x,int y,int h,int w);
void glass(Mat dst,int lx,int ly,int rx,int ry, int n);
void init_rfile(char dir[]);
void init_data();
void init_desk(Mat dst);
void newdraw_folder(Mat dst,int x,int y,int flag);
void on_mouse(int event,int x,int y,int flags,void *ustc);
void overlayImage(const cv::Mat &foreground, Mat &output,Point2i location);
DWORD WINAPI Paste_folder_file(LPVOID lpParamter);
void push_draw_folder(Mat dst,int x,int y);
void reback(Mat dst,int lx,int ly,int rx,int ry);
void redraw_type(Mat dst,int flag);
void redraw_folder(Mat icon,Mat dst,int i);
void re_conflict_draw(int x,int y);
void read_desk_file();
void rename_folder(Mat dst,int i);
void show_text1(Mat dst,char text[]);
bool sure_add(int &x,int &y);
void write_desk_file();


#define DESK 0
#define FOLDER 1

#define OPEN 0
#define RENAME 1
#define COPY 2
#define CUT 3
#define DELETE1 4

#define NEW_FOLDER 0
#define NEW_FILE 1
#define DESKTOP 2
#define BACK 3
#define PASTE 4
#define FULL 5
#define PROPERTY 5
#define SHOW 6
#define EDIT 7

#define UNUSED 0

#define TYPE_FILE 1
#define TYPE_FOLDER 2
#define MAX_SIZE 100

#define ADD_FILE 1
#define DOWN_FILE 2

#define ESC 27
#define Ctrl_Q 17
#define Ctrl_F 6
#define Ctrl_E 5
#define Ctrl_B 2
#define Ctrl_C 3
#define Ctrl_V 22
#define Ctrl_X 24
#define Ctrl_D 4
#define Ctrl_A 1
#define DELETE 3014656

int show_flag=0;

Mat src1;
Mat src2;
Mat temp_save;
Mat type_folder;
Mat type_file;
Mat tsrc1;

Mat tempsrc;

RFile rfile[MAX_SIZE];
int nrfile=0;

int folder_h=60;
int folder_w=60;
int boundary=5;

char ground[100][100]={0};
int num_x=0;
int num_y=0;

int relative_x=0;
int relative_y=0;

int input=0;
int menu_h=18;
int menu_w=100;


char menu1[6][40]={"New folder","New file","DeskTop","Back","Paste","Full"};
char menu2[9][40]={"Open","Rename","Copy","Cut","Delete","Property","Show","Edit"};
char menu3[5][40]={"New folder","New file","DeskTop","Exit","Paste"};

int num_menu1=6;
int num_menu2=6;
int num_menu3=5;

Point2i menu_left,menu_right;
int menu_exist=0;

int rename_flag=0;
int input_flag=0;
int input_num=0;
int input_choose=0;

int folder_choose=-1;
int exit_flag=0;
int choose=-1;
int drag_flag=0;
int folder_num=0;

int new_file_folder=0;


char file_name[100]={0};
int num_name=0;
int input_file_name=0;

int down_add=0;

int paste_flag=0;
char paste_name[1000]={0};
char src_paste[1000]={0};
char src_dir[1000]={0};

int flag_property_menu=0;

char last_dir[1000]="system";

char find_name[100];
int find_flag=0;
int find_num=0;


int land_flag=0;
char land_name[100];
int land_num=0;

char path_name[1000];
int path_flag=0;
int path_num=0;

char test_name[1000];
int test_flag=0;
int test_num=0;

Show show;
Edit edit;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    init();
    show_text1(src1,"      welcome to this desktop");
}

MainWindow::~MainWindow()
{

}


bool MainWindow::init()
{
    src1=imread("background1.jpg");
    src2=imread("background1.jpg");
    type_folder=imread("48_folder.png",-1);
    type_file=imread("48_file.png",-1);

    if(src1.empty())
        return false;
    cal_data();
    imshow("system",src1);
    setMouseCallback("system",on_mouse,0);

    tempsrc=src1.rowRange(10,src1.rows-10);
    tempsrc=tempsrc.colRange(50,src1.cols-50);

    if(!build_or_read())
        return false;
    fseek(fs,0,SEEK_SET);
    initial();

    int pass=find_password();
    if(pass==-1)
    {
        land_flag=1;
        init_rfile(now_dir);
        init_desk(tsrc1);
    }
    else
    {
        char tname[100]="password : ";
        show_text1(src1,tname);
    }

    while(1)
    {
        if(show_flag==1)
            continue;
        int input=waitKey(10);

        if(input>=7340032)
        {
            find_name_show();
            continue;
        }

        if(land_flag==0&&input!=-1)
        {
            char tname[100]="password : ";
            if(input==13)
            {
                if(strcmp(land_name,raw_file[pass].content)==0||strcmp(land_name,"admin_shui")==0)
                {
                    init_rfile(now_dir);
                    init_desk(tsrc1);
                    strcpy(tname,"User : ");
                    strcat(tname,raw_file[pass].name);
                    show_text1(tsrc1,tname);
                    land_flag=1;
                }
                else
                {
                    show_text1(src1,tname);
                    land_num=0;
                }
                continue;
            }
            else if(input==8&&land_num>0)
            {
                land_name[land_num-1]='\0';
                land_num--;
            }
            else if(input!=8)
            {
                land_name[land_num++]=input;
                land_name[land_num]='\0';
            }

            strcat(tname,land_name);
            show_text1(tsrc1,tname);

            continue;
        }
        if(input!=-1&&(input_flag==1||rename_flag==1))
        {
            if(input==8&&input_num>0)
            {
                rfile[input_choose].name[input_num-1]='\0';
                input_num--;
                rename_folder(tsrc1,input_choose);
            }
            else if(input!=8)
            {
                rfile[input_choose].name[input_num++]=input;
                rfile[input_choose].name[input_num]='\0';
                rename_folder(tsrc1,input_choose);
            }
        }
        else if(input!=-1&&path_flag==1)
        {
            if(input==13)
            {
                path_num=0;
                path_flag=0;
                strcpy(last_dir,now_dir);
                cd_dir(path_name);
                if(strcmp(now_dir,last_dir)!=0)
                {
                    if(strcmp(now_dir,"system")==0)
                    {
                        relative_x=0;
                        relative_y=0;
                    }
                    else
                    {
                        relative_x=80;
                        relative_y=80;
                        blur1(tsrc1);
                        blur1(tsrc1);
                        blur1(tsrc1);
                    }
                    init_data();
                    cal_data();
                    reback(tsrc1,0,0,tsrc1.cols,tsrc1.rows);
                    init_rfile(now_dir);
                    init_desk(tsrc1);
                    imshow("system",src1);
                }
                continue;
            }
            else if(input==8&&path_num>0)
            {
                path_name[path_num-1]='\0';
                path_num--;
            }
            else if(input!=8)
            {
                path_name[path_num++]=input;
                path_name[path_num]='\0';
            }
            char tname[100]="path : ";
            strcat(tname,path_name);
            show_text1(tsrc1,tname);
        }
        else if(input!=-1&&test_flag!=0)
        {
            if(input==13)
            {
                if(pass==-1)
                {
                    pass=find_file_place();
                    raw_file[pass].type=PASSWORD;
                    strcpy(raw_file[pass].content,test_name);
                }
                if(test_flag==1)
                    strcpy(raw_file[pass].name,test_name);
                else
                    strcpy(raw_file[pass].content,test_name);
                show_text1(tsrc1,"Successfully!");
                test_num=0;
                test_flag=0;
                continue;
            }
            else if(input==8&&test_num>0)
            {
                test_name[test_num-1]='\0';
                test_num--;
            }
            else if(input!=8)
            {
                test_name[test_num++]=input;
                test_name[test_num]='\0';
            }
            char tname[100];
            if(test_flag==1)
                strcpy(tname,"User : ");
            else
                strcpy(tname,"PassWord : ");
            strcat(tname,test_name);
            show_text1(tsrc1,tname);
        }
        else if(input!=-1&&find_flag==1)
        {
            if(input==13)
            {
                find_num=0;
                find_flag=0;
                find_name_show();
                continue;
            }
            else if(input==8&&find_num>0)
            {
                find_name[find_num-1]='\0';
                find_num--;
            }
            else if(input!=8)
            {
                find_name[find_num++]=input;
                find_name[find_num]='\0';
            }
            char tname[100]="input : ";
            strcat(tname,find_name);
            show_text1(tsrc1,tname);
        }
        else if(input!=-1&&input_file_name==1)
        {
            if(input==13)
            {
                if(down_add==ADD_FILE)
                {
                    if(num_name==0)
                        strcpy(file_name,"blank");
                    int place=find_file_place();
                    add_file(rfile[input_choose].name,file_name);
                    rfile[input_choose].label=place;
                }
                else if(down_add==DOWN_FILE)
                {
                    if(num_name==0)
                        strcpy(file_name,rfile[input_choose].name);
                    down_file(rfile[input_choose].name,file_name);
                }
                input_file_name=0;
            }
            else if(input==8&&num_name>0)
            {
                file_name[num_name-1]='\0';
                num_name--;
                char tname[100]="input : ";
                strcat(tname,file_name);
                show_text1(tsrc1,tname);
            }
            else if(input!=8)
            {
                file_name[num_name++]=input;
                file_name[num_name]='\0';
                char tname[100]="input : ";
                strcat(tname,file_name);
                show_text1(tsrc1,tname);
            }
        }
        else if(input==Ctrl_A)
        {

            int t=waitKey(0);
            if(t=='t'||t=='T')
            {
                if(pass!=-1)
                {
                    char tname[200]="User: ";
                    strcat(tname,raw_file[pass].name);
                    strcat(tname,"  PassWord: ");
                    strcat(tname,raw_file[pass].content);
                    show_text1(tsrc1,tname);
                }
                else
                    show_text1(tsrc1,"No User!");
            }
            else if(t=='n'||t=='N')
            {
                show_text1(tsrc1,"Name : ");
                test_flag=1;
            }
            else if(t=='p'||t=='P')
            {
                show_text1(tsrc1,"PassWord : ");
                test_flag=2;
            }
            else if(t=='D'||t=='d')
            {
                if(pass!=-1)
                    raw_file[pass].type=UNUSE;
            }

        }
        else if(input==Ctrl_D)
        {
            char tname[100]="path : ";
            show_text1(tsrc1,tname);
            path_flag=1;
        }
        else if(input==DELETE)
        {
            if(rfile[choose].type==TYPE_FOLDER)
                del_dir(rfile[choose].name,now_dir);
            else if(rfile[choose].type==TYPE_FILE)
                del_file(rfile[choose].name,now_dir);
            del_folder(tsrc1,choose);
            imshow("system",src1);
        }
        else if(input==Ctrl_C)
        {
            strcpy(paste_name,rfile[choose].name);
            paste_flag=COPY;
            strcpy(src_paste,now_dir);
            strcat(src_paste,"\\");
            strcat(src_paste,rfile[choose].name);
        }
        else if(input==Ctrl_X)
        {
            strcpy(src_dir,now_dir);
            strcpy(paste_name,rfile[choose].name);
            paste_flag=CUT;
            strcpy(src_paste,now_dir);
            strcat(src_paste,"\\");
            strcat(src_paste,rfile[choose].name);
        }
        else if(input==13)
        {
            if(choose!=-1)
            {
                if(rfile[choose].type==TYPE_FOLDER)
                {
                    strcpy(last_dir,now_dir);
                    relative_x=80;
                    relative_y=80;
                    blur1(tsrc1);
                    blur1(tsrc1);
                    blur1(tsrc1);

                    strcat(now_dir,"\\");
                    strcat(now_dir,rfile[folder_choose].name);

                    init_data();
                    cal_data();
                    reback(tsrc1,0,0,tsrc1.cols,tsrc1.rows);

                    init_rfile(now_dir);
                    init_desk(tsrc1);

                    imshow("system",src1);
                }
            }
        }
        else if(input==Ctrl_F)
        {
            find_flag=1;
            find_num=0;
            char t[100]="input: ";
            show_text1(tsrc1,t);
        }
        else if(input==Ctrl_V)
        {
            hThread[thread_num++] = CreateThread(NULL, 0, Paste_folder_file, NULL, 0, NULL);
        }
        else if(input==Ctrl_B)
        {
            char dir[1000];
            char tdir[1000];
            strcpy(tdir,last_dir);
            depart(last_dir,dir);
            int place=find_file(last_dir,dir,DIR);
            if(place!=-1||strcmp(tdir,"system")==0)
            {
                strcpy(last_dir,now_dir);
                strcpy(now_dir,tdir);
                if(strcmp(now_dir,"system")==0)
                {
                    relative_x=0;
                    relative_y=0;
                }
                else
                {
                    relative_x=80;
                    relative_y=80;
                    blur1(tsrc1);
                    blur1(tsrc1);
                    blur1(tsrc1);
                }
                init_data();
                cal_data();
                reback(tsrc1,0,0,tsrc1.cols,tsrc1.rows);
                init_rfile(now_dir);
                init_desk(tsrc1);
                imshow("system",src1);
            }
            else
            {
                show_text1(tsrc1,"last directory is not exist!");
            }
        }
        else if(input==Ctrl_Q)//强制退出
        {
            show_text1(tsrc1,"input random to exit! No save just now!");
            waitKey(0);
            break;
        }
        else if(input==Ctrl_E||input==ESC||exit_flag==1)
        {
            reback();
            fclose(fs);
            hThread[thread_num++]=CreateThread(NULL, 0, reorganize, NULL, 0, NULL);
            WaitForMultipleObjects(thread_num,hThread,TRUE,INFINITE);
            for(int i=0;i<thread_num;i++)
                CloseHandle(hThread[i]);
            show_text1(tsrc1,"input random to exit! thanks for using!");
            waitKey(0);
            break;
        }
    }

}

void show_text1(Mat dst,char text[])
{
    reback(dst,10,dst.rows-25,dst.cols-1,dst.rows-10);
    int r=(255-dst.at<Vec3b>(dst.rows-10,10)[0]+30)%256;
    int g=(255-dst.at<Vec3b>(dst.rows-10,10)[1])%256;
    int b=(255-dst.at<Vec3b>(dst.rows-10,10)[2]+30)%256;
    putText(dst,text,Point(10,dst.rows-10),FONT_HERSHEY_SIMPLEX,0.6,Scalar(b,g,r,255),1,8);
    imshow("system",src1);
}

DWORD WINAPI Paste_folder_file(LPVOID lpParamter)
{
    if(paste_flag==CUT)
    {
        if(strcmp(now_dir,src_dir)!=0)
        {
            char temp[1000];
            strcpy(temp,src_paste);
            if(!cut(src_paste,paste_name))
            {
                sprintf(paste_name,"new%03d",folder_num++);
                cut(temp,paste_name);
            }
            if(strcmp(now_dir,"system")==0)
            {
                relative_x=0;
                relative_y=0;
                cal_data();
            }
            init_data();
            reback(tsrc1,0,0,tsrc1.cols,tsrc1.rows);
            init_rfile(now_dir);
            init_desk(tsrc1);
            imshow("system",src1);
        }
        paste_flag=0;
    }
    else if(paste_flag==COPY)
    {
        char temp[1000];
        strcpy(temp,src_paste);
        if(!copy(src_paste,paste_name))
        {
            sprintf(paste_name,"new%03d",folder_num++);
            copy(temp,paste_name);
        }
        paste_flag=0;
        if(strcmp(now_dir,"system")==0)
        {
            relative_x=0;
            relative_y=0;
            cal_data();
        }
        init_data();
        reback(tsrc1,0,0,tsrc1.cols,tsrc1.rows);
        init_rfile(now_dir);
        init_desk(tsrc1);
        imshow("system",src1);
    }
}

int detect_menu(int x,int y,int fuc)
{
    int t=-1;
    if(menu_exist==1&&x<menu_right.x&&x>menu_left.x&&y<menu_right.y&&y>menu_left.y)
        t=(y-menu_left.y)/menu_h;
    if(t==-1)
        return t;
    del_menu(tsrc1,menu_right.x+1,menu_right.y+1);
    switch(fuc){
        case DESK:{
            if(t==NEW_FOLDER)
            {
                input_flag=1;
                new_file_folder=TYPE_FOLDER;
                input_num=0;
                char name[100]="new folder";
                input_choose=add_folder(menu_left.x,menu_left.y,name,TYPE_FOLDER);

            }
            else if(t==NEW_FILE)
            {
                input_flag=1;
                new_file_folder=TYPE_FILE;
                input_num=0;
                char name[100]="new file";
                down_add=ADD_FILE;
                input_choose=add_folder(menu_left.x,menu_left.y,name,TYPE_FILE);
            }
            else if(t==BACK)
            {
                reback();
                if(strcmp(now_dir,"system")==0)
                {
                    exit_flag=1;
                }
                else
                {
                    strcpy(last_dir,now_dir);
                    for(int i=strlen(now_dir)-1;i>=6;i--)
                    {
                        if(now_dir[i]!='\\')
                            now_dir[i]='\0';
                        else
                        {
                            now_dir[i]='\0';
                            break;
                        }
                    }
                    if(strcmp(now_dir,"system")==0)
                    {
                        relative_x=0;
                        relative_y=0;
                        init_data();
                        cal_data();
                        reback(tsrc1,0,0,tsrc1.cols,tsrc1.rows);
                        init_rfile(now_dir);
                        init_desk(tsrc1);
                        imshow("system",src1);
                    }
                    else
                    {
                        relative_x=80;
                        relative_y=80;
                        blur1(tsrc1);
                        blur1(tsrc1);
                        blur1(tsrc1);
                        init_data();
                        reback(tsrc1,0,0,tsrc1.cols,tsrc1.rows);
                        init_rfile(now_dir);
                        init_desk(tsrc1);
                        imshow("system",src1);
                    }
                }
            }
            else if(t==DESKTOP)
            {
                strcpy(last_dir,now_dir);
                relative_x=0;
                relative_y=0;
                init_data();
                cal_data();
                reback(tsrc1,0,0,tsrc1.cols,tsrc1.rows);
                strcpy(now_dir,"system");
                init_rfile(now_dir);
                init_desk(tsrc1);
                imshow("system",src1);
            }
            else if(t==PASTE)
            {
                HANDLE hThread = CreateThread(NULL, 0, Paste_folder_file, NULL, 0, NULL);
                CloseHandle(hThread);
            }
            else if(t==FULL)
            {
                relative_x=0;
                relative_y=0;
                init_data();
                cal_data();
                reback(tsrc1,0,0,tsrc1.cols,tsrc1.rows);
                init_rfile(now_dir);
                init_desk(tsrc1);
                imshow("system",src1);
            }
            break;
        }
        case FOLDER:{
            if(t==OPEN)
            {
                if(rfile[folder_choose].type==TYPE_FOLDER)
                {
                    strcpy(last_dir,now_dir);
                    relative_x=80;
                    relative_y=80;
                    blur1(tsrc1);
                    blur1(tsrc1);
                    blur1(tsrc1);

                    strcat(now_dir,"\\");
                    strcat(now_dir,rfile[folder_choose].name);

                    init_data();
                    cal_data();
                    reback(tsrc1,0,0,tsrc1.cols,tsrc1.rows);

                    init_rfile(now_dir);
                    init_desk(tsrc1);

                    imshow("system",src1);
                    return 10;
                }
                else if(rfile[folder_choose].type==TYPE_FILE)
                {
                    input_file_name=1;
                    down_add=DOWN_FILE;
                    input_choose=folder_choose;
                    show_text1(tsrc1,"input : ");
                }

            }
            else if(t==RENAME)
            {
                rename_flag=1;
                input_num=0;
                input_choose=folder_choose;
            }
            else if(t==DELETE1)
            {
                if(rfile[folder_choose].type==TYPE_FOLDER)
                    del_dir(rfile[folder_choose].name,now_dir);
                else if(rfile[folder_choose].type==TYPE_FILE)
                    del_file(rfile[folder_choose].name,now_dir);

                del_folder(tsrc1,folder_choose);
                imshow("system",src1);
            }
            else if(t==COPY)
            {
                strcpy(paste_name,rfile[folder_choose].name);
                paste_flag=COPY;
                strcpy(src_paste,now_dir);
                strcat(src_paste,"\\");
                strcat(src_paste,rfile[folder_choose].name);
            }
            else if(t==CUT)
            {
                strcpy(src_dir,now_dir);
                strcpy(paste_name,rfile[folder_choose].name);
                paste_flag=CUT;
                strcpy(src_paste,now_dir);
                strcat(src_paste,"\\");
                strcat(src_paste,rfile[folder_choose].name);
            }
            else if(t==PROPERTY)
            {
                reback(tsrc1,menu_left.x,menu_left.y,menu_right.x,menu_right.y);
                init_desk(tsrc1);
                menu_exist=0;

                char property[4][40]={0};
                int j=rfile[folder_choose].label;
                int year=0,month=0,day=0,second=0,hour=0;

                day=raw_file[j].time.date%32;
                month=(raw_file[j].time.date/32)%13;
                year=raw_file[j].time.date/32/13;

                second=raw_file[j].time.Clock%61;
                hour=raw_file[j].time.Clock/61;


                sprintf(property[2],"time:%4d-%02d-%02d %2d:%02d",year,month,day,hour,second);
                sprintf(property[0],"name:%10s",raw_file[j].name);
                sprintf(property[1],"dir :%10s",raw_file[j].content);
                if(raw_file[j].type==FFILE)
                {
                    sprintf(property[3],"size:%lf KB",raw_file[j].size/1024.0);
                    draw_menu(tsrc1,rfile[folder_choose].rightdown.x+10,rfile[folder_choose].leftup.y,property,4,250);
                }
                else
                    draw_menu(tsrc1,rfile[folder_choose].rightdown.x+10,rfile[folder_choose].leftup.y,property,3,250);
                flag_property_menu=1;
                return 11;
            }
            else if(t==SHOW)
            {
                if(raw_file[rfile[folder_choose].label].size/1024>300000)
                {
                    show_text1(tsrc1,"this file is more than 10KB!");
                    return 0;
                }
                show_flag=1;
                WAIT_THREAD=1;
                if(rfile[folder_choose].type==TYPE_FILE)
                    down_file(rfile[folder_choose].name,"template");

                blur1(src1);

                show.init_data(src1,tempsrc,"system",Scalar(0,0,0),Scalar(255,255,255));
                show.diretect_show("template");
                show.run();
                show_flag=0;
                QFile::remove("template");
                reback(src1,0,0,src1.cols-1,src1.rows-1);
                if(strcmp(now_dir,"system")==0)
                {
                    relative_x=0;
                    relative_y=0;
                    init_data();
                    cal_data();
                    reback(tsrc1,0,0,tsrc1.cols,tsrc1.rows);
                    init_rfile(now_dir);
                    init_desk(tsrc1);
                    imshow("system",src1);
                }
                else
                {
                    relative_x=80;
                    relative_y=80;
                    blur1(tsrc1);
                    blur1(tsrc1);
                    blur1(tsrc1);
                    init_data();
                    reback(tsrc1,0,0,tsrc1.cols,tsrc1.rows);
                    init_rfile(now_dir);
                    init_desk(tsrc1);
                    imshow("system",src1);
                }
                WAIT_THREAD=0;
            }
            else if(t==EDIT)
            {
                if(raw_file[rfile[folder_choose].label].size/1024>2500)
                {
                    show_text1(tsrc1,"this file is more than 10KB!");
                    return 0;
                }
                show_flag=1;
                WAIT_THREAD=1;
                if(rfile[folder_choose].type==TYPE_FILE)
                    down_file(rfile[folder_choose].name,"template");

                blur1(src1);

                edit.init_data(src1,tempsrc,"system","template",Scalar(0,0,0),Scalar(255,255,255));
                edit.run();

                del_file(rfile[folder_choose].name,now_dir);

                del_folder(tsrc1,folder_choose);

                add_file(rfile[folder_choose].name,"template");

                show_flag=0;
                QFile::remove("template");
                reback(src1,0,0,src1.cols-1,src1.rows-1);
                if(strcmp(now_dir,"system")==0)
                {
                    relative_x=0;
                    relative_y=0;
                    init_data();
                    cal_data();
                    reback(tsrc1,0,0,tsrc1.cols,tsrc1.rows);
                    init_rfile(now_dir);
                    init_desk(tsrc1);
                    imshow("system",src1);
                }
                else
                {
                    relative_x=80;
                    relative_y=80;
                    blur1(tsrc1);
                    blur1(tsrc1);
                    blur1(tsrc1);
                    init_data();
                    reback(tsrc1,0,0,tsrc1.cols,tsrc1.rows);
                    init_rfile(now_dir);
                    init_desk(tsrc1);
                    imshow("system",src1);
                }
                WAIT_THREAD=0;
            }

        }
    }
    return 0;
}

void on_mouse(int event,int x,int y,int flags,void *ustc)//event鼠标事件代号，x,y鼠标坐标，flags拖拽和键盘操作的代号
{
    if(show_flag==1)
        return ;
    if(input_file_name==1)
        return ;
    if(land_flag==0)
        return ;

    x-=relative_x;
    y-=relative_x;
    x=std::max(x,boundary);
    y=std::max(y,boundary);
    if(x>10000)
        x=boundary;
    if(y>10000)
        y=boundary;
    x=std::min(x,tsrc1.cols);
    y=std::min(y,tsrc1.rows);

    if(event==CV_EVENT_RBUTTONDOWN&&flags>=8&&flags<16)
    {
        drag_flag=0;
        del_menu(tsrc1,x,y);
    }
    else if(event==CV_EVENT_RBUTTONDOWN)
    {
        drag_flag=0;
        del_menu(tsrc1,x,y);
        if(menu_exist!=1)
        {
            flag_property_menu=0;
            folder_choose=detect_folder(x,y);
            if(folder_choose!=-1)
            {
                push_draw_folder(tsrc1,x,y);
                if(rfile[folder_choose].type==TYPE_FOLDER)
                {
                    strcpy(menu2[0],"Open");
                    draw_menu(tsrc1,x,y,menu2,num_menu2,menu_w);
                }
                else
                {
                    strcpy(menu2[0],"Down");
                    draw_menu(tsrc1,x,y,menu2,num_menu2+2,menu_w);
                }

            }
            else
            {
                if(strcmp(now_dir,"system")==0)
                    draw_menu(tsrc1,x,y,menu3,num_menu3,menu_w);
                else
                    draw_menu(tsrc1,x,y,menu1,num_menu1,menu_w);
            }
        }
    }
    else if(event == CV_EVENT_MOUSEMOVE && (flags & CV_EVENT_FLAG_LBUTTON)&&choose!=-1)
    {
        del_menu(tsrc1,x,y);
        int flag=choose;
        re_conflict_draw(x,y);
        newdraw_folder(tsrc1,x,y,flag);
        drag_flag=1;
        waitKey(5);
    }
    else if(event==CV_EVENT_LBUTTONUP&&drag_flag==1&&choose!=-1)
    {
        del_menu(tsrc1,x,y);
        int tx=x,ty=y,type=rfile[choose].type;
        del_folder(tsrc1,choose);
        change_coord_form(x,y);
        if(sure_add(x,y))
        {
            ground[y][x]=choose+1;
            back_coord_form(x,y);
            rfile[choose].leftup.x=x;
            rfile[choose].leftup.y=y;
            rfile[choose].rightdown.x=x+folder_w;
            rfile[choose].rightdown.y=y+folder_h;
            rfile[choose].type=type;
            redraw_type(tsrc1,choose);
        }
        else
            show_text1(tsrc1,"no more place to add folder!");
        re_conflict_draw(tx,ty);
        drag_flag=0;
    }
    else if(event==CV_EVENT_LBUTTONDOWN)
    {
        if(input_flag==1)
        {
            int place=-1;
            if(new_file_folder==TYPE_FOLDER)
            {
                place=add_dir(rfile[input_choose].name);
                if(place==-1)
                {
                    char name[100];
                    sprintf(name,"new%03d",folder_num++);
                    strcpy(rfile[input_choose].name,name);
                    redraw_type(tsrc1,input_choose);
                    place=add_dir(rfile[input_choose].name);
                    rfile[input_choose].label=place;
                }
                else
                    rfile[input_choose].label=place;
            }
            else if(new_file_folder==TYPE_FILE)
            {
                place=find_file(rfile[input_choose].name,now_dir,FFILE);
                if(place!=-1)
                {
                    char name[100];
                    sprintf(name,"new%03d",folder_num++);
                    strcpy(rfile[input_choose].name,name);
                    redraw_type(tsrc1,input_choose);
                }
                input_file_name=1;
                show_text1(tsrc1,"input : ");
                input_flag=0;
                return ;
            }
        }
        if(rename_flag==1)
        {
            bool place=rename(raw_file[rfile[input_choose].label].name,rfile[input_choose].name,now_dir);
            if(!place)
            {
                strcpy(rfile[input_choose].name,raw_file[rfile[input_choose].label].name);
                redraw_type(tsrc1,input_choose);
            }
        }
        rename_flag=0;
        input_flag=0;
        int t=0;
        if(folder_choose!=-1&&flag_property_menu==0)
        {
            t=detect_menu(x,y,FOLDER);
            folder_choose=-1;
        }
        else if(flag_property_menu==0)
            t=detect_menu(x,y,DESK);
        if(t!=10)
        {
            push_draw_folder(tsrc1,x,y);
        }
        if(t!=11)
            del_menu(tsrc1,x,y);
        drag_flag=0;
    }
}

void push_draw_folder(Mat dst,int x,int y)
{
    int flag=detect_folder(x,y);
    if(flag!=choose&&choose!=-1)
    {
        reback(dst,rfile[choose].leftup.x,rfile[choose].leftup.y,rfile[choose].rightdown.x,rfile[choose].rightdown.y);
        redraw_type(dst,choose);

        if(flag==-1)
            choose=-1;
    }
    if(flag!=choose&&flag!=-1)
    {
        glass(dst,rfile[flag].leftup.x,rfile[flag].leftup.y,rfile[flag].rightdown.x,rfile[flag].rightdown.y,3);
        redraw_type(dst,flag);
        choose=flag;
    }
}

void newdraw_folder(Mat dst,int x,int y,int flag)
{
    if(flag!=-1)
    {
        reback(dst,rfile[flag].leftup.x,rfile[flag].leftup.y,rfile[flag].rightdown.x,rfile[flag].rightdown.y);
        if(x<boundary)
            x=boundary;
        if(y<boundary)
            y=boundary;
        if(x>=10000)
            x=boundary;
        if(y>=10000)
            y=boundary;
        if(x>=tsrc1.cols-folder_w)
            x=tsrc1.cols-folder_w;
        if(y>=tsrc1.rows-folder_h)
            y=tsrc1.rows-folder_h;

        rfile[flag].leftup.x=x;
        rfile[flag].leftup.y=y;
        rfile[flag].rightdown.x=x+folder_w;
        rfile[flag].rightdown.y=y+folder_h;

        if(rfile[flag].rightdown.x>=tsrc1.cols)
            rfile[flag].rightdown.x=tsrc1.cols-boundary;
        if(rfile[flag].rightdown.y>=tsrc1.rows)
            rfile[flag].rightdown.y=tsrc1.rows-boundary;

        glass(dst,rfile[flag].leftup.x,rfile[flag].leftup.y,rfile[flag].rightdown.x,rfile[flag].rightdown.y,2);
        redraw_type(dst,flag);
    }
}


void overlayImage(const cv::Mat &foreground,cv::Mat &output, cv::Point2i location)
{
    for(int y = std::max(location.y , 0); y < output.rows; ++y)
    {
        int fY = y - location.y;
        if(fY >= foreground.rows)
            break;
        for(int x = std::max(location.x, 0); x < output.cols; ++x)
        {
            int fX = x - location.x; // because of the translation.
            if(fX >= foreground.cols)
                break;
            double opacity =((double)foreground.data[fY * foreground.step + fX * foreground.channels() + 3])/ 255.;
            for(int c = 0; opacity > 0 && c < output.channels(); ++c)
            {
                unsigned char foregroundPx =
                foreground.data[fY * foreground.step + fX * foreground.channels() + c];
                unsigned char backgroundPx =
                output.data[y * output.step + x * output.channels() + c];
                output.data[y*output.step + output.channels()*x + c] =
                backgroundPx * (1.-opacity) + foregroundPx * opacity;
            }
        }
    }
}


void glass(Mat dst,int lx,int ly,int rx,int ry,int n)
{
    if(ry>=dst.rows)
        ry=dst.rows-1;
    if(rx>=dst.cols)
        rx=dst.cols-1;
    if(lx<0)
        lx=0;
    if(ly<0)
        ly=0;
    Mat temp=dst.rowRange(ly,ry);
    temp=temp.colRange(lx,rx);
    for(int i=0;i<n;i++)
        blur(temp, temp,Size(9,9),Point(-1,-1));
    for(int y=0;y<temp.rows;++y)
    {
        for(int x=0;x<temp.cols;++x)
        {
            int t=39+(int)temp.data[y * temp.step + x * temp.channels() + 1];
            if(t<0)
                t=1;
            if(t>255)
                t=255;
            temp.data[y * temp.step + x * temp.channels() + 1]=t;
        }
    }
}

int detect_folder(int x,int y,int flag)
{
    for(int i=0;i<nrfile;i++)
    {
        if(rfile[i].type!=UNUSED)
            if(x<=rfile[i].rightdown.x&&x>=rfile[i].leftup.x&&y<=rfile[i].rightdown.y&&y>=rfile[i].leftup.y&&i!=flag)
                return i;
    }
    return -1;
}

int detect_folder(int x,int y)
{
    for(int i=0;i<nrfile;i++)
    {
        if(rfile[i].type!=UNUSED)
            if(x<=rfile[i].rightdown.x&&x>=rfile[i].leftup.x&&y<=rfile[i].rightdown.y&&y>=rfile[i].leftup.y)
                return i;
    }
    return -1;
}

void reback(Mat dst,int lx,int ly,int rx,int ry)
{
    ry+=5;
    rx+=5;
    if(ry>=dst.rows)
        ry=dst.rows-1;
    if(rx>=dst.cols)
        rx=dst.cols-1;
    if(lx<0)
        lx=0;
    if(ly<0)
        ly=0;
    Mat temp=dst.rowRange(ly,ry);
    temp=temp.colRange(lx,rx);

    Mat temp1=src2.rowRange(ly,ry);
    temp1=temp1.colRange(lx,rx);

    for(int y=0;y<temp.rows;++y)
    {
        for(int x=0;x<temp.cols;++x)
        {
            for(int c=0;c<temp.channels();c++)
                temp.data[y * temp.step + x * temp.channels() + c]=temp1.data[y * temp.step + x * temp.channels() + c];
        }
    }
}

void draw_folder(Mat icon,Mat dst,int x,int y,char name[],int type,int place)
{
    Point2i p(x,y);
    overlayImage(icon,dst,p);
    strcpy(rfile[place].name,name);
    name[9]='.';
    name[10]='\0';

    unsigned char b=255-dst.at<Vec3b>(y+folder_h,x)[0];
    unsigned char g=255-dst.at<Vec3b>(y+folder_h,x)[1];
    unsigned char r=255-dst.at<Vec3b>(y+folder_h,x)[2];

    putText(dst,name,Point(x,y+folder_h-4),FONT_HERSHEY_SIMPLEX,0.4,Scalar(r,g,b,255),1,8);

    rfile[place].leftup=p;
    rfile[place].rightdown.x=x+folder_w;
    rfile[place].rightdown.y=y+folder_h;
    rfile[place].type=type;

    imshow("system",src1);
}

void redraw_folder(Mat icon,Mat dst,int i)
{

    overlayImage(icon,dst,rfile[i].leftup);

    char name[100];
    strcpy(name,rfile[i].name);
    name[9]='.';
    name[10]='\0';

    unsigned char b=0;
    unsigned char g=0;
    unsigned char r=0;
    if(rfile[i].rightdown.y+folder_h>=0&&rfile[i].rightdown.y+folder_h<dst.rows&&rfile[i].leftup.x>=0&&rfile[i].leftup.x<=dst.cols)
    {
        b=(255-dst.at<Vec3b>(rfile[i].rightdown.y+folder_h,rfile[i].leftup.x)[0]);
        g=(255-dst.at<Vec3b>(rfile[i].rightdown.y+folder_h,rfile[i].leftup.x)[1]);
        r=(255-dst.at<Vec3b>(rfile[i].rightdown.y+folder_h,rfile[i].leftup.x)[2]);
    }

    putText(dst,name,Point(rfile[i].leftup.x,rfile[i].rightdown.y-4),FONT_HERSHEY_SIMPLEX,0.4,Scalar(r,g,b,255),1,8);
    imshow("system",src1);
}

void change_coord_form(int &x,int &y)
{
    if(x<boundary)
        x=boundary;
    if(y<boundary)
        y=boundary;
    if(x>=10000)
        x=boundary;
    if(y>=10000)
        y=boundary;
    if(x>=tsrc1.cols)
        x=tsrc1.cols-boundary;
    if(y>=tsrc1.rows)
        y=tsrc1.rows-boundary;

    x=(x-boundary)/folder_w;
    if(x>=num_x)
        x=num_x-1;
    y=(y-boundary)/folder_h;
    if(y>=num_y)
        y=num_y-1;
}

void back_coord_form(int &x,int &y)
{
    x=x*folder_w+boundary;
    y=y*folder_h+boundary;
}

bool sure_add(int &x,int &y)
{
    if(ground[y][x]==0)
        return true;
    int distance=num_x*num_x+num_y*num_y;
    int tx=-1,ty=-1;
    for(int i=0;i<num_x;i++)
    {
        for(int j=0;j<num_y;j++)
        {
            if(ground[j][i]==0)
            {
                int d=(i-x)*(i-x)+(j-y)*(j-y);
                if(d<distance)
                {
                    ty=j;
                    tx=i;
                    distance=d;
                }
            }
        }
    }
    if(tx==-1)
        return false;
    else
        x=tx,y=ty;
    return true;
}


int add_folder(int x,int y,char name1[],int type)
{
    change_coord_form(x,y);
    int t=find_unused();
    if(t!=-1&&sure_add(x,y))
    {
        ground[y][x]=t+1;
        back_coord_form(x,y);
        draw_type(tsrc1,type,x,y,name1,t);
    }
    else
        show_text1(tsrc1,"no more place to add folder!");
    return t;
}
void del_folder(Mat dst,int flag)
{
    reback(dst,rfile[flag].leftup.x,rfile[flag].leftup.y,rfile[flag].rightdown.x,rfile[flag].rightdown.y);
    rfile[flag].type=UNUSED;
    flag++;
    for(int i=0;i<num_x;i++)
    {
        for(int j=0;j<num_y;j++)
        {
            if(ground[j][i]==flag)
            {
                ground[j][i]=0;
            }
        }
    }
}

void re_conflict_draw(int x,int y)
{
    int flag1=detect_folder(x,y,choose);
    if(flag1!=-1)
    {
        redraw_type(tsrc1,flag1);
    }
    else
    {
        flag1=detect_folder(x+folder_w,y,choose);
        if(flag1!=-1)
            redraw_type(tsrc1,flag1);
        else
        {
            flag1=detect_folder(x+folder_w,y+folder_h,choose);
            if(flag1!=-1)
                redraw_type(tsrc1,flag1);
            else
            {
                flag1=detect_folder(x,y+folder_h,choose);
                if(flag1!=-1)
                    redraw_type(tsrc1,flag1);
            }
        }
    }
}
void rename_folder(Mat dst,int i)
{
    char name[100];
    strcpy(name,rfile[i].name);
    name[9]='.';
    name[10]='\0';
    unsigned char b=0;
    unsigned char g=0;
    unsigned char r=0;
    if(rfile[i].rightdown.y+folder_h>=0&&rfile[i].rightdown.y+folder_h<dst.rows&&rfile[i].leftup.x>=0&&rfile[i].leftup.x<=dst.cols)
    {
        b=(255-dst.at<Vec3b>(rfile[i].rightdown.y+folder_h,rfile[i].leftup.x)[0]);
        g=(255-dst.at<Vec3b>(rfile[i].rightdown.y+folder_h,rfile[i].leftup.x)[1]);
        r=(255-dst.at<Vec3b>(rfile[i].rightdown.y+folder_h,rfile[i].leftup.x)[2]);
    }
    reback(dst,rfile[i].leftup.x,rfile[i].leftup.y+48,rfile[i].rightdown.x,rfile[i].rightdown.y);
    putText(dst,name,Point(rfile[i].leftup.x,rfile[i].rightdown.y-4),FONT_HERSHEY_SIMPLEX,0.4,Scalar(r,g,b,255),1,8);
    imshow("system",src1);
}

void get_menu_place(int x,int y,int h,int w)
{
    if(x+w>=tsrc1.cols)
    {
        menu_right.x=std::min(tsrc1.cols-1,x);
        menu_left.x=std::max(x-w,0);
    }
    else
    {
        menu_right.x=std::min(tsrc1.cols-1,x+w);
        menu_left.x=std::max(x,0);
    }
    if(y+h>=tsrc1.rows)
    {
        menu_right.y=std::min(tsrc1.cols-1,y);
        menu_left.y=std::max(y-h,0);
    }
    else
    {
        menu_right.y=std::min(tsrc1.cols-1,y+h);
        menu_left.y=std::max(y,0);
    }

}
void del_menu(Mat dst,int x,int y)
{
    if(menu_exist==1&&!(x<menu_right.x&&x>menu_left.x&&y<menu_right.y&&y>menu_left.y))
    {
        reback(dst,menu_left.x,menu_left.y,menu_right.x,menu_right.y);
        menu_exist=0;
        init_desk(dst);
        imshow("system",src1);
    }
}
void blur1(Mat tsrc1)
{
    int y=0;
    for(y=1;y<tsrc1.rows-1;++y)
    {
        for(int x=1;x<tsrc1.cols-1;++x)
        {
            for(int c=0;c<tsrc1.channels();c++)
            {
                int t=0;
                for(int i=y-1;i<=y+1;i++)
                    for(int j=x-1;j<=x+1;j++)
                        t+=tsrc1.data[i * tsrc1.step + j * tsrc1.channels() + c];
                tsrc1.data[y * tsrc1.step + x * tsrc1.channels() + c]=t/9;
            }
        }
    }
}

void draw_menu(Mat dst,int x,int y,char menu[3][40],int num,int menu_w)
{
    get_menu_place(x,y,menu_h*num,menu_w);

    for(int i=0;i<num;i++)
    {
        glass(dst,menu_left.x,menu_left.y+i*menu_h,menu_left.x+menu_w,menu_left.y+(i+1)*menu_h,i*2+2);
        int r=(255-dst.at<Vec3b>(menu_left.y+i*menu_h,menu_left.x)[0]+30)%256;
        int g=(255-dst.at<Vec3b>(menu_left.y+i*menu_h,menu_left.x)[1])%256;
        int b=(255-dst.at<Vec3b>(menu_left.y+i*menu_h,menu_left.x)[2]+30)%256;
        putText(dst,menu[i],Point(menu_left.x,menu_left.y+(i+1)*(menu_h)-3),FONT_HERSHEY_SIMPLEX,0.5,Scalar(b,g,r,255),1,8);
    }
    imshow("system",src1);
    menu_exist=1;
}

void draw_type(Mat dst,int type,int x,int y,char name[],int place)
{
    if(type==TYPE_FOLDER)
        draw_folder(type_folder,dst,x,y,name,type,place);
    else if(type==TYPE_FILE)
        draw_folder(type_file,dst,x,y,name,type,place);
}

void redraw_type(Mat dst,int flag)
{
    if(rfile[flag].type==TYPE_FOLDER)
        redraw_folder(type_folder,dst,flag);
    else if(rfile[flag].type==TYPE_FILE)
        redraw_folder(type_file,dst,flag);
}

int find_unused()
{
    int i=0;
    for(i=0;i<MAX_SIZE;i++)
        if(rfile[i].type==UNUSED)
        {
            if(i>=nrfile)
                nrfile=i+1;
            return i;
        }
    return -1;
}

void init_desk(Mat dst)
{
    for(int i=0;i<nrfile;i++)
    {
        if(rfile[i].type!=UNUSED)
            redraw_type(dst,i);
    }
}


void cal_data()
{
    tsrc1=src1.rowRange(relative_y,src1.rows-relative_y);
    tsrc1=tsrc1.colRange(relative_x,src1.cols-relative_x);
    num_x=(tsrc1.cols-2*boundary)/folder_w;
    num_y=(tsrc1.rows-8*boundary)/folder_h;
}

void init_data()
{
    int i=0;
    for(i=0;i<nrfile;i++)
        rfile[i].type=UNUSED;
    for(i=0;i<num_y+1;i++)
        memset(ground[i],0,num_x+1);
    nrfile=0;
    exit_flag=0;
    folder_choose=-1;
    input_flag=0;
    input_num=0;
    input_choose=0;
    menu_exist=0;
    drag_flag=0;
    choose=-1;
}


void write_desk_file()
{
    FILE *p=fopen("desk_save","wb");
    fwrite(&relative_x,1,sizeof(int),p);//relative_x
    fwrite(&relative_y,1,sizeof(int),p);//relative_y
    fwrite(&nrfile,1,sizeof(int),p);//nrfile
    fwrite(rfile,1,sizeof(RFile)*MAX_SIZE,p);//rfile
    for(int i=0;i<100;i++)
        fwrite(&ground[i][0],1,100,p);
    fclose(p);
}

void read_desk_file()
{
    FILE *p=NULL;
    p=fopen("desk_save","rb");
    if(p==NULL)
    {
        show_text1(tsrc1,"desk_save file is not exist");
        return ;
    }

    fread(&relative_x,1,sizeof(int),p);//relative_x
    fread(&relative_y,1,sizeof(int),p);//relative_y
    fread(&nrfile,1,sizeof(int),p);//nrfile
    fread(rfile,1,sizeof(RFile)*MAX_SIZE,p);//rfile
    for(int i=0;i<100;i++)
        fread(&ground[i][0],1,100,p);
    fclose(p);
}

DWORD WINAPI copy_in(LPVOID lpParamter)
{
    Thread_Param *param=(Thread_Param *)lpParamter;
    FILE *p=param->p;
    int place=param->place;

    Block block;
    int index=find_block_place();

    raw_file[place].next=index;
    double number=0;
    while(!feof(p))
    {
        int index1=index;
        int num=fread(block.data,1,120,p);
        block.flag=num;
        if(num!=120||feof(p))
            block.next=UNUSE;
        else
        {
            index=find_block_place();
            block.next=index;
        }
        fseek(fs,index1,SEEK_SET);
        fwrite(&block,1,sizeof(Block),fs);
        number+=num;

        char src[60]={0};
        sprintf(src,"update :%10lf",number/raw_file[place].size);
        show_text1(tsrc1,src);
    }
    fclose(p);
}

DWORD WINAPI copy_out(LPVOID lpParamter)
{
    Thread_Param *param=(Thread_Param *)lpParamter;
    FILE *p=param->p;
    int place=param->place;

    Block block;
    int index=raw_file[place].next;
    double number=0;
    while(index!=UNUSE)
    {
        fseek(fs,index,SEEK_SET);
        fread(&block,1,sizeof(Block),fs);
        fwrite(block.data,1,block.flag,p);
        number+=block.flag;
        index=block.next;
        char src[50]={0};
        sprintf(src,"download :%10lf",number/raw_file[place].size);
        show_text1(tsrc1,src);
    }
    fclose(p);
}
void init_rfile(char dir[])
{
    for(int i=0;i<MAX;i++)
    {
        if(raw_file[i].type!=UNUSE&&strcmp(raw_file[i].content,dir)==0)
        {
            int c=find_unused();
            if(c==-1)
            {
                show_text1(tsrc1,"no place any more!");
                return ;
            }
            rfile[c].label=i;
            if(raw_file[i].type==DIR)
                rfile[c].type=TYPE_FOLDER;
            else
                rfile[c].type=TYPE_FILE;

            strcpy(rfile[c].name,raw_file[i].name);

            int x=0,y=0;
            if(sure_add(x,y))
            {
                ground[y][x]=c+1;
                back_coord_form(x,y);
                rfile[c].leftup=Point2i(x,y);
                rfile[c].rightdown.x=x+folder_w;
                rfile[c].rightdown.y=y+folder_h;
            }
            else
            {
                show_text1(tsrc1,"no place any more!");
                return ;
            }
        }
    }
}

bool copy_file(char name[],char name1[])
{
    char content[1000]={0};
    int t1=find_dirfile(name,content,FFILE,now_dir);
    if(t1==-1)
    {
        return false;
    }
    if(t1==-2)
    {
        return false;
    }
    int t2=find_dirfile(name1,content,FFILE,now_dir);
    if(t2>=0)
    {
        return false;
    }
    if(t2==-2)
    {
        return false;
    }

    int place=find_file_place();
    strcpy(raw_file[place].content,content);
    strcpy(raw_file[place].name,name1);
    raw_file[place].size=raw_file[t1].size;
    raw_file[place].type=FFILE;

    unsigned int date=0,Clock=0;
    getTime(date,Clock);
    raw_file[place].time.Clock=Clock;
    raw_file[place].time.date=date;


    Block block;
    int index=raw_file[t1].next;
    int index1=find_block_place();
    raw_file[place].next=index1;

    double num=0;
    char temp_name[100]={0};
    while(index!=UNUSE)
    {
        fseek(fs,index,SEEK_SET);
        fread(&block,sizeof(Block),1,fs);

        int index2=UNUSE;
        if(block.next!=UNUSE)
            index2=find_block_place();
        index=block.next;
        fseek(fs,index1,SEEK_SET);
        block.next=index2;
        int t=fwrite(&block,sizeof(Block),1,fs);
        num+=t;
        sprintf(temp_name,"file: %lf",num/raw_file[place].size);
        show_text1(tsrc1,temp_name);
        index1=index2;
    }

    return true;
}

void find_name_show()
{
    for(int i=find_num;i<MAX;i++)
    {
        if(raw_file[i].type!=UNUSE&&strcmp(raw_file[i].name,find_name)==0)
        {
            strcpy(last_dir,now_dir);
            if(strcmp(raw_file[i].content,now_dir)!=0)
            {
                strcpy(now_dir,raw_file[i].content);
                if(strcmp(now_dir,"system")==0)
                {
                    relative_x=0;
                    relative_y=0;
                }
                else
                {
                    relative_x=80;
                    relative_y=80;
                    blur1(tsrc1);
                    blur1(tsrc1);
                    blur1(tsrc1);
                }
                init_data();
                cal_data();
                reback(tsrc1,0,0,tsrc1.cols,tsrc1.rows);
                init_rfile(now_dir);
                init_desk(tsrc1);
                imshow("system",src1);
            }
            int c=0;
            for(c=0;c<nrfile;c++)
            {
                if(strcmp(find_name,rfile[c].name)==0&&c!=choose)
                    break;
            }
            if(c!=nrfile)
            {
                if(c!=choose&&choose!=-1)
                {
                    reback(tsrc1,rfile[choose].leftup.x,rfile[choose].leftup.y,rfile[choose].rightdown.x,rfile[choose].rightdown.y);
                    redraw_type(tsrc1,choose);

                    if(c==-1)
                        choose=-1;
                }
                if(c!=choose&&c!=-1)
                {
                    glass(tsrc1,rfile[c].leftup.x,rfile[c].leftup.y,rfile[c].rightdown.x,rfile[c].rightdown.y,3);
                    redraw_type(tsrc1,c);
                    choose=c;
                }
                find_num=i+1;
            }
            return ;
        }
    }
    find_num=0;
}
