#ifndef SHOW_H
#define SHOW_H

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

#define UP 2490368
#define DOWN 2621440
#define LEFT 2424832
#define RIGHT 2555904

#define END 2293760
#define HOME 2359296
#define PGUP 2162688
#define PGDOWN 2228224

#define CTRL_F 6
#define CTRL_O 15
#define CTRL_E 5

#define F1 7340032
#define F2 7405568

class Show{

public:
    Show();
    ~Show();
    bool init_data(Mat show_dst,Mat dst,const char show_text[],Scalar back1, Scalar fore1);

    void add_to_buf(FILE *p);
    void dispear_char_line(Mat dst,int y);
    void dispear_screen(Mat dst);
    void dispear_area(Mat dst,Point lp,Point rp);

    int find_str(Mat dst,int &x, int &y);
    int get_wide(char c);
    void input_str(int &num,char buf[],int input);
    bool start();
    void set_cursor(Mat dst,int x,int y);
    int show_str(Mat dst,int y,int num,char str[]);
    void show_buf(Mat dst);
    void show_text(Mat dst,int x,int y,char c);
    void dispear_line(Mat dst);

    void run();
    void line1(int sx,int sy,int ex,int ey,Scalar color);
    void diretect_show(char filename[]);

private:
    Scalar back;
    Scalar fore;
    int h;
    int w;
    Mat src;
    Mat show_src;

    char buf[80][75];
    int buf_x[80];
    int buf_y;

    int x,y;
    int last_x;
    int last_y;

    int char_h;
    int char_w;

    int max_w;
    int max_h;

    int t;
    Point l;
    Point r;

    FILE *p;
    bool valid;


    int find_str_flag;
    char find_str_buf[100];
    int find_str_num;
    int find_x,find_y;

    int open_flag;
    char open_buf[200];
    int open_num;

    int place_flag[100000];
    int num_place;

    int now_place;

    bool directect;

    char show_text1[100];

};


#endif // SHOW_H
