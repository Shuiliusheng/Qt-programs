#ifndef RUN_H
#define RUN_H
#include<stdio.h>
#include<iostream>
#include <Windows.h>
#include <windows.h>
#include<string.h>
#include<QThread>
using namespace std;

#define LCLICK "l"
#define LUP "0"
#define LDOWN "1"
#define DLCLICK "2"
#define RCLICK "r"
#define RUP "3"
#define RDOWN "4"
#define DRCLICK "5"
#define MDOWN "6"
#define MUP "7"
#define IDOWN "8"
#define IUP "9"
#define WHEEL "w"
#define IINPUT "i"
#define BEGIN "b"
#define SSLEEP "s"
#define EEND "e"
#define MOVE "m"
#define DDOWN "d"
#define UUP "u"


class Run: public QThread
{
public:
    Run();
    int run_file(const char name[]);
    int special_key(char str[]);
    int change(char &c);
    void change1(char &c);
    void output_key(char c);
    int runcmd(char cmd[]);
    void run_while(unsigned int place,int circle);

    void set_param(int sleep1,int circle1,char file[],bool run_flag1);

protected:
    void run();

private:
    int x,y;
    POINT point;
    FILE *p1;
    int sleep_time;
    int circle;
    char filename[200];
    bool run_flag;
};

#endif // RUN_H
