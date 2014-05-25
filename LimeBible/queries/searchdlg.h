#ifndef SEARCHDLG_H
#define SEARCHDLG_H

#include <QDialog>
#include <QTextEdit>
#include <QLabel>
#include <QComboBox>
#include <QGroupBox>
#include <QCheckBox>
#include <QRadioButton>



#define SEARCH_WIDTH            530
#define SEARCH_HEIGHT           450
#define CRITERIA_ALL_WORDS      100
#define CRITERIA_ANY_WORD       200
#define CRITERIA_EXACT_PHRASE   300



class SearchDlg : public QDialog
{
    Q_OBJECT
public:
    explicit SearchDlg(QWidget *parent = 0);

private:

    QComboBox *searchFieldCombo;
    QComboBox *criteriaCombo;
    QComboBox *oldTestamentCombo;
    QComboBox *newTestamentCombo;
    QGroupBox *criteriaGroupBox;
    QGroupBox *rangeGroupBox;
    QCheckBox *caseCheckBox;
    QRadioButton *entireBibleRadio;
    QRadioButton *oldTestamentRadio;
    QRadioButton *newTestamentRadio;
    QTextEdit *resultsTextEdit;
    QLineEdit *excludeLineEdit;
    QPushButton *searchButton;
    QPushButton *doneButton;
    QPushButton *cancelButton;




signals:

public slots:

};

#endif // SEARCHDLG_H
