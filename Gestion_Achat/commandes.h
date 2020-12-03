#ifndef COMMANDES_H
#define COMMANDES_H
#include <QDialog>
#include<QSqlQueryModel>
#include<QSqlQuery>
#include<QDate>


class Commande
{
public:
    Commande();
    Commande (QString,QString,QString,int,int,QDate,QString);
    QString get_id();
    QDate get_datee();
    QString get_idf();
    QString get_idp();
    QString get_etat();
    int get_prix();
    int get_quantite();





    bool ajouter();
    bool modifier();
    QSqlQueryModel *afficher();
    QSqlQueryModel *displayClause(QString cls);
    QSqlQueryModel *trideccroissant();
        QSqlQueryModel *tricroissant();


    bool supprimer(QString);

private:
    QDate datee;
    int quantite;
    QString id,id_f,id_p,etat;
    int prix;
};

#endif
