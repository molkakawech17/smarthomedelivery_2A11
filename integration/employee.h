#ifndef employee_H
#define employee_H

#include <QDialog>
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>


class employee
{

private:

    QString NOM;
    QString Prenom; // prenom
    int cin;// cin
    int age; // age
    QString poste;


public:

    employee (int a , QString b, int c, QString d,QString e);
    employee();

    int getcin();
    QString getposte();
    QString getPrenom();
    QString getNOM();
    int getage();

    void setcin(int a){cin=a;}
    void setNOM(QString b){NOM=b;}
    void setage(int c){age=c;}
    void setPrenom(QString d){Prenom=d;}
    void setposte(QString e){poste=e;}
    void modifier_employee(int cin);

    employee getemployee(int cin);

    bool ajouter_employee();
    bool chercheremployee(int cin);
    bool delateemployee(int cin);

    QSqlQueryModel* getAllemployeecin();
    QSqlQueryModel* getAllemployee();
    QSqlQueryModel* getAllemployeeavance(QString ch);
    QSqlQueryModel* getMattri();
    QSqlQueryModel* getemployeestriid();
    QSqlQueryModel* getemployeestrinom();
    QSqlQueryModel* getemployeestriprenom();
    QSqlQueryModel* getemployeestriage();
    QSqlQueryModel* getemployeestriposte();

};

#endif //
