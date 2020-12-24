#ifndef CONTRAT_H
#define CONTRAT_H


#include <QDialog>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QString>
#include "QTextBrowser"
#include "QtPrintSupport/QPrinter"


class contrat
{

private:

   QString salaire;
    QString datedeb; // datedeb
    int cin;// cin
    int duree; // duree
   QString EMAIL;


public:

    contrat (int a , QString b, int c, QString d,QString e);
    contrat();

    int getcin();
    QString getEMAIL();
    QString getdatedeb();
    QString getsalaire();
    int getduree();

    void setcin(int a){cin=a;}
    void setsalaire(QString b){salaire=b;}
    void setduree(int c){duree=c;}
    void setdatedeb(QString d){datedeb=d;}
    void setEMAIL(QString e){EMAIL=e;}
    void modifier_contrat(int cin);
    QSqlQuery exporter(int cin);


    contrat getcontrat(int cin);

    bool ajouter_contrat();
    bool cherchercontrat(int cin);
    bool delatecontrat(int cin);

    QSqlQueryModel* getAllcontratcin();
    QSqlQueryModel* getAllcontrat();
    QSqlQueryModel* getMattri();
    QSqlQueryModel* getAllcontratavance(QString cin);

};

#endif //
