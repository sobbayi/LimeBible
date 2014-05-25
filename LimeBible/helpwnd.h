#ifndef HELPWND_H
#define HELPWND_H

#include <QMainWindow>
//#include <QPrinter>
#include <QWebView>

class HelpWnd : public QMainWindow
{
    Q_OBJECT
public:
    explicit HelpWnd(QWidget *parent = 0);
    ~HelpWnd();
    QWebView *view;

private:

   // void creatToolBar();
   // void createActions();

signals:

public slots:
   // void back();
   // void forward();
   // void print();

};

#endif // HELPWND_H
