#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include<searchwindow.h>
#include<QAction>
#include<QMenu>
#include<QToolBar>
#include <QtSql/QtSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include<QStandardItemModel>
#include<QTimer>
namespace Ui {
class MainWindow;
class login1;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    SearchWindow s;

    void update_borrow();//更新借阅时的超出天数

    void connectdb();//连接数据库
    void initdata();//初始化数据库

///////////////登陆界面//////////////////////////
    void hide1(bool flag);//hide 系列，用于隐藏控件，使得界面可以分层，而不用使用太多界面
    //层次转换函数
    void hide(bool flag);//hide 系列，用于隐藏控件，使得界面可以分层，而不用使用太多界面

    //登陆层次
    bool login1();//登陆用户函数

    //注册层次
    int detect1();//注册时，用户输入信息的合法性
    bool reg();//注册到数据库的student表中

////////////////用户使用界面////////////////////////
    void hide2(bool flag);//层次转换函数
    void hide3(bool flag);
    void hide4(bool flag);

    ///开始界面显示层次
    void initpaint();//第二界面的初始化绘制
    void showmoney();//显示欠款金额
    void message();//第二界面的开始桌面显示书本过期提示信息
    void cal_num_lend();//计算此用户目前可以借阅的书本个数

    ///借阅层次
    bool detect_borrow();//进行借阅书籍时的输入合法性检测和能够借阅的判断
    bool detect_borrow1();//进一步的能够借阅的合法性判断，在detect_borrow之后


    ///借阅信息层次
    void gethistory();//获取历史借阅信息

    ///用户修改信息层次
    void write(bool flag);//在修改用户信息时，确定控件的属性
    void show_info();//获取用户的各个信息，并且显示
    /////////////////////////////////////////////////

private slots:

    void update_database();//后台运行的更新数据库，跟定时器相关联
///////////////登陆界面//////////////////////////
    //登陆层次
    void on_login_clicked();//进入注册用户的界面
    void on_getin_clicked();//登陆界面的登陆按钮的功能
    void on_search_clicked();//查询按钮的功能

    //注册层次
    void on_submit_clicked();//注册页面的确认按钮的功能实现
    void on_back_clicked();//从注册界面退回登陆界面


////////////////用户使用界面////////////////////////

    ///借阅层次
    void fborrow();//目录中的借阅操作对应的槽函数
    void on_f1search_clicked();//查询按钮的功能
    void on_f1sure_clicked();//借阅确认按钮的功能
    void on_f1delete_clicked();//取消借阅的按钮的操作
    void on_f1sure1_clicked();//借阅的第二次确认按钮的功能

    ///借阅信息层次
    void fsearch();//目录中的查询历史信息的操作对应的槽函数
    void on_f2xujie_clicked();//续借按钮的操作
    void on_f2back_clicked();//归还书籍按钮的操作
    void on_f2pay_clicked();//缴费操作按钮的功能

    ///用户修改信息层次
    void fchange();//目录中的修改用户信息的操作对应的槽函数
    void on_f3change_clicked();//信息修改按钮的功能
    void on_f3delete_clicked();//不修改的回退操作
    void on_f3sure_clicked();//修改的确认按钮

    void exit1();//返回开始界面
private:
    Ui::MainWindow *ui;
    Ui::login1 *ui2;
    QSqlDatabase db;
    QString namenum;//记录学号
    float moneyz;//记录欠款金额
    int days;//记录超出天数
    bool flag;//代表是否已经进入使用阶段
    int numbook;//可借书本个数
    QTimer *timer1;
    QSqlTableModel *model;// 该类提供了一个可读写单张 SQL 表的可编辑数据模型
};

#endif // MAINWINDOW_H
