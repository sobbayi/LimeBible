#include <QGridLayout>

#include "searchdlg.h"

SearchDlg::SearchDlg( MainWnd *parent) :
    QWidget(parent)
{

    searchFieldCombo = new QComboBox;
    searchFieldCombo->setEditable(true);
    criteriaCombo = new QComboBox;
    criteriaCombo->addItem(tr("Search for all of the Words"), QVariant(CRITERIA_ALL_WORDS));
    criteriaCombo->addItem(tr("Search for any of the Words"), QVariant(CRITERIA_ANY_WORD));
    criteriaCombo->addItem(tr("Search for the Exact Phrase"), QVariant(CRITERIA_EXACT_PHRASE));
    firstCombo = new QComboBox;
    buildBibleComboList(firstCombo);
    firstCombo->setCurrentIndex(0);
    connect(firstCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(handleFirstComboChange(int)));

    secondCombo = new QComboBox;
    buildBibleComboList(secondCombo);
    secondCombo->setCurrentIndex(65);
    connect(secondCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(handleSecondComboChange(int)));

    criteriaGroupBox = new QGroupBox(tr("Search Criteria"));
    rangeGroupBox = new QGroupBox(tr("Search Range"));

    caseCheckBox = new QCheckBox(tr("Case-sensitive"));

    entireBibleRadio = new QRadioButton(tr("Entire Bible"));
    connect(entireBibleRadio, SIGNAL(clicked()), this, SLOT(handleFullTestament()));
    entireBibleRadio->setChecked(true);
    oldTestamentRadio = new QRadioButton(tr("Old Testament"));
    connect(oldTestamentRadio, SIGNAL(clicked()), this, SLOT(handleFirstTestament()));
    newTestamentRadio = new QRadioButton(tr("New Testament"));
    connect(newTestamentRadio, SIGNAL(clicked()), this, SLOT(handleSecondTestament()));
    QLabel *excludeLabel = new QLabel(tr(""));//Exclude
    QLabel *spacer = new QLabel(tr(""));

    resultsListView = new QListWidget;
    resultsListView->setWordWrap(true);
  //  connect(resultsListView, SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),
  //          this, SLOT(getSearchId(QListWidgetItem*,QListWidgetItem*)));
    connect(resultsListView, SIGNAL(clicked(QModelIndex)),
            this, SLOT(searchResItemClicked(QModelIndex)));

   // excludeLineEdit = new QLineEdit;
    searchButton = new QPushButton(tr("Search"));
    connect(searchButton, SIGNAL(clicked()), this, SLOT(searchDlgSearch()));
    doneButton = new QPushButton(tr("Done"));
    connect(doneButton, SIGNAL(clicked()), this, SLOT(close()));
    cancelButton = new QPushButton(tr("Cancel"));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(close()));



    QGridLayout *mainLayout = new QGridLayout;
    QGridLayout *criteriaLayout = new QGridLayout;
    QGridLayout *rangeLayout = new QGridLayout;

    criteriaLayout->addWidget(criteriaCombo,    0, 0, 1, 4);
    criteriaLayout->addWidget(spacer,     1, 0, 1, 2);
 //   criteriaLayout->addWidget(caseCheckBox,     1, 0, 1, 2);
    criteriaLayout->addWidget(excludeLabel,     2, 0, 1, 1);
  //  criteriaLayout->addWidget(excludeLineEdit,  2, 1, 1, 3);

    rangeLayout->addWidget(entireBibleRadio,    0, 0);
    rangeLayout->addWidget(oldTestamentRadio,   1, 0);
    rangeLayout->addWidget(firstCombo,   1, 1);
    rangeLayout->addWidget(newTestamentRadio,   2, 0);
    rangeLayout->addWidget(secondCombo,   2, 1);

    criteriaGroupBox->setLayout(criteriaLayout);
    rangeGroupBox->setLayout(rangeLayout);

    mainLayout->addWidget(searchFieldCombo, 0, 0, 1, 3);
    mainLayout->addWidget(searchButton,     0, 3, 1, 1);
    mainLayout->addWidget(doneButton,       0, 4, 1, 1);
    mainLayout->addWidget(cancelButton,     0, 5, 1, 1);
    mainLayout->addWidget(criteriaGroupBox, 1, 0, 1, 3);
    mainLayout->addWidget(rangeGroupBox,    1, 3, 1, 3);
    mainLayout->addWidget(resultsListView,  2, 0, 1, 6);

    setFixedSize(SEARCH_WIDTH, SEARCH_HEIGHT );
    setWindowTitle(tr("Search LimeBible"));
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowFlags(Qt::Dialog);
    setLayout(mainLayout);

    dbConn = &parent->dbConn;
    bibleKjvTextEdit = parent->bibleKjvTextEdit;
    copyVersesAct    = parent->copyVersesAct;
}

void SearchDlg::searchDlgSearch()
{


    QString txtToSearch = searchFieldCombo->currentText();
    int criteriaInt = criteriaCombo->currentIndex();
    int first = firstCombo->currentIndex();
    int second = secondCombo->currentIndex();



     dbConn->getSearchedResults(txtToSearch, criteriaInt, first, second, dbConn->db);
     resultsListView->clear();

     QString tempTxt = DataHelper::s;
     QString tempInt = DataHelper::id;

     DataHelper::s.clear();
     DataHelper::id.clear();

     QStringList txtParams = tempTxt.split("|", QString::SkipEmptyParts);
     QStringList intParams = tempInt.split("|", QString::SkipEmptyParts);

    if(txtParams.size() == 0)
     {
      QListWidgetItem *w = new QListWidgetItem(tr("No Results Found, Please Check Spelling and Try Another Search"), resultsListView);
      w->setData(Qt::UserRole, QVariant(0));
     }
    else
    {

        for (int i = 0; i < txtParams.size(); i++)
        {

        QListWidgetItem *w = new QListWidgetItem(txtParams.at(i).toLocal8Bit(), resultsListView);
         w->setData(Qt::UserRole, QVariant(intParams.at(i).toInt()));
         if(i>0)
             if(i % 2 != 0)
                w->setBackgroundColor(QColor(189,221,165));

        }
    }

}

void SearchDlg::searchResItemClicked(QModelIndex mi )
{

    int row = mi.data(Qt::UserRole).toInt();

     dbConn->showSeachResult(row, bibleKjvTextEdit);
     copyVersesAct->setEnabled(true);
}


void SearchDlg::handleFirstTestament()
{
    firstCombo->setCurrentIndex(0);
    secondCombo->setCurrentIndex(38);
}

void SearchDlg::handleSecondTestament()
{
    firstCombo->setCurrentIndex(39);
    secondCombo->setCurrentIndex(65);
}

void SearchDlg::handleFullTestament()
{
    firstCombo->setCurrentIndex(0);
    secondCombo->setCurrentIndex(65);
}

void SearchDlg::handleFirstComboChange(int i)
{
    if(secondCombo->currentIndex()< i)
        secondCombo->setCurrentIndex(i);
}

void SearchDlg::handleSecondComboChange(int i)
{
    if(firstCombo->currentIndex()> i)
        firstCombo->setCurrentIndex(i);
}

void SearchDlg::buildBibleComboList(QComboBox *bibleList)
{
    bibleList->addItem(tr("Genesis"), QVariant(1));
        bibleList->addItem(tr("Exodus"), QVariant(2));
        bibleList->addItem(tr("Leviticus"), QVariant(3));
        bibleList->addItem(tr("Numbers"), QVariant(4));
        bibleList->addItem(tr("Deuteronomy"), QVariant(5));
        bibleList->addItem(tr("Joshua"), QVariant(6));
        bibleList->addItem(tr("Judges"), QVariant(7));
        bibleList->addItem(tr("Ruth"), QVariant(8));
        bibleList->addItem(tr("1 Samuel"), QVariant(9));
        bibleList->addItem(tr("2 Samuel"), QVariant(10));
        bibleList->addItem(tr("1 Kings"), QVariant(11));
        bibleList->addItem(tr("2 Kings"), QVariant(12));
        bibleList->addItem(tr("1 Chronicles"), QVariant(13));
        bibleList->addItem(tr("2 Chronicles"), QVariant(14));
        bibleList->addItem(tr("Ezra"), QVariant(15));
        bibleList->addItem(tr("Nehemiah"), QVariant(16));
        bibleList->addItem(tr("Esther"), QVariant(17));
        bibleList->addItem(tr("Job"), QVariant(18));
        bibleList->addItem(tr("Psalms"), QVariant(19));
        bibleList->addItem(tr("Proverbs"), QVariant(20));
        bibleList->addItem(tr("Ecclesiastes"), QVariant(21));
        bibleList->addItem(tr("Song of Solomon"), QVariant(22));
        bibleList->addItem(tr("Isaiah"), QVariant(23));
        bibleList->addItem(tr("Jeremiah"), QVariant(24));
        bibleList->addItem(tr("Lamentations"), QVariant(25));
        bibleList->addItem(tr("Ezekiel"), QVariant(26));
        bibleList->addItem(tr("Daniel"), QVariant(27));
        bibleList->addItem(tr("Hosea"), QVariant(28));
        bibleList->addItem(tr("Joel"), QVariant(29));
        bibleList->addItem(tr("Amos"), QVariant(30));
        bibleList->addItem(tr("Obadiah"), QVariant(31));
        bibleList->addItem(tr("Jonah"), QVariant(32));
        bibleList->addItem(tr("Micah"), QVariant(33));
        bibleList->addItem(tr("Nahum"), QVariant(34));
        bibleList->addItem(tr("Habakkuk"), QVariant(35));
        bibleList->addItem(tr("Zephaniah"), QVariant(36));
        bibleList->addItem(tr("Haggai"), QVariant(37));
        bibleList->addItem(tr("Zechariah"), QVariant(38));
        bibleList->addItem(tr("Malachi"), QVariant(39));
        bibleList->addItem(tr("Matthew"), QVariant(40));
        bibleList->addItem(tr("Mark"), QVariant(41));
        bibleList->addItem(tr("Luke"), QVariant(42));
        bibleList->addItem(tr("John"), QVariant(43));
        bibleList->addItem(tr("Acts"), QVariant(44));
        bibleList->addItem(tr("Romans"), QVariant(45));
        bibleList->addItem(tr("1 Corinthians"), QVariant(46));
        bibleList->addItem(tr("2 Corinthians"), QVariant(47));
        bibleList->addItem(tr("Galatians"), QVariant(48));
        bibleList->addItem(tr("Ephesians"), QVariant(49));
        bibleList->addItem(tr("Philippians"), QVariant(50));
        bibleList->addItem(tr("Colossians"), QVariant(51));
        bibleList->addItem(tr("1 Thessalonians"), QVariant(52));
        bibleList->addItem(tr("2 Thessalonians"), QVariant(53));
        bibleList->addItem(tr("1 Timothy"), QVariant(54));
        bibleList->addItem(tr("2 Timothy"), QVariant(55));
        bibleList->addItem(tr("Titus"), QVariant(56));
        bibleList->addItem(tr("Philemon"), QVariant(57));
        bibleList->addItem(tr("Hebrews"), QVariant(58));
        bibleList->addItem(tr("James"), QVariant(59));
        bibleList->addItem(tr("1 Peter"), QVariant(60));
        bibleList->addItem(tr("2 Peter"), QVariant(61));
        bibleList->addItem(tr("1 John"), QVariant(62));
        bibleList->addItem(tr("2 John"), QVariant(63));
        bibleList->addItem(tr("3 John"), QVariant(64));
        bibleList->addItem(tr("Jude"), QVariant(65));
        bibleList->addItem(tr("Revelation"), QVariant(66));
}
