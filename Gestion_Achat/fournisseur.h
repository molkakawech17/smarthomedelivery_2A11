#ifndef Fournisseur_H
#define Fournisseur_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include<QDate>

class Fournisseur
{public:
    Fournisseur();
    Fournisseur(QString,QString,QString,QString,long);
    QString get_cin();
    QString get_nom();
    long get_tel();

    QString get_prenom();
    QString get_mail();

    QDate get_date();
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    bool modifier();
    bool testmail(QString);
    bool testnumber(QString);
    bool testCin(QString);
    QSqlQueryModel *displayClause(QString cls);
    QSqlQueryModel *trideccroissant();
        QSqlQueryModel *tricroissant();


private:
    QString nom,prenom,mail,cin;
    long tel;


};

#endif // Fournisseur_H
