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
    
private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
    int lock[31];
    int temp;
    int plock[12];

    void setplock();
    void rllock(char str[],char str1[]);
    void prorl(char str[],char str1[]);
    void prorl1(char &str,char str1,int a);
    void rllock1(char str[]);
    void chargename();
    void chargefile();

};

#endif // MAINWINDOW_H
