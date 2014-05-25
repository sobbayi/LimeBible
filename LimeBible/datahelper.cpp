/**
 LimeBible 2.0 series

 */
#include <QMessageBox>
#include <QStringList>
#include <QFile>
#include "datahelper.h"

DataHelper::DataHelper(QObject *parent) :
    QObject(parent)
{

}

DataHelper::~DataHelper()
{
    sqlite3_close(db);
}

bool DataHelper::openDataConn()
{


    if(QFile::exists ( "core.ldb"))
    {
        sqlite3_open("core.ldb", &db);
        return true;
    }
    else
    {
        return false;
    }

}

QString DataHelper::s = "";
QString DataHelper::id = "";
int DataHelper::currentIndex = 0;

 int DataHelper::callback(void *notUsed, int argc, char **argv, char **azColName)
 {
     int i;
        if(QString("%1").arg(argv[0]).compare(QString("%1").arg(DataHelper::currentIndex)) == 0){
            s.append("<div style='background:#84DB27'><b>");
            DataHelper::currentIndex = 0;
        }
        else
            s.append("<div><b>");


     for(i=0; i<argc; i++){
              if(i>0)
                 s.append(QString("%1").arg(argv[i]));

           switch (i){

            case 0 :

                break;
            case 1 :
                s.append(" ");
                break;
            case 2 :
                s.append(":");
                break;
            case 3 :
                s.append("</b>  ");
                break;
            case 4 :
                 s.append("</div>");
                break;
            }
         }

    return 0;
 }

 int DataHelper::callbackSearch(void *notUsed, int argc, char **argv, char **azColName)
 {
     int i;

     for(i=0; i<argc; i++){

           switch (i){

            case 0 :
                id.append(QString("%1").arg(argv[i]));
                id.append("|");
                 break;
            case 1 :
               s.append(QString("%1").arg(argv[i]));
               s.append("|");
                break;
             }


         }

    return 0;
 }

void DataHelper::getBasicData(QString bookName, int chapter, sqlite3 *db)
{
    int rc;
    char *zErrMsg = 0;
    QString st = "SELECT id, abbr, chapter, verse, line FROM bible_kjv ";
    st.append("WHERE name MATCH '");
    st.append(bookName);
    st.append("' AND chapter = ");
    st.append(QString("%1").arg(chapter));
    st.append(" ORDER BY id");

    rc = sqlite3_exec(db, st.toLocal8Bit(), DataHelper::callback, 0, &zErrMsg);
        if( rc!=SQLITE_OK ){
          QMessageBox msgBox;

          msgBox.setText(QString("Error: %1\n").arg(sqlite3_errmsg(db)));
          msgBox.setStandardButtons(QMessageBox::Abort);
          msgBox.exec();
         sqlite3_free(zErrMsg);
       }

}



void DataHelper::getSearchedResults(QString searchText, int criteriaInt,
             int firstCombo, int secondCombo, sqlite3 *db)
{

   QString st = "SELECT id, abbr || ' ' || chapter || ':' "
           "|| verse || ' ' || line as content FROM bible_kjv ";

   QStringList sList = searchText.split(" ", QString::SkipEmptyParts);
   int c = sList.count();

   if(criteriaInt == 0)
   {
       st.append("WHERE line MATCH '");
       for(int i=0; i<c;i++){
           if(i>0)
          st.append(" AND ");
          st.append(sList[i]);

       }
       st.append("' ");

   }
   else if(criteriaInt == 1)
   {
       st.append("WHERE line MATCH '");
       for(int i=0; i<c;i++){
           if(i>0)
          st.append(" OR ");
          st.append(sList[i]);

       }
       st.append("' ");

   }
   else
   {
        st.append("WHERE line MATCH '\"");
        st.append(searchText);
        st.append("\"' ");
   }

   st.append(" AND (bookid >= ");
   st.append(QString("%1").arg(firstCombo+1));
   st.append(" AND bookid <= ");
   st.append(QString("%1").arg(secondCombo+1));
   st.append(")");


   int rc;
   char *zErrMsg = 0;

   rc = sqlite3_exec(db, st.toLocal8Bit(), DataHelper::callbackSearch, 0, &zErrMsg);
       if( rc!=SQLITE_OK ){
         QMessageBox msgBox;

         msgBox.setText(QString("Error: %1\n").arg(sqlite3_errmsg(db)));
         msgBox.setStandardButtons(QMessageBox::Abort);
         msgBox.exec();
        sqlite3_free(zErrMsg);
      }
}

void DataHelper::showSeachResult(int row, QTextEdit *textEdit)
{
    int rc;
    char *zErrMsg = 0;
    QString st = "SELECT id, abbr, chapter, verse, line FROM bible_kjv ";
    st.append("WHERE abbr = (SELECT abbr from bible_kjv WHERE id MATCH ");
    st.append(QString("%1").arg(row));
    st.append(") AND chapter = (SELECT chapter from bible_kjv WHERE id MATCH ");
    st.append(QString("%1").arg(row));
    st.append(")");

    currentIndex = row;
    rc = sqlite3_exec(db, st.toLocal8Bit(), DataHelper::callback, 0, &zErrMsg);
        if( rc!=SQLITE_OK ){
          QMessageBox msgBox;

          msgBox.setText(QString("Error: %1\n").arg(sqlite3_errmsg(db)));
          msgBox.setStandardButtons(QMessageBox::Abort);
          msgBox.exec();
         sqlite3_free(zErrMsg);

       }
        textEdit->setHtml(DataHelper::s);
        textEdit->setEnabled(true);
        DataHelper::s.clear();

}
