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

void SearchWindow::init()//查询界面的初始化，设置一些控件是否显示和背景
{
    setMaximumSize(702,481);
    setMinimumSize(702,481);

    setAutoFillBackground(true);
    QPalette p;
    QPixmap p1("./xingkong1.jpg");//背景
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

void SearchWindow::searchbook()//查询书目的功能实现
{
    ui1->result->clearSpans();///表格内没有分界线
    QSqlTableModel *model=new QSqlTableModel;
    model->setTable("book");//设置要查询的表名
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    this->model=model;//赋值给私有变量，减少方法参数
    model->removeColumn(model->fieldIndex("图书简介"));

    ui1->result->setEditTriggers(QAbstractItemView::NoEditTriggers);//不可编辑

    QString sql,s2;

    sql=ui1->choose->currentText();//查询方式，即查询过程中的属性名
    int index=ui1->choose->currentIndex();//第几个，用于区分下一步骤

    if(index!=3)//不是下拉框。需要自己填写
    {
        s2=ui1->bookname->text();
        if(index==1)
            sql=sql+tr("=")+tr("'")+s2+tr("'");//编号的唯一性确定查询方式
        else
            sql=sql+tr(" ")+tr("like '%")+s2+tr("%")+tr("'");//使用like谓词进行书名的查询
    }
    else
    {
        s2=ui1->subject->currentText();//下拉框内容
        sql=sql+tr("=")+tr("'")+s2+tr("'");
    }
    model->setFilter(sql);//设置where语句的内容
    model->select();//进行查询

    ui1->result->setModel(model);//将结果显示在表格中
    ui1->result->show();
}



void SearchWindow::on_bsearch_clicked()//查询按钮的功能的具体实现
{
    ui1->result->setVisible(true);//设置界面中一些控件是否显示
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

void SearchWindow::on_choose_activated(int index)//根据第一个下拉框的内容，选择显示下一层次的控件
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


void SearchWindow::on_result_pressed(const QModelIndex &index)//实现书籍简介显示的实现
{
    QString temp=model->data(model->index(index.row(),0)).toString();//获取书籍编号
    QSqlQuery query;
    QString sql=QString::fromLocal8Bit("select 图书简介,图书名称 from book where 图书编号 = ")+tr("'")+temp+tr("'");
    bool flag=query.exec(sql);//通过书籍编号查询获得书籍的简介内容，显示
    if(flag)
    {
        ui1->intro->clear();
        query.next();
        temp=tr("编号 ")+temp+tr(":")+query.value(1).toString()+tr("\n具体简介:\n")+query.value(0).toString();
        ui1->intro->appendPlainText(temp);
    }
}
