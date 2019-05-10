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

    void update_borrow();//���½���ʱ�ĳ�������

    void connectdb();//�������ݿ�
    void initdata();//��ʼ�����ݿ�

///////////////��½����//////////////////////////
    void hide1(bool flag);//hide ϵ�У��������ؿؼ���ʹ�ý�����Էֲ㣬������ʹ��̫�����
    //���ת������
    void hide(bool flag);//hide ϵ�У��������ؿؼ���ʹ�ý�����Էֲ㣬������ʹ��̫�����

    //��½���
    bool login1();//��½�û�����

    //ע����
    int detect1();//ע��ʱ���û�������Ϣ�ĺϷ���
    bool reg();//ע�ᵽ���ݿ��student����

////////////////�û�ʹ�ý���////////////////////////
    void hide2(bool flag);//���ת������
    void hide3(bool flag);
    void hide4(bool flag);

    ///��ʼ������ʾ���
    void initpaint();//�ڶ�����ĳ�ʼ������
    void showmoney();//��ʾǷ����
    void message();//�ڶ�����Ŀ�ʼ������ʾ�鱾������ʾ��Ϣ
    void cal_num_lend();//������û�Ŀǰ���Խ��ĵ��鱾����

    ///���Ĳ��
    bool detect_borrow();//���н����鼮ʱ������Ϸ��Լ����ܹ����ĵ��ж�
    bool detect_borrow1();//��һ�����ܹ����ĵĺϷ����жϣ���detect_borrow֮��


    ///������Ϣ���
    void gethistory();//��ȡ��ʷ������Ϣ

    ///�û��޸���Ϣ���
    void write(bool flag);//���޸��û���Ϣʱ��ȷ���ؼ�������
    void show_info();//��ȡ�û��ĸ�����Ϣ��������ʾ
    /////////////////////////////////////////////////

private slots:

    void update_database();//��̨���еĸ������ݿ⣬����ʱ�������
///////////////��½����//////////////////////////
    //��½���
    void on_login_clicked();//����ע���û��Ľ���
    void on_getin_clicked();//��½����ĵ�½��ť�Ĺ���
    void on_search_clicked();//��ѯ��ť�Ĺ���

    //ע����
    void on_submit_clicked();//ע��ҳ���ȷ�ϰ�ť�Ĺ���ʵ��
    void on_back_clicked();//��ע������˻ص�½����


////////////////�û�ʹ�ý���////////////////////////

    ///���Ĳ��
    void fborrow();//Ŀ¼�еĽ��Ĳ�����Ӧ�Ĳۺ���
    void on_f1search_clicked();//��ѯ��ť�Ĺ���
    void on_f1sure_clicked();//����ȷ�ϰ�ť�Ĺ���
    void on_f1delete_clicked();//ȡ�����ĵİ�ť�Ĳ���
    void on_f1sure1_clicked();//���ĵĵڶ���ȷ�ϰ�ť�Ĺ���

    ///������Ϣ���
    void fsearch();//Ŀ¼�еĲ�ѯ��ʷ��Ϣ�Ĳ�����Ӧ�Ĳۺ���
    void on_f2xujie_clicked();//���谴ť�Ĳ���
    void on_f2back_clicked();//�黹�鼮��ť�Ĳ���
    void on_f2pay_clicked();//�ɷѲ�����ť�Ĺ���

    ///�û��޸���Ϣ���
    void fchange();//Ŀ¼�е��޸��û���Ϣ�Ĳ�����Ӧ�Ĳۺ���
    void on_f3change_clicked();//��Ϣ�޸İ�ť�Ĺ���
    void on_f3delete_clicked();//���޸ĵĻ��˲���
    void on_f3sure_clicked();//�޸ĵ�ȷ�ϰ�ť

    void exit1();//���ؿ�ʼ����
private:
    Ui::MainWindow *ui;
    Ui::login1 *ui2;
    QSqlDatabase db;
    QString namenum;//��¼ѧ��
    float moneyz;//��¼Ƿ����
    int days;//��¼��������
    bool flag;//�����Ƿ��Ѿ�����ʹ�ý׶�
    int numbook;//�ɽ��鱾����
    QTimer *timer1;
    QSqlTableModel *model;// �����ṩ��һ���ɶ�д���� SQL ��Ŀɱ༭����ģ��
};

#endif // MAINWINDOW_H
