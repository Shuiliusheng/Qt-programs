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
#include<QMessageBox>
#include <QTextCodec>
#include<QDebug>
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
    //层次转换函数
    void hide1(bool flag);//hide 系列，用于隐藏控件，使得界面可以分层，而不用使用太多界面
    void hide(bool flag);//hide 系列，用于隐藏控件，使得界面可以分层，而不用使用太多界面

    //登陆层次
    bool login1();//登陆用户函数

    //注册层次
    int detect1();//注册时，用户输入信息的合法性
    bool reg();//注册到数据库的student表中


////////////////用户使用界面////////////////////////
    void hide2(bool flag);//层次转换函数
    void hide3(bool flag);
    void hide5(bool flag);
    void hide6(bool flag);
    void hide7(bool flag);
    void hide4(bool flag,int i);

///开始界面显示层次
    void initpaint();//第二界面的初始化绘制，包括各个目录内容


//////////////用户信息操作目录
    //处理用户各种请求层次
    int cal_num_lend(QString name);//根据用户的学号和相应的级别计算此人可借的本数
    void update_sure(QString name,QString num);//根据学号和书籍编号，在进行借书确认后，对数据库进行更新
    void update_xujie(QString name,QString num);//根据学号和书籍编号，在进行续借确认后，对数据库进行更新
    void update_back(QString name,QString num);//根据学号和书籍编号，在进行归还确认后，对数据库进行更新
    void update_pay(QString name);//根据学号，在确认缴费操作后对student表更新
    void update_add(QString name);//根据学号，在确认用户注册申请操作后对student表更新

    //查看用户信息层次
    void update_deletes(QString name);//根据学号，在执行删除学生信息后，对数据库进行更新



///////图书信息操作目录
    //添加书籍层次
    bool addbook(QString str[]);//根据添加书目输入的信息，对book表进行数据更新

    //删除书籍信息层次
    void update_deleteb(QString name);//在执行删除书目之后，对数据库进行数据更新

private slots:
    void update_database();//更新数据库


///////////////登陆界面//////////////////////////
    //登陆层次
    void on_login_clicked();//登陆按钮操作
    void on_reg_clicked();//进入注册层次入口按钮
    void on_search_clicked();//查询书籍按钮
    //注册层次
    void on_back_clicked();//回退到开始登陆界面按钮
    void on_submit_clicked();//注册界面时的注册确认按钮功能


////////////////用户使用界面////////////////////////
    ///开始界面显示层次
    void message();


//////////////用户信息操作目录
    //处理用户各种请求层次
    void dispose_apply();//处理各种申请的槽函数
    void on_f11chose_activated(const QString &arg1);//根据下拉框，决定处理哪种请求
    void on_result_pressed(const QModelIndex &index);//确定用户选择的哪条记录，并显示出来
    void on_f11sure_clicked();//用户的第一次确认单个处理按钮
    void on_f11sureall_clicked();//用户的第一次确认所有处理按钮
    void on_f11bsure_clicked();//用户的第二次确认单个处理按钮，并进行处理
    void on_f11bback_clicked();//用户的第二次确认单个处理确认时的取消按钮
    void on_f11bsure1_clicked();//用户的第二次确认所有处理按钮，并进行处理
    void on_f11bback1_clicked();//用户的第二次确认所有处理确认时的取消按钮


    //查看用户信息层次
    void show_student();//显示学生信息的槽函数，用于查看和删除学生目录
    void on_f12method_activated(const QString &arg1);//根据下拉框，确定查询学生信息的方式
    void on_f12sure_clicked();//根据输入和查询方式，确定学生结果的确认按钮
    void on_f12delete_clicked();//删除单个学生信息的第一次确认按钮，第二次确认为对话框
    void on_f12delete1_clicked();//删除毕业学生信息的第一次确认按钮，第二次确认为对话框


    //查看管理员信息层次。。特殊用户可以，只有一个,不可传递
    void show_student1();//超级用户操作//显示管理员的所有信息的槽函数，用于目录的相应
    void on_f12b2_clicked();//确认修改管理员信息操作的按钮，第二次确认为对话框
    void on_f12b1_clicked();//确认删除管理员信息操作的按钮，第二次确认为对话框
    void on_f12b3_clicked();//确认增加管理员信息操作的按钮，第二次确认为对话框


///////图书信息操作目录
    //添加书籍层次
    void change_book();//添加书籍目录对应的槽函数，用于初始化层次
    void on_f21b1_clicked();//确认根据用户输入添加书籍的按钮，内置合法性检查
    void on_f21b2_clicked();//通过文件进行书目添加的按钮，有格式要求，会提示
    void on_f21b3_clicked();//导出书目信息的按钮，可选择保存路径


    //删除书籍信息层次
    void delete_book();//删除书籍信息目录对应槽函数，用于初始层次
    void on_f22c1_activated(const QString &arg1);//根据下拉框，选择查询图书的方式
    void on_f22b1_2_clicked();//根据查询方式和输入内容查找图书信息
    void on_f22b1_clicked();//删除书籍的确认按钮，第二次确认为对话框
    void on_f22b2_clicked();//删除所有书籍，就目前查找到的，第二次确认为对话框

//////用户信息修改目录
    void change_useinfo();//修改用户信息目录对应的槽函数，用于初始化层次
    void on_f3b_clicked();//确认修改用户信息的确认按钮，第二次确认为对话框


/////返回开始界面层次
    void returns();//返回开始界面的槽函数

private:
    Ui::MainWindow *ui;
    Ui::login1 *ui2;
    QSqlDatabase db;
    QString namenum;//记录管理员号
    float moneyz;//记录欠款金额
    int days;//记录超出天数
    bool flag;
    QSqlTableModel *model;// 该类提供了一个可读写单张 SQL 表的可编辑数据模型
    QSqlTableModel *model1;
    QSqlTableModel *model2;
    QTimer *timer1;//定时器，用于实时的更新数据
    int recordnum;//所选记录的位置
};

#endif // MAINWINDOW_H
