/**
 LimeBible 1.0 series

 */
#ifndef DATAHELPER_H
#define DATAHELPER_H

#include <QObject>
#include <QMessageBox>
#include <QTextEdit>
#include "sqlite3.h"

class DataHelper : public QObject
{
    Q_OBJECT
public:
    explicit DataHelper(QObject *parent = 0);
    ~DataHelper();
    static QString s ;
    static QString id ;
    static int currentIndex;
    bool openDataConn();
    static int callback(void *notUsed, int argc, char **argv, char **azColName);
    static int callbackSearch(void *notUsed, int argc, char **argv, char **azColName);
    void getBasicData(QString bookName, int chapter, sqlite3 *db);

    void getSearchedResults(QString searchText,
                                 int criteriaInt,
                                 int firstCombo,
                                 int secondCombo,
                                 sqlite3 *db);
    void showSeachResult(int row, QTextEdit *textEdit);


    sqlite3* db;



signals:


public slots:

};

#endif // DATAHELPER_H
