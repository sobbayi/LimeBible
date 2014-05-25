/**
 LimeBible 2.0 series

 */
#include <QLabel>
#include <QStatusBar>
#include <QToolButton>
#include <QMenuBar>
#include <QToolBar>
#include <QMenu>
#include <QAction>
#include <QMessageBox>
#include <QList>
#include <QGridLayout>
#include <QFileDialog>
#include <QPrintDialog>
#include <QPrintPreviewDialog>
#include <Qprinter>
#include <QFont>
#include <QFontDialog>
#include <QTextStream>
#include <QDesktopServices>
#include <QTextCursor>
#include <QTextList>
#include <QTextListFormat>
#include "globals.h"
#include "mainwnd.h"
#include "aboutdlg.h"
#include "updatedlg.h"
#include "datahelper.h"
//#include "limeres.h"

MainWnd::MainWnd(QWidget *parent)
    : QMainWindow(parent)
{
    setBaseSize(BASE_WIDTH, BASE_HEIGHT);
    setMinimumSize(BASE_WIDTH, BASE_HEIGHT);
    setWindowTitle(tr("Lime Bible"));
    setWindowIcon(QIcon(QPixmap(":/images/limebible-icon.png")));

    // keep this here to prevent a segfault there is an action that does a check
    // on it during initialization
    studyNotesTextEdit = new QTextEdit;

    createFontCombo();
    createActions();
  //  createToolBarMenus();
    createMenuBar();
    createToolBar();
    createStatusBar();


    splitter = new QSplitter;
    setCentralWidget(splitter);
    createOutLiner();

    QGridLayout *outlinerLayout = new QGridLayout;
    outlinerLayout->setContentsMargins(MAIN_MARGIN_LEFT, MAIN_MARGIN_TOP, MAIN_MARGIN_RIGHT, MAIN_MARGIN_BOTTOM);

    QGridLayout *bibleLayout = new QGridLayout;
    bibleLayout->setContentsMargins(MAIN_MARGIN_LEFT, MAIN_MARGIN_TOP, MAIN_MARGIN_RIGHT, MAIN_MARGIN_BOTTOM);

    QGridLayout *notesLayout = new QGridLayout;
    notesLayout->setContentsMargins(MAIN_MARGIN_LEFT, MAIN_MARGIN_TOP, MAIN_MARGIN_RIGHT, MAIN_MARGIN_BOTTOM);

    QGridLayout *bibleInTabLayout = new QGridLayout;
    bibleInTabLayout->setContentsMargins(MAIN_MARGIN_LEFT, 0, MAIN_MARGIN_RIGHT, 0);

    QGridLayout *notesInTabLayout = new QGridLayout;
    notesInTabLayout->setContentsMargins(MAIN_MARGIN_LEFT, 0, MAIN_MARGIN_RIGHT, 0);

    QWidget    *outlinerWidget = new QWidget;

    QWidget    *mainBibleWidget = new QWidget;
    QWidget    *mainNotesWidget = new QWidget;
    QWidget    *bibleTabsWidget = new QWidget;
    QWidget    *studyNotesTabWidget = new QWidget;

    bibleKjvTextEdit = new QTextEdit;
    bibleKjvTextEdit->setFont(QFont("Georgia", 12));
    bibleKjvTextEdit->setReadOnly(true);

    connect(bibleKjvTextEdit, SIGNAL(copyAvailable(bool)), this, SLOT(bibleTextSelected(bool)));


    studyNotesTextEdit->setFont(QFont("Georgia", 12));
    connect(studyNotesTextEdit, SIGNAL(textChanged()), this, SLOT(notesHouseKeeping()));
    connect(studyNotesTextEdit, SIGNAL(copyAvailable(bool)), this, SLOT(notesSelections(bool)));
    connect(studyNotesTextEdit, SIGNAL(redoAvailable(bool)), this, SLOT(greyUnGreyRedo(bool)));
    connect(studyNotesTextEdit, SIGNAL(undoAvailable(bool)), this, SLOT(greyUngreyUndo(bool)));
    connect(studyNotesTextEdit, SIGNAL(selectionChanged()), this, SLOT(studyNotesSelChanged()));

    bibleTabs = new QTabWidget;
    bibleInTabLayout->addWidget(bibleEditToolBar, 0, 0);
    bibleInTabLayout->addWidget(bibleKjvTextEdit, 1, 0);
    bibleTabsWidget->setLayout(bibleInTabLayout);
    bibleTabs->addTab(bibleTabsWidget, "KJV");


    notesTabs = new QTabWidget;
    notesInTabLayout->addWidget( notesLayoutToolBar, 0, 0);
    notesInTabLayout->addWidget( notesFontToolBar, 1, 0);
    notesInTabLayout->addWidget( studyNotesTextEdit, 2, 0);
    studyNotesTabWidget->setLayout(notesInTabLayout);
    notesTabs->addTab(studyNotesTabWidget, "Study Notes");


 //   outlinerLayout->addWidget(oulinerTitleLabel, 0, 0);
    outlinerLayout->addWidget(bibleBooksTreeWidget, 0, 0);
    outlinerWidget->setLayout(outlinerLayout);

  //  bibleLayout->addWidget(bibleTitleLabel, 0, 0);
    bibleLayout->addWidget(bibleTabs, 0, 0);
    mainBibleWidget->setLayout(bibleLayout);

   // notesLayout->addWidget(notesTitleLabel, 0, 0);
    notesLayout->addWidget(notesTabs,0, 0);
    mainNotesWidget->setLayout(notesLayout);

    shouldSaveBool = false;
    doTextChanges  = true;
    QList<int> parts;
    parts.append((this->width()/20)*3);
    parts.append((this->width()/20)*12);
    parts.append((this->width()/20)*5);
    splitter->addWidget(outlinerWidget);
    splitter->addWidget(mainBibleWidget);
    splitter->addWidget(mainNotesWidget);
    splitter->setSizes(parts);


}

void MainWnd::bibleTextSelected(bool b)
{
    if(b)
    {
    copySelectionAct->setEnabled(true);
    }

    else
    {
     copySelectionAct->setEnabled(false);
    }
}

void MainWnd::studyNotesSelChanged()
{
     if(doTextChanges)
     {
         fontComboBox->setCurrentFont(studyNotesTextEdit->currentFont());

         int f = studyNotesTextEdit->currentFont().pointSize();
         int s = fontSizeComboBox->count();
         int j;

                  for( int i = 0 ; i < s ; i++ )
                  {
                      fontSizeComboBox->setCurrentIndex(i);
                      j = fontSizeComboBox->currentText().toInt();
                      if(j == f)
                            break;
                  }

     }


             if(studyNotesTextEdit->currentFont().weight() == QFont::Bold)
                boldAct->setChecked(true);
                 else
                boldAct->setChecked(false);

             if(studyNotesTextEdit->currentFont().style() == QFont::StyleItalic)
                italicAct->setChecked(true);
                 else
                italicAct->setChecked(false);

             if(studyNotesTextEdit->currentFont().underline() == true)
                 underlineAct->setChecked(true);
                  else
                 underlineAct->setChecked(false);

}

void MainWnd::checkForUpdates()
{

         UpdateDlg *updateDialog = new UpdateDlg(this);
         updateDialog->setAttribute(Qt::WA_DeleteOnClose);
         updateDialog->show();
         updateDialog->raise();
         updateDialog->checkForUpdatesNow();

}

void MainWnd::notesHouseKeeping()
{
    shouldSaveBool = true;
    if(studyNotesTextEdit->toPlainText().length() > 0)
    {
    clearAct->setEnabled(true);
    selectAllAct->setEnabled(true);
    }

    else
    {
     clearAct->setEnabled(false);
    selectAllAct->setEnabled(false);
    }

}

void MainWnd::greyUngreyUndo(bool b)
{
    if(b)
      undoAct->setEnabled(true);
    else
      undoAct->setEnabled(false);
}

void MainWnd::greyUnGreyRedo(bool b)
{
    if(b)
        redoAct->setEnabled(true);
    else
        redoAct->setEnabled(false);
}


void MainWnd::notesSelections(bool b)
{

    if(b)
    {
    copyAct->setEnabled(true);
    cutAct->setEnabled(true);
    doTextChanges = false;
    }

    else
    {
     copyAct->setEnabled(false);
     cutAct->setEnabled(false);
     doTextChanges = true;
    }

}


void MainWnd::saveNotesFile()
{
    currOpenSavedFile = QFileDialog::getSaveFileName(this, tr("Save File"),
                       currOpenFile, tr("LimeBible Study Notes (*.lbf);;All Files (*.*)"));

                QFile file(currOpenSavedFile);
            if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
                {}
            else{
                QTextStream out(&file);
                QString  entireFile;
                entireFile = studyNotesTextEdit->toHtml();
                out << entireFile;
                }
            shouldSaveBool = false;
}

void MainWnd::newStudyNote()
{

        if(!shouldSaveBool)
        {
            if(studyNotesTextEdit->toPlainText().length() > 0)
                        studyNotesTextEdit->clear();
            redoAct->setEnabled(false);
            undoAct->setEnabled(false);
        }
        else
        {
            QMessageBox msgBox;
            msgBox.setText(tr("The text in the current study note has been modified."));
            msgBox.setInformativeText(tr("Do you want to save your changes?"));
            msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
            msgBox.setDefaultButton(QMessageBox::Save);
            msgBox.setIcon(QMessageBox::Warning);
            int ret = msgBox.exec();

                        switch(ret)
                {
                    case QMessageBox::Save:{
                    // Save was clicked.. handle it
                      saveNotesFile();
                      studyNotesTextEdit->clear();
                      shouldSaveBool = false;
                      redoAct->setEnabled(false);
                      undoAct->setEnabled(false);
                }
                break;
                case QMessageBox::Discard:
                        studyNotesTextEdit->clear();
                        shouldSaveBool = false;
                        redoAct->setEnabled(false);
                        undoAct->setEnabled(false);
                break;
                case QMessageBox::Cancel:
                        msgBox.close();

                break;
                default:
                    // should never be reached
                break;
                  }

        }

}

void MainWnd::openStudyNote()
{


  if(shouldSaveBool)
  {
      QMessageBox msgBox;
      msgBox.setText(tr("The text in the current study note has been modified."));
      msgBox.setInformativeText(tr("Do you want to save your changes?"));
      msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
      msgBox.setDefaultButton(QMessageBox::Save);
      msgBox.setIcon(QMessageBox::Warning);
      int ret = msgBox.exec();

          switch(ret)
          {
              case QMessageBox::Save:{
              // Save was clicked.. handle it
                saveStudyNoteAs();
                shouldSaveBool = false;
                openLimeBibleStudyNote();
          }
          break;
          case QMessageBox::Discard:
                  shouldSaveBool = false;
                  openLimeBibleStudyNote();
          break;
          case QMessageBox::Cancel:
                  msgBox.close();
          break;
          default:
              // should never be reached
          break;
            }

  }
  else
  {
      openLimeBibleStudyNote();
  }

}

void MainWnd::openLimeBibleStudyNote()
{

    currOpenFile = QFileDialog::getOpenFileName(this,
         tr("Open LimeBible Study Notes"), NULL, tr("LimeBible Study Notes (*.lbf)"));

          if (!currOpenFile.isEmpty())
          {
              QFile file(currOpenFile);
         if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
              { }
                else
                {
                    QTextStream in(&file);
                    if(studyNotesTextEdit->toPlainText().length() > 0)
                        studyNotesTextEdit->clear();
                    redoAct->setEnabled(false);
                    undoAct->setEnabled(false);
                    while (!in.atEnd()) {
                    QString line = in.readLine();
                    studyNotesTextEdit->setHtml(line);
                       }
                    shouldSaveBool = false;
                }
          }

}

void MainWnd::closeStudyNote()
{

    if(shouldSaveBool)
    {

        QMessageBox msgBox;
        msgBox.setWindowTitle(tr("LimeBible Warning"));
        msgBox.setText(tr("The text in the current study note has been modified."));
        msgBox.setInformativeText(tr("Do you want to save your changes?"));
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);
        msgBox.setIcon(QMessageBox::Warning);
        int ret = msgBox.exec();
        if(ret){

            switch(ret)
             {
              case QMessageBox::Save:
                // Save was clicked.. handle it
                 saveNotesFile();
                 studyNotesTextEdit->clear();
                 shouldSaveBool = false;
                 redoAct->setEnabled(false);
                 undoAct->setEnabled(false);
              break;
              case QMessageBox::Discard:
                 studyNotesTextEdit->clear();
                 shouldSaveBool = false;
                 redoAct->setEnabled(false);
                 undoAct->setEnabled(false);
              break;
              case QMessageBox::Cancel:
                 msgBox.close();

              break;
              default:
                 // should never be reached
              break;
             }


        }
    }
    else
    {
        if(studyNotesTextEdit->toPlainText().length() > 0)
            studyNotesTextEdit->clear();
        redoAct->setEnabled(false);
        undoAct->setEnabled(false);
    }



}

void MainWnd::saveStudyNote()
{

    if (!currOpenSavedFile.isEmpty())
        {
            QFile file(currOpenSavedFile);
            if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
                    {}
            else{
               QTextStream out(&file);
               QString  text;
               text = studyNotesTextEdit->toHtml();
               out << text;
               shouldSaveBool = false;
            }
        }
        else
        {
             saveNotesFile();
        }

}

void MainWnd::saveStudyNoteAs()
{
    saveNotesFile();
}

void MainWnd::previewStudyNote()
{
#ifndef QT_NO_PRINTER
    QPrinter printer(QPrinter::HighResolution);
    QPrintPreviewDialog preview(&printer, studyNotesTextEdit);
    preview.setWindowFlags ( Qt::Window );
    connect(&preview, SIGNAL(paintRequested(QPrinter *)), SLOT(printPreviewNotes(QPrinter *)));
    preview.exec();
#endif
}

void MainWnd::printPreviewNotes(QPrinter *printer)
{
#ifndef QT_NO_PRINTER
        studyNotesTextEdit->print(printer);
#endif
}

void MainWnd::printStudyNote()
{

#ifndef QT_NO_PRINTER
    QPrinter *printer = new QPrinter();
    QPrintDialog printDialog(printer, studyNotesTextEdit);
    if (printDialog.exec() == QDialog::Accepted) {
        // print ...
        studyNotesTextEdit->print(printer);

    }
    delete printer;
    printer = NULL;

#endif

}

void MainWnd::searchBible()
{

    searchDlg = new SearchDlg(this);
    searchDlg->show();
    searchDlg->raise();
}

void MainWnd::copySelectedVerses()
{

    QTextCursor cursor = bibleKjvTextEdit->textCursor();
    QTextBlockFormat block;

    cursor.select(QTextCursor::BlockUnderCursor);
    bibleKjvTextEdit->setTextCursor(cursor);
    bibleKjvTextEdit->copy();

}

void MainWnd::printChapters()
{
#ifndef QT_NO_PRINTER
    QPrinter *printer = new QPrinter();
    QPrintDialog printDialog(printer, bibleKjvTextEdit);
    if (printDialog.exec() == QDialog::Accepted) {
        // print ...
        bibleKjvTextEdit->print(printer);

    }
    delete printer;
    printer = NULL;

#endif

}

void MainWnd::undoChange()
{
studyNotesTextEdit->undo();
}

void MainWnd::redoChange()
{
    studyNotesTextEdit->redo();
}

void MainWnd::copyNotesSelection()
{
    studyNotesTextEdit->copy();
}

void MainWnd::cutNotesSelection()
{
 studyNotesTextEdit->cut();
}

void MainWnd::pasteFromClipboard()
{
    if(studyNotesTextEdit->canPaste())
    studyNotesTextEdit->paste();

}

void MainWnd::clearStudyNotesText()
{

    if(shouldSaveBool)
    {

        QMessageBox msgBox;
        msgBox.setWindowTitle(tr("LimeBible Warning"));
        msgBox.setText(tr("The current study note has been modified and proceeding with this action will delete all your notes."));
        msgBox.setInformativeText(tr("Do you want to save your changes first?"));
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);
        msgBox.setIcon(QMessageBox::Warning);
        int ret = msgBox.exec();
        if(ret){

            switch(ret)
             {
              case QMessageBox::Save:
                // Save was clicked.. handle it
                saveStudyNoteAs();
                shouldSaveBool = false;
                studyNotesTextEdit->clear();
              break;
              case QMessageBox::Discard:
                 shouldSaveBool = false;
                studyNotesTextEdit->clear();
              break;
              case QMessageBox::Cancel:
                 msgBox.close();

              break;
              default:
                 // should never be reached
              break;
             }


        }
    }
    else
    {
        if(studyNotesTextEdit->toPlainText().length() > 0)
        studyNotesTextEdit->clear();
    }


}

void MainWnd::selectAllStudyNotesText()
{
    studyNotesTextEdit->selectAll();
}

void MainWnd::openFontsDialog()
{

    bool ok;

     QFont font = QFontDialog::getFont(
                     &ok, bibleKjvTextEdit->currentFont(), this);
     if (ok) {
         bibleKjvTextEdit->setFont(font);
     }

}

//void MainWnd::openPreferencesDialog()
//{

//    QMessageBox::about(this, tr("About Menu"),
//                 tr("Thank you, I see it works."));

//}

void MainWnd::openHelpTopics()
{

    QDesktopServices::openUrl(QUrl("docs/index.html", QUrl::TolerantMode));

}


void MainWnd::selectEntireChapter()
{
    bibleKjvTextEdit->selectAll();

}

void MainWnd::copyBibleTextSelection()
{
  bibleKjvTextEdit->copy();
}

void MainWnd::pasteSelectionToNotes()
{
    if(studyNotesTextEdit->canPaste())
           studyNotesTextEdit->paste();

}

//void MainWnd::highlightBibleSelection()
//{
//   //

//}

void MainWnd::previewChapters()
{
#ifndef QT_NO_PRINTER
    QPrinter printer(QPrinter::HighResolution);
    QPrintPreviewDialog preview(&printer, bibleKjvTextEdit);
    preview.setWindowFlags ( Qt::Window );
    connect(&preview, SIGNAL(paintRequested(QPrinter *)), SLOT(printPreviewBible(QPrinter *)));
    preview.exec();
#endif
}

void MainWnd::printPreviewBible(QPrinter *printer)
{
#ifndef QT_NO_PRINTER
     bibleKjvTextEdit->print(printer);
#endif
}

void MainWnd::setWordWrap()
{
    if(studyNotesTextEdit->lineWrapMode() == QTextEdit::WidgetWidth)
        studyNotesTextEdit->setLineWrapMode(QTextEdit::NoWrap);
    else
        studyNotesTextEdit->setLineWrapMode(QTextEdit::WidgetWidth);
}


void MainWnd::decreaseIndent()
{
    applyIndent(DECREASE_INDENT);
}

void MainWnd::increaseIndent()
{
    applyIndent(INCREASE_INDENT);
}

void MainWnd::applyIndent(int i)
{

    QTextCursor cursor = studyNotesTextEdit->textCursor();
    QTextBlockFormat block;


    if(!cursor.hasSelection())
        cursor.select(QTextCursor::BlockUnderCursor);

    block = cursor.blockFormat();
    if(i == DECREASE_INDENT )
        block.setIndent(0);
    else
        block.setIndent(1);


         cursor.setBlockFormat(block);
      studyNotesTextEdit->setTextCursor(cursor);

}

void MainWnd::setBold()
{
   if(boldAct->isChecked())
    studyNotesTextEdit->setFontWeight(QFont::Bold);
   else
    studyNotesTextEdit->setFontWeight(QFont::Normal);

}

void MainWnd::setItalics()
{

   if(italicAct->isChecked())
    studyNotesTextEdit->setFontItalic(true);
   else
    studyNotesTextEdit->setFontItalic(false);

}

void MainWnd::setUnderline()
{

   if(underlineAct->isChecked())
    studyNotesTextEdit->setFontUnderline(true);
   else
    studyNotesTextEdit->setFontUnderline(false);

}

void MainWnd::setUnOrdered()
{
    formatTextList(TEXTLIST_UNORDERED);
}

void MainWnd::setOrdered()
{
    formatTextList(TEXTLIST_ORDERED);
}

void MainWnd::formatTextList(int i)
{

    QTextListFormat listFormat;
    QTextCursor cursor = studyNotesTextEdit->textCursor();

    if(!cursor.hasSelection())
        cursor.select(QTextCursor::BlockUnderCursor);

         listFormat.setIndent(listFormat.indent());

            if(i == TEXTLIST_UNORDERED)
                listFormat.setStyle(QTextListFormat::ListDisc);
            else
                listFormat.setStyle(QTextListFormat::ListDecimal);

        cursor.createList(listFormat);
        studyNotesTextEdit->setTextCursor(cursor);

}

void MainWnd::setAlignLeft()
{
studyNotesTextEdit->setAlignment(Qt::AlignLeft);
}

void MainWnd::setAlignCenter()
{
studyNotesTextEdit->setAlignment(Qt::AlignHCenter);
}

void MainWnd::setAlignRight()
{
studyNotesTextEdit->setAlignment(Qt::AlignRight);
}

void MainWnd::chapterClickedSimulator(QTreeWidgetItem* treeWidgetItem, int index)
{

    QString check = treeWidgetItem->text(index);
    QString s;

        if(treeWidgetItem->childCount() > 0)
        {

            QString str;
            QString lowerCaseStr;
            str = treeWidgetItem->text(index);
            lowerCaseStr = str.toLower();
            lowerCaseStr.replace(QString(" "), QString("_"));

            s = "<div align='center'><img src=':/images/";
            s.append(lowerCaseStr);
            s.append(".png' /></div>");
            bibleKjvTextEdit->setHtml(s);
             bibleKjvTextEdit->setEnabled(false);
             bibleKjvTextEdit->setStyleSheet("background-color: rgba(255, 255, 255, 255);");
             copyVersesAct->setEnabled(false);

        }
        else
         {

             s = treeWidgetItem->parent()->text(index);
             s.append(":");
             s.append(treeWidgetItem->text(index));

             QStringList queryParams = s.split(":", QString::SkipEmptyParts);
             QString str = queryParams[1];
             int i = str.toInt();


              dbConn.getBasicData(queryParams[0], i, dbConn.db);


               bibleKjvTextEdit->setHtml(DataHelper::s);
               bibleKjvTextEdit->setEnabled(true);
               copyVersesAct->setEnabled(true);
               DataHelper::s.clear();

         }

}

void MainWnd::treeSelectionChanged()
{
   QList<QTreeWidgetItem *> item = bibleBooksTreeWidget->selectedItems();
   chapterClickedSimulator(item[0],  0);
}

void MainWnd::createOutLiner()
{

    bibleBooksTreeWidget  = new QTreeWidget;
    bibleBooksTreeWidget->setColumnCount(1);
    bibleBooksTreeWidget->setHeaderHidden(true);
    connect(bibleBooksTreeWidget, SIGNAL(itemSelectionChanged()),
            this, SLOT(treeSelectionChanged()));


    QTreeWidgetItem *books[66];
    QTreeWidgetItem *testaments[2];
    QTreeWidgetItem *chapters[150];




    QString testamentsArray[] = {
        "Old Testament", "New Testament"
    };
    int chaptersArray[] = {
        50, 40, 27, 36, 34, 24, 21,  4,  31, 24,
        22, 25, 29, 36, 10, 13, 10, 42, 150, 31,
        12,  8, 66, 52,  5, 48, 12, 14,   3,  9,
         1,  4,  7,  3,  3,  3,  2, 14,   4, 28,
        16, 24, 21, 28, 16, 16, 13,  6,   6,  4,
         4,  5,  3,  6,  4,  3,  1, 13,   5,  5,
         3,  5,  1,  1,  1, 22
    };

    QString booksArray[] = {
    "Genesis",          "Exodus",           "Leviticus",
    "Numbers",          "Deuteronomy",      "Joshua",
    "Judges",           "Ruth",             "1 Samuel",
    "2 Samuel",         "1 Kings",          "2 Kings",
    "1 Chronicles",     "2 Chronicles",     "Ezra",
    "Nehemiah",         "Esther",           "Job",
    "Psalms",           "Proverbs",         "Ecclesiastes",
    "Song of Solomon",  "Isaiah",           "Jeremiah",
    "Lamentations",     "Ezekiel",          "Daniel",
    "Hosea",            "Joel",             "Amos",
    "Obadiah",          "Jonah",            "Micah",
    "Nahum",            "Habakkuk",         "Zephaniah",
    "Haggai",           "Zechariah",        "Malachi",
    "Matthew",          "Mark",             "Luke",
    "John",             "Acts",             "Romans",
    "1 Corinthians",    "2 Corinthians",    "Galatians",
    "Ephesians",        "Philippians",      "Colossians",
    "1 Thessalonians",  "2 Thessalonians",  "1 Timothy",
    "2 Timothy",        "Titus",            "Philemon",
    "Hebrews",          "James",            "1 Peter",
    "2 Peter",          "1 John",           "2 John",
    "3 John",           "Jude",             "Revelation"
   };

        int x = 0;
        int j = 0;
        int m;
        for(int i = 0 ; i < 2 ; i++)
        {
        if(i == 0){m = 38;}else{m=66;}


          testaments[i] = new QTreeWidgetItem(bibleBooksTreeWidget);
          testaments[i]->setText(0, testamentsArray[i]);
          testaments[i]->setIcon(0, QIcon(":/images/books.png"));
        //  if(i==0)
              testaments[i]->setExpanded(true);

            for( ; j < 66; j++)
            {
                books[j]  = new QTreeWidgetItem(testaments[i]);
                books[j]->setText(0, booksArray[j]);
                books[j]->setIcon(0, QIcon(":/images/book.png"));
                //if(j==0)
                  //  books[j]->setExpanded(true);

                    for(int k= 0; k < chaptersArray[j]; k++)
                    {
                        chapters[k]  = new QTreeWidgetItem(books[j]);
                        chapters[k]->setText(0, QString("%1").arg(k+1));
                        chapters[k]->setIcon(0, QIcon(":/images/book_open.png"));
                        chapters[k]->setToolTip(0, QString("Chapter: %1").arg(k+1));
                      //  if(k==0 && j==0)
                         //   chapters[k]->setSelected(true);

                    }

                    if(i == 0 && x == m)
                       {j++;break;}
;
                    x++;

            }
        }

}

void MainWnd::about()
{

    AboutDlg dialog(this);
   // dialog.setAttribute(Qt::WA_DeleteOnClose);
    dialog.exec();

}

void MainWnd::exitApp()
{
    if(shouldSaveBool)
    {

        QMessageBox msgBox;
        msgBox.setWindowTitle(tr("LimeBible Warning"));
        msgBox.setText(tr("The text in the current study note has been modified."));
        msgBox.setInformativeText(tr("Do you want to save your changes?"));
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);
        msgBox.setIcon(QMessageBox::Warning);
        int ret = msgBox.exec();
        if(ret){

            switch(ret)
             {
              case QMessageBox::Save:
                // Save was clicked.. handle it
                 saveNotesFile();

                 close();
              break;
              case QMessageBox::Discard:

                 close();
              break;
              case QMessageBox::Cancel:
                 msgBox.close();

              break;
              default:
                 // should never be reached
              break;
             }


        }
    }
    else
    {


        close();
    }

}

void MainWnd::setNotesFontFace(QFont f)
{
 studyNotesTextEdit->setFontFamily(f.family());

}

void MainWnd::setNotesFontSize(QString s)
{
  studyNotesTextEdit->setFontPointSize(s.toInt());
}

void MainWnd::createFontCombo()
{

    fontComboBox = new QFontComboBox();
    fontComboBox->setFontFilters(QFontComboBox::ScalableFonts);
    fontComboBox->setWritingSystem(QFontDatabase::Latin);
    fontComboBox->setCurrentFont(QFont("Georgia"));
    fontSizeComboBox = new QComboBox();
    fontSizeComboBox->addItem(tr("6"), QVariant(6));
    fontSizeComboBox->addItem(tr("7"), QVariant(7));
    fontSizeComboBox->addItem(tr("8"), QVariant(8));
    fontSizeComboBox->addItem(tr("9"), QVariant(9));
    fontSizeComboBox->addItem(tr("10"), QVariant(10));
    fontSizeComboBox->addItem(tr("11"), QVariant(11));
    fontSizeComboBox->addItem(tr("12"), QVariant(12));
    fontSizeComboBox->addItem(tr("14"), QVariant(14));
    fontSizeComboBox->addItem(tr("16"), QVariant(16));
    fontSizeComboBox->addItem(tr("18"), QVariant(18));
    fontSizeComboBox->addItem(tr("20"), QVariant(20));
    fontSizeComboBox->addItem(tr("22"), QVariant(22));
    fontSizeComboBox->addItem(tr("24"), QVariant(24));
    fontSizeComboBox->addItem(tr("26"), QVariant(26));
    fontSizeComboBox->addItem(tr("28"), QVariant(28));
    fontSizeComboBox->addItem(tr("36"), QVariant(36));
    fontSizeComboBox->addItem(tr("48"), QVariant(48));
    fontSizeComboBox->addItem(tr("72"), QVariant(72));
    fontSizeComboBox->setCurrentIndex(6);
    fontSizeComboBox->setSizeAdjustPolicy(QComboBox::AdjustToContents);
    connect(fontComboBox, SIGNAL(currentFontChanged(QFont)), this, SLOT(setNotesFontFace(QFont)));
    connect(fontSizeComboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(setNotesFontSize(QString)));

}

void MainWnd::createStatusBar()
{
    QLabel * licenseeLabel = new QLabel(
            tr(" ")
            , this);
    QLabel * activityLabel = new QLabel(tr("Ready"), this);
    licenseeLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    activityLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);

    statusBar()->addPermanentWidget(licenseeLabel);
    statusBar()->addWidget(activityLabel);

}

void MainWnd::createMenuBar()
{

    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(closeAct);
    fileMenu->addSeparator();
    fileMenu->addAction(saveAct);
    fileMenu->addAction(saveAsAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);


    bibleMenu = menuBar()->addMenu(tr("&Bible"));
    bibleMenu->addAction(searchAct);
    bibleMenu->addSeparator();
    bibleMenu->addAction(selectWholeChapterAct);
    bibleMenu->addAction(copySelectionAct);
    bibleMenu->addAction(copyVersesAct);
    bibleMenu->addAction(pasteToNotesAct);
    bibleMenu->addSeparator();
    bibleMenu->addAction(previewVersesAct);
    bibleMenu->addAction(printVersesAct);


    notesMenu = menuBar()->addMenu(tr("&Notes"));
    notesMenu->addAction(undoAct);
    notesMenu->addAction(redoAct);
    notesMenu->addSeparator();
    notesMenu->addAction(copyAct);
    notesMenu->addAction(cutAct);
    notesMenu->addAction(pasteAct);
    notesMenu->addSeparator();
    notesMenu->addAction(selectAllAct);
    notesMenu->addAction(clearAct);
    notesMenu->addSeparator();
    notesMenu->addAction(previewAct);
    notesMenu->addAction(printAct);


    formatMenu = menuBar()->addMenu(tr("&Format"));
    formatMenu->addAction(fontSettingsAct);
    formatMenu->addSeparator();
    formatMenu->addAction(wordWrapAct);
    formatMenu->addSeparator();
    formatMenu->addAction(decreaseIndentAct);
    formatMenu->addAction(increaseIndentAct);
    formatMenu->addSeparator();
//    formatMenu->addAction(preferencesAct);

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(helpContentsAct);
    helpMenu->addAction(updatesCheckAct);
    helpMenu->addSeparator();
    helpMenu->addAction(aboutAct);

}



//void MainWnd::createToolBarMenus()
//{
//    colorSelectmenu = new QMenu();

//    QAction *redAction = new QAction(QIcon(":/images/red.png"),"Red", this);
//    QAction *greenAction = new QAction(QIcon(":/images/green.png"),"Green", this);
//    QAction *blueAction = new QAction(QIcon(":/images/blue.png"),"Blue", this);
//    QAction *cyanAction = new QAction(QIcon(":/images/cyan.png"),"Cyan", this);
//    QAction *magentaAction = new QAction(QIcon(":/images/magenta.png"),"Magenta", this);
//    QAction *yellowAction = new QAction(QIcon(":/images/yellow.png"),"Yellow", this);
//    QAction *grayAction = new QAction(QIcon(":/images/gray.png"),"Gray", this);
//    colorSelectmenu->addAction(redAction);
//    colorSelectmenu->addAction(greenAction);
//    colorSelectmenu->addAction(blueAction);
//    colorSelectmenu->addAction(cyanAction);
//    colorSelectmenu->addAction(magentaAction);
//    colorSelectmenu->addAction(yellowAction);
//    colorSelectmenu->addAction(grayAction);



//}

void MainWnd::createToolBar()
{

    fileToolBar = addToolBar(tr("File"));
    fileToolBar->addAction(newAct);
    fileToolBar->addAction(openAct);
    fileToolBar->addAction(closeAct);
    fileToolBar->addSeparator();
    fileToolBar->addAction(saveAct);

    helpToolBar = addToolBar(tr("Help"));
    helpToolBar->addAction(updatesCheckAct);
    helpToolBar->addAction(helpContentsAct);

    bibleEditToolBar = addToolBar(tr("Bible Edit"));
    bibleEditToolBar->addAction(selectWholeChapterAct);
    bibleEditToolBar->addAction(copySelectionAct);
    bibleEditToolBar->addAction(copyVersesAct);
    bibleEditToolBar->addAction(pasteToNotesAct);
    bibleEditToolBar->addSeparator();
    //bibleEditToolBar->addAction(highlightSelectionAct);


//    QToolButton* toolButton = new QToolButton();
//    toolButton->setIcon(QIcon(":/images/note_edit.png"));
//    toolButton->setMenu(colorSelectmenu);
//    toolButton->setPopupMode(QToolButton::InstantPopup);
//    bibleEditToolBar->addWidget(toolButton);



    bibleEditToolBar->addSeparator();
    bibleEditToolBar->addAction(searchAct);
    bibleEditToolBar->addSeparator();
    bibleEditToolBar->addAction(previewVersesAct);
    bibleEditToolBar->addAction(printVersesAct);
    bibleEditToolBar->addSeparator();

    notesLayoutToolBar = addToolBar(tr("Notes Layout"));
    notesLayoutToolBar->addAction(undoAct);
    notesLayoutToolBar->addAction(redoAct);
    notesLayoutToolBar->addSeparator();
    notesLayoutToolBar->addAction(copyAct);
    notesLayoutToolBar->addAction(cutAct);
    notesLayoutToolBar->addAction(pasteAct);
    notesLayoutToolBar->addSeparator();
    notesLayoutToolBar->addAction(selectAllAct);
    notesLayoutToolBar->addAction(clearAct);
    notesLayoutToolBar->addSeparator();
    notesLayoutToolBar->addAction(alignLeftAct);
    notesLayoutToolBar->addAction(alignCenterAct);
    notesLayoutToolBar->addAction(alignRightAct);
    notesLayoutToolBar->addSeparator();
    notesLayoutToolBar->addAction(dotBulletAct);
    notesLayoutToolBar->addAction(numBulletAct);
    notesLayoutToolBar->addAction(decreaseIndentAct);
    notesLayoutToolBar->addAction(increaseIndentAct);
    notesLayoutToolBar->addSeparator();
    notesLayoutToolBar->addAction(wordWrapAct);
    notesLayoutToolBar->addSeparator();


    notesFontToolBar = addToolBar(tr("Notes Font"));
    notesFontToolBar->addWidget(fontComboBox);
    notesFontToolBar->addSeparator();
    notesFontToolBar->addWidget(fontSizeComboBox);
    notesFontToolBar->addSeparator();
    notesFontToolBar->addAction(boldAct);
    notesFontToolBar->addAction(italicAct);
    notesFontToolBar->addAction(underlineAct);
    notesFontToolBar->addSeparator();
 //   notesFontToolBar->addWidget(fontColorToolButton);
 //   notesFontToolBar->addWidget(highlightToolButton);

}

void MainWnd::createActions()
{

    newAct  = new QAction(QIcon(":/images/page_add.png"), tr("&New"), this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("Create new Study Notes File"));
    connect(newAct, SIGNAL(triggered()), this, SLOT(newStudyNote()));

    openAct = new QAction(QIcon(":/images/door_open.png"), tr("&Open"), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Open Study Notes File"));
    connect(openAct, SIGNAL(triggered()), this, SLOT(openStudyNote()));

    closeAct = new QAction(QIcon(":/images/door.png"),tr("&Close"), this);
    closeAct->setShortcuts(QKeySequence::Close);
    closeAct->setStatusTip(tr("Close Current Study Notes File"));
    connect(closeAct, SIGNAL(triggered()), this, SLOT(closeStudyNote()));


    saveAct = new QAction(QIcon(":/images/disk.png"), tr("&Save"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save Study Notes"));
    connect(saveAct, SIGNAL(triggered()), this, SLOT(saveStudyNote()));

    saveAsAct = new QAction(QIcon(":/images/save_as.png"), tr("Save &As"), this);
    saveAsAct->setShortcuts(QKeySequence::SaveAs);
    saveAsAct->setStatusTip(tr("Save Study Notes As"));
    connect(saveAsAct, SIGNAL(triggered()), this, SLOT(saveStudyNoteAs()));

    exitAct = new QAction(QIcon(":/images/cancel.png"),tr("E&xit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Exit the LimeBible"));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(exitApp()));




    searchAct = new QAction(QIcon(":/images/find.png"), tr("Search"), this);
    searchAct->setShortcuts(QKeySequence::Find);
    searchAct->setStatusTip(tr("Search the Bible Text"));
    connect(searchAct, SIGNAL(triggered()), this, SLOT(searchBible()));

    selectWholeChapterAct = new QAction(QIcon(":/images/select.png"), tr("&Select Chapter"), this);
    selectWholeChapterAct->setShortcut(tr("Alt+B+S"));
    selectWholeChapterAct->setStatusTip(tr("Select the Entire Chapter"));
    connect(selectWholeChapterAct, SIGNAL(triggered()), this, SLOT(selectEntireChapter()));

    copySelectionAct = new QAction(QIcon(":/images/page_white_copy.png"),tr("&Copy Selection"), this);
    copySelectionAct->setShortcut(tr("Alt+B+C"));
    copySelectionAct->setEnabled(false);
    copySelectionAct->setStatusTip(tr("Copy Text from the Bible"));
    connect(copySelectionAct, SIGNAL(triggered()), this, SLOT(copyBibleTextSelection()));

    copyVersesAct = new QAction(QIcon(":/images/education.png"),tr("Copy &Verses"), this);
    copyVersesAct->setShortcut(tr("Alt+B+V"));
    copyVersesAct->setStatusTip(tr("Copy Verse at Cursor from the Bible"));
    connect(copyVersesAct, SIGNAL(triggered()), this, SLOT(copySelectedVerses()));

    pasteToNotesAct = new QAction(QIcon(":/images/page_paste.png"), tr("&Paste to Notes"), this);
    pasteToNotesAct->setShortcut(tr("Alt+B+P"));
    pasteToNotesAct->setStatusTip(tr("Paste Text to Current Notes"));
    connect(pasteToNotesAct, SIGNAL(triggered()), this, SLOT(pasteSelectionToNotes()));
///////////////////////////////////////
//    highlightSelectionAct = new QAction(QIcon(":/images/note_edit.png"), tr("&Highlight"), this);
//    highlightSelectionAct->setShortcut(tr("Alt+B+H"));
//   //  highlightSelectionAct->setMenu(colorSelectmenu);

//    //highlightSelectionAct->setEnabled(false);
//    highlightSelectionAct->setStatusTip(tr("Highlight Selected Text"));
//    connect(highlightSelectionAct, SIGNAL(triggered()), this, SLOT(highlightBibleSelection()));

    /////////////////////////////

    previewVersesAct = new QAction(QIcon(":/images/document_inspector.png"),tr("Previe&w Chapters"), this);
    previewVersesAct->setShortcut(tr("Alt+B+W"));
    previewVersesAct->setStatusTip(tr("Print Preview the Current Chapter"));
    connect(previewVersesAct, SIGNAL(triggered()), this, SLOT(previewChapters()));

    printVersesAct = new QAction(QIcon(":/images/printer.png"),tr("P&rint Chapter"), this);
    printVersesAct->setShortcut(tr("Alt+B+R"));
    printVersesAct->setStatusTip(tr("Print the Current Chapter"));
    connect(printVersesAct, SIGNAL(triggered()), this, SLOT(printChapters()));




    undoAct = new QAction(QIcon(":/images/arrow_undo.png"),tr("&Undo"), this);
    undoAct->setShortcuts(QKeySequence::Undo);
    undoAct->setEnabled(false);
    undoAct->setStatusTip(tr("Undo Last Action"));
    connect(undoAct, SIGNAL(triggered()), this, SLOT(undoChange()));

    redoAct = new QAction(QIcon(":/images/arrow_redo.png"),tr("&Redo"), this);
    redoAct->setShortcuts(QKeySequence::Redo);
    redoAct->setEnabled(false);
    redoAct->setStatusTip(tr("Redo Last Action"));
    connect(redoAct, SIGNAL(triggered()), this, SLOT(redoChange()));

    copyAct = new QAction(QIcon(":/images/page_copy.png"),tr("Copy"), this);
    copyAct->setShortcuts(QKeySequence::Copy);
    copyAct->setEnabled(false);
    copyAct->setStatusTip(tr("Copy From Clipboard"));
    connect(copyAct, SIGNAL(triggered()), this, SLOT(copyNotesSelection()));

    cutAct = new QAction(QIcon(":/images/cut.png"),tr("Cut"), this);
    cutAct->setShortcuts(QKeySequence::Cut);
    cutAct->setEnabled(false);
    cutAct->setStatusTip(tr("Cut to Clipboard"));
    connect(cutAct, SIGNAL(triggered()), this, SLOT(cutNotesSelection()));

    pasteAct = new QAction(QIcon(":/images/page_paste.png"), tr("Paste"), this);
    pasteAct->setShortcuts(QKeySequence::Paste);
    if(!studyNotesTextEdit->canPaste())
            pasteAct->setEnabled(false);
    pasteAct->setStatusTip(tr("Paste From Clipboard"));
    connect(pasteAct, SIGNAL(triggered()), this, SLOT(pasteFromClipboard()));

    clearAct = new QAction(QIcon(":/images/draw_eraser.png"), tr("C&lear All"), this);
    clearAct->setShortcut(tr("Alt+N+L"));
    clearAct->setEnabled(false);
    clearAct->setStatusTip(tr("Clear all Study Notes Text"));
    connect(clearAct, SIGNAL(triggered()), this, SLOT(clearStudyNotesText()));

    selectAllAct = new QAction(QIcon(":/images/select.png"),tr("Select &All"), this);
    selectAllAct->setShortcuts(QKeySequence::SelectAll);
    selectAllAct->setEnabled(false);
    selectAllAct->setStatusTip(tr("Select all Study Notes Text"));
    connect(selectAllAct, SIGNAL(triggered()), this, SLOT(selectAllStudyNotesText()));

    previewAct = new QAction(QIcon(":/images/document_inspector.png"), tr("Print P&review"), this);
    previewAct->setShortcut(tr("Alt+N+R"));
    previewAct->setStatusTip(tr("Study Notes Print Preview"));
    connect(previewAct, SIGNAL(triggered()), this, SLOT(previewStudyNote()));

    printAct = new QAction(QIcon(":/images/printer.png"), tr("&Print..."), this);
    printAct->setShortcuts(QKeySequence::Print);
    printAct->setStatusTip(tr("Print Study Notes"));
    connect(printAct, SIGNAL(triggered()), this, SLOT(printStudyNote()));




    fontSettingsAct = new QAction(QIcon(":/images/font.png"), tr("&Fonts..."), this);
    fontSettingsAct->setShortcut(tr("Alt+F+F"));
    fontSettingsAct->setStatusTip(tr("Open Fonts Dialog"));
    connect(fontSettingsAct, SIGNAL(triggered()), this, SLOT(openFontsDialog()));

    wordWrapAct = new QAction(QIcon(":/images/layer_redraw.png"), tr("&Word Wrap"), this);
    wordWrapAct->setShortcut(tr("Alt+F+W"));
    wordWrapAct->setStatusTip(tr("Wrap Text in Notes"));
    wordWrapAct->setCheckable(true);
    wordWrapAct->setChecked(true);
    connect(wordWrapAct, SIGNAL(triggered()), this, SLOT(setWordWrap()));


    decreaseIndentAct = new QAction(QIcon(":/images/text_indent_remove.png"), tr("&Decrease Indent"), this);
    decreaseIndentAct->setShortcut(tr("Alt+F+D"));
    decreaseIndentAct->setStatusTip(tr("Decrease Text Indent"));
    connect(decreaseIndentAct, SIGNAL(triggered()), this, SLOT(decreaseIndent()));

    increaseIndentAct = new QAction(QIcon(":/images/text_indent.png"), tr("&Increase Indent"), this);
    increaseIndentAct->setShortcut(tr("Alt+F+I"));
    increaseIndentAct->setStatusTip(tr("Increase Text Indent"));
    connect(increaseIndentAct, SIGNAL(triggered()), this, SLOT(increaseIndent()));

//    preferencesAct = new QAction(tr("&Preferences"), this);
//    preferencesAct->setShortcut(tr("Alt+T+P"));
//    preferencesAct->setStatusTip(tr("Open LimeBible Preferences Dialog"));
//    connect(preferencesAct, SIGNAL(triggered()), this, SLOT(openPreferencesDialog()));

    alignLeftAct = new QAction(QIcon(":/images/text_align_left.png"), tr("Align &Left"), this);
    alignLeftAct->setShortcut(tr("Alt+F+L"));
    alignLeftAct->setStatusTip(tr("Align Text to the Left"));
    connect(alignLeftAct, SIGNAL(triggered()), this, SLOT(setAlignLeft()));

    alignCenterAct = new QAction(QIcon(":/images/text_align_center.png"), tr("Align &Center"), this);
    alignCenterAct->setShortcut(tr("Alt+F+C"));
    alignCenterAct->setStatusTip(tr("Align Text Within the Center"));
    connect(alignCenterAct, SIGNAL(triggered()), this, SLOT(setAlignCenter()));

    alignRightAct = new QAction(QIcon(":/images/text_align_right.png"), tr("Align &Right"), this);
    alignRightAct->setShortcut(tr("Alt+F+R"));
    alignRightAct->setStatusTip(tr("ALign Text to the Right"));
    connect(alignRightAct, SIGNAL(triggered()), this, SLOT(setAlignRight()));

    dotBulletAct = new QAction(QIcon(":/images/text_list_bullets.png"), tr("&Unordered List"), this);
    dotBulletAct->setShortcut(tr("Alt+F+U"));
    dotBulletAct->setStatusTip(tr("Set Point Bullets"));
    connect(dotBulletAct, SIGNAL(triggered()), this, SLOT(setUnOrdered()));

    numBulletAct = new QAction(QIcon(":/images/text_list_numbers.png"), tr("&Ordered List"), this);
    numBulletAct->setShortcut(tr("Alt+F+O"));
    numBulletAct->setStatusTip(tr("Number Items in the List"));
    connect(numBulletAct, SIGNAL(triggered()), this, SLOT(setOrdered()));

    boldAct = new QAction(QIcon(":/images/text_bold.png"), tr("Bold"), this);
    boldAct->setCheckable(true);
    connect(boldAct, SIGNAL(triggered()), this, SLOT(setBold()));

    italicAct = new QAction(QIcon(":/images/text_italic.png"), tr("Italics"), this);
    italicAct->setCheckable(true);
    connect(italicAct, SIGNAL(triggered()), this, SLOT(setItalics()));

    underlineAct = new QAction(QIcon(":/images/text_underline.png"), tr("Underline"), this);
    underlineAct->setCheckable(true);
    connect(underlineAct, SIGNAL(triggered()), this, SLOT(setUnderline()));

  //   fontColorToolButton = new QToolButton();
  //   highlightToolButton = new QToolButton();

    helpContentsAct = new QAction(QIcon(":/images/help.png"), tr("&Help Contents..."), this);
    helpContentsAct->setShortcuts(QKeySequence::HelpContents);
    helpContentsAct->setStatusTip(tr("Get Help on for LimeBible"));
    connect(helpContentsAct, SIGNAL(triggered()), this, SLOT(openHelpTopics()));

    updatesCheckAct = new QAction(QIcon(":/images/update.png"),tr("&Check for Updates..."), this);
    updatesCheckAct->setShortcut(tr("Alt+H+C"));
    updatesCheckAct->setStatusTip(tr("Check for Lime Bible Updates"));
    connect(updatesCheckAct, SIGNAL(triggered()), this, SLOT(checkForUpdates()));

    aboutAct = new QAction(tr("&About"), this);
    aboutAct->setShortcut(tr("Alt+H+A"));
    aboutAct->setStatusTip(tr("Show the Lime Bible's About Box"));
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

}



MainWnd::~MainWnd()
{

}
