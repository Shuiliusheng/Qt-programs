#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_login1.h"
#include<QFileDialog>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),ui2(new Ui::login1),timer1(new QTimer(this))
{
    ui->setupUi(this);
    days=0;
    flag=false;
    recordnum=-1;
    setAutoFillBackground(true);//设置背景
    QPalette p;
    QPixmap p1("./xingkong.jpg");
    p.setBrush(QPalette::Window,QBrush(p1));
    setPalette(p);

    QTextCodec::setCodecForTr(QTextCodec::codecForName("GB2312"));//设置中文显示
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("GB2312"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("GB2312"));

    setMaximumSize(392,363);//设置界面的固定大小
    setMinimumSize(392,363);
    hide(true);
    hide1(false);
    connectdb();//连接数据库

    initdata();//用于初始化数据库内容
    QTimer *timer=new QTimer(this);

    connect(timer,SIGNAL(timeout()),this,SLOT(update_database()));
    timer->start(60000);//一分钟执行一次更新数据库操作
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::connectdb()//连接数据库
{
    db = QSqlDatabase::addDatabase("QSQLITE");
 //   db = QSqlDatabase::addDatabase("QODBC");//选择数据库引擎
    db.setDatabaseName("library");
    db.setUserName(tr("sa"));
    db.setPassword("12345");

    if (!db.open())//打开数据库
    {
       QMessageBox::critical(0, qApp->tr("Cannot open database"),qApp->tr("Unable to establish a database connection."), QMessageBox::Cancel);
       close();//关闭应用
       return ;
    }
}
void MainWindow::initdata()//使用程序初始化构建或者添加数据
{
//    QSqlQuery query;QString sql;
//    sql=QString::fromLocal8Bit("select * Admin");
//    query.exec(sql);
//    namenum=QString::fromLocal8Bit("2013302544");
}
void MainWindow::update_borrow()//更新借阅时的超出天数
{
    QSqlQuery query;
    QString sql=QString::fromLocal8Bit("select 学号 from student where 已借本数 != '-1'");
    query.exec(sql);
    qDebug()<<query.lastError()<<endl;
    while(query.next())
    {
        QString name=query.value(0).toString();
        QString sql=QString::fromLocal8Bit("select 借出日期,图书编号,可借天数 from borrow where 学号 = '");
        sql=sql+name+tr("' and 借书请求 = 'False'");//结束请求为False代表已经借到书籍
        if(query.exec(sql))
        {
            while(query.next())
            {
                QString temp=query.value(0).toString();
                int day=query.value(2).toInt();
                QDate date=QDate::currentDate();//现在的日期
                QDate date1=QDate::fromString(temp,"yyyyMMdd");//将20130411的格式转化为QDate类型
                int day1=day-date.toJulianDay()+date1.toJulianDay();
                if(day1<0)
                {
                    QString temp1=query.value(1).toString();
                    day1*=-1;
                    sql=QString::fromLocal8Bit("update borrow set 超出天数 = '");
                    sql=sql+QString::number(day1)+tr("' where 学号 = '");
                    sql=sql+name+tr("' and 图书编号 = '")+temp1+tr("'");//拼接查询语句
                    if(!query.exec(sql))
                        qDebug()<<query.lastError()<<endl;
                }
            }
        }
    }
}
void MainWindow::update_database()
{
    if(flag)
    {
        update_borrow();
    }
}

///////////////登陆界面//////////////////////////
//层次转换函数
void MainWindow::hide1(bool flag)//hide 系列，用于隐藏控件，使得界面可以分层，而不用使用太多界面
{
    ui->usename1->setVisible(flag);
    ui->usename1->setText(tr("2013300000"));
    ui->lname1->setVisible(flag);
    ui->luse1->setVisible(flag);
    ui->name->setVisible(flag);
    ui->name->setText(tr(""));
    ui->submit->setVisible(flag);
    ui->password1->setVisible(flag);
    ui->password1->setText(tr(""));
    ui->lpass1->setVisible(flag);
    ui->back->setVisible(flag);
}
void MainWindow::hide(bool flag)//hide 系列，用于隐藏控件，使得界面可以分层，而不用使用太多界面
{
    ui->luse->setVisible(flag);
    ui->password->setVisible(flag);
    ui->password->setText(tr(""));
    ui->usename->setVisible(flag);
    ui->usename->setText(tr(""));
    ui->reg->setVisible(flag);
    ui->login->setVisible(flag);
    ui->search->setVisible(flag);
    ui->lpass->setVisible(flag);
    ui->lpass->setVisible(flag);
}

//登陆层次
bool MainWindow::login1()//登陆用户函数
{
    QSqlQuery query;
    QString sql,sql1=ui->usename->text();
    sql=QString::fromLocal8Bit("select 登陆密码,申请状态 from Admin where 管理员号 = '")+sql1+tr("'");
    query.exec(sql);

    query.next();
    QString pass1=query.value(0).toString();//根据学号获取相应的密码和已借的本数
    bool tflag=query.value(1).toBool();//使用申请状态来表示此用户注册但未被高级管理员确认

    QString pass=ui->password->text();
    if(QString::compare(pass1,pass)!=0)//密码不同
    {
        QMessageBox::warning(0, qApp->tr("登陆"),qApp->tr("密码错误！请检查！"), QMessageBox::Default);
        return false;
    }
    else
    {
        if(!tflag)//未被确认的用户
        {
            QMessageBox::warning(0, qApp->tr("登陆"),qApp->tr("尚未通过申请确认！"), QMessageBox::Default);
            return false;
        }
        else
            return true;
    }
}
void MainWindow::on_login_clicked()//登陆按钮操作
{
    QString usename=ui->usename->text();//获取用户名和密码
    QString name=ui->password->text();

    if(usename.isEmpty()||usename.isNull()||name.isEmpty()||name.isNull())//合法性检查
    {
        QMessageBox::warning(0, qApp->tr("提交"),qApp->tr("输入错误！请检查！"), QMessageBox::Default);
    }
    else
    {
        if(login1())//登陆
        {
            this->flag=true;
            this->namenum=usename;//存储管理员号，用于下一界面的使用

            update_borrow();

            initpaint();//初始化绘制下一界面

            setAutoFillBackground(true);//设置下一界面的背景
            QPalette p;
            QPixmap p1("./xingkong5.jpg");
            p.setBrush(QPalette::Window,QBrush(p1));
            setPalette(p);

            setMaximumSize(652,486);//设置固定大小
            setMinimumSize(652,486);

            connect(timer1,SIGNAL(timeout()),this,SLOT(message()));
            timer1->start(5000);//设置定时器，5秒钟检测一次用户申请

            message();//进行是否有用户请求，进行提示
            hide2(false);//设置层次的控件分层隐藏函数
            hide3(false);
            hide5(false);
            hide6(false);
            hide7(false);
            ui2->date->setText(QDate::currentDate().toString("yyyy-MM-dd"));//显示当前日期

        }
        else
            hide(true);//无法登陆，返回登陆界面的登陆层次
    }
}
void MainWindow::on_reg_clicked()//进入注册层次入口按钮
{
    hide(false);
    hide1(true);
    setMaximumSize(392,363);
    setMinimumSize(392,363);
}
void MainWindow::on_search_clicked()//查询书籍按钮
{
    s.init();//另一界面的初始化
    s.show();//另一界面的唤起
}

//注册层次
int MainWindow::detect1()//注册时，用户输入信息的合法性
{
    QString usename=ui->usename1->text();
    if(usename.isEmpty()||usename.isNull())
        return 0;
    QString name=ui->name->text();
    if(name.isEmpty()||name.isNull())
        return 1;
    QString pass1=ui->password1->text();
    if(pass1.isEmpty()||pass1.isNull())
        return 3;
    if(pass1.length()>=29)
        return 6;

    QSqlQuery query;
    QString sql;
    sql=QString::fromLocal8Bit("select 登陆密码 from Admin where 管理员号=")+usename;
    query.exec(sql);
    query.next();
    QString temp=query.value(0).toString();//通过查询，判断是否已经被注册过
    if(temp.isNull()||temp.isEmpty())//没有登录密码，即为未注册此用户
        return 5;
    else
        return 4;//返回值用于确定提示消息的类型
}
bool MainWindow::reg()//注册到数据库的student表中
{
    QSqlQuery query;

    /////将用户的输入信息组合在一起，形成一个sql插入语句
    QString sql,s1,s2;
    sql=QString::fromLocal8Bit("insert into Admin(管理员号,姓名,登陆密码,申请状态) values('");
    s1=ui->usename1->text();
    s2=ui->name->text();
    sql=sql+s1+tr("','")+s2+tr("','");
    s1=ui->password1->text();
    sql=sql+s1+tr("','False')");//等号左边的不用引号，右边需要引号
    bool flag=query.exec(sql);
//    qDebug() <<query.lastError()<<endl;//如果错误，输出错误类型
    return flag;
}
void MainWindow::on_submit_clicked()//注册界面时的注册确认按钮功能
{
    int flag=detect1();//用户信息检查合法性
    if(flag==5)//用户输入正确
    {
        if(reg())//注册
            QMessageBox::information(0, qApp->tr("注册"),qApp->tr("申请提交成功"), QMessageBox::Ok);
        else
            QMessageBox::warning(0, qApp->tr("注册"),qApp->tr("请重新注册！"), QMessageBox::Default);
        ///转换界面
        hide(false);
        hide1(true);
        setMaximumSize(392,363);
        setMinimumSize(392,363);
    }
    else
    {
        switch(flag){//根据返回的数据，显示出不同的错误信息
        case 0:QMessageBox::warning(0, qApp->tr("注册"),qApp->tr("管理员号不能为空！"), QMessageBox::Default);
               break;
        case 1:QMessageBox::warning(0, qApp->tr("注册"),qApp->tr("姓名不能为空！"), QMessageBox::Default);
               break;
        case 3:QMessageBox::warning(0, qApp->tr("注册"),qApp->tr("密码不能为空！"), QMessageBox::Default);
               break;
        case 6:QMessageBox::warning(0, qApp->tr("注册"),qApp->tr("密码过长！"), QMessageBox::Default);
               break;
        default:QMessageBox::warning(0, qApp->tr("注册"),qApp->tr("此管理员号已被注册！"), QMessageBox::Default);
        }
    }
}
void MainWindow::on_back_clicked()//回退到开始登陆界面按钮
{
    hide1(false);
    hide(true);
    setMaximumSize(392,363);
    setMinimumSize(392,363);
}



////////////////用户使用界面////////////////////////
//层次转换函数
void MainWindow::hide2(bool flag)//设置每一个层次的控件的显隐性
{
    ui2->f11chose->setVisible(flag);
    ui2->f11l1->setVisible(flag);
    ui2->f11l2->setVisible(flag);
    ui2->f11l3->setVisible(flag);
    ui2->result->setVisible(flag);
    ui2->f11l4->setVisible(flag);
    ui2->f11sureall->setVisible(flag);
    ui2->f11sure->setVisible(flag);
    ui2->f11l5->setVisible(flag);

    ui2->f11bback->setVisible(flag);
    ui2->f11bsure->setVisible(flag);
    ui2->f11bsure1->setVisible(flag);
    ui2->f11bback1->setVisible(flag);
}
void MainWindow::hide3(bool flag)
{
    ui2->f12method->setVisible(flag);
    ui2->f12l1->setVisible(flag);
    ui2->f12b1->setVisible(false);
    ui2->f12b3->setVisible(false);
    ui2->f12b2->setVisible(false);
    ui2->f12l2->setVisible(false);
    ui2->f12college->setVisible(false);
    ui2->f12grade->setVisible(false);
    ui2->f12sure->setVisible(false);
    ui2->f12input->setVisible(false);

    ui2->result->setVisible(flag);
    ui2->f12delete->setVisible(flag);
    ui2->f12delete1->setVisible(flag);
}
void MainWindow::hide5(bool flag)
{
    ui2->f21l1->setVisible(flag);
    ui2->f21l2->setVisible(flag);
    ui2->f21l3->setVisible(flag);
    ui2->f21l4->setVisible(flag);
    ui2->f21b1->setVisible(flag);
    ui2->f21b2->setVisible(flag);
    ui2->f21b3->setVisible(flag);

    ui2->f21in1->setVisible(flag);
    ui2->f21in1->setText("");
    ui2->f21in2->setVisible(flag);
    ui2->f21in2->setText("");
    ui2->f21in3->setVisible(flag);
    ui2->f21in3->setText("");
    ui2->f21in4->setVisible(flag);
}
void MainWindow::hide6(bool flag)
{
    ui2->result->setVisible(flag);
    ui2->f22b1->setVisible(false);
    ui2->f22b1_2->setVisible(false);
    ui2->f22b2->setVisible(false);
    ui2->f22c1->setVisible(flag);
    ui2->f22c2->setVisible(false);
    ui2->f22l1->setVisible(flag);
    ui2->f22l2->setVisible(false);
    ui2->f12l3->setVisible(flag);
    ui2->f12l4->setVisible(flag);
    ui2->f22in1->setVisible(false);
}
void MainWindow::hide7(bool flag)
{
    ui2->f3b->setVisible(flag);
    ui2->f3in1->setVisible(flag);
    ui2->f3in2->setVisible(flag);
    ui2->f3in3->setVisible(flag);
    ui2->f3l1->setVisible(flag);
    ui2->f3l2->setVisible(flag);
    ui2->f3l3->setVisible(flag);
}
void MainWindow::hide4(bool flag,int i)
{
    ui2->f12method->setVisible(!flag);
    ui2->f12l1->setVisible(!flag);

    ui2->f12l2->setVisible(flag);
    ui2->f12sure->setVisible(flag);
    ui2->f12college->setVisible(false);
    ui2->f12input->setVisible(false);
    ui2->f12grade->setVisible(false);
    switch(i){
        case 2:ui2->f12college->setVisible(flag);break;
        case 3:ui2->f12grade->setVisible(flag);break;
        case 7:break;
        default:ui2->f12input->setVisible(flag);
    }
}

///开始界面显示层次
void MainWindow::initpaint()//第二界面的初始化绘制，包括各个目录内容
{
    ui2->setupUi(this);//唤起第二界面

    QMenu *first1,*second,*third;///添加功能目录和目录内的内容选项
    first1=menuBar()->addMenu(tr("使用功能"));

    QAction *start=new QAction(QIcon("./tubiao3.jpg"),tr("开始界面"),this);
    start->setStatusTip(tr("开始界面"));
    start->setWhatsThis(tr("开始界面"));
    connect(start,SIGNAL(triggered()),this,SLOT(returns()));

    first1->addAction(start);

    second=first1->addMenu(QIcon("./tubiao2.jpg"),tr("用户信息操作"));

    third=first1->addMenu(QIcon("./tubiao1.jpg"),tr("图书信息操作"));

    QAction *addbook=new QAction(QIcon("./tubiao1.jpg"),tr("添加图书信息"),this);
    addbook->setStatusTip(tr("添加图书信息"));
    addbook->setWhatsThis(tr("添加图书信息"));
    connect(addbook,SIGNAL(triggered()),this,SLOT(change_book()));//和change_book()槽函数连接在一起

    QAction *deletebook=new QAction(QIcon("./tubiao1.jpg"),tr("删除图书信息"),this);
    deletebook->setStatusTip(tr("删除信息操作"));
    deletebook->setWhatsThis(tr("删除信息操作"));
    connect(deletebook,SIGNAL(triggered()),this,SLOT(delete_book()));//和change_book()槽函数连接在一起

    QAction *searchbook=new QAction(QIcon("./tubiao1.jpg"),tr("查询图书信息"),this);
    searchbook->setStatusTip(tr("查询图书信息"));
    searchbook->setWhatsThis(tr("查询图书信息"));
    connect(searchbook,SIGNAL(triggered()),this,SLOT(on_search_clicked()));//和change_book()槽函数连接在一起

    third->addAction(addbook);
    third->addAction(deletebook);
    third->addAction(searchbook);

    QAction *change_data=new QAction(QIcon("./tubiao3.jpg"),tr("修改信息"),this);
    change_data->setStatusTip(tr("修改用户信息"));
    change_data->setWhatsThis(tr("修改用户信息"));
    connect(change_data,SIGNAL(triggered()),this,SLOT(change_useinfo()));


    QAction *exit=new QAction(QIcon("./tubiao3.jpg"),tr("注销退出"),this);
    exit->setStatusTip(tr("用户注销退出"));
    exit->setWhatsThis(tr("用户注销退出"));
    connect(exit,SIGNAL(triggered()),this,SLOT(close()));

    first1->addAction(change_data);
    first1->addAction(exit);


    QAction *make_sure=new QAction(QIcon("./tubiao1.jpg"),tr("处理用户请求"),this);
    make_sure->setStatusTip(tr("处理用户请求"));
    make_sure->setWhatsThis(tr("处理用户请求"));
    connect(make_sure,SIGNAL(triggered()),this,SLOT(dispose_apply()));

    QAction *lookinfo=new QAction(QIcon("./tubiao4.jpg"),tr("查看用户信息"),this);
    lookinfo->setStatusTip(tr("查看用户信息"));
    lookinfo->setWhatsThis(tr("查看用户信息"));
    connect(lookinfo,SIGNAL(triggered()),this,SLOT(show_student()));

    QAction *lookinfo1=new QAction(QIcon("./tubiao4.jpg"),tr("查看管理员信息"),this);
    lookinfo1->setStatusTip(tr("查看管理员信息"));
    lookinfo1->setWhatsThis(tr("查看管理员信息"));
    connect(lookinfo1,SIGNAL(triggered()),this,SLOT(show_student1()));


    second->addAction(make_sure);
    second->addAction(lookinfo);
    if(QString::compare(namenum,tr("2013302544"))==0)//超级用户编号
    {
        second->addAction(lookinfo1);
    }



}
void MainWindow::message()//检查是否有用户请求，进行提示
{
    QSqlTableModel *model=new QSqlTableModel;//设置Qt内数据库查询的模型，用户tableview中的配套结果显示
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);//设置属性，只有提交操作才会修改数据库
    ui2->result->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置显示结果之后的结果不能被修改

    QString sql=QString::fromLocal8Bit("借书请求 = 'True'");//拼接形成查询语句
    QString sql1=QString::fromLocal8Bit("续借请求 = 'True'");
    QString sql2=QString::fromLocal8Bit("归还请求 = 'True'");
    QString sql3=QString::fromLocal8Bit("已借本数 = -1 ");
    QString sql4=QString::fromLocal8Bit("缴费请求 = 'True'");
    QString showt=tr(" ^-^ Welcome to Use *-*\n" );
    int num=0;

    model->setTable("borrow");//设置查询的表
    model->setFilter(sql);//设置where的查询语句
    model->select();//查询结果
    num=model->rowCount();//结果的元组个数num
    showt=showt+tr("现有：借书请求")+QString::number(num)+tr("个\n");

    model->setFilter(sql1);
    model->select();
    num=model->rowCount();
    showt=showt+tr("     续借请求")+QString::number(num)+tr("个\n");

    model->setFilter(sql2);
    model->select();
    num=model->rowCount();
    showt=showt+tr("     归还请求")+QString::number(num)+tr("个\n");

    model->setTable("student");//设置查询的表
    model->setFilter(sql4);
    model->select();
    num=model->rowCount();
    showt=showt+tr("     缴费请求")+QString::number(num)+tr("个\n");

    model->setFilter(sql3);
    model->select();
    num=model->rowCount();
    showt=showt+tr("     注册请求")+QString::number(num)+tr("个");
    ui2->stext->setText(showt);

    this->model=model;//将其赋给私有变量，减少方法的参数传递
}

//////////////用户信息操作目录
//处理用户各种请求层次
void MainWindow::dispose_apply()//处理各种申请的槽函数
{
    timer1->stop();
    ui2->stext->setVisible(false);
    hide2(true);//设置层次的控件分层隐藏函数
    ui2->f11bback->setVisible(false);
    ui2->f11bsure->setVisible(false);
    ui2->f11bsure1->setVisible(false);
    ui2->f11bback1->setVisible(false);
    hide3(false);
    hide5(false);
    hide6(false);
    hide7(false);
    on_f11chose_activated(ui2->f11chose->currentText());
}
int MainWindow::cal_num_lend(QString name)//根据用户的学号和相应的级别计算此人可借的本数
{
    QSqlQuery query;
    QString  sql=QString::fromLocal8Bit("select 级别,已借本数 from student where 学号 = '");
    sql=sql+name+tr("'");
    if(query.exec(sql))
    {
        if(query.next())
        {
            QString level=query.value(0).toString();
            int num=query.value(1).toInt();
            int num2=0;
            if(QString::compare(level,tr("本科生"))==0)
                num2=10;
            else if(QString::compare(level,tr("研究生"))==0)
                num2=15;
            else if(QString::compare(level,tr("博士"))==0)
                num2=20;
            else
                num2=25;
            int numbook=num2-num;
            return numbook;
        }
    }
    return 0;
}
void MainWindow::update_sure(QString name, QString num)//根据学号和书籍编号，在进行借书确认后，对数据库进行更新
{
    if(cal_num_lend(name)!=0)
    {
        QSqlQuery query;

        //更新借阅信息表的可借天数为30，超出天数为0，续借状态为false,借书请求置为False，借出日期为今天，管理员号为当前管理员号
        QString sql=QString::fromLocal8Bit("update borrow set 可借天数 = '30' , 超出天数 = '0',续借状态 = 'False',借书请求 = 'False',");
        sql=sql+tr("借出日期 = '");
        QString date=QDate::currentDate().toString("yyyyMMdd");
        sql=sql+date+tr("', 管理员号 = '")+namenum+tr("' where 学号='");
        sql=sql+name+tr("' and 图书编号= '")+num+tr("'");
        query.exec(sql);

        //更新书籍信息表的此书的借阅状态
        sql=QString::fromLocal8Bit("update book set 借阅状态 = 'True',借阅次数=借阅次数+'1' where 图书编号= '")+num+tr("'");
        query.exec(sql);

        //更新学生信息表中的学生借阅本数
        sql=QString::fromLocal8Bit("update student set 已借本数=已借本数+'1' where 学号= '")+name+tr("'");
        if(query.exec(sql))
            ui2->f11l5->setText(tr("借阅申请\n确认完成"));
        else
            ui2->f11l5->setText(tr("借阅申请\n未执行"));
    }
    else
    {
        ui2->f11l5->setText(tr("此人借书数目\n已达到级别"));
    }
}
void MainWindow::update_xujie(QString name, QString num)//根据学号和书籍编号，在进行续借确认后，对数据库进行更新
{
    QSqlQuery query;

    //更新借阅信息表的续借状态为True,续借申请为false,管理员号为当前管理员号,可借天数增加15天
    QString sql=QString::fromLocal8Bit("update borrow set 可借天数 = 可借天数+'15',续借状态 = 'True',续借请求 = 'False',");

    sql=sql+tr("管理员号 = '")+namenum+tr("' where 学号='");
    sql=sql+name+tr("' and 图书编号= '")+num+tr("'");
    if(query.exec(sql))
        ui2->f11l5->setText(tr("续借申请\n确认完成"));
    else
        ui2->f11l5->setText(tr("续借申请\n未执行"));
}
void MainWindow::update_back(QString name, QString num)//根据学号和书籍编号，在进行归还确认后，对数据库进行更新
{
    QSqlQuery query;

    //删除此借阅信息
    QString sql;

    QString temp=this->model->data(model->index(recordnum,2)).toString();
    QDate d1=QDate::fromString(temp,"yyyyMMdd");
    int day=this->model->data(model->index(recordnum,3)).toInt();
    days=QDate::currentDate().toJulianDay()-d1.toJulianDay()-day;
    if(days>0)
    {
        sql=QString::fromLocal8Bit("update student set 欠款金额 = 欠款金额 + '");
        sql=sql+QString::number(days*0.1)+tr("' where 学号 = '")+name+tr("'");
        query.exec(sql);
        qDebug()<<"::"<<query.lastError()<<endl;
    }

    this->model->removeRow(recordnum);
    this->model->submitAll();

    //更新书籍信息表的此书的借阅状态
    sql=QString::fromLocal8Bit("update book set 借阅状态 = 'False' where 图书编号= '")+num+tr("'");
    query.exec(sql);

    //更新学生信息表中的学生借阅本数
    sql=QString::fromLocal8Bit("update student set 已借本数=已借本数-'1' where 学号= '")+name+tr("'");

    if(query.exec(sql))
        ui2->f11l5->setText(tr("归还申请\n确认完成"));
    else
        ui2->f11l5->setText(tr("归还申请\n未执行"));
}
void MainWindow::update_pay(QString name)//根据学号，在确认缴费操作后对student表更新
{
    //更改欠款金额和缴费申请状态
    QString sql=QString::fromLocal8Bit("update student set 欠款金额='0',缴费请求='False' where 学号= '")+name+tr("'");
    QSqlQuery query;
    if(query.exec(sql))
        ui2->f11l5->setText(tr("缴费申请\n确认完成"));
    else
        ui2->f11l5->setText(tr("缴费申请\n未执行"));
//    qDebug()<<query.lastError()<<endl;
}
void MainWindow::update_add(QString name)//根据学号，在确认用户注册申请操作后对student表更新
{
    //更改用户申请状态
    QString sql=QString::fromLocal8Bit("update student set 已借本数='0' where 学号= '")+name+tr("'");
    QSqlQuery query;
    if(query.exec(sql))
        ui2->f11l5->setText(tr("注册申请\n确认完成"));
    else
        ui2->f11l5->setText(tr("注册申请\n未执行"));
}
//槽函数
void MainWindow::on_f11chose_activated(const QString &arg1)//根据下拉框，决定处理哪种请求
{
    if(ui2->f11chose->currentIndex()>2)//设置查询使用的表
        this->model->setTable("student");
    else
        this->model->setTable("borrow");
    QString sql=QString::fromLocal8Bit(" = 'True'");

    if(ui2->f11chose->currentIndex()==4)
        sql=tr("已借本数 = '-1'");
    else
        sql=arg1+sql;

    this->model->setFilter(sql);
    this->model->select();

    ui2->f11l3->setText(arg1+QString::number(model->rowCount())+tr("个"));//设置选择个请求的个数显示
    ui2->result->setModel(this->model);
    ui2->result->show();
    ui2->f11l4->setText("");
}
void MainWindow::on_result_pressed(const QModelIndex &index)//确定用户选择的哪条记录，并显示出来
{
    recordnum=index.row();
    ui2->f11l4->setText(tr(" 现已选中\n 第")+QString::number(index.row()+1)+tr("条记录"));
    ui2->f12l3->setText(tr(" 现已选中\n 第")+QString::number(index.row()+1)+tr("条记录"));
}
void MainWindow::on_f11sure_clicked()//用户的第一次确认单个处理按钮
{
    ui2->f11bback->setVisible(true);
    ui2->f11bsure->setVisible(true);
    ui2->f11bsure1->setVisible(false);
    ui2->f11bback1->setVisible(false);
    ui2->f11sure->setVisible(false);
}
void MainWindow::on_f11sureall_clicked()//用户的第一次确认所有处理按钮
{
    ui2->f11bback1->setVisible(true);
    ui2->f11bsure1->setVisible(true);
    ui2->f11bsure->setVisible(false);
    ui2->f11bback->setVisible(false);
    ui2->f11sureall->setVisible(false);
}
void MainWindow::on_f11bsure_clicked()//用户的第二次确认单个处理按钮，并进行处理
{
    QString temp=ui2->f11l4->text();
    if(temp.isEmpty()||temp.isNull())
    {
        QMessageBox::warning(0, qApp->tr("确认请求"),(tr("未选择任何记录！！！")), QMessageBox::Default);
        on_f11bback_clicked();
        return ;
    }
    QString name=model->data(model->index(recordnum,0)).toString();//获取学号
    QString t2=model->data(model->index(recordnum,1)).toString();//获取图书编号

    int pos=ui2->f11chose->currentIndex();

    switch(pos){
        case 0: update_sure(name,t2);break;
        case 1:update_xujie(name,t2);break;
        case 2:update_back(name,t2);break;
        case 3:update_pay(name);break;
        default:update_add(name);
    }
    QMessageBox::information(0, qApp->tr("确认申请"),qApp->tr("确认操作执行完毕！"), QMessageBox::Default);
    this->model->select();
    ui2->result->setModel(this->model);
    ui2->result->show();
    on_f11bback_clicked();
}
void MainWindow::on_f11bback_clicked()//用户的第二次确认单个处理确认时的取消按钮
{
    ui2->f11bsure->setVisible(false);
    ui2->f11bback->setVisible(false);
    ui2->f11sure->setVisible(true);
}
void MainWindow::on_f11bsure1_clicked()//用户的第二次确认所有处理按钮，并进行处理
{
    for(int i=0;i<model->rowCount();i++)
    {
        QString name=model->data(model->index(i,0)).toString();//获取学号
        QString t2=model->data(model->index(i,1)).toString();//获取图书编号

        int pos=ui2->f11chose->currentIndex();

        switch(pos){
            case 0: update_sure(name,t2);break;
            case 1:update_xujie(name,t2);break;
            case 2:update_back(name,t2);break;
            case 3:update_pay(name);break;
            default:update_add(name);
        }
    }
    QMessageBox::information(0, qApp->tr("确认申请"),qApp->tr("所有确认操作执行完毕！"), QMessageBox::Default);
    this->model->select();
    ui2->result->setModel(this->model);
    ui2->result->show();
    on_f11bback1_clicked();
}
void MainWindow::on_f11bback1_clicked()//用户的第二次确认所有处理确认时的取消按钮
{
    ui2->f11bsure1->setVisible(false);
    ui2->f11bback1->setVisible(false);
    ui2->f11sureall->setVisible(true);
}


//查看用户信息层次
void MainWindow::show_student()//显示学生信息的槽函数，用于查看和删除学生目录
{
    hide2(false);
    hide5(false);
    hide3(true);
    hide6(false);
    hide7(false);
    timer1->stop();
    ui2->f12delete->setVisible(false);
    ui2->f12delete1->setVisible(false);
    ui2->stext->setVisible(true);
    ui2->result->setVisible(false);
}
void MainWindow::update_deletes(QString name)//根据学号，在执行删除学生信息后，对数据库进行更新
{
    QSqlTableModel *model1=new QSqlTableModel;//设置Qt内数据库查询的模型，用户tableview中的配套结果显示
    model1->setEditStrategy(QSqlTableModel::OnManualSubmit);//设置属性，只有提交操作才会修改数据库
    model1->setTable("borrow");
    model1->removeColumns(2,8);
    QString sql=QString::fromLocal8Bit("学号 = '")+name+tr("'");
    model1->setFilter(sql);
    model1->select();

    QSqlQuery query;
    QString sql1=QString::fromLocal8Bit("update book set 借阅状态 = 'False' where 图书编号= '");
    int n=0,n1=model1->rowCount();
    for(n=0;n<n1;n++)
    {
        QString num=model1->data(model1->index(n,1)).toString();
        QString sql=sql1+num+tr("'");
        query.exec(sql);
    }
    for(n=n1-1;n>=0;n--)
        model1->removeRow(n);
    model1->submitAll();
}
//槽函数
void MainWindow::on_f12method_activated(const QString &arg1)//根据下拉框，确定查询学生信息的方式
{
    int num=ui2->f12method->currentIndex();
    if(num<6)
        hide4(true,num);
    else
        hide4(true,7);

    ui2->f12l2->setText(arg1+tr(":"));
}
void MainWindow::on_f12sure_clicked()//根据输入和查询方式，确定学生结果的确认按钮
{
    ui2->f12delete->setVisible(true);
    ui2->f12delete1->setVisible(true);
    recordnum=0;
    hide4(false,7);
    ui2->result->setVisible(true);
    QString method=ui2->f12method->currentText();
    QString name;
    int num=ui2->f12method->currentIndex();
    if(num==2)
        name=ui2->f12college->currentText();
    else if(num==3)
        name=ui2->f12grade->currentText();
    else
        name=ui2->f12input->text();

    QString sql=method+tr(" like '%")+name+tr("%'");

    this->model->setTable("student");
    this->model->removeColumn(model->fieldIndex("登陆密码"));
    this->model->setFilter(sql);
    this->model->select();
    ui2->result->setModel(this->model);
    ui2->result->show();

}
void MainWindow::on_f12delete_clicked()//删除单个学生信息的第一次确认按钮，第二次确认为对话框
{
    int curRow = ui2->result->currentIndex().row();
    //获取选中的行
    QString name=this->model->data(this->model->index(curRow,0)).toString();
    this->model->removeRow(curRow);
    int ok = QMessageBox::warning(this,tr("删除当前行!"),tr("你确定删除当前行吗？"),QMessageBox::No,QMessageBox::Yes);
    if(ok == QMessageBox::No)
    {
        this->model->revertAll(); //如果不删除，则撤销
        ui2->f12l4->setText(tr("删除已撤销！"));
    }
    else
    {
        ui2->f12l4->setText(tr("成功删除!"));
        this->model->submitAll(); //否则提交，在数据库中删除该行
        update_deletes(name);
    }
}
void MainWindow::on_f12delete1_clicked()//删除毕业学生信息的第一次确认按钮，第二次确认为对话框
{
    QSqlTableModel *model1=new QSqlTableModel;//设置Qt内数据库查询的模型，用户tableview中的配套结果显示
    model1->setEditStrategy(QSqlTableModel::OnManualSubmit);//设置属性，只有提交操作才会修改数据库
    model1->setTable("student");
    model1->removeColumns(1,4);
    model1->removeColumns(6,4);

    model1->select();
    int n=0,n1=model1->rowCount();
    for(n=n1-1;n>=0;n--)
    {
        QString temp=model1->data(model1->index(n,1)).toString();
        QDate de=QDate::fromString(temp,"yyyyMM");
        QDate dc=QDate::currentDate();
        int t=de.toJulianDay()-dc.toJulianDay();
        if(t<0)
        {
            QString name=model1->data(model1->index(n,0)).toString();
            model1->removeRow(n);
            update_deletes(name);
        }
    }
    int ok=QMessageBox::warning(this,tr("删除毕业学生"),tr("你确定执行此操作吗？"),QMessageBox::No,QMessageBox::Yes);
    if(ok == QMessageBox::No)
    {
        model1->revertAll(); //如果不删除，则撤销
        ui2->f12l4->setText(tr("删除已撤销！"));
    }
    else
    {
        ui2->f12l4->setText(tr("成功删除!"));
        model1->submitAll(); //否则提交，在数据库中删除该行
    }
}


//查看管理员信息层次。。特殊用户可以，只有一个,不可传递
void MainWindow::show_student1()//显示管理员的所有信息的槽函数，用于目录的相应
{
    ui2->f12l3->setText(tr(""));
    hide2(false);
    hide5(false);
    hide3(false);

    hide6(false);
    hide7(false);
    timer1->stop();
    ui2->stext->setVisible(false);
    ui2->result->setVisible(true);
    ui2->f12b1->setVisible(true);
    ui2->f12b2->setVisible(true);
    ui2->f12b3->setVisible(true);
    QSqlTableModel *model1=new QSqlTableModel;//设置Qt内数据库查询的模型，用户tableview中的配套结果显示
    model1->setEditStrategy(QSqlTableModel::OnManualSubmit);//设置属性，只有提交操作才会修改数据库
    model1->setTable("Admin");
    model1->select();
    ui2->result->setEditTriggers(QAbstractItemView::AllEditTriggers);
    ui2->result->setModel(model1);
    ui2->result->show();
    this->model1=model1;
}
void MainWindow::on_f12b2_clicked()//确认修改管理员信息操作的按钮，第二次确认为对话框
{
    ui2->f12l4->setVisible(true);
    int ok=QMessageBox::warning(this,tr("确认修改"),tr("你确定执行此操作吗？"),QMessageBox::No,QMessageBox::Yes);
    if(ok == QMessageBox::No)
    {
        model1->revertAll();
        ui2->f12l4->setText(tr("修改已撤销！"));
    }
    else
    {
        ui2->f12l4->setText(tr("成功修改!"));
        if(!model1->submitAll()) //否则提交，在数据库中修改记录
            ui2->f12l4->setText(tr("操作失败!"));
        model1->select();
        ui2->result->setModel(model1);
        ui2->result->show();
    }

}
void MainWindow::on_f12b1_clicked()//确认删除管理员信息操作的按钮，第二次确认为对话框
{
    int curRow = ui2->result->currentIndex().row();
    this->model1->removeRow(curRow);
    ui2->f12l4->setVisible(true);
    int ok=QMessageBox::warning(this,tr("确认删除"),tr("你确定执行此操作吗？"),QMessageBox::No,QMessageBox::Yes);
    if(ok == QMessageBox::No)
    {
        model1->revertAll();
        ui2->f12l4->setText(tr("删除已撤销！"));
    }
    else
    {
        ui2->f12l4->setText(tr("成功删除!"));
        if(!model1->submitAll()) //否则删除，在数据库中修改记录
            ui2->f12l4->setText(tr("操作失败!"));
        model1->select();
        ui2->result->setModel(model1);
        ui2->result->show();
    }
}
void MainWindow::on_f12b3_clicked()//确认增加管理员信息操作的按钮，第二次确认为对话框
{
    int ok=QMessageBox::warning(this,tr("确认添加"),tr("你确定执行此操作吗？"),QMessageBox::No,QMessageBox::Yes);
    if(ok == QMessageBox::No)
    {
        ui2->f12l4->setText(tr("添加已撤销！"));
    }
    else
    {
        ui2->f12l4->setText(tr("成功添加!"));
        int rowNum = model1->rowCount(); //获得表的行数
        model1->insertRow(rowNum); //添加行
    }

}



//////////////////图书信息操作目录
//添加书籍层次
bool MainWindow::addbook(QString str[])//根据添加书目输入的信息，对book表进行数据更新
{
    if(str[0].isEmpty()||str[0].isNull())
    {
        QMessageBox::warning(this,tr("添加书籍"),tr("编号不能为空"),QMessageBox::Yes);
        return false;
    }
    QSqlQuery query;
    QString sql=QString::fromLocal8Bit("insert into book values('");
    sql=sql+str[0]+tr("','");
    sql=sql+str[1]+tr("','");
    sql=sql+str[2]+tr("','");
    sql=sql+str[3]+tr("','");
    sql=sql+(QDate::currentDate().toString("yyyyMM"))+tr("','");
    sql=sql+tr("0','False')");
    if(!query.exec(sql))
    {
        QMessageBox::warning(this,tr("添加书籍"),tr("书籍编号重复"),QMessageBox::Yes);
        return false;
    }
    return true;
}
//槽函数
void MainWindow::change_book()//添加书籍目录对应的槽函数，用于初始化层次
{
    hide5(true);
    hide2(false);
    hide3(false);
    hide6(false);
    hide7(false);
    ui2->stext->setVisible(false);
    ui2->result->setVisible(false);

}
void MainWindow::on_f21b1_clicked()//确认根据用户输入添加书籍的按钮，内置合法性检查
{
    QString num=ui2->f21in1->text();
    if(num.isEmpty()||num.isNull())
    {
        QMessageBox::warning(this,tr("添加书籍"),tr("编号不能为空"),QMessageBox::Yes);
        return ;
    }
    QSqlQuery query;
    QString sql=QString::fromLocal8Bit("insert into book values('");
    sql=sql+num+tr("','");
    sql=sql+ui2->f21in2->text()+tr("','");
    sql=sql+ui2->f21in3->toPlainText()+tr("','");
    sql=sql+ui2->f21in4->currentText()+tr("','");
    sql=sql+(QDate::currentDate().toString("yyyyMM"))+tr("','");
    sql=sql+tr("0','False')");
    if(!query.exec(sql))
    {
        QMessageBox::warning(this,tr("添加书籍"),tr("书籍编号重复"),QMessageBox::Yes);
    }
    else
    {
        QMessageBox::information(this,tr("添加书籍"),tr("添加书籍成功"),QMessageBox::Yes);
    }
}
void MainWindow::on_f21b2_clicked()//通过文件进行书目添加的按钮，有格式要求，会提示
{
    QString form=QString::fromLocal8Bit("00000003\n计算机科学与技术\n无\n计算机\n");
    QMessageBox::information(this,tr("书目格式"),form+tr("00000003\n计算机科学与技术\n没有大作业\n计算机"),QMessageBox::Yes);
    QString fname=QFileDialog::getOpenFileName(this,tr("find book information file"),"",tr("*.txt"));
    QFile file(fname);
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        QMessageBox::warning(this,tr("添加书目"),tr("文件打开失败!"),QMessageBox::Yes);
        return;
    }
    QString str[4];
    QTextStream in(&file);
    int i=0,num=0;
    while(!in.atEnd())
    {
        str[i]=in.readLine();
        qDebug()<<str[i]<<endl;
        i++;
        if(i==4)
        {
            i=0;
            if(!addbook(str))
            {
                int ok=QMessageBox::warning(this,tr("添加书目"),tr("添加出错，继续？中断？"),QMessageBox::No,QMessageBox::Yes);
                if(ok==QMessageBox::No)
                    break;
            }
            else
                num++;
        }
    }
    QMessageBox::warning(this,tr("添加书目"),tr("添加结束,添加本数")+QString::number(num),QMessageBox::Yes);
    file.close();
}
void MainWindow::on_f21b3_clicked()//导出书目信息的按钮，可选择保存路径
{
    QString fname=QFileDialog::getExistingDirectory(this,tr("保存目录位置"),tr("选择目录"),QFileDialog::ShowDirsOnly );
//    QFileDialog::getExistingDirectory
    fname.append("书目.txt");
    QFile file(fname);
    if(!file.open(QIODevice::WriteOnly|QIODevice::Text))
    {
        QMessageBox::warning(this,tr("创建文件"),tr("文件创建失败!"),QMessageBox::Yes);
        return;
    }
    QTextStream out(&file);
    QSqlQuery query;
    int num=0;
    QString sql=QString::fromLocal8Bit("select 图书编号,图书名称,图书简介,归属学科 from book");
    if(query.exec(sql))
    {
        while(query.next())
        {
            for(int i=0;i<4;i++)
            {
                QString temp=query.value(i).toString();
                out<<temp<<endl;
            }
            num++;
        }
    }
    else
        QMessageBox::warning(this,tr("书目导出"),tr("导出失败！"),QMessageBox::Yes);
    QMessageBox::warning(this,tr("导出书目"),tr("添加结束,导出本数")+QString::number(num),QMessageBox::Yes);
    file.close();
}


//删除书籍信息层次
void MainWindow::update_deleteb(QString name)//在执行删除书目之后，对数据库进行数据更新
{
    QSqlTableModel *model1=new QSqlTableModel;//设置Qt内数据库查询的模型，用户tableview中的配套结果显示
    model1->setEditStrategy(QSqlTableModel::OnManualSubmit);//设置属性，只有提交操作才会修改数据库
    model1->setTable("borrow");
    model1->removeColumns(2,8);
    QString sql=QString::fromLocal8Bit("图书编号 = '")+name+tr("'");
    model1->setFilter(sql);
    model1->select();

    QSqlQuery query;
    QString sql1=QString::fromLocal8Bit("update student set 已借本数 = 已借本数-'1' where 学号= '");
    int n=0,n1=model1->rowCount();
    for(n=0;n<n1;n++)
    {
        QString num=model1->data(model1->index(n,0)).toString();
        QString sql=sql1+num+tr("'");
        query.exec(sql);
    }
    for(n=n1-1;n>=0;n--)
        model1->removeRow(n);
    model1->submitAll();
}
//槽函数
void MainWindow::delete_book()//删除书籍信息目录对应槽函数，用于初始层次
{
    hide2(false);//设置层次的控件分层隐藏函数
    hide3(false);
    hide5(false);
    hide6(true);
    hide7(false);
    ui2->f12l3->setText(tr(""));
    ui2->f12l4->setText(tr(""));
    ui2->result->setVisible(false);


}
void MainWindow::on_f22c1_activated(const QString &arg1)//根据下拉框，选择查询图书的方式
{
    ui2->f22c1->setVisible(false);
    ui2->f22l1->setVisible(false);
    ui2->f22l2->setVisible(true);
    ui2->f22b1_2->setVisible(true);
    if(ui2->f22c1->currentIndex()<3)
        ui2->f22in1->setVisible(true);
    else
        ui2->f22c2->setVisible(true);

    ui2->f22l2->setText(arg1+tr(":"));
}
void MainWindow::on_f22b1_2_clicked()//根据查询方式和输入内容查找图书信息
{
    ui2->f22b1->setVisible(true);
    ui2->f22b2->setVisible(true);
    ui2->result->setVisible(true);
    QSqlTableModel *model2=new QSqlTableModel;//设置Qt内数据库查询的模型，用户tableview中的配套结果显示
    model2->setEditStrategy(QSqlTableModel::OnManualSubmit);//设置属性，只有提交操作才会修改数据库
    model2->setTable("book");

    QString sql=QString::fromLocal8Bit("");
    sql=sql+ui2->f22c1->currentText()+tr(" like '%");
    if(ui2->f22c2->currentIndex()==3)
        sql=sql+ui2->f22c2->currentText()+tr("%'");
    else
        sql=sql+ui2->f22in1->text()+tr("%'");

    model2->select();
    this->model2=model2;
    ui2->result->setModel(model2);
    ui2->result->show();

    ui2->f22c1->setVisible(true);
    ui2->f22l1->setVisible(true);
    ui2->f22l2->setVisible(false);
    ui2->f22b1_2->setVisible(false);

    ui2->f22in1->setVisible(false);
    ui2->f22c2->setVisible(false);

}
void MainWindow::on_f22b1_clicked()//删除书籍的确认按钮，第二次确认为对话框
{
    int curRow = ui2->result->currentIndex().row();
    //获取选中的行
    QString name=this->model2->data(this->model2->index(curRow,0)).toString();
    this->model2->removeRow(curRow);
    int ok = QMessageBox::warning(this,tr("删除当前行!"),tr("你确定删除当前行吗？"),QMessageBox::No,QMessageBox::Yes);
    if(ok == QMessageBox::No)
    {
        this->model2->revertAll(); //如果不删除，则撤销
        ui2->f12l4->setText(tr("删除已撤销！"));
    }
    else
    {
        ui2->f12l4->setText(tr("成功删除!"));
        this->model2->submitAll(); //否则提交，在数据库中删除该行
        update_deleteb(name);
    }
}
void MainWindow::on_f22b2_clicked()//删除所有书籍，就目前查找到的，第二次确认为对话框
{
    int n=0,n1=model2->rowCount();
    for(n=n1-1;n>=0;n--)
    {
        QString name=model2->data(model2->index(n,0)).toString();
        model2->removeRow(n);
        update_deleteb(name);
    }
    int ok=QMessageBox::warning(this,tr("删除书籍"),tr("你确定执行此操作吗？"),QMessageBox::No,QMessageBox::Yes);
    if(ok == QMessageBox::No)
    {
        model2->revertAll(); //如果不删除，则撤销
        ui2->f12l4->setText(tr("删除已撤销！"));
    }
    else
    {
        ui2->f12l4->setText(tr("成功删除!"));
        model2->submitAll(); //否则提交，在数据库中删除该行
    }
}


/////////////////用户信息修改目录
void MainWindow::change_useinfo()//修改用户信息目录对应的槽函数，用于初始化层次
{
    ui2->stext->setVisible(false);
    hide2(false);//设置层次的控件分层隐藏函数
    hide3(false);
    hide5(false);
    hide6(false);
    hide7(true);
    ui2->f3in1->setEnabled(false);
    ui2->f3in1->setText(namenum);
    ui2->f3in2->setEnabled(true);
    ui2->f3in3->setEnabled(true);

    QSqlQuery query;
    QString sql=QString::fromLocal8Bit("select 姓名,登陆密码 from Admin where 管理员号 = '");
    sql=sql+namenum+tr("'");//拼接成查询语句

    if(query.exec(sql))//执行，根据学号获取各个信息
    {
        if(query.next())
        {
            ui2->f3in2->setText(query.value(0).toString());//显示获取到的信息
            ui2->f3in3->setText(query.value(1).toString());
        }
    }
    qDebug()<<query.lastError()<<endl;
}
void MainWindow::on_f3b_clicked()//确认修改用户信息的确认按钮，第二次确认为对话框
{
    ui2->f3in2->setEnabled(false);
    ui2->f3in3->setEnabled(false);

    ///用户输入的信息的合法性检查
    QString name=ui2->f3in2->text();
    if(name.isEmpty()||name.isNull())
    {
        QMessageBox::warning(0, qApp->tr("修改信息"),qApp->tr("姓名不能为空！"), QMessageBox::Default);
        return ;
    }
    QString pas=ui2->f3in3->text();

    QString sql=QString::fromLocal8Bit("update Admin set 姓名 = '");
    sql=sql+name+tr("' , 登陆密码 = '")+pas+tr("' where 管理员号 = '");
    sql=sql+namenum+tr("'");//拼接更新操作的sql语句

    QSqlQuery query;

    int ok=QMessageBox::warning(this,tr("修改信息"),tr("你确定执行此操作吗？"),QMessageBox::No,QMessageBox::Yes);
    if(ok == QMessageBox::Yes)
    {
        if(query.exec(sql))//执行此语句，修改数据库
        {
            QMessageBox::information(0, qApp->tr("修改信息"),qApp->tr("修改成功"), QMessageBox::Default);
        }
    }
}


///////////////////返回开始界面层次
void MainWindow::returns()//返回开始界面的槽函数
{
    message();//进行是否有用户请求，进行提示
    hide2(false);//设置层次的控件分层隐藏函数
    hide3(false);
    hide5(false);
    hide6(false);
    hide7(false);
    ui2->stext->setVisible(true);
}
