#include "connexion.h"
#include "QSqlDatabase"
connexion::connexion()
{

}
bool connexion::createConnection(){
   bool test=false;
 QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
 db.setDatabaseName("test-bd");
 db.setUserName("aziz");
 db.setPassword("lionelzizou12388");
 if (db.open())
     test=true;
 return test;
}
