#ifndef TEXTEDIT_H
#define TEXTEDIT_H

#include <QTextEdit>
#include <QTextCursor>
#include <QKeyEvent>
#include <QTextCharFormat>
class TextEdit :public QTextEdit
{
    Q_OBJECT
public:
    TextEdit(QWidget *parent = 0);
    void find_str(int &place,int &max,char str1[]);
    bool detect_str(char *str);
    bool over_char(char c);
    int find_char(int place, char c);
    int find_char_forward(int place, char c);
    int getblock(char *str,int place);

    void color_str(char str[],char backc,char nextc,int rawplace, QColor color);

    void color_str_fore(char str[],char nextc,int rawplace, QColor color);

    void color_str_back(char str[],char backc,int rawplace, QColor color);

    void set_use(bool flag);

private slots:
    void keyPressEvent(QKeyEvent *event);
    void textchanged();
    void cursorpositionchanged();

private:
    int flag1;
    int flag;
    int last;
    bool useflag;
    QTextCharFormat format;
};

#endif // TEXTEDIT_H
