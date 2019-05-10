#ifndef SEARCHWINDOW_H
#define SEARCHWINDOW_H


#include <QMainWindow>
#include<QAction>
#include<QMenu>
#include<QToolBar>
#include <QtSql/QtSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include<QStandardItemModel>
namespace Ui {
class SearchWindow;
}

class SearchWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SearchWindow(QWidget *parent = 0);
    ~SearchWindow();
    void searchbook();
    void init();
private slots:
    void on_bsearch_clicked();

    void on_choose_activated(int index);

    void on_result_pressed(const QModelIndex &index);

private:
    Ui::SearchWindow *ui1;
    QSqlTableModel *model;

};
#endif // SEARCHWINDOW_H
