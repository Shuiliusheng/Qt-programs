#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QMessageBox>
#include <QTextCodec>
#include<QDebug>
#include<ui_login1.h>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),ui2(new Ui::login1),timer1(new QTimer(this))
{
    ui->setupUi(this);
    days=0;
    flag=false;
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
    hide(false);

    connectdb();//连接数据库
    initdata();//c
    QTimer *timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(update_database()));
    timer->start(600000);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete ui2;
}


void MainWindow::update_borrow()//更新借阅时的超出天数
{
    days=0;
    QSqlQuery query;
    QString sql=QString::fromLocal8Bit("select 借出日期,图书编号,可借天数 from borrow where 学号 = '");
    sql=sql+namenum+tr("' and 借书请求 = 'False'");//结束请求为False代表已经借到书籍
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
                days+=day1;
                sql=QString::fromLocal8Bit("update borrow set 超出天数 = '");
                sql=sql+QString::number(day1)+tr("' where 学号 = '");
                sql=sql+namenum+tr("' and 图书编号 = '")+temp1+tr("'");//拼接查询语句
                qDebug()<<sql<<endl;
                if(!query.exec(sql))
                    qDebug()<<query.lastError()<<endl;
            }
        }
    }
}


void MainWindow::update_database()//后台运行的更新数据库，跟定时器相关联
{
    if(flag)
    {
        update_borrow();
    }
}

void MainWindow::connectdb()//连接数据库
{
    db = QSqlDatabase::addDatabase("QSQLITE");
//    db = QSqlDatabase::addDatabase("QODBC");//选择数据库引擎
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


}

///////////////登陆界面//////////////////////////
///////////////////////////层次转换函数
void MainWindow::hide1(bool flag)//hide 系列，用于隐藏控件，使得界面可以分层，而不用使用太多界面
{
    ui->luse->setVisible(flag);
    ui->welcome->setVisible(flag);
    ui->lpass->setVisible(flag);
    ui->password->setVisible(flag);
    ui->password->setText(tr(""));
    ui->usename->setVisible(flag);
    ui->usename->setText(tr(""));
    ui->getin->setVisible(flag);
    ui->login->setVisible(flag);
    ui->search->setVisible(flag);
}
void MainWindow::hide(bool flag)//hide 系列，用于隐藏控件，使得界面可以分层，而不用使用太多界面
{
    ui->luse1->setVisible(flag);
    ui->usename1->setVisible(flag);
    ui->usename1->setText(tr("2013302544"));
    ui->lname1->setVisible(flag);
    ui->name->setVisible(flag);
    ui->name->setText(tr(""));
    ui->lstart->setVisible(flag);
    ui->starttime->setVisible(flag);
    ui->starttime->setText(tr("201309"));
    ui->lover->setVisible(flag);
    ui->overtime->setVisible(flag);
    ui->overtime->setText(tr("201709"));
    ui->lcollege->setVisible(flag);
    ui->college->setVisible(flag);
    ui->lgrade->setVisible(flag);
    ui->grade->setVisible(flag);
    ui->submit->setVisible(flag);
    ui->password1->setVisible(flag);
    ui->password1->setText(tr(""));
    ui->lpass1->setVisible(flag);
    ui->back->setVisible(flag);
}

///////////////////////////登陆层次
bool MainWindow::login1()//登陆用户函数
{
    QSqlQuery query;
    QString sql,sql1=ui->usename->text();
    sql=QString::fromLocal8Bit("select 登陆密码,已借本数 from student where 学号=")+sql1;
    query.exec(sql);

    query.next();
    QString pass1=query.value(0).toString();//根据学号获取相应的密码和已借的本数
    int temp1=query.value(1).toInt();//使用本数-1来表示此用户注册但未被管理员确认

    QString pass=ui->password->text();
    if(QString::compare(pass1,pass)!=0)//密码不同
    {
        QMessageBox::warning(0, qApp->tr("登陆"),qApp->tr("密码错误！请检查！"), QMessageBox::Default);
        return false;
    }
    else
    {
        if(temp1==-1)//未被确认的用户
        {
            QMessageBox::warning(0, qApp->tr("登陆"),qApp->tr("尚未通过申请确认！"), QMessageBox::Default);
            return false;
        }
        else
            return true;
    }
}
void MainWindow::on_login_clicked()//进入注册用户的界面
{
    hide1(false);
    hide(true);
    setMaximumSize(378,423);
    setMinimumSize(378,423);
}
void MainWindow::on_getin_clicked()//登陆界面的登陆按钮的功能
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
            this->namenum=usename;//存储学号，用于下一界面的使用

            update_borrow();

            initpaint();//初始化绘制下一界面

            setAutoFillBackground(true);//设置下一界面的背景
            QPalette p;
            QPixmap p1("./xingkong5.jpg");
            p.setBrush(QPalette::Window,QBrush(p1));
            setPalette(p);

            setMaximumSize(652,486);//设置固定大小
            setMinimumSize(652,486);
            cal_num_lend();
            message();//进行是否有超出日期的书籍，进行提示

            connect(timer1,SIGNAL(timeout()),this,SLOT(message()));
            timer1->start(6000);

            hide2(false);//设置层次的控件分层隐藏函数
            hide3(false);
            hide4(false);

            showmoney();//显示欠款金额
            ui2->date->setText(QDate::currentDate().toString("yyyy-MM-dd"));//显示当前日期

        }
        else
            hide1(true);//无法登陆，返回登陆界面的登陆层次
    }
}
void MainWindow::on_search_clicked()//查询按钮的功能
{
    s.init();//另一界面的初始化
    s.show();//另一界面的唤起
}

///////////////////////////注册层次
int MainWindow::detect1()//注册时，用户输入信息的合法性
{
    QString usename=ui->usename1->text();
    if(usename.isEmpty()||usename.isNull())
        return 0;
    QString name=ui->name->text();
    if(name.isEmpty()||name.isNull())
        return 1;
    QString start=ui->starttime->text();
    if(start.length()!=6)
        return 2;
    QString end=ui->overtime->text();
    if(end.length()!=6)
        return 2;
    QString pass1=ui->password1->text();
    if(pass1.isEmpty()||pass1.isNull())
        return 3;
    if(pass1.length()>=29)
        return 6;

    QSqlQuery query;
    QString sql;
    sql=QString::fromLocal8Bit("select 登陆密码 from student where 学号=")+usename;
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
    QString sql,s1,s2,s3;
    sql=QString::fromLocal8Bit("insert into student(学号,姓名,学院,级别,入学年份,结束时间,已借本数,欠款金额,登陆密码,缴费请求) values(");
    s1=ui->usename1->text();
    s2=ui->name->text();
    s3=ui->college->currentText();
    sql=sql+s1+tr(",'")+s2+tr("','")+s3+tr("','");
    s1=ui->grade->currentText();
    s2=ui->starttime->text();
    s3=ui->overtime->text();
    sql=sql+s1+tr("',")+s2+tr(",")+s3+tr(",")+tr("'-1','-1',");
    s1=ui->password1->text();
    sql=sql+s1+tr(",'False')");//等号左边的不用引号，右边需要引号

    bool flag=query.exec(sql);
    return flag;
}
void MainWindow::on_submit_clicked()//注册页面的确认按钮的功能实现
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
        case 0:QMessageBox::warning(0, qApp->tr("注册"),qApp->tr("学号不能为空！"), QMessageBox::Default);
               break;
        case 1:QMessageBox::warning(0, qApp->tr("注册"),qApp->tr("姓名不能为空！"), QMessageBox::Default);
               break;
        case 2:QMessageBox::warning(0, qApp->tr("注册"),qApp->tr("年份格式错误！"), QMessageBox::Default);
               break;
        case 3:QMessageBox::warning(0, qApp->tr("注册"),qApp->tr("密码不能为空！"), QMessageBox::Default);
               break;
        case 6:QMessageBox::warning(0, qApp->tr("注册"),qApp->tr("密码过长！"), QMessageBox::Default);
               break;
        default:QMessageBox::warning(0, qApp->tr("注册"),qApp->tr("此学号已被注册！"), QMessageBox::Default);
        }
    }
}
void MainWindow::on_back_clicked()//从注册界面退回登陆界面
{
    hide(false);
    hide1(true);
    setMaximumSize(392,363);
    setMinimumSize(392,363);
}

///////////////////////////用户使用界面////////////////////////
///////////////////////////层次转换函数
void MainWindow::hide2(bool flag)//层次显示使用的隐藏和显示函数，用于统一操作
{
    ui2->f1l1->setVisible(flag);
    ui2->f1l2->setVisible(flag);
    ui2->f1name->setVisible(flag);
    ui2->f1name->setText(tr("00000000"));
    ui2->f1search->setVisible(flag);
    ui2->f1sure->setVisible(flag);
    ui2->f1sure1->setVisible(flag);
    ui2->f1delete->setVisible(flag);
}
void MainWindow::hide3(bool flag)//层次显示使用的隐藏和显示函数，用于统一操作
{
    gethistory();//获取现有借阅书籍的信息
    showmoney();//显示欠款金额
    ui2->f2back->setVisible(flag);
    ui2->f2l1->setVisible(flag);
    ui2->f2pay->setVisible(flag);
    ui2->f2xujie->setVisible(flag);
    ui2->f2info->setVisible(flag);
    ui2->f2info->clearSpans();
}
void MainWindow::hide4(bool flag)//层次显示使用的隐藏和显示函数，用于统一操作
{
//    showmoney();
    ui2->f3co->setVisible(flag);
    ui2->f3college->setVisible(flag);
    ui2->f3gra->setVisible(flag);
    ui2->f3l1->setVisible(flag);
    ui2->f3l2->setVisible(flag);
    ui2->f3l3->setVisible(flag);
    ui2->f3l4->setVisible(flag);
    ui2->f3l5->setVisible(flag);
    ui2->f3l6->setVisible(flag);
    ui2->f3l7->setVisible(flag);
    ui2->f3name->setVisible(flag);
    ui2->f3use->setVisible(flag);
    ui2->f3starttime->setVisible(flag);
    ui2->f3password->setVisible(flag);
    ui2->f3overtime->setVisible(flag);
    ui2->f3change->setVisible(flag);
    ui2->f3delete->setVisible(flag);
    ui2->f3sure->setVisible(flag);
}

////////////////////////////借阅层次
void MainWindow::initpaint()//第二界面的初始化绘制
{
    ui2->setupUi(this);//唤起第二界面

    QMenu *first1;///添加功能目录和目录内的内容选项
    first1=menuBar()->addMenu(tr("使用功能"));

    QAction *borrow=new QAction(QIcon("./tubiao1.jpg"),tr("借阅功能"),this);
    borrow->setStatusTip(tr("借阅书籍"));
    borrow->setWhatsThis(tr("借阅书籍"));
    connect(borrow,SIGNAL(triggered()),this,SLOT(fborrow()));//和fborrow槽函数连接在一起

    QAction *history=new QAction(QIcon("./tubiao2.jpg"),tr("借阅历史"),this);
    history->setStatusTip(tr("借阅历史信息"));
    history->setWhatsThis(tr("借阅历史信息"));
    connect(history,SIGNAL(triggered()),this,SLOT(fsearch()));
    QAction *change_data=new QAction(QIcon("./tubiao3.jpg"),tr("修改信息"),this);
    change_data->setStatusTip(tr("修改用户信息"));
    change_data->setWhatsThis(tr("修改用户信息"));
    connect(change_data,SIGNAL(triggered()),this,SLOT(fchange()));

    QAction *start=new QAction(QIcon("./tubiao3.jpg"),tr("开始界面"),this);
    start->setStatusTip(tr("开始界面"));
    start->setWhatsThis(tr("开始界面"));
    connect(start,SIGNAL(triggered()),this,SLOT(exit1()));

    QAction *exit=new QAction(QIcon("./tubiao3.jpg"),tr("注销退出"),this);
    exit->setStatusTip(tr("用户注销退出"));
    exit->setWhatsThis(tr("用户注销退出"));
    connect(exit,SIGNAL(triggered()),this,SLOT(close()));

    first1->addAction(start);
    first1->addAction(borrow);
    first1->addAction(history);
    first1->addAction(change_data);
    first1->addAction(exit);
}
void MainWindow::showmoney()//显示欠款金额
{
    QSqlQuery query;

    QString sql=QString::fromLocal8Bit("select 欠款金额 from student where 学号 = '");
    sql=sql+namenum+tr("'");//拼接形成查询语句

    if(query.exec(sql))//执行，根据学号获取欠款金额
    {
        if(query.next())
        {
            QString m=query.value(0).toString();
            float m1=m.toFloat();
            moneyz=m1;
            if(m1>5)//超过5元，系统会提醒
                QMessageBox::warning(0, qApp->tr("欠款提醒"),(tr("欠款达到了")+m+tr("元!!!")), QMessageBox::Default);
            ui2->fmoney->setText(tr("欠款: ")+m+tr(" 元"));
        }
    }
    else
        qDebug()<<query.lastError()<<endl;//输出错误信息
}
void MainWindow::message()//第二界面的开始桌面显示书本过期提示信息
{
    QSqlTableModel *model=new QSqlTableModel;//设置Qt内数据库查询的模型，用户tableview中的配套结果显示
    model->setTable("borrow");//设置查询的表
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);//设置属性，只有提交操作才会修改数据库
    ui2->f2info->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置显示结果之后的结果不能被修改

    QString sql=QString::fromLocal8Bit("学号 = '");//拼接形成查询语句
    sql=sql+namenum+tr("'");

    model->setFilter(sql);//设置where的查询语句
    model->select();//查询结果
    this->model=model;//将其赋给私有变量，减少方法的参数传递

    int num=model->rowCount(),n=0;//结果的元组个数num

    QDate date=QDate::currentDate();//和当前日期，逐条比较，确定是否超出可借天数，
    QString stext=QString::fromLocal8Bit("注意！！！\n书籍:");//对于超出的显示出来
    for(int i=0;i<num;i++)
    {
        QString temp=model->data(model->index(i,1)).toString();
        QString t1=model->data(model->index(i,2)).toString();

        bool state=model->data(model->index(i,6)).toBool();
        int day=model->data(model->index(i,3)).toInt();

        QDate date1=QDate::fromString(t1,"yyyyMMdd");;
        int day1=day-date.toJulianDay()+date1.toJulianDay();

        if(day1<=0&&!state)//state为借阅状态，为True代表未借阅成功
        {
            n++;//设置查询的条数
            stext=stext+temp+tr(" 过期 ")+QString::number(day1*-1)+tr("天!\n");//拼接形成显示字串
        }
    }
    cal_num_lend();
    if(n==0)//根据是否有，显示不同的输出
        ui2->stext->setText(tr(" ^-^ Welcome to Use *-* ")+tr("\n\n   您还可以借阅")+QString::number(numbook)+tr("本书籍。"));
    else
        ui2->stext->setText(tr("您还可以借阅")+QString::number(numbook)+tr("本书籍。\n")+stext);
}
void MainWindow::cal_num_lend()//计算此用户目前可以借阅的书本个数
{
    numbook=0;
    QSqlQuery query;
    QString  sql=QString::fromLocal8Bit("select 级别,已借本数 from student where 学号 = '");
    sql=sql+namenum+tr("'");
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
            numbook=num2-num;
        }
    }
}

////////////////////////////借阅层次
bool MainWindow::detect_borrow()//进行借阅书籍时的输入合法性检测和能够借阅的判断
{
    QString name=ui2->f1name->text();
    if(name.isEmpty()||name.isNull())//书籍标号是否合格
    {
        QMessageBox::warning(0, qApp->tr("借阅书籍"),qApp->tr("书籍编号不能为空！"), QMessageBox::Default);
        return false;
    }
    if(name.length()!=8)
    {
        QMessageBox::warning(0, qApp->tr("借阅书籍"),qApp->tr("书籍编号错误！"), QMessageBox::Default);
        return false;
    }

    QSqlQuery query;
    QString sql=QString::fromLocal8Bit("select 图书名称 借阅状态 from book where 图书编号='");
    sql=sql+name+tr("'");//拼接为查询语句


    if(query.exec(sql))//执行查询语句，根据图书编号，确定书名和状态
    {
        query.next();
        QString temp=query.value(0).toString();
        bool tflag=query.value(1).toBool();

        if(temp.isNull()||temp.isEmpty())//结果为空，没有这个编号
        {
            QMessageBox::warning(0, qApp->tr("借阅书籍"),qApp->tr("不存在！请检查！"), QMessageBox::Default);
            return false;
        }
        name=name+tr(" : ")+temp;

        if(tflag==true)//应经被借阅的表识
        {
            QMessageBox::warning(0, qApp->tr("借阅书籍"),qApp->tr("此书已经被借阅！"), QMessageBox::Default);
            return false;
        }
        else//输出此学号的书籍姓名
            QMessageBox::question(0, qApp->tr("借阅书籍"),name, QMessageBox::Ok);
    }
    return true;
}
bool MainWindow::detect_borrow1()//进一步的能够借阅的合法性判断，在detect_borrow之后
{
    if(moneyz>=5)///欠款太多，不能借阅其他书籍
    {
        QMessageBox::warning(0, qApp->tr("欠款提醒"),qApp->tr("请先还清欠款！"), QMessageBox::Default);
        return false;
    }

    QString s1=ui2->f1name->text();
    QString sql=QString::fromLocal8Bit("select 借出日期 from borrow where 学号 = '");
    sql=sql+namenum+tr("' and 图书编号 ='")+s1+tr("'");//拼接语句

    QSqlQuery query;
    if(query.exec(sql))//通过学号和图书编号，判断是否有无借阅状态
    {                  //和上次中书籍表中的标志不冲突，原因是为成功借阅是，此标志不改变
        if(!query.next())
            return true;
        QString temp=query.value(0).toString();
        if(temp.isEmpty()||temp.isNull())//如果返回值为空，则没有此记录或者已经归还，代表未被借阅
            return true;
        QMessageBox::warning(0, qApp->tr("借阅书籍"),qApp->tr("此书已被您借阅"), QMessageBox::Default);

    }
    if(numbook==0)//借阅书籍的数目达到了级别的限制
    {
        QMessageBox::warning(0, qApp->tr("借阅书籍"),qApp->tr("您借书数目达到了级别限制！"), QMessageBox::Default);
        return false;
    }
    else
        return true;
    return false;
}
void MainWindow::fborrow()//目录中的借阅操作对应的槽函数
{
    ui2->stext->setVisible(false);//设置该层次的显示控件为可见的
    ui2->centralwidget->repaint();
    setMaximumSize(316,361);//此层次的界面大小
    setMinimumSize(316,361);
    //initpaint();
    hide2(true);
    hide3(false);
    hide4(false);
    ui2->f1sure1->setVisible(false);
    ui2->f1delete->setVisible(false);
}
void MainWindow::on_f1search_clicked()//查询按钮的功能
{
    s.init();//另一界面的初始化
    s.show();//另一界面的唤起
}
void MainWindow::on_f1sure_clicked()//借阅确认按钮的功能
{
    if(detect_borrow())//首先进行输入信息的合法行检测和能否借阅的判断
    {
        ui2->f1delete->setVisible(true);//如果正确，进入下一次最后确认借阅的界面
        ui2->f1sure1->setVisible(true);
        ui2->f1sure->setVisible(false);
    }

}
void MainWindow::on_f1delete_clicked()//取消借阅的按钮的操作
{
    ui2->f1delete->setVisible(false);//退回上一个借阅的层次
    ui2->f1sure1->setVisible(false);
    ui2->f1sure->setVisible(true);
}
void MainWindow::on_f1sure1_clicked()//借阅的第二次确认按钮的功能
{
    if(detect_borrow1())//进一步的借阅合法性检查
    {
        QSqlQuery query;
        QString sql,s1;
        sql=QString::fromLocal8Bit("insert into borrow(学号,图书编号,续借状态,借书请求,续借请求,归还请求) values('");
        s1=ui2->f1name->text();
        sql=sql+namenum+tr("' , '")+s1+tr("','")+tr("False','True','False','False')");
        //拼接形成插入语句
        if(!query.exec(sql))
            qDebug() <<query.lastError()<<endl;
        else
        {
            //成功借阅的提示
            QMessageBox::information(0, qApp->tr("借阅书籍"),qApp->tr("申请已经提交"), QMessageBox::Default);
        }
    }
    on_f1delete_clicked();//向上退回一层次
}


////////////////////////////借阅信息层次
void MainWindow::gethistory()//获取历史借阅信息
{
    model->select();//model的内部内容，已经在判断过期书籍的方法中被填充完毕，执行显示即可
    ui2->f2info->setModel(model);
    ui2->f2info->show();
}
void MainWindow::fsearch()//目录中的查询历史信息的操作对应的槽函数
{
    ui2->stext->setVisible(false);//设置该层次的显示控件为可见的
    setMaximumSize(652,486);//设置次层次的界面大小
    setMinimumSize(652,486);
    hide3(true);
    hide2(false);
    hide4(false);

}
void MainWindow::on_f2xujie_clicked()//续借按钮的操作
{
    QModelIndex index=ui2->f2info->currentIndex();
    QString temp=model->data(model->index(index.row(),1)).toString();//图书编号

    bool state=model->data(model->index(index.row(),5)).toBool();//续借状态
    bool state1=model->data(model->index(index.row(),6)).toBool();//借书请求
    bool state2=model->data(model->index(index.row(),7)).toBool();//续借请求
    bool state3=model->data(model->index(index.row(),8)).toBool();//归还请求

    QString t1=model->data(model->index(index.row(),2)).toString();//借出日期
    int day=model->data(model->index(index.row(),3)).toInt();//可借天数

    QDate date=QDate::currentDate();//现在的日期
    QDate date1=QDate::fromString(t1,"yyyyMMdd");//将20130411的格式转化为QDate类型
    int day1=day-date.toJulianDay()+date1.toJulianDay();//计算可借天数与今日和借出日期的差值的差值
    //为正代表为过期，代表还有天数可用，为负代表过期

    ////续借的合法性的判断
    if(state)//已在续借状态中
    {
        QMessageBox::warning(0, qApp->tr("续借书籍"),qApp->tr("已在续借状态中\n不允许再次续借！"), QMessageBox::Default);
        return ;
    }
    else if(state1)//尚未成功借阅
    {
        QMessageBox::warning(0, qApp->tr("续借书籍"),qApp->tr("尚未成功借阅！"), QMessageBox::Default);
        return ;
    }
    else if(state2)//续借申请已在使用
    {
        QMessageBox::warning(0, qApp->tr("续借书籍"),qApp->tr("续借申请已在使用！"), QMessageBox::Default);
        return ;
    }
    else if(state3)//已提出归还申请
    {
        QMessageBox::warning(0, qApp->tr("续借书籍"),qApp->tr("已提出归还申请！\n不允许续借！"), QMessageBox::Default);
        return ;
    }
    else if(day1>10)//请在距离期限多余10天
    {
        QMessageBox::warning(0, qApp->tr("续借书籍"),qApp->tr("请在距离期限10天内\n续借！"), QMessageBox::Default);
        return ;
    }
    else if(day1<0)//书籍过期
    {
        QMessageBox::warning(0, qApp->tr("续借书籍"),qApp->tr("借书期限过期\n不允许续借！"), QMessageBox::Default);
        return ;
    }
    else//合法之后进行续借
    {
        QString sql=QString::fromLocal8Bit("update borrow set 续借请求 = 'True' where 学号 = '");
        sql=sql+namenum+tr("' and 图书编号 = '")+temp+tr("'");//拼接查询语句

        QSqlQuery query;
        if(query.exec(sql))//执行，将借阅信息表中的该元组的续借标识设置为True
        {
            model->select();
            ui2->f2info->setModel(model);
            ui2->f2info->show();//重新显示借阅的信息
            //提示消息
            QMessageBox::information(0, qApp->tr("续借书籍"),qApp->tr("提交申请成功！"), QMessageBox::Default);
        }
        else
            qDebug()<<query.lastError()<<endl;//显示错误信息
    }
}
void MainWindow::on_f2back_clicked()//归还书籍按钮的操作
{
    QModelIndex index=ui2->f2info->currentIndex();
    QString temp=model->data(model->index(index.row(),1)).toString();//图书编号
    bool state=model->data(model->index(index.row(),6)).toBool();//借书请求
    bool state1=model->data(model->index(index.row(),8)).toBool();//归还请求

    ///能够归还操作的合法性检查
    if(state)//尚未成功借阅
    {
        QMessageBox::warning(0, qApp->tr("归还书籍"),qApp->tr("尚未成功借阅！"), QMessageBox::Default);
        return ;
    }
    else if(state1)//已提出归还申请
    {
        QMessageBox::warning(0, qApp->tr("归还书籍"),qApp->tr("已提出归还申请!"), QMessageBox::Default);
        return ;
    }
    else//合法之后
    {
        QString sql=QString::fromLocal8Bit("update borrow set 归还请求 = 'True' where 学号 = '");
        sql=sql+namenum+tr("' and 图书编号 = '")+temp+tr("'");//拼接得到更新语句

        QSqlQuery query;
        if(query.exec(sql))//执行更新操作,将借阅信息表中的该元组的归还标识设置为True
        {
            model->select();
            ui2->f2info->setModel(model);
            ui2->f2info->show();//重新显示借阅的信息

            QMessageBox::information(0, qApp->tr("归还请求"),qApp->tr("提交申请成功！"), QMessageBox::Default);
        }
        else
            qDebug()<<query.lastError()<<endl;
    }
}
void MainWindow::on_f2pay_clicked()//缴费操作按钮的功能
{
    if(moneyz==0)//没欠款
    {
        QMessageBox::warning(0, qApp->tr("缴费"),qApp->tr("暂无欠款!"), QMessageBox::Default);
    }
    else
    {

        QString sql=QString::fromLocal8Bit("update student set 缴费请求 = 'True' where 学号 = '");
        sql=sql+namenum+tr("'");//拼接更新的sql语句

        QSqlQuery query;
        if(query.exec(sql))//执行更新操作,将学生信息表中的该元组的缴费标识设置为True
        {
            QMessageBox::information(0, qApp->tr("缴费请求"),qApp->tr("提交申请成功！"), QMessageBox::Default);
        }
        else
            qDebug()<<query.lastError()<<endl;
    }
}


////////////////////////////用户修改信息层次
void MainWindow::fchange()//目录中的修改用户信息的操作对应的槽函数
{
    ui2->stext->setVisible(false);//设置该层次的显示控件为可见的
    setMaximumSize(455,510);
    setMinimumSize(455,510);
    hide3(false);
    hide2(false);
    hide4(true);

    show_info();//显示用户的个人的信息
    write(false);//设置未进行修改时的控件属性
}
void MainWindow::write(bool flag)//在修改用户信息时，确定控件的属性
{
    ui2->f3co->setEnabled(flag);//enabled 代表不能被修改
    ui2->f3gra->setEnabled(false);//级别不允许被自己修改
    ui2->f3use->setEnabled(false);//学号不允许随意修改
    ui2->f3name->setEnabled(flag);
    ui2->f3starttime->setEnabled(flag);
    ui2->f3overtime->setEnabled(flag);
    ui2->f3password->setEnabled(flag);

    ui2->f3college->setVisible(flag);
    ui2->f3co->setVisible(!flag);
}
void MainWindow::show_info()//获取用户的各个信息，并且显示
{
    QSqlQuery query;
    QString sql=QString::fromLocal8Bit("select 学号,姓名,学院,级别,入学年份,结束时间,登陆密码 from student where 学号 = '");
    sql=sql+namenum+tr("'");//拼接成查询语句

    if(query.exec(sql))//执行，根据学号获取各个信息
    {
        if(query.next())
        {
            ui2->f3use->setText(namenum);
            ui2->f3name->setText(query.value(1).toString());//显示获取到的信息
            ui2->f3co->setText(query.value(2).toString());
            ui2->f3gra->setText(query.value(3).toString());
            ui2->f3starttime->setText(query.value(4).toString());
            ui2->f3overtime->setText(query.value(5).toString());
            ui2->f3password->setText(query.value(6).toString());
        }
    }
    else
        qDebug()<<query.lastError()<<endl;//输出执行过程中的错误，用于天时
}
void MainWindow::on_f3change_clicked()//信息修改按钮的功能
{
    write(true);//设置相关控件的属性
}
void MainWindow::on_f3delete_clicked()//不修改的回退操作
{
    show_info();//重新显示用户的信息
    write(false);//设置相关空间的属性
}
void MainWindow::on_f3sure_clicked()//修改的确认按钮
{

    ///用户输入的信息的合法性检查
    QString name=ui2->f3name->text();
    if(name.isEmpty()||name.isNull())
    {
        QMessageBox::warning(0, qApp->tr("修改信息"),qApp->tr("姓名不能为空！"), QMessageBox::Default);
        return ;
    }
    QString start=ui2->f3starttime->text();
    QString over=ui2->f3overtime->text();
    if(start.length()!=6||over.length()!=6)
    {
        QMessageBox::warning(0, qApp->tr("修改信息"),qApp->tr("时间请按格式填写!"), QMessageBox::Default);
        return ;
    }
    QString pas=ui2->f3password->text();
    if(pas.length()<=0||pas.length()>29)
    {
        QMessageBox::warning(0, qApp->tr("修改信息"),qApp->tr("请正确填写密码!\n最长不超过29个字符"), QMessageBox::Default);
        return ;
    }
    ///执行到此处合法
//    QString grade=ui2->f3grade->currentText();
    QString collge=ui2->f3college->currentText();

    QString sql=QString::fromLocal8Bit("update student set 姓名 = '");
    sql=sql+name+tr("' , 学院 = '")+collge+tr("' ,")+tr("入学年份 = '");
    sql=sql+start+tr("' , 结束时间 = '")+over+tr("' , 登陆密码 = '")+pas+tr("' where 学号 = '");
    sql=sql+namenum+tr("'");//拼接更新操作的sql语句

    QSqlQuery query;
    if(query.exec(sql))//执行此语句，修改数据库
    {
        show_info();//成功后重新回到用户信息显示的层次
        write(false);//设置控件属性
        QMessageBox::information(0, qApp->tr("修改信息"),qApp->tr("修改成功"), QMessageBox::Default);
    }
    else
        qDebug()<<query.lastError()<<endl;
}

//////////////////////////////////////////////////
void MainWindow::exit1()//返回开始界面
{
    message();//进行是否有超出日期的书籍，进行提示

    hide2(false);//设置层次的控件分层隐藏函数
    hide3(false);
    hide4(false);
    setMaximumSize(652,486);//设置固定大小
    setMinimumSize(652,486);
    ui2->stext->setVisible(true);
    showmoney();//显示欠款金额
}
