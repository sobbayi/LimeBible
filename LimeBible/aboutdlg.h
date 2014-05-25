/**
 LimeBible 1.0 series

 */

#ifndef ABOUTDLG_H
#define ABOUTDLG_H

#include <QDialog>
#include <QLabel>
#include "globals.h"



class AboutDlg : public QDialog
{
    Q_OBJECT
public:
   explicit AboutDlg(QWidget *parent = 0);

private:

    QLabel *limeBibleLabel;
    QLabel *versionLabel;
    QLabel *copyrightLabel;
    QLabel *homepageLabel;
    QLabel *developerLabel;
    QLabel *warning1Label;
    QLabel *warning2Label;
    QLabel *supportLabel;
    QLabel *spacer1Label;
    QLabel *spacer2Label;
    QPushButton *okPushButton;

signals:

public slots:

};

#endif // ABOUTDLG_H
