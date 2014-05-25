/**
 LimeBible 2.0 series

 */
#include <QtGui>
#include "aboutdlg.h"

AboutDlg::AboutDlg(QWidget *parent):
    QDialog(parent)
{

    limeBibleLabel = new QLabel(tr("LimeBible"));
    limeBibleLabel->setPixmap(QPixmap(":/images/limebible-logo.png"));
    limeBibleLabel->setStyleSheet(tr(
    "font: 75 20pt \"Kristen ITC\";background-color: rgba(85, 170, 0, 0);"
    ));
    limeBibleLabel->setAlignment(Qt::AlignCenter);
    versionLabel = new QLabel(tr("Version 1.3.0.064 (Windows)"));
    versionLabel->setAlignment(Qt::AlignCenter);
    versionLabel->setStyleSheet(tr( "background-color: rgba(85, 170, 0, 0);" ));

    spacer2Label = new QLabel(tr(
    "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">"
    "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">"
    "p, li { white-space: pre-wrap; }"
    "</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">"
    "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">"
    "<a href=\"http://www.limebible.com\"><span style=\" font-size:8pt; font-weight:600; text-decoration: underline; color:#55007f;\">"
    "www.limebible.com</span></a></p></body></html>"
                                  ));
    spacer2Label->setStyleSheet(tr( "background-color: rgba(85, 170, 0, 0);" ));
    spacer2Label->setAlignment(Qt::AlignCenter);

    copyrightLabel = new QLabel(tr("Copyright (c) 2011 - 2012, Sobbayi Interactive"));
    copyrightLabel->setAlignment(Qt::AlignCenter);
    copyrightLabel->setStyleSheet(tr( "background-color: rgba(85, 170, 0, 0);" ));

  //  spacer1Label = new QLabel(tr(" "));
  //  spacer1Label->setStyleSheet(tr( "background-color: rgba(85, 170, 0, 0);" ));


    homepageLabel = new QLabel(tr(
    "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">"
    "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">"
    "p, li { white-space: pre-wrap; }"
    "</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">"
    "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">"
    "<a href=\"http://www.sobbayi.com\"><span style=\" font-size:8pt; font-weight:600; text-decoration: underline; color:#55007f;\">"
    "www.sobbayi.com</span></a></p></body></html>"
    ));
    homepageLabel->setAlignment(Qt::AlignCenter);
    homepageLabel->setStyleSheet(tr( "background-color: rgba(85, 170, 0, 0);" ));
    homepageLabel->setOpenExternalLinks(true);
    developerLabel = new QLabel(tr("Development: Sobbayi Interactive, Some Bible Resources: o-bible.com"));
    developerLabel->setAlignment(Qt::AlignCenter);
    developerLabel->setStyleSheet(tr( "background-color: rgba(85, 170, 0, 0);" ));



    warning1Label = new QLabel(tr(
    "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">"
     "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">"
     "p, li { white-space: pre-wrap; }"
     "</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">"
     "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">"
     "<span style=\" font-size:8pt; font-weight:600;\">LimeBible is free software. It is illigal to sell copies, but if you find</span></p></body></html>"
    ));
    warning1Label->setAlignment(Qt::AlignCenter);
    warning1Label->setStyleSheet(tr( "background-color: rgba(85, 170, 0, 0);" ));
    warning2Label = new QLabel(tr(
    "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">"
     "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">"
     "p, li { white-space: pre-wrap; }"
     "</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">"
     "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">"
     "<span style=\" font-size:8pt; font-weight:600;\">it useful and want to support its development please visit:</span></p></body></html>"
    ));
    warning2Label->setAlignment(Qt::AlignCenter);
    warning2Label->setStyleSheet(tr( "background-color: rgba(85, 170, 0, 0);" ));
    supportLabel = new QLabel(tr(
    "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">"
     "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">"
     "p, li { white-space: pre-wrap; }"
     "</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">"
     "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">"
     "<a href=\"http://www.limebible.com/support/\"><span style=\" font-size:8pt; font-weight:600;"
    "text-decoration: underline; color:#00007f;\">www.limebible.com/support</span></a></p></body></html>"
    ));
    supportLabel->setAlignment(Qt::AlignCenter);
    supportLabel->setStyleSheet(tr( "background-color: rgba(85, 170, 0, 0);" ));
    supportLabel->setOpenExternalLinks(true);
    okPushButton = new QPushButton(tr("Ok"));
    connect(okPushButton, SIGNAL(clicked()), this, SLOT(accept()));

    setFixedSize(ABOUT_WIDTH, ABOUT_HEIGHT );
    setStyleSheet(tr("background-color: rgba(189, 221, 165, 255);"
     ));

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(limeBibleLabel, 0, 0, 1, 4);
    mainLayout->addWidget(versionLabel, 1, 0, 1, 4);
    mainLayout->addWidget(spacer2Label, 2, 0, 1, 4);
   // mainLayout->addWidget(spacer1Label, 3, 0, 1, 4);
    mainLayout->addWidget(copyrightLabel, 4, 0, 1, 4);
    mainLayout->addWidget(homepageLabel, 5, 0, 1, 4);
    mainLayout->addWidget(developerLabel, 6, 0, 1, 4);
    mainLayout->addWidget(warning1Label, 7, 0, 1, 4);
    mainLayout->addWidget(warning2Label, 8, 0, 1, 4);
    mainLayout->addWidget(supportLabel, 9, 0, 1, 4);
    mainLayout->addWidget(okPushButton, 10, 3);
    setWindowFlags(Qt::SplashScreen);
    setLayout(mainLayout);


}


