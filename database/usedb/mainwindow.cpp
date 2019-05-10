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
    hide(false);

    connectdb();//�������ݿ�
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


void MainWindow::update_borrow()//���½���ʱ�ĳ�������
{
    days=0;
    QSqlQuery query;
    QString sql=QString::fromLocal8Bit("select �������,ͼ����,�ɽ����� from borrow where ѧ�� = '");
    sql=sql+namenum+tr("' and �������� = 'False'");//��������ΪFalse�����Ѿ��赽�鼮
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
                days+=day1;
                sql=QString::fromLocal8Bit("update borrow set �������� = '");
                sql=sql+QString::number(day1)+tr("' where ѧ�� = '");
                sql=sql+namenum+tr("' and ͼ���� = '")+temp1+tr("'");//ƴ�Ӳ�ѯ���
                qDebug()<<sql<<endl;
                if(!query.exec(sql))
                    qDebug()<<query.lastError()<<endl;
            }
        }
    }
}


void MainWindow::update_database()//��̨���еĸ������ݿ⣬����ʱ�������
{
    if(flag)
    {
        update_borrow();
    }
}

void MainWindow::connectdb()//�������ݿ�
{
    db = QSqlDatabase::addDatabase("QSQLITE");
//    db = QSqlDatabase::addDatabase("QODBC");//ѡ�����ݿ�����
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


}

///////////////��½����//////////////////////////
///////////////////////////���ת������
void MainWindow::hide1(bool flag)//hide ϵ�У��������ؿؼ���ʹ�ý�����Էֲ㣬������ʹ��̫�����
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
void MainWindow::hide(bool flag)//hide ϵ�У��������ؿؼ���ʹ�ý�����Էֲ㣬������ʹ��̫�����
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

///////////////////////////��½���
bool MainWindow::login1()//��½�û�����
{
    QSqlQuery query;
    QString sql,sql1=ui->usename->text();
    sql=QString::fromLocal8Bit("select ��½����,�ѽ豾�� from student where ѧ��=")+sql1;
    query.exec(sql);

    query.next();
    QString pass1=query.value(0).toString();//����ѧ�Ż�ȡ��Ӧ��������ѽ�ı���
    int temp1=query.value(1).toInt();//ʹ�ñ���-1����ʾ���û�ע�ᵫδ������Աȷ��

    QString pass=ui->password->text();
    if(QString::compare(pass1,pass)!=0)//���벻ͬ
    {
        QMessageBox::warning(0, qApp->tr("��½"),qApp->tr("����������飡"), QMessageBox::Default);
        return false;
    }
    else
    {
        if(temp1==-1)//δ��ȷ�ϵ��û�
        {
            QMessageBox::warning(0, qApp->tr("��½"),qApp->tr("��δͨ������ȷ�ϣ�"), QMessageBox::Default);
            return false;
        }
        else
            return true;
    }
}
void MainWindow::on_login_clicked()//����ע���û��Ľ���
{
    hide1(false);
    hide(true);
    setMaximumSize(378,423);
    setMinimumSize(378,423);
}
void MainWindow::on_getin_clicked()//��½����ĵ�½��ť�Ĺ���
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
            this->namenum=usename;//�洢ѧ�ţ�������һ�����ʹ��

            update_borrow();

            initpaint();//��ʼ��������һ����

            setAutoFillBackground(true);//������һ����ı���
            QPalette p;
            QPixmap p1("./xingkong5.jpg");
            p.setBrush(QPalette::Window,QBrush(p1));
            setPalette(p);

            setMaximumSize(652,486);//���ù̶���С
            setMinimumSize(652,486);
            cal_num_lend();
            message();//�����Ƿ��г������ڵ��鼮��������ʾ

            connect(timer1,SIGNAL(timeout()),this,SLOT(message()));
            timer1->start(6000);

            hide2(false);//���ò�εĿؼ��ֲ����غ���
            hide3(false);
            hide4(false);

            showmoney();//��ʾǷ����
            ui2->date->setText(QDate::currentDate().toString("yyyy-MM-dd"));//��ʾ��ǰ����

        }
        else
            hide1(true);//�޷���½�����ص�½����ĵ�½���
    }
}
void MainWindow::on_search_clicked()//��ѯ��ť�Ĺ���
{
    s.init();//��һ����ĳ�ʼ��
    s.show();//��һ����Ļ���
}

///////////////////////////ע����
int MainWindow::detect1()//ע��ʱ���û�������Ϣ�ĺϷ���
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
    sql=QString::fromLocal8Bit("select ��½���� from student where ѧ��=")+usename;
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
    QString sql,s1,s2,s3;
    sql=QString::fromLocal8Bit("insert into student(ѧ��,����,ѧԺ,����,��ѧ���,����ʱ��,�ѽ豾��,Ƿ����,��½����,�ɷ�����) values(");
    s1=ui->usename1->text();
    s2=ui->name->text();
    s3=ui->college->currentText();
    sql=sql+s1+tr(",'")+s2+tr("','")+s3+tr("','");
    s1=ui->grade->currentText();
    s2=ui->starttime->text();
    s3=ui->overtime->text();
    sql=sql+s1+tr("',")+s2+tr(",")+s3+tr(",")+tr("'-1','-1',");
    s1=ui->password1->text();
    sql=sql+s1+tr(",'False')");//�Ⱥ���ߵĲ������ţ��ұ���Ҫ����

    bool flag=query.exec(sql);
    return flag;
}
void MainWindow::on_submit_clicked()//ע��ҳ���ȷ�ϰ�ť�Ĺ���ʵ��
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
        case 0:QMessageBox::warning(0, qApp->tr("ע��"),qApp->tr("ѧ�Ų���Ϊ�գ�"), QMessageBox::Default);
               break;
        case 1:QMessageBox::warning(0, qApp->tr("ע��"),qApp->tr("��������Ϊ�գ�"), QMessageBox::Default);
               break;
        case 2:QMessageBox::warning(0, qApp->tr("ע��"),qApp->tr("��ݸ�ʽ����"), QMessageBox::Default);
               break;
        case 3:QMessageBox::warning(0, qApp->tr("ע��"),qApp->tr("���벻��Ϊ�գ�"), QMessageBox::Default);
               break;
        case 6:QMessageBox::warning(0, qApp->tr("ע��"),qApp->tr("���������"), QMessageBox::Default);
               break;
        default:QMessageBox::warning(0, qApp->tr("ע��"),qApp->tr("��ѧ���ѱ�ע�ᣡ"), QMessageBox::Default);
        }
    }
}
void MainWindow::on_back_clicked()//��ע������˻ص�½����
{
    hide(false);
    hide1(true);
    setMaximumSize(392,363);
    setMinimumSize(392,363);
}

///////////////////////////�û�ʹ�ý���////////////////////////
///////////////////////////���ת������
void MainWindow::hide2(bool flag)//�����ʾʹ�õ����غ���ʾ����������ͳһ����
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
void MainWindow::hide3(bool flag)//�����ʾʹ�õ����غ���ʾ����������ͳһ����
{
    gethistory();//��ȡ���н����鼮����Ϣ
    showmoney();//��ʾǷ����
    ui2->f2back->setVisible(flag);
    ui2->f2l1->setVisible(flag);
    ui2->f2pay->setVisible(flag);
    ui2->f2xujie->setVisible(flag);
    ui2->f2info->setVisible(flag);
    ui2->f2info->clearSpans();
}
void MainWindow::hide4(bool flag)//�����ʾʹ�õ����غ���ʾ����������ͳһ����
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

////////////////////////////���Ĳ��
void MainWindow::initpaint()//�ڶ�����ĳ�ʼ������
{
    ui2->setupUi(this);//����ڶ�����

    QMenu *first1;///��ӹ���Ŀ¼��Ŀ¼�ڵ�����ѡ��
    first1=menuBar()->addMenu(tr("ʹ�ù���"));

    QAction *borrow=new QAction(QIcon("./tubiao1.jpg"),tr("���Ĺ���"),this);
    borrow->setStatusTip(tr("�����鼮"));
    borrow->setWhatsThis(tr("�����鼮"));
    connect(borrow,SIGNAL(triggered()),this,SLOT(fborrow()));//��fborrow�ۺ���������һ��

    QAction *history=new QAction(QIcon("./tubiao2.jpg"),tr("������ʷ"),this);
    history->setStatusTip(tr("������ʷ��Ϣ"));
    history->setWhatsThis(tr("������ʷ��Ϣ"));
    connect(history,SIGNAL(triggered()),this,SLOT(fsearch()));
    QAction *change_data=new QAction(QIcon("./tubiao3.jpg"),tr("�޸���Ϣ"),this);
    change_data->setStatusTip(tr("�޸��û���Ϣ"));
    change_data->setWhatsThis(tr("�޸��û���Ϣ"));
    connect(change_data,SIGNAL(triggered()),this,SLOT(fchange()));

    QAction *start=new QAction(QIcon("./tubiao3.jpg"),tr("��ʼ����"),this);
    start->setStatusTip(tr("��ʼ����"));
    start->setWhatsThis(tr("��ʼ����"));
    connect(start,SIGNAL(triggered()),this,SLOT(exit1()));

    QAction *exit=new QAction(QIcon("./tubiao3.jpg"),tr("ע���˳�"),this);
    exit->setStatusTip(tr("�û�ע���˳�"));
    exit->setWhatsThis(tr("�û�ע���˳�"));
    connect(exit,SIGNAL(triggered()),this,SLOT(close()));

    first1->addAction(start);
    first1->addAction(borrow);
    first1->addAction(history);
    first1->addAction(change_data);
    first1->addAction(exit);
}
void MainWindow::showmoney()//��ʾǷ����
{
    QSqlQuery query;

    QString sql=QString::fromLocal8Bit("select Ƿ���� from student where ѧ�� = '");
    sql=sql+namenum+tr("'");//ƴ���γɲ�ѯ���

    if(query.exec(sql))//ִ�У�����ѧ�Ż�ȡǷ����
    {
        if(query.next())
        {
            QString m=query.value(0).toString();
            float m1=m.toFloat();
            moneyz=m1;
            if(m1>5)//����5Ԫ��ϵͳ������
                QMessageBox::warning(0, qApp->tr("Ƿ������"),(tr("Ƿ��ﵽ��")+m+tr("Ԫ!!!")), QMessageBox::Default);
            ui2->fmoney->setText(tr("Ƿ��: ")+m+tr(" Ԫ"));
        }
    }
    else
        qDebug()<<query.lastError()<<endl;//���������Ϣ
}
void MainWindow::message()//�ڶ�����Ŀ�ʼ������ʾ�鱾������ʾ��Ϣ
{
    QSqlTableModel *model=new QSqlTableModel;//����Qt�����ݿ��ѯ��ģ�ͣ��û�tableview�е����׽����ʾ
    model->setTable("borrow");//���ò�ѯ�ı�
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);//�������ԣ�ֻ���ύ�����Ż��޸����ݿ�
    ui2->f2info->setEditTriggers(QAbstractItemView::NoEditTriggers);//������ʾ���֮��Ľ�����ܱ��޸�

    QString sql=QString::fromLocal8Bit("ѧ�� = '");//ƴ���γɲ�ѯ���
    sql=sql+namenum+tr("'");

    model->setFilter(sql);//����where�Ĳ�ѯ���
    model->select();//��ѯ���
    this->model=model;//���丳��˽�б��������ٷ����Ĳ�������

    int num=model->rowCount(),n=0;//�����Ԫ�����num

    QDate date=QDate::currentDate();//�͵�ǰ���ڣ������Ƚϣ�ȷ���Ƿ񳬳��ɽ�������
    QString stext=QString::fromLocal8Bit("ע�⣡����\n�鼮:");//���ڳ�������ʾ����
    for(int i=0;i<num;i++)
    {
        QString temp=model->data(model->index(i,1)).toString();
        QString t1=model->data(model->index(i,2)).toString();

        bool state=model->data(model->index(i,6)).toBool();
        int day=model->data(model->index(i,3)).toInt();

        QDate date1=QDate::fromString(t1,"yyyyMMdd");;
        int day1=day-date.toJulianDay()+date1.toJulianDay();

        if(day1<=0&&!state)//stateΪ����״̬��ΪTrue����δ���ĳɹ�
        {
            n++;//���ò�ѯ������
            stext=stext+temp+tr(" ���� ")+QString::number(day1*-1)+tr("��!\n");//ƴ���γ���ʾ�ִ�
        }
    }
    cal_num_lend();
    if(n==0)//�����Ƿ��У���ʾ��ͬ�����
        ui2->stext->setText(tr(" ^-^ Welcome to Use *-* ")+tr("\n\n   �������Խ���")+QString::number(numbook)+tr("���鼮��"));
    else
        ui2->stext->setText(tr("�������Խ���")+QString::number(numbook)+tr("���鼮��\n")+stext);
}
void MainWindow::cal_num_lend()//������û�Ŀǰ���Խ��ĵ��鱾����
{
    numbook=0;
    QSqlQuery query;
    QString  sql=QString::fromLocal8Bit("select ����,�ѽ豾�� from student where ѧ�� = '");
    sql=sql+namenum+tr("'");
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
            numbook=num2-num;
        }
    }
}

////////////////////////////���Ĳ��
bool MainWindow::detect_borrow()//���н����鼮ʱ������Ϸ��Լ����ܹ����ĵ��ж�
{
    QString name=ui2->f1name->text();
    if(name.isEmpty()||name.isNull())//�鼮����Ƿ�ϸ�
    {
        QMessageBox::warning(0, qApp->tr("�����鼮"),qApp->tr("�鼮��Ų���Ϊ�գ�"), QMessageBox::Default);
        return false;
    }
    if(name.length()!=8)
    {
        QMessageBox::warning(0, qApp->tr("�����鼮"),qApp->tr("�鼮��Ŵ���"), QMessageBox::Default);
        return false;
    }

    QSqlQuery query;
    QString sql=QString::fromLocal8Bit("select ͼ������ ����״̬ from book where ͼ����='");
    sql=sql+name+tr("'");//ƴ��Ϊ��ѯ���


    if(query.exec(sql))//ִ�в�ѯ��䣬����ͼ���ţ�ȷ��������״̬
    {
        query.next();
        QString temp=query.value(0).toString();
        bool tflag=query.value(1).toBool();

        if(temp.isNull()||temp.isEmpty())//���Ϊ�գ�û��������
        {
            QMessageBox::warning(0, qApp->tr("�����鼮"),qApp->tr("�����ڣ����飡"), QMessageBox::Default);
            return false;
        }
        name=name+tr(" : ")+temp;

        if(tflag==true)//Ӧ�������ĵı�ʶ
        {
            QMessageBox::warning(0, qApp->tr("�����鼮"),qApp->tr("�����Ѿ������ģ�"), QMessageBox::Default);
            return false;
        }
        else//�����ѧ�ŵ��鼮����
            QMessageBox::question(0, qApp->tr("�����鼮"),name, QMessageBox::Ok);
    }
    return true;
}
bool MainWindow::detect_borrow1()//��һ�����ܹ����ĵĺϷ����жϣ���detect_borrow֮��
{
    if(moneyz>=5)///Ƿ��̫�࣬���ܽ��������鼮
    {
        QMessageBox::warning(0, qApp->tr("Ƿ������"),qApp->tr("���Ȼ���Ƿ�"), QMessageBox::Default);
        return false;
    }

    QString s1=ui2->f1name->text();
    QString sql=QString::fromLocal8Bit("select ������� from borrow where ѧ�� = '");
    sql=sql+namenum+tr("' and ͼ���� ='")+s1+tr("'");//ƴ�����

    QSqlQuery query;
    if(query.exec(sql))//ͨ��ѧ�ź�ͼ���ţ��ж��Ƿ����޽���״̬
    {                  //���ϴ����鼮���еı�־����ͻ��ԭ����Ϊ�ɹ������ǣ��˱�־���ı�
        if(!query.next())
            return true;
        QString temp=query.value(0).toString();
        if(temp.isEmpty()||temp.isNull())//�������ֵΪ�գ���û�д˼�¼�����Ѿ��黹������δ������
            return true;
        QMessageBox::warning(0, qApp->tr("�����鼮"),qApp->tr("�����ѱ�������"), QMessageBox::Default);

    }
    if(numbook==0)//�����鼮����Ŀ�ﵽ�˼��������
    {
        QMessageBox::warning(0, qApp->tr("�����鼮"),qApp->tr("��������Ŀ�ﵽ�˼������ƣ�"), QMessageBox::Default);
        return false;
    }
    else
        return true;
    return false;
}
void MainWindow::fborrow()//Ŀ¼�еĽ��Ĳ�����Ӧ�Ĳۺ���
{
    ui2->stext->setVisible(false);//���øò�ε���ʾ�ؼ�Ϊ�ɼ���
    ui2->centralwidget->repaint();
    setMaximumSize(316,361);//�˲�εĽ����С
    setMinimumSize(316,361);
    //initpaint();
    hide2(true);
    hide3(false);
    hide4(false);
    ui2->f1sure1->setVisible(false);
    ui2->f1delete->setVisible(false);
}
void MainWindow::on_f1search_clicked()//��ѯ��ť�Ĺ���
{
    s.init();//��һ����ĳ�ʼ��
    s.show();//��һ����Ļ���
}
void MainWindow::on_f1sure_clicked()//����ȷ�ϰ�ť�Ĺ���
{
    if(detect_borrow())//���Ƚ���������Ϣ�ĺϷ��м����ܷ���ĵ��ж�
    {
        ui2->f1delete->setVisible(true);//�����ȷ��������һ�����ȷ�Ͻ��ĵĽ���
        ui2->f1sure1->setVisible(true);
        ui2->f1sure->setVisible(false);
    }

}
void MainWindow::on_f1delete_clicked()//ȡ�����ĵİ�ť�Ĳ���
{
    ui2->f1delete->setVisible(false);//�˻���һ�����ĵĲ��
    ui2->f1sure1->setVisible(false);
    ui2->f1sure->setVisible(true);
}
void MainWindow::on_f1sure1_clicked()//���ĵĵڶ���ȷ�ϰ�ť�Ĺ���
{
    if(detect_borrow1())//��һ���Ľ��ĺϷ��Լ��
    {
        QSqlQuery query;
        QString sql,s1;
        sql=QString::fromLocal8Bit("insert into borrow(ѧ��,ͼ����,����״̬,��������,��������,�黹����) values('");
        s1=ui2->f1name->text();
        sql=sql+namenum+tr("' , '")+s1+tr("','")+tr("False','True','False','False')");
        //ƴ���γɲ������
        if(!query.exec(sql))
            qDebug() <<query.lastError()<<endl;
        else
        {
            //�ɹ����ĵ���ʾ
            QMessageBox::information(0, qApp->tr("�����鼮"),qApp->tr("�����Ѿ��ύ"), QMessageBox::Default);
        }
    }
    on_f1delete_clicked();//�����˻�һ���
}


////////////////////////////������Ϣ���
void MainWindow::gethistory()//��ȡ��ʷ������Ϣ
{
    model->select();//model���ڲ����ݣ��Ѿ����жϹ����鼮�ķ����б������ϣ�ִ����ʾ����
    ui2->f2info->setModel(model);
    ui2->f2info->show();
}
void MainWindow::fsearch()//Ŀ¼�еĲ�ѯ��ʷ��Ϣ�Ĳ�����Ӧ�Ĳۺ���
{
    ui2->stext->setVisible(false);//���øò�ε���ʾ�ؼ�Ϊ�ɼ���
    setMaximumSize(652,486);//���ôβ�εĽ����С
    setMinimumSize(652,486);
    hide3(true);
    hide2(false);
    hide4(false);

}
void MainWindow::on_f2xujie_clicked()//���谴ť�Ĳ���
{
    QModelIndex index=ui2->f2info->currentIndex();
    QString temp=model->data(model->index(index.row(),1)).toString();//ͼ����

    bool state=model->data(model->index(index.row(),5)).toBool();//����״̬
    bool state1=model->data(model->index(index.row(),6)).toBool();//��������
    bool state2=model->data(model->index(index.row(),7)).toBool();//��������
    bool state3=model->data(model->index(index.row(),8)).toBool();//�黹����

    QString t1=model->data(model->index(index.row(),2)).toString();//�������
    int day=model->data(model->index(index.row(),3)).toInt();//�ɽ�����

    QDate date=QDate::currentDate();//���ڵ�����
    QDate date1=QDate::fromString(t1,"yyyyMMdd");//��20130411�ĸ�ʽת��ΪQDate����
    int day1=day-date.toJulianDay()+date1.toJulianDay();//����ɽ���������պͽ�����ڵĲ�ֵ�Ĳ�ֵ
    //Ϊ������Ϊ���ڣ��������������ã�Ϊ���������

    ////����ĺϷ��Ե��ж�
    if(state)//��������״̬��
    {
        QMessageBox::warning(0, qApp->tr("�����鼮"),qApp->tr("��������״̬��\n�������ٴ����裡"), QMessageBox::Default);
        return ;
    }
    else if(state1)//��δ�ɹ�����
    {
        QMessageBox::warning(0, qApp->tr("�����鼮"),qApp->tr("��δ�ɹ����ģ�"), QMessageBox::Default);
        return ;
    }
    else if(state2)//������������ʹ��
    {
        QMessageBox::warning(0, qApp->tr("�����鼮"),qApp->tr("������������ʹ�ã�"), QMessageBox::Default);
        return ;
    }
    else if(state3)//������黹����
    {
        QMessageBox::warning(0, qApp->tr("�����鼮"),qApp->tr("������黹���룡\n���������裡"), QMessageBox::Default);
        return ;
    }
    else if(day1>10)//���ھ������޶���10��
    {
        QMessageBox::warning(0, qApp->tr("�����鼮"),qApp->tr("���ھ�������10����\n���裡"), QMessageBox::Default);
        return ;
    }
    else if(day1<0)//�鼮����
    {
        QMessageBox::warning(0, qApp->tr("�����鼮"),qApp->tr("�������޹���\n���������裡"), QMessageBox::Default);
        return ;
    }
    else//�Ϸ�֮���������
    {
        QString sql=QString::fromLocal8Bit("update borrow set �������� = 'True' where ѧ�� = '");
        sql=sql+namenum+tr("' and ͼ���� = '")+temp+tr("'");//ƴ�Ӳ�ѯ���

        QSqlQuery query;
        if(query.exec(sql))//ִ�У���������Ϣ���еĸ�Ԫ��������ʶ����ΪTrue
        {
            model->select();
            ui2->f2info->setModel(model);
            ui2->f2info->show();//������ʾ���ĵ���Ϣ
            //��ʾ��Ϣ
            QMessageBox::information(0, qApp->tr("�����鼮"),qApp->tr("�ύ����ɹ���"), QMessageBox::Default);
        }
        else
            qDebug()<<query.lastError()<<endl;//��ʾ������Ϣ
    }
}
void MainWindow::on_f2back_clicked()//�黹�鼮��ť�Ĳ���
{
    QModelIndex index=ui2->f2info->currentIndex();
    QString temp=model->data(model->index(index.row(),1)).toString();//ͼ����
    bool state=model->data(model->index(index.row(),6)).toBool();//��������
    bool state1=model->data(model->index(index.row(),8)).toBool();//�黹����

    ///�ܹ��黹�����ĺϷ��Լ��
    if(state)//��δ�ɹ�����
    {
        QMessageBox::warning(0, qApp->tr("�黹�鼮"),qApp->tr("��δ�ɹ����ģ�"), QMessageBox::Default);
        return ;
    }
    else if(state1)//������黹����
    {
        QMessageBox::warning(0, qApp->tr("�黹�鼮"),qApp->tr("������黹����!"), QMessageBox::Default);
        return ;
    }
    else//�Ϸ�֮��
    {
        QString sql=QString::fromLocal8Bit("update borrow set �黹���� = 'True' where ѧ�� = '");
        sql=sql+namenum+tr("' and ͼ���� = '")+temp+tr("'");//ƴ�ӵõ��������

        QSqlQuery query;
        if(query.exec(sql))//ִ�и��²���,��������Ϣ���еĸ�Ԫ��Ĺ黹��ʶ����ΪTrue
        {
            model->select();
            ui2->f2info->setModel(model);
            ui2->f2info->show();//������ʾ���ĵ���Ϣ

            QMessageBox::information(0, qApp->tr("�黹����"),qApp->tr("�ύ����ɹ���"), QMessageBox::Default);
        }
        else
            qDebug()<<query.lastError()<<endl;
    }
}
void MainWindow::on_f2pay_clicked()//�ɷѲ�����ť�Ĺ���
{
    if(moneyz==0)//ûǷ��
    {
        QMessageBox::warning(0, qApp->tr("�ɷ�"),qApp->tr("����Ƿ��!"), QMessageBox::Default);
    }
    else
    {

        QString sql=QString::fromLocal8Bit("update student set �ɷ����� = 'True' where ѧ�� = '");
        sql=sql+namenum+tr("'");//ƴ�Ӹ��µ�sql���

        QSqlQuery query;
        if(query.exec(sql))//ִ�и��²���,��ѧ����Ϣ���еĸ�Ԫ��Ľɷѱ�ʶ����ΪTrue
        {
            QMessageBox::information(0, qApp->tr("�ɷ�����"),qApp->tr("�ύ����ɹ���"), QMessageBox::Default);
        }
        else
            qDebug()<<query.lastError()<<endl;
    }
}


////////////////////////////�û��޸���Ϣ���
void MainWindow::fchange()//Ŀ¼�е��޸��û���Ϣ�Ĳ�����Ӧ�Ĳۺ���
{
    ui2->stext->setVisible(false);//���øò�ε���ʾ�ؼ�Ϊ�ɼ���
    setMaximumSize(455,510);
    setMinimumSize(455,510);
    hide3(false);
    hide2(false);
    hide4(true);

    show_info();//��ʾ�û��ĸ��˵���Ϣ
    write(false);//����δ�����޸�ʱ�Ŀؼ�����
}
void MainWindow::write(bool flag)//���޸��û���Ϣʱ��ȷ���ؼ�������
{
    ui2->f3co->setEnabled(flag);//enabled �����ܱ��޸�
    ui2->f3gra->setEnabled(false);//���������Լ��޸�
    ui2->f3use->setEnabled(false);//ѧ�Ų����������޸�
    ui2->f3name->setEnabled(flag);
    ui2->f3starttime->setEnabled(flag);
    ui2->f3overtime->setEnabled(flag);
    ui2->f3password->setEnabled(flag);

    ui2->f3college->setVisible(flag);
    ui2->f3co->setVisible(!flag);
}
void MainWindow::show_info()//��ȡ�û��ĸ�����Ϣ��������ʾ
{
    QSqlQuery query;
    QString sql=QString::fromLocal8Bit("select ѧ��,����,ѧԺ,����,��ѧ���,����ʱ��,��½���� from student where ѧ�� = '");
    sql=sql+namenum+tr("'");//ƴ�ӳɲ�ѯ���

    if(query.exec(sql))//ִ�У�����ѧ�Ż�ȡ������Ϣ
    {
        if(query.next())
        {
            ui2->f3use->setText(namenum);
            ui2->f3name->setText(query.value(1).toString());//��ʾ��ȡ������Ϣ
            ui2->f3co->setText(query.value(2).toString());
            ui2->f3gra->setText(query.value(3).toString());
            ui2->f3starttime->setText(query.value(4).toString());
            ui2->f3overtime->setText(query.value(5).toString());
            ui2->f3password->setText(query.value(6).toString());
        }
    }
    else
        qDebug()<<query.lastError()<<endl;//���ִ�й����еĴ���������ʱ
}
void MainWindow::on_f3change_clicked()//��Ϣ�޸İ�ť�Ĺ���
{
    write(true);//������ؿؼ�������
}
void MainWindow::on_f3delete_clicked()//���޸ĵĻ��˲���
{
    show_info();//������ʾ�û�����Ϣ
    write(false);//������ؿռ������
}
void MainWindow::on_f3sure_clicked()//�޸ĵ�ȷ�ϰ�ť
{

    ///�û��������Ϣ�ĺϷ��Լ��
    QString name=ui2->f3name->text();
    if(name.isEmpty()||name.isNull())
    {
        QMessageBox::warning(0, qApp->tr("�޸���Ϣ"),qApp->tr("��������Ϊ�գ�"), QMessageBox::Default);
        return ;
    }
    QString start=ui2->f3starttime->text();
    QString over=ui2->f3overtime->text();
    if(start.length()!=6||over.length()!=6)
    {
        QMessageBox::warning(0, qApp->tr("�޸���Ϣ"),qApp->tr("ʱ���밴��ʽ��д!"), QMessageBox::Default);
        return ;
    }
    QString pas=ui2->f3password->text();
    if(pas.length()<=0||pas.length()>29)
    {
        QMessageBox::warning(0, qApp->tr("�޸���Ϣ"),qApp->tr("����ȷ��д����!\n�������29���ַ�"), QMessageBox::Default);
        return ;
    }
    ///ִ�е��˴��Ϸ�
//    QString grade=ui2->f3grade->currentText();
    QString collge=ui2->f3college->currentText();

    QString sql=QString::fromLocal8Bit("update student set ���� = '");
    sql=sql+name+tr("' , ѧԺ = '")+collge+tr("' ,")+tr("��ѧ��� = '");
    sql=sql+start+tr("' , ����ʱ�� = '")+over+tr("' , ��½���� = '")+pas+tr("' where ѧ�� = '");
    sql=sql+namenum+tr("'");//ƴ�Ӹ��²�����sql���

    QSqlQuery query;
    if(query.exec(sql))//ִ�д���䣬�޸����ݿ�
    {
        show_info();//�ɹ������»ص��û���Ϣ��ʾ�Ĳ��
        write(false);//���ÿؼ�����
        QMessageBox::information(0, qApp->tr("�޸���Ϣ"),qApp->tr("�޸ĳɹ�"), QMessageBox::Default);
    }
    else
        qDebug()<<query.lastError()<<endl;
}

//////////////////////////////////////////////////
void MainWindow::exit1()//���ؿ�ʼ����
{
    message();//�����Ƿ��г������ڵ��鼮��������ʾ

    hide2(false);//���ò�εĿؼ��ֲ����غ���
    hide3(false);
    hide4(false);
    setMaximumSize(652,486);//���ù̶���С
    setMinimumSize(652,486);
    ui2->stext->setVisible(true);
    showmoney();//��ʾǷ����
}
