//#include <QtGui>
#include <QMessageBox>
//#include <stdio.h>
#include "limeres.h"


LimeRes::LimeRes()
{
 //   QMessageBox msgBox(QMessageBox::Information,
 //                      "My Res Library",
 //                      "Loaded from a working DLL",
 //                      QMessageBox::Ok);
//    msgBox.exec();
}

MY_EXPORT void add()
{
       QMessageBox msgBox(QMessageBox::Information,
                          "My Res Library",
                          "Loaded from a working DLL",
                          QMessageBox::Ok);
       msgBox.exec();
}
