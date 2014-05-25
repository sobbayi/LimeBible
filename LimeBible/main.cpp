/**
 LimeBible 2.0 series

 */
#include <QtGui/QApplication>
#include <QMessageBox>
#include <QResource>
#include "mainwnd.h"

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    if(!QResource::registerResource("bible_en.rcc"))
    {
        QMessageBox msgBox(QMessageBox::Critical,
                           "no resource",
                           "Resources are missing or Corrupt, Please reinstall application",
                           QMessageBox::Ok);
          msgBox.exec();
    }
    QResource::registerResource("limebible.rcc");
    MainWnd w;

    if(w.dbConn.openDataConn() == true)
    {

        w.dbConn.getBasicData("Genesis", 1, w.dbConn.db);
        w.bibleKjvTextEdit->setHtml(DataHelper::s);
        DataHelper::s.clear();
        w.showMaximized();
        return a.exec();
    }
    else{

        QMessageBox msgBox(QMessageBox::Critical,
                           "Limebible Database Connection Error",
                           "LimeBible will have to quit. Unable to open scriptures",
                           QMessageBox::Ok);
          msgBox.exec();
          return 0;

    }

}
