#ifndef SEARCHDLG_H
#define SEARCHDLG_H

#include <QWidget>
#include <QToolButton>
#include <QGroupBox>
#include <QCheckBox>
#include <QRadioButton>
#include <QLineEdit>
#include <QPushButton>
#include <QListWidget>
#include <QComboBox>
#include <QTextEdit>
#include <QLabel>
#include <QAction>
#include "globals.h"
#include "datahelper.h"
#include "mainwnd.h"

class MainWnd;

class SearchDlg : public QWidget
{
    Q_OBJECT
public:
    explicit SearchDlg(MainWnd *parent = 0);
    DataHelper *dbConn;
    QTextEdit *bibleKjvTextEdit;
    QAction   *copyVersesAct;

private:
    MainWnd* parentMainWin;

        void buildBibleComboList(QComboBox *bibleList);

    QComboBox *searchFieldCombo;
    QComboBox *criteriaCombo;
    QComboBox *firstCombo;
    QComboBox *secondCombo;
    QGroupBox *criteriaGroupBox;
    QGroupBox *rangeGroupBox;
    QCheckBox *caseCheckBox;
    QRadioButton *entireBibleRadio;
    QRadioButton *oldTestamentRadio;
    QRadioButton *newTestamentRadio;
    QTextEdit *resultsTextEdit;
    QListWidget *resultsListView;
    QLineEdit *excludeLineEdit;
    QPushButton *searchButton;
    QPushButton *doneButton;
    QPushButton *cancelButton;



signals:

private slots:
    void searchDlgSearch();
    void handleFirstTestament();
    void handleSecondTestament();
    void handleFullTestament();
    void handleFirstComboChange(int);
    void handleSecondComboChange(int);
    void searchResItemClicked(QModelIndex mi);

};

#endif // SEARCHDLG_H
