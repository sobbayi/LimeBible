/**
 LimeBible 2.0 series

 */
#include <QGridLayout>
#include <QtNetwork>
#include <QUrl>
#include <QMessageBox>
//#include <cstdlib>
#include <QProcess>
#include "updatedlg.h"

UpdateDlg::UpdateDlg(QWidget *parent) :
    QDialog(parent)
{


 isUpToDate = true;
 QLabel *blank2Label = new QLabel("");
 QLabel *blank3Label = new QLabel("");
 QLabel *blank4Label = new QLabel("");
 availUpdateLabel = new QLabel(tr("Please wait as we check for available updates"));
 confirmUpdateLabel = new QLabel(tr(" "));
 updateInfoPlainTextEdit = new QPlainTextEdit();
 updateInfoPlainTextEdit->setReadOnly(true);
 yesPushButton = new QPushButton(tr("Yes"));
 yesPushButton->setVisible(false);
 connect(yesPushButton, SIGNAL(clicked()), this, SLOT(doDownload()));
 cancelPushButton = new QPushButton(tr("Cancel"));
 connect(cancelPushButton, SIGNAL(clicked()), this, SLOT(close()));


 statusLabel = new QLabel;

 setFixedSize(UPDATE_WIDTH, UPDATE_HEIGHT );
 QGridLayout *mainLayout = new QGridLayout;
 mainLayout->addWidget(availUpdateLabel, 0, 0, 1, 4);
 mainLayout->addWidget(blank2Label, 1, 0, 1, 4);
 mainLayout->addWidget(updateInfoPlainTextEdit, 2, 0, 1, 4);
 mainLayout->addWidget(blank3Label, 3, 0, 1, 4);
 mainLayout->addWidget(confirmUpdateLabel , 4, 0, 1, 4);
 mainLayout->addWidget(blank4Label, 5, 0, 1, 4);
 mainLayout->addWidget(yesPushButton, 6, 2);
 mainLayout->addWidget(cancelPushButton, 6, 3);
 setWindowFlags(Qt::FramelessWindowHint);
 setLayout(mainLayout);
 setWindowFlags(Qt::Dialog);
 setWindowTitle(tr("LimeBible Updates"));

}

UpdateDlg::~UpdateDlg()
{
}

void UpdateDlg::checkForUpdatesNow()
{

    QNetworkRequest request;
   // request.setUrl(QUrl("http://localhost/limebible/distrib/update.php"));
    request.setUrl(QUrl("http://www.limebible.com/distrib/update.php"));
    request.setRawHeader("User-Agent", "LimeBible 1.3.0 Windows");

    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(handleNetworkData(QNetworkReply*)));

    manager->get(request);

}

void UpdateDlg::handleNetworkData(QNetworkReply *networkReply)
{
    QUrl url = networkReply->url();
        if (!networkReply->error()) {
            QString ver;
            QString filesize;
            QString curr;
            QString det;
            QString rating;

            QByteArray response(networkReply->readAll());
            QXmlStreamReader xml(response);
                   while (!xml.atEnd()) {
                       xml.readNext();
                       if(xml.name() == "version"){
                           ver = xml.readElementText();
                       }
                       if(xml.name() == "filesize"){
                           filesize = xml.readElementText();
                       }
                       if(xml.name() == "current"){
                           curr = xml.readElementText();
                           if(curr.compare("yes") == 0)
                              isUpToDate = true;
                           else
                              isUpToDate = false;
                       }
                       if(xml.name() == "details"){
                           det = xml.readElementText();
                       }
                       if(xml.name() == "downloadUrl"){
                           dUrl = xml.readElementText();
                         }
                       if(xml.name() == "rating"){
                           rating = xml.readElementText();
                         }

                   }

                   if (xml.hasError()) {
             availUpdateLabel->setText(tr("Error with update file"));
             updateInfoPlainTextEdit->setPlainText(tr("There seems to be a problem with the update file. "
                                                      "No action on your part is required, it will be corrected automatically."
                                                      "If the problem persists you may go directly to www.sobbayi.com and download "
                                                      "the latest version of LimeBible from there."));
             confirmUpdateLabel->setText(tr("Try and check for available updates later"));
             yesPushButton->setVisible(false);
                      }
                   else{


                       if(isUpToDate){

                           updateInfoPlainTextEdit->setPlainText(tr("No details to show"));
                           availUpdateLabel->setText(tr("You are using the latest version of LimeBible"));
                           confirmUpdateLabel->setText(tr(" "));
                           yesPushButton->setVisible(false);
                           cancelPushButton->setText(tr("Ok"));
                       }
                       else
                       {
                           QString *info = new QString(tr("The latest available version is "));
                           info->append(tr(" \n\n"));
                           info->append(ver);
                           info->append(tr(" \n"));
                           info->append(filesize);
                           info->append(tr(" \n"));
                           info->append(rating);
                           info->append(tr(" \n\n"));
                           info->append(det);


                           updateInfoPlainTextEdit->setPlainText(*info);
                           availUpdateLabel->setText(tr("A new version of LimeBible is available"));
                           confirmUpdateLabel->setText(tr("Do you want to download and install this update?"));
                           yesPushButton->setText(tr("Yes"));
                           yesPushButton->setVisible(true);

                       }
                   }

        }
        else
        {
            availUpdateLabel->setText(tr("No Connection to Server"));
            updateInfoPlainTextEdit->setPlainText(tr("There seems to be a problem connecting to our servers. "
                                                     "Please check your network connection."));
            confirmUpdateLabel->setText(tr("Try and check for available updates later"));
            yesPushButton->setVisible(false);

        }

        networkReply->deleteLater();

}

void UpdateDlg::startDownload(QUrl url)
{
    reply = manager->get(QNetworkRequest(url));
    connect(reply, SIGNAL(finished()),
                 this, SLOT(downloadFinished()));
    connect(reply, SIGNAL(readyRead()),
                 this, SLOT(downloadFileReadyRead()));
    connect(reply, SIGNAL(downloadProgress(qint64,qint64)),
                 this, SLOT(downloadFileProgress(qint64,qint64)));
}

void UpdateDlg::downloadFileProgress(qint64 bytesRead, qint64 totalBytes)
{
    progressDialog->setMaximum(totalBytes);
    progressDialog->setValue(bytesRead);
}

void UpdateDlg::downloadFinished()
 {

    QString fileName;

     QVariant redirectionTarget = reply->attribute(QNetworkRequest::RedirectionTargetAttribute);
     if (reply->error()) {
         file->remove();
         QMessageBox::information(this, tr("Download LimeBible Updates..."),
                                  tr("Download failed: %1.")
                                  .arg(reply->errorString()));

     }  else {
        fileName = QFileInfo(QUrl(dUrl).path()).fileName();

     }

     progressDialog->hide();
     file->flush();
     file->close();
     reply->deleteLater();
     reply = 0;
     delete file;
     file = 0;
     QString program = "";

      program.append(QDir::tempPath());
      program.append("/");
      program.append(fileName);
      QProcess *myProcess = new QProcess();
      myProcess->start(program);
       connect(this,SIGNAL(destroyed()),this->parent(),SLOT(close()));
      close();


 }

void UpdateDlg::doDownload()
{
    url = dUrl;
     QMessageBox msgBox;
     msgBox.setWindowTitle(tr("LimeBible Update Warning"));
     msgBox.setText(tr("This action will download the update, shutdown LimeBible and start the update process. "
                       "Any unsaved work will be lost. Remember, you can always run this updater any other time."
                       ));
     msgBox.setInformativeText(tr("Do you want to Proceed with the Update?"));
     msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
     msgBox.setDefaultButton(QMessageBox::Yes);
     msgBox.setIcon(QMessageBox::Warning);
     int ret = msgBox.exec();
     if(ret){

         switch(ret)
          {
             case QMessageBox::Yes :
            {
                 // Save was clicked.. handle it


              QFileInfo fileInfo(url.path());
              QString fileName = fileInfo.fileName();
              QString fullPath = "";

              fullPath.append(QDir::tempPath());
              fullPath.append("/");
              fullPath.append(fileName);
              if (fileName.isEmpty())
                  fileName = "";

              if (QFile::exists(fullPath)) {
                    QFile::remove(fullPath);
              }

              file = new QFile(fullPath);

              if (!file->open(QIODevice::WriteOnly)) {
                  QMessageBox::information(this, tr("Download LimeBible Updates..."),
                                           tr("Unable to save the file %1: %2.")
                                           .arg(fileName).arg(file->errorString()));
                  delete file;
                  file = 0;
                  return;
              }
              progressDialog = new QProgressDialog(this);
              progressDialog->setWindowTitle(tr("Downloading..."));
              progressDialog->setLabelText(tr("Download LimeBible Updates..."));

              // schedule the request
              startDownload(url);
                }
             break;
             case QMessageBox::No :

              msgBox.close();
              close();

             break;
             default:
                  // should never be reached
             break;
           }
     }

}

void UpdateDlg::downloadFileReadyRead()
 {
     // this slot gets called every time the QNetworkReply has new data.
     // We read all of its new data and write it into the file.
     // That way we use less RAM than when reading it at the finished()
     // signal of the QNetworkReply
     if (file)
         file->write(reply->readAll());
 }
