#include <QtGui>
#include "searchdlg.h"

SearchDlg::SearchDlg(QWidget *parent) :
    QDialog(parent)
{

    searchFieldCombo = new QComboBox;
    searchFieldCombo->setEditable(true);
    criteriaCombo = new QComboBox;
    criteriaCombo->addItem(tr("Search for all of the Words"), QVariant(CRITERIA_ALL_WORDS));
    criteriaCombo->addItem(tr("Search for any of the Words"), QVariant(CRITERIA_ANY_WORD));
    criteriaCombo->addItem(tr("Search for the Exact Phrase"), QVariant(CRITERIA_EXACT_PHRASE));
    oldTestamentCombo = new QComboBox;
    oldTestamentCombo->addItem(tr("Genesis"), QVariant(1));
    oldTestamentCombo->addItem(tr("Exodus"), QVariant(2));
    oldTestamentCombo->addItem(tr("Leviticus"), QVariant(3));
    oldTestamentCombo->addItem(tr("Numbers"), QVariant(4));
    oldTestamentCombo->addItem(tr("Deuteronomy"), QVariant(5));
    oldTestamentCombo->addItem(tr("Joshua"), QVariant(6));
    oldTestamentCombo->addItem(tr("Judges"), QVariant(7));
    oldTestamentCombo->addItem(tr("Ruth"), QVariant(8));
    oldTestamentCombo->addItem(tr("1 Samuel"), QVariant(9));
    oldTestamentCombo->addItem(tr("2 Samuel"), QVariant(10));
    oldTestamentCombo->addItem(tr("1 Kings"), QVariant(11));
    oldTestamentCombo->addItem(tr("2 Kings"), QVariant(12));
    oldTestamentCombo->addItem(tr("1 Chronicles"), QVariant(13));
    oldTestamentCombo->addItem(tr("2 Chronicles"), QVariant(14));
    oldTestamentCombo->addItem(tr("Ezra"), QVariant(15));
    oldTestamentCombo->addItem(tr("Nehemiah"), QVariant(16));
    oldTestamentCombo->addItem(tr("Esther"), QVariant(17));
    oldTestamentCombo->addItem(tr("Job"), QVariant(18));
    oldTestamentCombo->addItem(tr("Psalms"), QVariant(19));
    oldTestamentCombo->addItem(tr("Proverbs"), QVariant(20));
    oldTestamentCombo->addItem(tr("Ecclesiastes"), QVariant(21));
    oldTestamentCombo->addItem(tr("Song of Solomon"), QVariant(22));
    oldTestamentCombo->addItem(tr("Isaiah"), QVariant(23));
    oldTestamentCombo->addItem(tr("Jeremiah"), QVariant(24));
    oldTestamentCombo->addItem(tr("Lamentations"), QVariant(25));
    oldTestamentCombo->addItem(tr("Ezekiel"), QVariant(26));
    oldTestamentCombo->addItem(tr("Daniel"), QVariant(27));
    oldTestamentCombo->addItem(tr("Hosea"), QVariant(28));
    oldTestamentCombo->addItem(tr("Joel"), QVariant(29));
    oldTestamentCombo->addItem(tr("Amos"), QVariant(30));
    oldTestamentCombo->addItem(tr("Obadiah"), QVariant(31));
    oldTestamentCombo->addItem(tr("Jonah"), QVariant(32));
    oldTestamentCombo->addItem(tr("Micah"), QVariant(33));
    oldTestamentCombo->addItem(tr("Nahum"), QVariant(34));
    oldTestamentCombo->addItem(tr("Habakkuk"), QVariant(35));
    oldTestamentCombo->addItem(tr("Zephaniah"), QVariant(36));
    oldTestamentCombo->addItem(tr("Haggai"), QVariant(37));
    oldTestamentCombo->addItem(tr("Zechariah"), QVariant(38));
    oldTestamentCombo->addItem(tr("Malachi"), QVariant(39));

    newTestamentCombo = new QComboBox;
    newTestamentCombo->addItem(tr("Matthew"), QVariant(55));
    newTestamentCombo->addItem(tr("Mark"), QVariant(56));
    newTestamentCombo->addItem(tr("Luke"), QVariant(57));
    newTestamentCombo->addItem(tr("John"), QVariant(58));
    newTestamentCombo->addItem(tr("Acts"), QVariant(59));
    newTestamentCombo->addItem(tr("Romans"), QVariant(60));
    newTestamentCombo->addItem(tr("1 Corinthians"), QVariant(61));
    newTestamentCombo->addItem(tr("2 Corinthians"), QVariant(62));
    newTestamentCombo->addItem(tr("Galatians"), QVariant(63));
    newTestamentCombo->addItem(tr("Ephesians"), QVariant(64));
    newTestamentCombo->addItem(tr("Philippians"), QVariant(65));
    newTestamentCombo->addItem(tr("Colossians"), QVariant(66));
    newTestamentCombo->addItem(tr("1 Thessalonians"), QVariant(67));
    newTestamentCombo->addItem(tr("2 Thessalonians"), QVariant(68));
    newTestamentCombo->addItem(tr("1 Timothy"), QVariant(69));
    newTestamentCombo->addItem(tr("2 Timothy"), QVariant(70));
    newTestamentCombo->addItem(tr("Titus"), QVariant(71));
    newTestamentCombo->addItem(tr("Philemon"), QVariant(72));
    newTestamentCombo->addItem(tr("Hebrews"), QVariant(73));
    newTestamentCombo->addItem(tr("James"), QVariant(74));
    newTestamentCombo->addItem(tr("1 Peter"), QVariant(75));
    newTestamentCombo->addItem(tr("2 Peter"), QVariant(76));
    newTestamentCombo->addItem(tr("1 John"), QVariant(77));
    newTestamentCombo->addItem(tr("2 John"), QVariant(78));
    newTestamentCombo->addItem(tr("3 John"), QVariant(79));
    newTestamentCombo->addItem(tr("Jude"), QVariant(80));
    newTestamentCombo->addItem(tr("Revelation"), QVariant(81));


    criteriaGroupBox = new QGroupBox(tr("Search Criteria"));
    rangeGroupBox = new QGroupBox(tr("Search Range"));

    caseCheckBox = new QCheckBox(tr("Case-sensitive"));

    entireBibleRadio = new QRadioButton(tr("Entire Bible"));
    entireBibleRadio->setChecked(true);
    oldTestamentRadio = new QRadioButton(tr("Old Testament"));
    newTestamentRadio = new QRadioButton(tr("New Testament"));

    QLabel *excludeLabel = new QLabel(tr("Exclude"));;

    resultsTextEdit = new QTextEdit;
    excludeLineEdit = new QLineEdit;

    searchButton = new QPushButton(tr("Search"));
    doneButton = new QPushButton(tr("Done"));
    connect(doneButton, SIGNAL(clicked()), this, SLOT(accept()));
    cancelButton = new QPushButton(tr("Cancel"));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));

    setFixedSize(SEARCH_WIDTH, SEARCH_HEIGHT );
    QGridLayout *mainLayout = new QGridLayout;
    QGridLayout *criteriaLayout = new QGridLayout;
    QGridLayout *rangeLayout = new QGridLayout;

    criteriaLayout->addWidget(criteriaCombo,    0, 0, 1, 4);
    criteriaLayout->addWidget(caseCheckBox,     1, 0, 1, 2);
    criteriaLayout->addWidget(excludeLabel,     2, 0, 1, 1);
    criteriaLayout->addWidget(excludeLineEdit,  2, 1, 1, 3);

    rangeLayout->addWidget(entireBibleRadio,    0, 0);
    rangeLayout->addWidget(oldTestamentRadio,   1, 0);
    rangeLayout->addWidget(oldTestamentCombo,   1, 1);
    rangeLayout->addWidget(newTestamentRadio,   2, 0);
    rangeLayout->addWidget(newTestamentCombo,   2, 1);

    criteriaGroupBox->setLayout(criteriaLayout);
    rangeGroupBox->setLayout(rangeLayout);

    mainLayout->addWidget(searchFieldCombo, 0, 0, 1, 3);
    mainLayout->addWidget(searchButton,     0, 3, 1, 1);
    mainLayout->addWidget(doneButton,       0, 4, 1, 1);
    mainLayout->addWidget(cancelButton,     0, 5, 1, 1);
    mainLayout->addWidget(criteriaGroupBox, 1, 0, 1, 3);
    mainLayout->addWidget(rangeGroupBox,    1, 3, 1, 3);
    mainLayout->addWidget(resultsTextEdit,  2, 0, 1, 6);


    setWindowTitle(tr("Search LimeBible"));
    setLayout(mainLayout);

}
