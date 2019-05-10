#ifndef MAINWINDOW_H
#define MAINWINDOW_H
 
#include <QMainWindow>
#include <QDesktopWidget>
#include <QTextStream>
#include <QMouseEvent>
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include "text.h"
#include <QToolBar>
#include <QAction>
#include<QLineEdit>
#include<QCheckBox>
#include<QCursor>
#include<QKeyEvent>
#include<QPalette>
#define CTRL 16777249
#define EXIT 69
#define SAVE 83
#define UP 85
#define DOWN 68
#define QUIT 81

namespace Ui {
class MainWindow;
class QDialog;
class QLineEdit;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT



public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void draw_toolbar();
    bool find_method(QTextEdit *edit,QString findtext,int method);
    void resize_btn();
    void read_temp();
private slots:
    void on_addfile_clicked();

    void open_file();

    void close_tab();

    void on_newfile_clicked();

    void change_tab_name(QString name);

    void save_file();

    void save_as();

    void find_text();
    void find_str();
    void find_str1();

    void big_text();

    void small_text();

    void replace_text();
    void replace_str_down();
    void replace_str_up();
    void replace_all();

    void set_background();

    void open_light();

    void fontlight();

    void codeing();

    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);

    void mouseMoveEvent(QMouseEvent *event);

    void mouseReleaseEvent(QMouseEvent *event);

    void resizeEvent( QResizeEvent * event );

    void save_temp();

private:
    Ui::MainWindow *ui;
    QDialog *findDlg;
    QLineEdit *findLineEdit;
    QLineEdit *replaceLineEdit;
    QCheckBox *check2;
    QCheckBox *check1;
    QPushButton *btn;
    QPushButton *btn1;
    QPushButton *btn2;
    bool press;
    QPoint oldPos;
};

#endif // MAINWINDOW_H
