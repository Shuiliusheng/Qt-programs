#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setplock();
    void charge(int &str);
private slots:
    void on_btn1_clicked();


    void on_btn2_clicked();

    void on_lock_clicked();

private:
    Ui::MainWindow *ui;
    void prolock(char str[], char str1[]);
    void prorl(char str[],char str1[]);
    void prorl1(char &str,char str1,int a);
    void start(char str[],char str1[]);
    void data();
    void lockf();
    void llock(char str[],char str1[]);
    void rllock(char str[],char str1[]);


    void llock1(char str[]);
    void rllock1(char str[]);

    int plock[10];
    char slock[31];
    char flock[11];
    int lock[31];
    int lockplace[31];
    int n;
    int temp;
};

#endif // MAINWINDOW_H
