
//#include <QGridLayout>
//#include <QAction>
//#include <QToolBar>
//#include <QPrintDialog>
#include <QWebView>
#include "helpwnd.h"

HelpWnd::HelpWnd(QWidget *parent) :
    QMainWindow(parent)
{
   // QWidget *widget = new QWidget;
   // setCentralWidget(widget);

    setWindowTitle(tr("LimeBible Help"));
    setBaseSize(320, 400);


   // QGridLayout *layout = new QGridLayout;
    view  = new QWebView(this);
    view->setAttribute(Qt::WA_DeleteOnClose);
    setCentralWidget(view);



  //  QAction *backAct = new QAction(QIcon(":/images/resultset_previous.png"), tr("Back"), this);
  //  connect(backAct, SIGNAL(triggered()), this, SLOT(back()));

  //  QAction *forwardAct = new QAction(QIcon(":/images/resultset_next.png"),tr("Forward"), this);
  //  connect(forwardAct, SIGNAL(triggered()), this, SLOT(forward()));

  //  QAction *printAct = new QAction(QIcon(":/images/printer32.png"),tr("Print"), this);
  //  connect(printAct, SIGNAL(triggered()), this, SLOT(print()));

  //  QToolBar *toolBar;
  //  toolBar = addToolBar(tr("Navigation"));
 //   toolBar->addAction(backAct);
  //  toolBar->addAction(forwardAct);
  //  toolBar->addSeparator();
  //  toolBar->addAction(printAct);
  //  toolBar->addSeparator();

   // layout->addWidget(view, 0, 0);
    //widget->setLayout(layout);

    view->load(QUrl("docs/index.html"));

    view->show();


}

HelpWnd::~HelpWnd()
{
view->deleteLater();
}

//void HelpWnd::back()
//{
//  view->back();
//}

//void HelpWnd::forward()
//{
//    view->forward();
//}

//void HelpWnd::print()
//{
//#ifndef QT_NO_PRINTER
//    QPrinter *printer = new QPrinter();
//    QPrintDialog printDialog(printer, view);
//    if (printDialog.exec() == QDialog::Accepted) {
//        // print ...
//        view->print(printer);

//    }
//    delete printer;
//    printer = NULL;

//#endif
//}

