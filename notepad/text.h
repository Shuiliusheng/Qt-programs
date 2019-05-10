#ifndef TEXT_H
#define TEXT_H

#include<QWidget>
#include<QDebug>
#include<QTextEdit>
#include<QPushButton>
#include "textedit.h"
class Text : public QWidget
{
    Q_OBJECT
public:
    Text(QWidget *parent = 0);
    QWidget *widget;
    QPushButton *open;
    QPushButton *close;
    TextEdit *edit;

    int coding;

    void init(int x,int y,int w,int h, QString filename);

    void resize_ui(int x,int y,int w,int h);

    int getblock(char *str,int place);

    void set_coding(bool flag);
public slots:
    void open_file1();

    void close_tab1();

    void text_change();

    void cursor_change();

signals:
    void nameChanged(QString name);
public:
    int flag;
    int last;

};

#endif // TEXT_H
