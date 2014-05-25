/**
 LimeBible 1.0 series

 */
#ifndef MAINWND_H
#define MAINWND_H

#include <QtGui/QMainWindow>
#include <QSplitter>
#include <QTreeWidget>
//#include <QTextEdit>
#include <QToolBox>
 #include <QFontComboBox>
#include <QToolButton>
//#include <QGroupBox>
//#include <QCheckBox>
//#include <QRadioButton>
//#include <QLineEdit>
//#include <QPushButton>
#include <QListWidget>

#include "datahelper.h"
#include "searchdlg.h"

class SearchDlg;

class MainWnd : public QMainWindow
{
    Q_OBJECT

public:
    MainWnd(QWidget *parent = 0);
    ~MainWnd();

    DataHelper dbConn;
        QAction *copyVersesAct;

private:
    bool shouldSaveBool;
    bool doTextChanges;

 //   void createToolBarMenus();
    void createMenuBar();
    void createStatusBar();
    void createToolBar();
    void createActions();
    void createFontCombo();
    void createOutLiner();
    void openLimeBibleStudyNote();
    void saveNotesFile();
    void chapterClickedSimulator(QTreeWidgetItem* treeWidgetItem, int index);


    QString currOpenFile;
    QString currOpenSavedFile;



    QMenu *fileMenu;
    QMenu *bibleMenu;
    QMenu *notesMenu;
    QMenu *formatMenu;
    QMenu *helpMenu;

    QMenu *colorSelectmenu;

    QAction *newAct;
    QAction *openAct;
    QAction *closeAct;
    QAction *saveAct;
    QAction *saveAsAct;
    QAction *exitAct;

    QAction *searchAct;
 //   QAction *copyVersesAct;
    QAction *copySelectionAct;
    QAction *printVersesAct;
    QAction *previewVersesAct;
    QAction *selectWholeChapterAct;
    QAction *pasteToNotesAct;
//    QAction *highlightSelectionAct;

    QAction *undoAct;
    QAction *redoAct;
    QAction *copyAct;
    QAction *cutAct;
    QAction *pasteAct;
    QAction *clearAct;
    QAction *selectAllAct;
    QAction *previewAct;
    QAction *printAct;

    QAction *fontSettingsAct;
    QAction *wordWrapAct;
    QAction *decreaseIndentAct;
    QAction *increaseIndentAct;
    QAction *preferencesAct;
    QAction *alignLeftAct;
    QAction *alignCenterAct;
    QAction *alignRightAct;
    QAction *dotBulletAct;
    QAction *numBulletAct;

    QAction *boldAct;
    QAction *italicAct;
    QAction *underlineAct;


    QAction *helpContentsAct;
    QAction *updatesCheckAct;
    QAction *aboutAct;

    QToolBar *fileToolBar;
    QToolBar *helpToolBar; //place holder
    QToolBar *bibleEditToolBar;
    QToolBar *notesLayoutToolBar;
    QToolBar *notesFontToolBar;
    QListWidget *notesListWidget;
    QTreeWidget *bibleBooksTreeWidget;
    QTreeWidget *newTestTreeWidget;


    QSplitter *splitter;
    QToolBox  *outlinerToolBox;
    QTabWidget *bibleTabs;
    QTabWidget *notesTabs;
    QFontComboBox * fontComboBox;
    QComboBox * fontSizeComboBox;

//    QToolButton *fontColorToolButton;
//    QToolButton *highlightToolButton;

    //search Stuff
    SearchDlg *searchDlg;



public:
    QTextEdit *bibleKjvTextEdit;
    QTextEdit *studyNotesTextEdit;

private slots:

    void treeSelectionChanged();
    void exitApp();
    void about();
    void checkForUpdates();
    void newStudyNote();
    void openStudyNote();
    void closeStudyNote();
    void saveStudyNote();
    void saveStudyNoteAs();
    void previewStudyNote();
    void printStudyNote();
    void searchBible();
    void copySelectedVerses();
    void printChapters();
    void undoChange();
    void redoChange();
    void copyNotesSelection();
    void cutNotesSelection();
    void pasteFromClipboard();
    void clearStudyNotesText();
    void selectAllStudyNotesText();
    void openFontsDialog();
    //void openPreferencesDialog(); // remember to comment and restore on version 1.0/2.0
    void openHelpTopics();

    void selectEntireChapter();
    void copyBibleTextSelection();
    void pasteSelectionToNotes();
    //void highlightBibleSelection();
    void previewChapters();
    void setWordWrap();
    void decreaseIndent();
    void increaseIndent();
    void applyIndent(int);
    void setBold();
    void setItalics();
    void setUnderline();
    void setUnOrdered();
    void formatTextList(int);
    void setOrdered();
    void setAlignLeft();
    void setAlignCenter();
    void setAlignRight();
    void notesHouseKeeping();
    void notesSelections(bool);
    void bibleTextSelected(bool);
    void greyUnGreyRedo(bool);
    void greyUngreyUndo(bool);
    void setNotesFontFace(QFont);
    void setNotesFontSize(QString);
    void printPreviewBible(QPrinter*);
    void printPreviewNotes(QPrinter*);
    void studyNotesSelChanged();


};

#endif // MAINWND_H
