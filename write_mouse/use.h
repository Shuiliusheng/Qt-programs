#ifndef USE_H
#define USE_H

#include <QMainWindow>
#include "run.h"
namespace Ui {
class Use;
}

class Use : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit Use(QWidget *parent = 0);
    ~Use();
    Run runfile;
private slots:
    void on_pushButton_clicked();

    void on_start_clicked();

private:
    Ui::Use *ui;
    char filename[200];
    int sleep;
    int circle;
};

#endif // USE_H
