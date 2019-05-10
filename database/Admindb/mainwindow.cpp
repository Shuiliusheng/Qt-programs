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
    setAutoFillBackground(true);//���ñ���
    QPalette p;
    QPixmap p1("./xingkong.jpg");
    p.setBrush(QPalette::Window,QBrush(p1));
    setPalette(p);

    QTextCodec::setCodecForTr(QTextCodec::codecForName("GB2312"));//����������ʾ
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("GB2312"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("GB2312"));

    setMaximumSize(392,363);//���ý���Ĺ̶���С
    setMinimumSize(392,363);
    hide(true);
    hide1(false);
    connectdb();//�������ݿ�

    initdata();//���ڳ�ʼ�����ݿ�����
    QTimer *timer=new QTimer(this);

    connect(timer,SIGNAL(timeout()),this,SLOT(update_database()));
    timer->start(60000);//һ����ִ��һ�θ������ݿ����
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::connectdb()//�������ݿ�
{
    db = QSqlDatabase::addDatabase("QSQLITE");
 //   db = QSqlDatabase::addDatabase("QODBC");//ѡ�����ݿ�����
    db.setDatabaseName("library");
    db.setUserName(tr("sa"));
    db.setPassword("12345");

    if (!db.open())//�����ݿ�
    {
       QMessageBox::critical(0, qApp->tr("Cannot open database"),qApp->tr("Unable to establish a database connection."), QMessageBox::Cancel);
       close();//�ر�Ӧ��
       return ;
    }
}
void MainWindow::initdata()//ʹ�ó����ʼ�����������������
{
//    QSqlQuery query;QString sql;
//    sql=QString::fromLocal8Bit("select * Admin");
//    query.exec(sql);
//    namenum=QString::fromLocal8Bit("2013302544");
}
void MainWindow::update_borrow()//���½���ʱ�ĳ�������
{
    QSqlQuery query;
    QString sql=QString::fromLocal8Bit("select ѧ�� from student where �ѽ豾�� != '-1'");
    query.exec(sql);
    qDebug()<<query.lastError()<<endl;
    while(query.next())
    {
        QString name=query.value(0).toString();
        QString sql=QString::fromLocal8Bit("select �������,ͼ����,�ɽ����� from borrow where ѧ�� = '");
        sql=sql+name+tr("' and �������� = 'False'");//��������ΪFalse�����Ѿ��赽�鼮
        if(query.exec(sql))
        {
            while(query.next())
            {
                QString temp=query.value(0).toString();
                int day=query.value(2).toInt();
                QDate date=QDate::currentDate();//���ڵ�����
                QDate date1=QDate::fromString(temp,"yyyyMMdd");//��20130411�ĸ�ʽת��ΪQDate����
                int day1=day-date.toJulianDay()+date1.toJulianDay();
                if(day1<0)
                {
                    QString temp1=query.value(1).toString();
                    day1*=-1;
                    sql=QString::fromLocal8Bit("update borrow set �������� = '");
                    sql=sql+QString::number(day1)+tr("' where ѧ�� = '");
                    sql=sql+name+tr("' and ͼ���� = '")+temp1+tr("'");//ƴ�Ӳ�ѯ���
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

///////////////��½����//////////////////////////
//���ת������
void MainWindow::hide1(bool flag)//hide ϵ�У��������ؿؼ���ʹ�ý�����Էֲ㣬������ʹ��̫�����
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
void MainWindow::hide(bool flag)//hide ϵ�У��������ؿؼ���ʹ�ý�����Էֲ㣬������ʹ��̫�����
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

//��½���
bool MainWindow::login1()//��½�û�����
{
    QSqlQuery query;
    QString sql,sql1=ui->usename->text();
    sql=QString::fromLocal8Bit("select ��½����,����״̬ from Admin where ����Ա�� = '")+sql1+tr("'");
    query.exec(sql);

    query.next();
    QString pass1=query.value(0).toString();//����ѧ�Ż�ȡ��Ӧ��������ѽ�ı���
    bool tflag=query.value(1).toBool();//ʹ������״̬����ʾ���û�ע�ᵫδ���߼�����Աȷ��

    QString pass=ui->password->text();
    if(QString::compare(pass1,pass)!=0)//���벻ͬ
    {
        QMessageBox::warning(0, qApp->tr("��½"),qApp->tr("����������飡"), QMessageBox::Default);
        return false;
    }
    else
    {
        if(!tflag)//δ��ȷ�ϵ��û�
        {
            QMessageBox::warning(0, qApp->tr("��½"),qApp->tr("��δͨ������ȷ�ϣ�"), QMessageBox::Default);
            return false;
        }
        else
            return true;
    }
}
void MainWindow::on_login_clicked()//��½��ť����
{
    QString usename=ui->usename->text();//��ȡ�û���������
    QString name=ui->password->text();

    if(usename.isEmpty()||usename.isNull()||name.isEmpty()||name.isNull())//�Ϸ��Լ��
    {
        QMessageBox::warning(0, qApp->tr("�ύ"),qApp->tr("����������飡"), QMessageBox::Default);
    }
    else
    {
        if(login1())//��½
        {
            this->flag=true;
            this->namenum=usename;//�洢����Ա�ţ�������һ�����ʹ��

            update_borrow();

            initpaint();//��ʼ��������һ����

            setAutoFillBackground(true);//������һ����ı���
            QPalette p;
            QPixmap p1("./xingkong5.jpg");
            p.setBrush(QPalette::Window,QBrush(p1));
            setPalette(p);

            setMaximumSize(652,486);//���ù̶���С
            setMinimumSize(652,486);

            connect(timer1,SIGNAL(timeout()),this,SLOT(message()));
            timer1->start(5000);//���ö�ʱ����5���Ӽ��һ���û�����

            message();//�����Ƿ����û����󣬽�����ʾ
            hide2(false);//���ò�εĿؼ��ֲ����غ���
            hide3(false);
            hide5(false);
            hide6(false);
            hide7(false);
            ui2->date->setText(QDate::currentDate().toString("yyyy-MM-dd"));//��ʾ��ǰ����

        }
        else
            hide(true);//�޷���½�����ص�½����ĵ�½���
    }
}
void MainWindow::on_reg_clicked()//����ע������ڰ�ť
{
    hide(false);
    hide1(true);
    setMaximumSize(392,363);
    setMinimumSize(392,363);
}
void MainWindow::on_search_clicked()//��ѯ�鼮��ť
{
    s.init();//��һ����ĳ�ʼ��
    s.show();//��һ����Ļ���
}

//ע����
int MainWindow::detect1()//ע��ʱ���û�������Ϣ�ĺϷ���
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
    sql=QString::fromLocal8Bit("select ��½���� from Admin where ����Ա��=")+usename;
    query.exec(sql);
    query.next();
    QString temp=query.value(0).toString();//ͨ����ѯ���ж��Ƿ��Ѿ���ע���
    if(temp.isNull()||temp.isEmpty())//û�е�¼���룬��Ϊδע����û�
        return 5;
    else
        return 4;//����ֵ����ȷ����ʾ��Ϣ������
}
bool MainWindow::reg()//ע�ᵽ���ݿ��student����
{
    QSqlQuery query;

    /////���û���������Ϣ�����һ���γ�һ��sql�������
    QString sql,s1,s2;
    sql=QString::fromLocal8Bit("insert into Admin(����Ա��,����,��½����,����״̬) values('");
    s1=ui->usename1->text();
    s2=ui->name->text();
    sql=sql+s1+tr("','")+s2+tr("','");
    s1=ui->password1->text();
    sql=sql+s1+tr("','False')");//�Ⱥ���ߵĲ������ţ��ұ���Ҫ����
    bool flag=query.exec(sql);
//    qDebug() <<query.lastError()<<endl;//������������������
    return flag;
}
void MainWindow::on_submit_clicked()//ע�����ʱ��ע��ȷ�ϰ�ť����
{
    int flag=detect1();//�û���Ϣ���Ϸ���
    if(flag==5)//�û�������ȷ
    {
        if(reg())//ע��
            QMessageBox::information(0, qApp->tr("ע��"),qApp->tr("�����ύ�ɹ�"), QMessageBox::Ok);
        else
            QMessageBox::warning(0, qApp->tr("ע��"),qApp->tr("������ע�ᣡ"), QMessageBox::Default);
        ///ת������
        hide(false);
        hide1(true);
        setMaximumSize(392,363);
        setMinimumSize(392,363);
    }
    else
    {
        switch(flag){//���ݷ��ص����ݣ���ʾ����ͬ�Ĵ�����Ϣ
        case 0:QMessageBox::warning(0, qApp->tr("ע��"),qApp->tr("����Ա�Ų���Ϊ�գ�"), QMessageBox::Default);
               break;
        case 1:QMessageBox::warning(0, qApp->tr("ע��"),qApp->tr("��������Ϊ�գ�"), QMessageBox::Default);
               break;
        case 3:QMessageBox::warning(0, qApp->tr("ע��"),qApp->tr("���벻��Ϊ�գ�"), QMessageBox::Default);
               break;
        case 6:QMessageBox::warning(0, qApp->tr("ע��"),qApp->tr("���������"), QMessageBox::Default);
               break;
        default:QMessageBox::warning(0, qApp->tr("ע��"),qApp->tr("�˹���Ա���ѱ�ע�ᣡ"), QMessageBox::Default);
        }
    }
}
void MainWindow::on_back_clicked()//���˵���ʼ��½���水ť
{
    hide1(false);
    hide(true);
    setMaximumSize(392,363);
    setMinimumSize(392,363);
}



////////////////�û�ʹ�ý���////////////////////////
//���ת������
void MainWindow::hide2(bool flag)//����ÿһ����εĿؼ���������
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

///��ʼ������ʾ���
void MainWindow::initpaint()//�ڶ�����ĳ�ʼ�����ƣ���������Ŀ¼����
{
    ui2->setupUi(this);//����ڶ�����

    QMenu *first1,*second,*third;///��ӹ���Ŀ¼��Ŀ¼�ڵ�����ѡ��
    first1=menuBar()->addMenu(tr("ʹ�ù���"));

    QAction *start=new QAction(QIcon("./tubiao3.jpg"),tr("��ʼ����"),this);
    start->setStatusTip(tr("��ʼ����"));
    start->setWhatsThis(tr("��ʼ����"));
    connect(start,SIGNAL(triggered()),this,SLOT(returns()));

    first1->addAction(start);

    second=first1->addMenu(QIcon("./tubiao2.jpg"),tr("�û���Ϣ����"));

    third=first1->addMenu(QIcon("./tubiao1.jpg"),tr("ͼ����Ϣ����"));

    QAction *addbook=new QAction(QIcon("./tubiao1.jpg"),tr("���ͼ����Ϣ"),this);
    addbook->setStatusTip(tr("���ͼ����Ϣ"));
    addbook->setWhatsThis(tr("���ͼ����Ϣ"));
    connect(addbook,SIGNAL(triggered()),this,SLOT(change_book()));//��change_book()�ۺ���������һ��

    QAction *deletebook=new QAction(QIcon("./tubiao1.jpg"),tr("ɾ��ͼ����Ϣ"),this);
    deletebook->setStatusTip(tr("ɾ����Ϣ����"));
    deletebook->setWhatsThis(tr("ɾ����Ϣ����"));
    connect(deletebook,SIGNAL(triggered()),this,SLOT(delete_book()));//��change_book()�ۺ���������һ��

    QAction *searchbook=new QAction(QIcon("./tubiao1.jpg"),tr("��ѯͼ����Ϣ"),this);
    searchbook->setStatusTip(tr("��ѯͼ����Ϣ"));
    searchbook->setWhatsThis(tr("��ѯͼ����Ϣ"));
    connect(searchbook,SIGNAL(triggered()),this,SLOT(on_search_clicked()));//��change_book()�ۺ���������һ��

    third->addAction(addbook);
    third->addAction(deletebook);
    third->addAction(searchbook);

    QAction *change_data=new QAction(QIcon("./tubiao3.jpg"),tr("�޸���Ϣ"),this);
    change_data->setStatusTip(tr("�޸��û���Ϣ"));
    change_data->setWhatsThis(tr("�޸��û���Ϣ"));
    connect(change_data,SIGNAL(triggered()),this,SLOT(change_useinfo()));


    QAction *exit=new QAction(QIcon("./tubiao3.jpg"),tr("ע���˳�"),this);
    exit->setStatusTip(tr("�û�ע���˳�"));
    exit->setWhatsThis(tr("�û�ע���˳�"));
    connect(exit,SIGNAL(triggered()),this,SLOT(close()));

    first1->addAction(change_data);
    first1->addAction(exit);


    QAction *make_sure=new QAction(QIcon("./tubiao1.jpg"),tr("�����û�����"),this);
    make_sure->setStatusTip(tr("�����û�����"));
    make_sure->setWhatsThis(tr("�����û�����"));
    connect(make_sure,SIGNAL(triggered()),this,SLOT(dispose_apply()));

    QAction *lookinfo=new QAction(QIcon("./tubiao4.jpg"),tr("�鿴�û���Ϣ"),this);
    lookinfo->setStatusTip(tr("�鿴�û���Ϣ"));
    lookinfo->setWhatsThis(tr("�鿴�û���Ϣ"));
    connect(lookinfo,SIGNAL(triggered()),this,SLOT(show_student()));

    QAction *lookinfo1=new QAction(QIcon("./tubiao4.jpg"),tr("�鿴����Ա��Ϣ"),this);
    lookinfo1->setStatusTip(tr("�鿴����Ա��Ϣ"));
    lookinfo1->setWhatsThis(tr("�鿴����Ա��Ϣ"));
    connect(lookinfo1,SIGNAL(triggered()),this,SLOT(show_student1()));


    second->addAction(make_sure);
    second->addAction(lookinfo);
    if(QString::compare(namenum,tr("2013302544"))==0)//�����û����
    {
        second->addAction(lookinfo1);
    }



}
void MainWindow::message()//����Ƿ����û����󣬽�����ʾ
{
    QSqlTableModel *model=new QSqlTableModel;//����Qt�����ݿ��ѯ��ģ�ͣ��û�tableview�е����׽����ʾ
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);//�������ԣ�ֻ���ύ�����Ż��޸����ݿ�
    ui2->result->setEditTriggers(QAbstractItemView::NoEditTriggers);//������ʾ���֮��Ľ�����ܱ��޸�

    QString sql=QString::fromLocal8Bit("�������� = 'True'");//ƴ���γɲ�ѯ���
    QString sql1=QString::fromLocal8Bit("�������� = 'True'");
    QString sql2=QString::fromLocal8Bit("�黹���� = 'True'");
    QString sql3=QString::fromLocal8Bit("�ѽ豾�� = -1 ");
    QString sql4=QString::fromLocal8Bit("�ɷ����� = 'True'");
    QString showt=tr(" ^-^ Welcome to Use *-*\n" );
    int num=0;

    model->setTable("borrow");//���ò�ѯ�ı�
    model->setFilter(sql);//����where�Ĳ�ѯ���
    model->select();//��ѯ���
    num=model->rowCount();//�����Ԫ�����num
    showt=showt+tr("���У���������")+QString::number(num)+tr("��\n");

    model->setFilter(sql1);
    model->select();
    num=model->rowCount();
    showt=showt+tr("     ��������")+QString::number(num)+tr("��\n");

    model->setFilter(sql2);
    model->select();
    num=model->rowCount();
    showt=showt+tr("     �黹����")+QString::number(num)+tr("��\n");

    model->setTable("student");//���ò�ѯ�ı�
    model->setFilter(sql4);
    model->select();
    num=model->rowCount();
    showt=showt+tr("     �ɷ�����")+QString::number(num)+tr("��\n");

    model->setFilter(sql3);
    model->select();
    num=model->rowCount();
    showt=showt+tr("     ע������")+QString::number(num)+tr("��");
    ui2->stext->setText(showt);

    this->model=model;//���丳��˽�б��������ٷ����Ĳ�������
}

//////////////�û���Ϣ����Ŀ¼
//�����û�����������
void MainWindow::dispose_apply()//�����������Ĳۺ���
{
    timer1->stop();
    ui2->stext->setVisible(false);
    hide2(true);//���ò�εĿؼ��ֲ����غ���
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
int MainWindow::cal_num_lend(QString name)//�����û���ѧ�ź���Ӧ�ļ��������˿ɽ�ı���
{
    QSqlQuery query;
    QString  sql=QString::fromLocal8Bit("select ����,�ѽ豾�� from student where ѧ�� = '");
    sql=sql+name+tr("'");
    if(query.exec(sql))
    {
        if(query.next())
        {
            QString level=query.value(0).toString();
            int num=query.value(1).toInt();
            int num2=0;
            if(QString::compare(level,tr("������"))==0)
                num2=10;
            else if(QString::compare(level,tr("�о���"))==0)
                num2=15;
            else if(QString::compare(level,tr("��ʿ"))==0)
                num2=20;
            else
                num2=25;
            int numbook=num2-num;
            return numbook;
        }
    }
    return 0;
}
void MainWindow::update_sure(QString name, QString num)//����ѧ�ź��鼮��ţ��ڽ��н���ȷ�Ϻ󣬶����ݿ���и���
{
    if(cal_num_lend(name)!=0)
    {
        QSqlQuery query;

        //���½�����Ϣ��Ŀɽ�����Ϊ30����������Ϊ0������״̬Ϊfalse,����������ΪFalse���������Ϊ���죬����Ա��Ϊ��ǰ����Ա��
        QString sql=QString::fromLocal8Bit("update borrow set �ɽ����� = '30' , �������� = '0',����״̬ = 'False',�������� = 'False',");
        sql=sql+tr("������� = '");
        QString date=QDate::currentDate().toString("yyyyMMdd");
        sql=sql+date+tr("', ����Ա�� = '")+namenum+tr("' where ѧ��='");
        sql=sql+name+tr("' and ͼ����= '")+num+tr("'");
        query.exec(sql);

        //�����鼮��Ϣ��Ĵ���Ľ���״̬
        sql=QString::fromLocal8Bit("update book set ����״̬ = 'True',���Ĵ���=���Ĵ���+'1' where ͼ����= '")+num+tr("'");
        query.exec(sql);

        //����ѧ����Ϣ���е�ѧ�����ı���
        sql=QString::fromLocal8Bit("update student set �ѽ豾��=�ѽ豾��+'1' where ѧ��= '")+name+tr("'");
        if(query.exec(sql))
            ui2->f11l5->setText(tr("��������\nȷ�����"));
        else
            ui2->f11l5->setText(tr("��������\nδִ��"));
    }
    else
    {
        ui2->f11l5->setText(tr("���˽�����Ŀ\n�Ѵﵽ����"));
    }
}
void MainWindow::update_xujie(QString name, QString num)//����ѧ�ź��鼮��ţ��ڽ�������ȷ�Ϻ󣬶����ݿ���и���
{
    QSqlQuery query;

    //���½�����Ϣ�������״̬ΪTrue,��������Ϊfalse,����Ա��Ϊ��ǰ����Ա��,�ɽ���������15��
    QString sql=QString::fromLocal8Bit("update borrow set �ɽ����� = �ɽ�����+'15',����״̬ = 'True',�������� = 'False',");

    sql=sql+tr("����Ա�� = '")+namenum+tr("' where ѧ��='");
    sql=sql+name+tr("' and ͼ����= '")+num+tr("'");
    if(query.exec(sql))
        ui2->f11l5->setText(tr("��������\nȷ�����"));
    else
        ui2->f11l5->setText(tr("��������\nδִ��"));
}
void MainWindow::update_back(QString name, QString num)//����ѧ�ź��鼮��ţ��ڽ��й黹ȷ�Ϻ󣬶����ݿ���и���
{
    QSqlQuery query;

    //ɾ���˽�����Ϣ
    QString sql;

    QString temp=this->model->data(model->index(recordnum,2)).toString();
    QDate d1=QDate::fromString(temp,"yyyyMMdd");
    int day=this->model->data(model->index(recordnum,3)).toInt();
    days=QDate::currentDate().toJulianDay()-d1.toJulianDay()-day;
    if(days>0)
    {
        sql=QString::fromLocal8Bit("update student set Ƿ���� = Ƿ���� + '");
        sql=sql+QString::number(days*0.1)+tr("' where ѧ�� = '")+name+tr("'");
        query.exec(sql);
        qDebug()<<"::"<<query.lastError()<<endl;
    }

    this->model->removeRow(recordnum);
    this->model->submitAll();

    //�����鼮��Ϣ��Ĵ���Ľ���״̬
    sql=QString::fromLocal8Bit("update book set ����״̬ = 'False' where ͼ����= '")+num+tr("'");
    query.exec(sql);

    //����ѧ����Ϣ���е�ѧ�����ı���
    sql=QString::fromLocal8Bit("update student set �ѽ豾��=�ѽ豾��-'1' where ѧ��= '")+name+tr("'");

    if(query.exec(sql))
        ui2->f11l5->setText(tr("�黹����\nȷ�����"));
    else
        ui2->f11l5->setText(tr("�黹����\nδִ��"));
}
void MainWindow::update_pay(QString name)//����ѧ�ţ���ȷ�ϽɷѲ������student�����
{
    //����Ƿ����ͽɷ�����״̬
    QString sql=QString::fromLocal8Bit("update student set Ƿ����='0',�ɷ�����='False' where ѧ��= '")+name+tr("'");
    QSqlQuery query;
    if(query.exec(sql))
        ui2->f11l5->setText(tr("�ɷ�����\nȷ�����"));
    else
        ui2->f11l5->setText(tr("�ɷ�����\nδִ��"));
//    qDebug()<<query.lastError()<<endl;
}
void MainWindow::update_add(QString name)//����ѧ�ţ���ȷ���û�ע������������student�����
{
    //�����û�����״̬
    QString sql=QString::fromLocal8Bit("update student set �ѽ豾��='0' where ѧ��= '")+name+tr("'");
    QSqlQuery query;
    if(query.exec(sql))
        ui2->f11l5->setText(tr("ע������\nȷ�����"));
    else
        ui2->f11l5->setText(tr("ע������\nδִ��"));
}
//�ۺ���
void MainWindow::on_f11chose_activated(const QString &arg1)//���������򣬾���������������
{
    if(ui2->f11chose->currentIndex()>2)//���ò�ѯʹ�õı�
        this->model->setTable("student");
    else
        this->model->setTable("borrow");
    QString sql=QString::fromLocal8Bit(" = 'True'");

    if(ui2->f11chose->currentIndex()==4)
        sql=tr("�ѽ豾�� = '-1'");
    else
        sql=arg1+sql;

    this->model->setFilter(sql);
    this->model->select();

    ui2->f11l3->setText(arg1+QString::number(model->rowCount())+tr("��"));//����ѡ�������ĸ�����ʾ
    ui2->result->setModel(this->model);
    ui2->result->show();
    ui2->f11l4->setText("");
}
void MainWindow::on_result_pressed(const QModelIndex &index)//ȷ���û�ѡ���������¼������ʾ����
{
    recordnum=index.row();
    ui2->f11l4->setText(tr(" ����ѡ��\n ��")+QString::number(index.row()+1)+tr("����¼"));
    ui2->f12l3->setText(tr(" ����ѡ��\n ��")+QString::number(index.row()+1)+tr("����¼"));
}
void MainWindow::on_f11sure_clicked()//�û��ĵ�һ��ȷ�ϵ�������ť
{
    ui2->f11bback->setVisible(true);
    ui2->f11bsure->setVisible(true);
    ui2->f11bsure1->setVisible(false);
    ui2->f11bback1->setVisible(false);
    ui2->f11sure->setVisible(false);
}
void MainWindow::on_f11sureall_clicked()//�û��ĵ�һ��ȷ�����д���ť
{
    ui2->f11bback1->setVisible(true);
    ui2->f11bsure1->setVisible(true);
    ui2->f11bsure->setVisible(false);
    ui2->f11bback->setVisible(false);
    ui2->f11sureall->setVisible(false);
}
void MainWindow::on_f11bsure_clicked()//�û��ĵڶ���ȷ�ϵ�������ť�������д���
{
    QString temp=ui2->f11l4->text();
    if(temp.isEmpty()||temp.isNull())
    {
        QMessageBox::warning(0, qApp->tr("ȷ������"),(tr("δѡ���κμ�¼������")), QMessageBox::Default);
        on_f11bback_clicked();
        return ;
    }
    QString name=model->data(model->index(recordnum,0)).toString();//��ȡѧ��
    QString t2=model->data(model->index(recordnum,1)).toString();//��ȡͼ����

    int pos=ui2->f11chose->currentIndex();

    switch(pos){
        case 0: update_sure(name,t2);break;
        case 1:update_xujie(name,t2);break;
        case 2:update_back(name,t2);break;
        case 3:update_pay(name);break;
        default:update_add(name);
    }
    QMessageBox::information(0, qApp->tr("ȷ������"),qApp->tr("ȷ�ϲ���ִ����ϣ�"), QMessageBox::Default);
    this->model->select();
    ui2->result->setModel(this->model);
    ui2->result->show();
    on_f11bback_clicked();
}
void MainWindow::on_f11bback_clicked()//�û��ĵڶ���ȷ�ϵ�������ȷ��ʱ��ȡ����ť
{
    ui2->f11bsure->setVisible(false);
    ui2->f11bback->setVisible(false);
    ui2->f11sure->setVisible(true);
}
void MainWindow::on_f11bsure1_clicked()//�û��ĵڶ���ȷ�����д���ť�������д���
{
    for(int i=0;i<model->rowCount();i++)
    {
        QString name=model->data(model->index(i,0)).toString();//��ȡѧ��
        QString t2=model->data(model->index(i,1)).toString();//��ȡͼ����

        int pos=ui2->f11chose->currentIndex();

        switch(pos){
            case 0: update_sure(name,t2);break;
            case 1:update_xujie(name,t2);break;
            case 2:update_back(name,t2);break;
            case 3:update_pay(name);break;
            default:update_add(name);
        }
    }
    QMessageBox::information(0, qApp->tr("ȷ������"),qApp->tr("����ȷ�ϲ���ִ����ϣ�"), QMessageBox::Default);
    this->model->select();
    ui2->result->setModel(this->model);
    ui2->result->show();
    on_f11bback1_clicked();
}
void MainWindow::on_f11bback1_clicked()//�û��ĵڶ���ȷ�����д���ȷ��ʱ��ȡ����ť
{
    ui2->f11bsure1->setVisible(false);
    ui2->f11bback1->setVisible(false);
    ui2->f11sureall->setVisible(true);
}


//�鿴�û���Ϣ���
void MainWindow::show_student()//��ʾѧ����Ϣ�Ĳۺ��������ڲ鿴��ɾ��ѧ��Ŀ¼
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
void MainWindow::update_deletes(QString name)//����ѧ�ţ���ִ��ɾ��ѧ����Ϣ�󣬶����ݿ���и���
{
    QSqlTableModel *model1=new QSqlTableModel;//����Qt�����ݿ��ѯ��ģ�ͣ��û�tableview�е����׽����ʾ
    model1->setEditStrategy(QSqlTableModel::OnManualSubmit);//�������ԣ�ֻ���ύ�����Ż��޸����ݿ�
    model1->setTable("borrow");
    model1->removeColumns(2,8);
    QString sql=QString::fromLocal8Bit("ѧ�� = '")+name+tr("'");
    model1->setFilter(sql);
    model1->select();

    QSqlQuery query;
    QString sql1=QString::fromLocal8Bit("update book set ����״̬ = 'False' where ͼ����= '");
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
//�ۺ���
void MainWindow::on_f12method_activated(const QString &arg1)//����������ȷ����ѯѧ����Ϣ�ķ�ʽ
{
    int num=ui2->f12method->currentIndex();
    if(num<6)
        hide4(true,num);
    else
        hide4(true,7);

    ui2->f12l2->setText(arg1+tr(":"));
}
void MainWindow::on_f12sure_clicked()//��������Ͳ�ѯ��ʽ��ȷ��ѧ�������ȷ�ϰ�ť
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
    this->model->removeColumn(model->fieldIndex("��½����"));
    this->model->setFilter(sql);
    this->model->select();
    ui2->result->setModel(this->model);
    ui2->result->show();

}
void MainWindow::on_f12delete_clicked()//ɾ������ѧ����Ϣ�ĵ�һ��ȷ�ϰ�ť���ڶ���ȷ��Ϊ�Ի���
{
    int curRow = ui2->result->currentIndex().row();
    //��ȡѡ�е���
    QString name=this->model->data(this->model->index(curRow,0)).toString();
    this->model->removeRow(curRow);
    int ok = QMessageBox::warning(this,tr("ɾ����ǰ��!"),tr("��ȷ��ɾ����ǰ����"),QMessageBox::No,QMessageBox::Yes);
    if(ok == QMessageBox::No)
    {
        this->model->revertAll(); //�����ɾ��������
        ui2->f12l4->setText(tr("ɾ���ѳ�����"));
    }
    else
    {
        ui2->f12l4->setText(tr("�ɹ�ɾ��!"));
        this->model->submitAll(); //�����ύ�������ݿ���ɾ������
        update_deletes(name);
    }
}
void MainWindow::on_f12delete1_clicked()//ɾ����ҵѧ����Ϣ�ĵ�һ��ȷ�ϰ�ť���ڶ���ȷ��Ϊ�Ի���
{
    QSqlTableModel *model1=new QSqlTableModel;//����Qt�����ݿ��ѯ��ģ�ͣ��û�tableview�е����׽����ʾ
    model1->setEditStrategy(QSqlTableModel::OnManualSubmit);//�������ԣ�ֻ���ύ�����Ż��޸����ݿ�
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
    int ok=QMessageBox::warning(this,tr("ɾ����ҵѧ��"),tr("��ȷ��ִ�д˲�����"),QMessageBox::No,QMessageBox::Yes);
    if(ok == QMessageBox::No)
    {
        model1->revertAll(); //�����ɾ��������
        ui2->f12l4->setText(tr("ɾ���ѳ�����"));
    }
    else
    {
        ui2->f12l4->setText(tr("�ɹ�ɾ��!"));
        model1->submitAll(); //�����ύ�������ݿ���ɾ������
    }
}


//�鿴����Ա��Ϣ��Ρ��������û����ԣ�ֻ��һ��,���ɴ���
void MainWindow::show_student1()//��ʾ����Ա��������Ϣ�Ĳۺ���������Ŀ¼����Ӧ
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
    QSqlTableModel *model1=new QSqlTableModel;//����Qt�����ݿ��ѯ��ģ�ͣ��û�tableview�е����׽����ʾ
    model1->setEditStrategy(QSqlTableModel::OnManualSubmit);//�������ԣ�ֻ���ύ�����Ż��޸����ݿ�
    model1->setTable("Admin");
    model1->select();
    ui2->result->setEditTriggers(QAbstractItemView::AllEditTriggers);
    ui2->result->setModel(model1);
    ui2->result->show();
    this->model1=model1;
}
void MainWindow::on_f12b2_clicked()//ȷ���޸Ĺ���Ա��Ϣ�����İ�ť���ڶ���ȷ��Ϊ�Ի���
{
    ui2->f12l4->setVisible(true);
    int ok=QMessageBox::warning(this,tr("ȷ���޸�"),tr("��ȷ��ִ�д˲�����"),QMessageBox::No,QMessageBox::Yes);
    if(ok == QMessageBox::No)
    {
        model1->revertAll();
        ui2->f12l4->setText(tr("�޸��ѳ�����"));
    }
    else
    {
        ui2->f12l4->setText(tr("�ɹ��޸�!"));
        if(!model1->submitAll()) //�����ύ�������ݿ����޸ļ�¼
            ui2->f12l4->setText(tr("����ʧ��!"));
        model1->select();
        ui2->result->setModel(model1);
        ui2->result->show();
    }

}
void MainWindow::on_f12b1_clicked()//ȷ��ɾ������Ա��Ϣ�����İ�ť���ڶ���ȷ��Ϊ�Ի���
{
    int curRow = ui2->result->currentIndex().row();
    this->model1->removeRow(curRow);
    ui2->f12l4->setVisible(true);
    int ok=QMessageBox::warning(this,tr("ȷ��ɾ��"),tr("��ȷ��ִ�д˲�����"),QMessageBox::No,QMessageBox::Yes);
    if(ok == QMessageBox::No)
    {
        model1->revertAll();
        ui2->f12l4->setText(tr("ɾ���ѳ�����"));
    }
    else
    {
        ui2->f12l4->setText(tr("�ɹ�ɾ��!"));
        if(!model1->submitAll()) //����ɾ���������ݿ����޸ļ�¼
            ui2->f12l4->setText(tr("����ʧ��!"));
        model1->select();
        ui2->result->setModel(model1);
        ui2->result->show();
    }
}
void MainWindow::on_f12b3_clicked()//ȷ�����ӹ���Ա��Ϣ�����İ�ť���ڶ���ȷ��Ϊ�Ի���
{
    int ok=QMessageBox::warning(this,tr("ȷ�����"),tr("��ȷ��ִ�д˲�����"),QMessageBox::No,QMessageBox::Yes);
    if(ok == QMessageBox::No)
    {
        ui2->f12l4->setText(tr("����ѳ�����"));
    }
    else
    {
        ui2->f12l4->setText(tr("�ɹ����!"));
        int rowNum = model1->rowCount(); //��ñ������
        model1->insertRow(rowNum); //�����
    }

}



//////////////////ͼ����Ϣ����Ŀ¼
//����鼮���
bool MainWindow::addbook(QString str[])//���������Ŀ�������Ϣ����book��������ݸ���
{
    if(str[0].isEmpty()||str[0].isNull())
    {
        QMessageBox::warning(this,tr("����鼮"),tr("��Ų���Ϊ��"),QMessageBox::Yes);
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
        QMessageBox::warning(this,tr("����鼮"),tr("�鼮����ظ�"),QMessageBox::Yes);
        return false;
    }
    return true;
}
//�ۺ���
void MainWindow::change_book()//����鼮Ŀ¼��Ӧ�Ĳۺ��������ڳ�ʼ�����
{
    hide5(true);
    hide2(false);
    hide3(false);
    hide6(false);
    hide7(false);
    ui2->stext->setVisible(false);
    ui2->result->setVisible(false);

}
void MainWindow::on_f21b1_clicked()//ȷ�ϸ����û���������鼮�İ�ť�����úϷ��Լ��
{
    QString num=ui2->f21in1->text();
    if(num.isEmpty()||num.isNull())
    {
        QMessageBox::warning(this,tr("����鼮"),tr("��Ų���Ϊ��"),QMessageBox::Yes);
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
        QMessageBox::warning(this,tr("����鼮"),tr("�鼮����ظ�"),QMessageBox::Yes);
    }
    else
    {
        QMessageBox::information(this,tr("����鼮"),tr("����鼮�ɹ�"),QMessageBox::Yes);
    }
}
void MainWindow::on_f21b2_clicked()//ͨ���ļ�������Ŀ��ӵİ�ť���и�ʽҪ�󣬻���ʾ
{
    QString form=QString::fromLocal8Bit("00000003\n�������ѧ�뼼��\n��\n�����\n");
    QMessageBox::information(this,tr("��Ŀ��ʽ"),form+tr("00000003\n�������ѧ�뼼��\nû�д���ҵ\n�����"),QMessageBox::Yes);
    QString fname=QFileDialog::getOpenFileName(this,tr("find book information file"),"",tr("*.txt"));
    QFile file(fname);
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        QMessageBox::warning(this,tr("�����Ŀ"),tr("�ļ���ʧ��!"),QMessageBox::Yes);
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
                int ok=QMessageBox::warning(this,tr("�����Ŀ"),tr("��ӳ����������жϣ�"),QMessageBox::No,QMessageBox::Yes);
                if(ok==QMessageBox::No)
                    break;
            }
            else
                num++;
        }
    }
    QMessageBox::warning(this,tr("�����Ŀ"),tr("��ӽ���,��ӱ���")+QString::number(num),QMessageBox::Yes);
    file.close();
}
void MainWindow::on_f21b3_clicked()//������Ŀ��Ϣ�İ�ť����ѡ�񱣴�·��
{
    QString fname=QFileDialog::getExistingDirectory(this,tr("����Ŀ¼λ��"),tr("ѡ��Ŀ¼"),QFileDialog::ShowDirsOnly );
//    QFileDialog::getExistingDirectory
    fname.append("��Ŀ.txt");
    QFile file(fname);
    if(!file.open(QIODevice::WriteOnly|QIODevice::Text))
    {
        QMessageBox::warning(this,tr("�����ļ�"),tr("�ļ�����ʧ��!"),QMessageBox::Yes);
        return;
    }
    QTextStream out(&file);
    QSqlQuery query;
    int num=0;
    QString sql=QString::fromLocal8Bit("select ͼ����,ͼ������,ͼ����,����ѧ�� from book");
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
        QMessageBox::warning(this,tr("��Ŀ����"),tr("����ʧ�ܣ�"),QMessageBox::Yes);
    QMessageBox::warning(this,tr("������Ŀ"),tr("��ӽ���,��������")+QString::number(num),QMessageBox::Yes);
    file.close();
}


//ɾ���鼮��Ϣ���
void MainWindow::update_deleteb(QString name)//��ִ��ɾ����Ŀ֮�󣬶����ݿ�������ݸ���
{
    QSqlTableModel *model1=new QSqlTableModel;//����Qt�����ݿ��ѯ��ģ�ͣ��û�tableview�е����׽����ʾ
    model1->setEditStrategy(QSqlTableModel::OnManualSubmit);//�������ԣ�ֻ���ύ�����Ż��޸����ݿ�
    model1->setTable("borrow");
    model1->removeColumns(2,8);
    QString sql=QString::fromLocal8Bit("ͼ���� = '")+name+tr("'");
    model1->setFilter(sql);
    model1->select();

    QSqlQuery query;
    QString sql1=QString::fromLocal8Bit("update student set �ѽ豾�� = �ѽ豾��-'1' where ѧ��= '");
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
//�ۺ���
void MainWindow::delete_book()//ɾ���鼮��ϢĿ¼��Ӧ�ۺ��������ڳ�ʼ���
{
    hide2(false);//���ò�εĿؼ��ֲ����غ���
    hide3(false);
    hide5(false);
    hide6(true);
    hide7(false);
    ui2->f12l3->setText(tr(""));
    ui2->f12l4->setText(tr(""));
    ui2->result->setVisible(false);


}
void MainWindow::on_f22c1_activated(const QString &arg1)//����������ѡ���ѯͼ��ķ�ʽ
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
void MainWindow::on_f22b1_2_clicked()//���ݲ�ѯ��ʽ���������ݲ���ͼ����Ϣ
{
    ui2->f22b1->setVisible(true);
    ui2->f22b2->setVisible(true);
    ui2->result->setVisible(true);
    QSqlTableModel *model2=new QSqlTableModel;//����Qt�����ݿ��ѯ��ģ�ͣ��û�tableview�е����׽����ʾ
    model2->setEditStrategy(QSqlTableModel::OnManualSubmit);//�������ԣ�ֻ���ύ�����Ż��޸����ݿ�
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
void MainWindow::on_f22b1_clicked()//ɾ���鼮��ȷ�ϰ�ť���ڶ���ȷ��Ϊ�Ի���
{
    int curRow = ui2->result->currentIndex().row();
    //��ȡѡ�е���
    QString name=this->model2->data(this->model2->index(curRow,0)).toString();
    this->model2->removeRow(curRow);
    int ok = QMessageBox::warning(this,tr("ɾ����ǰ��!"),tr("��ȷ��ɾ����ǰ����"),QMessageBox::No,QMessageBox::Yes);
    if(ok == QMessageBox::No)
    {
        this->model2->revertAll(); //�����ɾ��������
        ui2->f12l4->setText(tr("ɾ���ѳ�����"));
    }
    else
    {
        ui2->f12l4->setText(tr("�ɹ�ɾ��!"));
        this->model2->submitAll(); //�����ύ�������ݿ���ɾ������
        update_deleteb(name);
    }
}
void MainWindow::on_f22b2_clicked()//ɾ�������鼮����Ŀǰ���ҵ��ģ��ڶ���ȷ��Ϊ�Ի���
{
    int n=0,n1=model2->rowCount();
    for(n=n1-1;n>=0;n--)
    {
        QString name=model2->data(model2->index(n,0)).toString();
        model2->removeRow(n);
        update_deleteb(name);
    }
    int ok=QMessageBox::warning(this,tr("ɾ���鼮"),tr("��ȷ��ִ�д˲�����"),QMessageBox::No,QMessageBox::Yes);
    if(ok == QMessageBox::No)
    {
        model2->revertAll(); //�����ɾ��������
        ui2->f12l4->setText(tr("ɾ���ѳ�����"));
    }
    else
    {
        ui2->f12l4->setText(tr("�ɹ�ɾ��!"));
        model2->submitAll(); //�����ύ�������ݿ���ɾ������
    }
}


/////////////////�û���Ϣ�޸�Ŀ¼
void MainWindow::change_useinfo()//�޸��û���ϢĿ¼��Ӧ�Ĳۺ��������ڳ�ʼ�����
{
    ui2->stext->setVisible(false);
    hide2(false);//���ò�εĿؼ��ֲ����غ���
    hide3(false);
    hide5(false);
    hide6(false);
    hide7(true);
    ui2->f3in1->setEnabled(false);
    ui2->f3in1->setText(namenum);
    ui2->f3in2->setEnabled(true);
    ui2->f3in3->setEnabled(true);

    QSqlQuery query;
    QString sql=QString::fromLocal8Bit("select ����,��½���� from Admin where ����Ա�� = '");
    sql=sql+namenum+tr("'");//ƴ�ӳɲ�ѯ���

    if(query.exec(sql))//ִ�У�����ѧ�Ż�ȡ������Ϣ
    {
        if(query.next())
        {
            ui2->f3in2->setText(query.value(0).toString());//��ʾ��ȡ������Ϣ
            ui2->f3in3->setText(query.value(1).toString());
        }
    }
    qDebug()<<query.lastError()<<endl;
}
void MainWindow::on_f3b_clicked()//ȷ���޸��û���Ϣ��ȷ�ϰ�ť���ڶ���ȷ��Ϊ�Ի���
{
    ui2->f3in2->setEnabled(false);
    ui2->f3in3->setEnabled(false);

    ///�û��������Ϣ�ĺϷ��Լ��
    QString name=ui2->f3in2->text();
    if(name.isEmpty()||name.isNull())
    {
        QMessageBox::warning(0, qApp->tr("�޸���Ϣ"),qApp->tr("��������Ϊ�գ�"), QMessageBox::Default);
        return ;
    }
    QString pas=ui2->f3in3->text();

    QString sql=QString::fromLocal8Bit("update Admin set ���� = '");
    sql=sql+name+tr("' , ��½���� = '")+pas+tr("' where ����Ա�� = '");
    sql=sql+namenum+tr("'");//ƴ�Ӹ��²�����sql���

    QSqlQuery query;

    int ok=QMessageBox::warning(this,tr("�޸���Ϣ"),tr("��ȷ��ִ�д˲�����"),QMessageBox::No,QMessageBox::Yes);
    if(ok == QMessageBox::Yes)
    {
        if(query.exec(sql))//ִ�д���䣬�޸����ݿ�
        {
            QMessageBox::information(0, qApp->tr("�޸���Ϣ"),qApp->tr("�޸ĳɹ�"), QMessageBox::Default);
        }
    }
}


///////////////////���ؿ�ʼ������
void MainWindow::returns()//���ؿ�ʼ����Ĳۺ���
{
    message();//�����Ƿ����û����󣬽�����ʾ
    hide2(false);//���ò�εĿؼ��ֲ����غ���
    hide3(false);
    hide5(false);
    hide6(false);
    hide7(false);
    ui2->stext->setVisible(true);
}
