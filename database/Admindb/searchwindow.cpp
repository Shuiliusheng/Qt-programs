#include "searchwindow.h"
#include "ui_searchwindow.h"


SearchWindow::SearchWindow(QWidget *parent) :
    QMainWindow(parent),
    ui1(new Ui::SearchWindow)
{
    ui1->setupUi(this);
}

SearchWindow::~SearchWindow()
{
    delete ui1;
}

void SearchWindow::init()//��ѯ����ĳ�ʼ��������һЩ�ؼ��Ƿ���ʾ�ͱ���
{
    setMaximumSize(702,481);
    setMinimumSize(702,481);

    setAutoFillBackground(true);
    QPalette p;
    QPixmap p1("./xingkong1.jpg");//����
    p.setBrush(QPalette::Window,QBrush(p1));
    setPalette(p);


    ui1->bookname->setVisible(false);
    ui1->bsearch->setVisible(false);
    ui1->l3->setVisible(false);
    ui1->subject->setVisible(false);
    ui1->result->setVisible(false);
    ui1->intro->setVisible(false);
    ui1->label_2->setVisible(false);
    ui1->result->setShowGrid(false);
}

void SearchWindow::searchbook()//��ѯ��Ŀ�Ĺ���ʵ��
{
    ui1->result->clearSpans();///�����û�зֽ���
    QSqlTableModel *model=new QSqlTableModel;
    model->setTable("book");//����Ҫ��ѯ�ı���
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    this->model=model;//��ֵ��˽�б��������ٷ�������
    model->removeColumn(model->fieldIndex("ͼ����"));

    ui1->result->setEditTriggers(QAbstractItemView::NoEditTriggers);//���ɱ༭

    QString sql,s2;

    sql=ui1->choose->currentText();//��ѯ��ʽ������ѯ�����е�������
    int index=ui1->choose->currentIndex();//�ڼ���������������һ����

    if(index!=3)//������������Ҫ�Լ���д
    {
        s2=ui1->bookname->text();
        if(index==1)
            sql=sql+tr("=")+tr("'")+s2+tr("'");//��ŵ�Ψһ��ȷ����ѯ��ʽ
        else
            sql=sql+tr(" ")+tr("like '%")+s2+tr("%")+tr("'");//ʹ��likeν�ʽ��������Ĳ�ѯ
    }
    else
    {
        s2=ui1->subject->currentText();//����������
        sql=sql+tr("=")+tr("'")+s2+tr("'");
    }
    model->setFilter(sql);//����where��������
    model->select();//���в�ѯ

    ui1->result->setModel(model);//�������ʾ�ڱ����
    ui1->result->show();
}



void SearchWindow::on_bsearch_clicked()//��ѯ��ť�Ĺ��ܵľ���ʵ��
{
    ui1->result->setVisible(true);//���ý�����һЩ�ؼ��Ƿ���ʾ
    ui1->intro->setVisible(true);
    ui1->label_2->setVisible(true);
    ui1->intro->clear();
    searchbook();
    ui1->choose->setVisible(true);
    ui1->l2->setVisible(true);
    ui1->bookname->setVisible(false);
    ui1->bsearch->setVisible(false);
    ui1->l3->setVisible(false);
    ui1->subject->setVisible(false);
}

void SearchWindow::on_choose_activated(int index)//���ݵ�һ������������ݣ�ѡ����ʾ��һ��εĿؼ�
{
    if(index!=0)
    {
        ui1->choose->setVisible(false);
        ui1->l2->setVisible(false);

        ui1->bsearch->setVisible(true);
        ui1->l3->setVisible(true);
        if(index==3)
            ui1->subject->setVisible(true);
        else
            ui1->bookname->setVisible(true);
        ui1->l3->setText(ui1->choose->currentText());
    }
}


void SearchWindow::on_result_pressed(const QModelIndex &index)//ʵ���鼮�����ʾ��ʵ��
{
    QString temp=model->data(model->index(index.row(),0)).toString();//��ȡ�鼮���
    QSqlQuery query;
    QString sql=QString::fromLocal8Bit("select ͼ����,ͼ������ from book where ͼ���� = ")+tr("'")+temp+tr("'");
    bool flag=query.exec(sql);//ͨ���鼮��Ų�ѯ����鼮�ļ�����ݣ���ʾ
    if(flag)
    {
        ui1->intro->clear();
        query.next();
        temp=tr("��� ")+temp+tr(":")+query.value(1).toString()+tr("\n������:\n")+query.value(0).toString();
        ui1->intro->appendPlainText(temp);
    }
}
