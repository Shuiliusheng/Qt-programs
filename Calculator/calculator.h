#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>
#include<QTimer>
namespace Ui {
class Calculator;
}

class Calculator : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit Calculator(QWidget *parent = 0);
    ~Calculator();
private slots:
    void eexit();
    void showarea();
    void add();
    void reduce();
    void multy();
    void divide();
    void showTime();
    void changeTime();
    void systemTime();
private:
    Ui::Calculator *ui;
    double result;
    int a,b,c;


};

#endif // CALCULATOR_H
