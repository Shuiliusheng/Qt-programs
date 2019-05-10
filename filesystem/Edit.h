#ifndef EDIT_H
#define EDIT_H

#include<opencv2/opencv.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<iostream>
#include<string.h>
#include<stdio.h>
using namespace std;
using namespace cv;

#define BACKSPACE 8
#define ESC 27
#define ENTER 13
#define TAB 9

#define UP 2490368
#define DOWN 2621440
#define LEFT 2424832
#define RIGHT 2555904

#define END 2293760
#define HOME 2359296
#define PGUP 2162688
#define PGDOWN 2228224

#define CTRL_B 2
#define CTRL_E 5
#define CTRL_D 4
#define CTRL_S 19
#define CTRL_F 6
#define CTRL_R 18
#define CTRL_C 3
#define CTRL_X 24
#define CTRL_V 22
#define CTRL_O 15

#define F1 7340032
#define F2 7405568
#define F3 7471104
#define F4 7536640
#define F5 7602176


class Edit{
public:
    Edit();
    ~Edit();
    void dispear_area(Mat dst,Point lp,Point rp);
    void dispear_line(Mat dst);
    void draw_line(Mat dst,int x,int y);
    int get_wide(char c);
    void show_text(Mat dst,int x,int y,char c);
    void show_line(Mat dst,int y);
    void show_buf(Mat dst);
    void dispear_char_line(Mat dst,int y);
    void add_char(int x,int y,char c,char flag[]);
    int del_char(Mat dst);
    void del_line(Mat dst,int y);
    void show_str(Mat dst,int y,int num,char str[]);
    void add_line(Mat dst);
    void input_str(Mat src,int &num,char buf[],int input);
    int find_str(int &x,int &y);
    void replace_str(Mat src1,char src[],char dst[],int x1,int y1);
    void input_char(Mat dst,char c);
    void copy_str(Mat dst,int sx,int sy,int ex,int ey);
    void cut_str(Mat dst,int sx,int sy,int ex,int ey);
    bool start();
    void save_now(char name[]);
    void help_show(Mat dst);

    bool init_data(Mat show_dst,Mat dst,char show_text[],char filename[],Scalar back1, Scalar fore1);
    void run();
    void line1(int sx,int sy,int ex,int ey,Scalar color);

private:
    Scalar back;
    Scalar fore;
    int h;
    int w;
    Mat src;
    Mat show_src;
    char show_text1[100];
    bool valid;

    char buf[50000][75];
    int buf_x[50000];
    int buf_y;

    int x,y;
    int last_x;
    int last_y;

    char flag[50000];


    int char_h;
    int char_w;

    int max_w;
    int max_h;

    int find_str_flag;
    char find_str_buf[100];
    int find_str_num;
    int find_x,find_y;

    int replace_str_flag;
    char replace_src_buf[100];
    char replace_dst_buf[100];
    int replace_str_num;
    int replace_x,replace_y;


    int copy_flag;
    int copy_x,copy_y;
    int last_copy_x,last_copy_y;
    char copy_buf[10000];

    int cut_flag;
    int cut_x,cut_y;
    int last_cut_x,last_cut_y;


    int save_name_flag;
    char save_name_buf[200];
    int save_name_num;

    int open_flag;
    char open_buf[200];
    int open_num;

    int start_y;

    int t;
    Point l;
    Point r;


};

#endif // EDIT_H
