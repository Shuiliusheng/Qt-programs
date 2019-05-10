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

    void update_borrow();//���½���ʱ�ĳ�������
    void connectdb();//�������ݿ�
    void initdata();//��ʼ�����ݿ�

///////////////��½����//////////////////////////
    //���ת������
    void hide1(bool flag);//hide ϵ�У��������ؿؼ���ʹ�ý�����Էֲ㣬������ʹ��̫�����
    void hide(bool flag);//hide ϵ�У��������ؿؼ���ʹ�ý�����Էֲ㣬������ʹ��̫�����

    //��½���
    bool login1();//��½�û�����

    //ע����
    int detect1();//ע��ʱ���û�������Ϣ�ĺϷ���
    bool reg();//ע�ᵽ���ݿ��student����


////////////////�û�ʹ�ý���////////////////////////
    void hide2(bool flag);//���ת������
    void hide3(bool flag);
    void hide5(bool flag);
    void hide6(bool flag);
    void hide7(bool flag);
    void hide4(bool flag,int i);

///��ʼ������ʾ���
    void initpaint();//�ڶ�����ĳ�ʼ�����ƣ���������Ŀ¼����


//////////////�û���Ϣ����Ŀ¼
    //�����û�����������
    int cal_num_lend(QString name);//�����û���ѧ�ź���Ӧ�ļ��������˿ɽ�ı���
    void update_sure(QString name,QString num);//����ѧ�ź��鼮��ţ��ڽ��н���ȷ�Ϻ󣬶����ݿ���и���
    void update_xujie(QString name,QString num);//����ѧ�ź��鼮��ţ��ڽ�������ȷ�Ϻ󣬶����ݿ���и���
    void update_back(QString name,QString num);//����ѧ�ź��鼮��ţ��ڽ��й黹ȷ�Ϻ󣬶����ݿ���и���
    void update_pay(QString name);//����ѧ�ţ���ȷ�ϽɷѲ������student�����
    void update_add(QString name);//����ѧ�ţ���ȷ���û�ע������������student�����

    //�鿴�û���Ϣ���
    void update_deletes(QString name);//����ѧ�ţ���ִ��ɾ��ѧ����Ϣ�󣬶����ݿ���и���



///////ͼ����Ϣ����Ŀ¼
    //����鼮���
    bool addbook(QString str[]);//���������Ŀ�������Ϣ����book��������ݸ���

    //ɾ���鼮��Ϣ���
    void update_deleteb(QString name);//��ִ��ɾ����Ŀ֮�󣬶����ݿ�������ݸ���

private slots:
    void update_database();//�������ݿ�


///////////////��½����//////////////////////////
    //��½���
    void on_login_clicked();//��½��ť����
    void on_reg_clicked();//����ע������ڰ�ť
    void on_search_clicked();//��ѯ�鼮��ť
    //ע����
    void on_back_clicked();//���˵���ʼ��½���水ť
    void on_submit_clicked();//ע�����ʱ��ע��ȷ�ϰ�ť����


////////////////�û�ʹ�ý���////////////////////////
    ///��ʼ������ʾ���
    void message();


//////////////�û���Ϣ����Ŀ¼
    //�����û�����������
    void dispose_apply();//�����������Ĳۺ���
    void on_f11chose_activated(const QString &arg1);//���������򣬾���������������
    void on_result_pressed(const QModelIndex &index);//ȷ���û�ѡ���������¼������ʾ����
    void on_f11sure_clicked();//�û��ĵ�һ��ȷ�ϵ�������ť
    void on_f11sureall_clicked();//�û��ĵ�һ��ȷ�����д���ť
    void on_f11bsure_clicked();//�û��ĵڶ���ȷ�ϵ�������ť�������д���
    void on_f11bback_clicked();//�û��ĵڶ���ȷ�ϵ�������ȷ��ʱ��ȡ����ť
    void on_f11bsure1_clicked();//�û��ĵڶ���ȷ�����д���ť�������д���
    void on_f11bback1_clicked();//�û��ĵڶ���ȷ�����д���ȷ��ʱ��ȡ����ť


    //�鿴�û���Ϣ���
    void show_student();//��ʾѧ����Ϣ�Ĳۺ��������ڲ鿴��ɾ��ѧ��Ŀ¼
    void on_f12method_activated(const QString &arg1);//����������ȷ����ѯѧ����Ϣ�ķ�ʽ
    void on_f12sure_clicked();//��������Ͳ�ѯ��ʽ��ȷ��ѧ�������ȷ�ϰ�ť
    void on_f12delete_clicked();//ɾ������ѧ����Ϣ�ĵ�һ��ȷ�ϰ�ť���ڶ���ȷ��Ϊ�Ի���
    void on_f12delete1_clicked();//ɾ����ҵѧ����Ϣ�ĵ�һ��ȷ�ϰ�ť���ڶ���ȷ��Ϊ�Ի���


    //�鿴����Ա��Ϣ��Ρ��������û����ԣ�ֻ��һ��,���ɴ���
    void show_student1();//�����û�����//��ʾ����Ա��������Ϣ�Ĳۺ���������Ŀ¼����Ӧ
    void on_f12b2_clicked();//ȷ���޸Ĺ���Ա��Ϣ�����İ�ť���ڶ���ȷ��Ϊ�Ի���
    void on_f12b1_clicked();//ȷ��ɾ������Ա��Ϣ�����İ�ť���ڶ���ȷ��Ϊ�Ի���
    void on_f12b3_clicked();//ȷ�����ӹ���Ա��Ϣ�����İ�ť���ڶ���ȷ��Ϊ�Ի���


///////ͼ����Ϣ����Ŀ¼
    //����鼮���
    void change_book();//����鼮Ŀ¼��Ӧ�Ĳۺ��������ڳ�ʼ�����
    void on_f21b1_clicked();//ȷ�ϸ����û���������鼮�İ�ť�����úϷ��Լ��
    void on_f21b2_clicked();//ͨ���ļ�������Ŀ��ӵİ�ť���и�ʽҪ�󣬻���ʾ
    void on_f21b3_clicked();//������Ŀ��Ϣ�İ�ť����ѡ�񱣴�·��


    //ɾ���鼮��Ϣ���
    void delete_book();//ɾ���鼮��ϢĿ¼��Ӧ�ۺ��������ڳ�ʼ���
    void on_f22c1_activated(const QString &arg1);//����������ѡ���ѯͼ��ķ�ʽ
    void on_f22b1_2_clicked();//���ݲ�ѯ��ʽ���������ݲ���ͼ����Ϣ
    void on_f22b1_clicked();//ɾ���鼮��ȷ�ϰ�ť���ڶ���ȷ��Ϊ�Ի���
    void on_f22b2_clicked();//ɾ�������鼮����Ŀǰ���ҵ��ģ��ڶ���ȷ��Ϊ�Ի���

//////�û���Ϣ�޸�Ŀ¼
    void change_useinfo();//�޸��û���ϢĿ¼��Ӧ�Ĳۺ��������ڳ�ʼ�����
    void on_f3b_clicked();//ȷ���޸��û���Ϣ��ȷ�ϰ�ť���ڶ���ȷ��Ϊ�Ի���


/////���ؿ�ʼ������
    void returns();//���ؿ�ʼ����Ĳۺ���

private:
    Ui::MainWindow *ui;
    Ui::login1 *ui2;
    QSqlDatabase db;
    QString namenum;//��¼����Ա��
    float moneyz;//��¼Ƿ����
    int days;//��¼��������
    bool flag;
    QSqlTableModel *model;// �����ṩ��һ���ɶ�д���� SQL ��Ŀɱ༭����ģ��
    QSqlTableModel *model1;
    QSqlTableModel *model2;
    QTimer *timer1;//��ʱ��������ʵʱ�ĸ�������
    int recordnum;//��ѡ��¼��λ��
};

#endif // MAINWINDOW_H
