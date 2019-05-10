#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui/QPushButton>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void init();
    void showbtn();
    void setsrc();
    void delpicture(int x1,int y1,int x2,int y2);
    void delpicture1(int x1,int y1,int x2,int y2);
    void copy(int ex, int ey, int sx, int sy);
    void btnfuc(int x,int y);
    void setsrc1();
private slots:
    void on_btn1_clicked();

    void on_btn2_clicked();

    void on_btn3_clicked();

    void on_btn4_clicked();

    void on_btn5_clicked();

    void on_btn6_clicked();

    void on_btn7_clicked();

    void on_btn8_clicked();

    void on_btn9_clicked();

    void on_btn10_clicked();

    void on_btn11_clicked();

    void on_btn12_clicked();

    void on_btn13_clicked();

    void on_btn14_clicked();

    void on_btn15_clicked();

    void on_btn16_clicked();

    void on_btn04_clicked();

    void on_btn05_clicked();

    void on_btn06_clicked();

    void on_btn141_clicked();

    void on_btn151_clicked();

    void on_btn161_clicked();

    void on_btn24_clicked();

    void on_btn25_clicked();

    void on_btn26_clicked();

    void on_btn34_clicked();

    void on_btn35_clicked();

    void on_btn36_clicked();

    void on_btn40_clicked();

    void on_btn41_clicked();

    void on_btn42_clicked();

    void on_btn43_clicked();

    void on_btn44_clicked();

    void on_btn45_clicked();

    void on_btn46_clicked();

    void on_btn50_clicked();

    void on_btn51_clicked();

    void on_btn52_clicked();

    void on_btn53_clicked();

    void on_btn54_clicked();

    void on_btn55_clicked();

    void on_btn56_clicked();

    void on_btn60_clicked();

    void on_btn61_clicked();

    void on_btn62_clicked();

    void on_btn63_clicked();

    void on_btn64_clicked();

    void on_btn65_clicked();

    void on_btn66_clicked();

    void on_cut_clicked();

    void on_add_clicked();

private:
    Ui::MainWindow *ui;
    int number;
    int times[3];
    int x0;
    int y0;
    QPushButton* btn[7][7];
    int source[7][7];
    int source1[7][7];
    void charge(int sx,int sy,int ex,int ey,int &flag);
};

#endif // MAINWINDOW_H
