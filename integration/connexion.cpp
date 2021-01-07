#include "connexion.h"
#include <QSqlError>
Connection::Connection()
{

}

bool Connection::createconnect()
{
    bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("test-bd");
db.setUserName("aziz");//inserer nom de l'utilisateur
db.setPassword("Lionelzizou12388");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;

else throw QString ("Erreur Paramétres"+db.lastError().text());


    return  test;
}
