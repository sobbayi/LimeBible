/**
 LimeBible 2.0 series

 */
#ifndef UPDATEDLG_H
#define UPDATEDLG_H

#include <QDialog>
#include <QLabel>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QProgressDialog>
#include <QUrl>

#include <QLabel>
#include "globals.h"



class QNetworkReply;
class QFile;

class UpdateDlg : public QDialog
{
    Q_OBJECT
public:
    explicit UpdateDlg(QWidget *parent = 0);
    ~UpdateDlg();
    void startDownload(QUrl url);

private:
    QLabel *availUpdateLabel;
    QLabel *confirmUpdateLabel;
    QPlainTextEdit *updateInfoPlainTextEdit;
    QPushButton *yesPushButton;
    QPushButton *cancelPushButton;
    QNetworkAccessManager *manager;

    QProgressDialog *progressDialog;
    bool isUpToDate;
    QString dUrl;
    QFile *file;
    QNetworkReply *reply;

    QLabel *statusLabel; //to delete
   QUrl url;

signals:

public slots:
    void checkForUpdatesNow();
    void handleNetworkData(QNetworkReply *networkReply);
    void downloadFileReadyRead();
    void downloadFinished();
    void doDownload();
    void downloadFileProgress(qint64 bytesRead, qint64 totalBytes);
};

#endif // UPDATEDLG_H
