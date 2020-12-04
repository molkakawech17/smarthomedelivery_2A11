#ifndef Promotion_H
#define Promotion_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include<QDate>

class Promotion
{public:
    Promotion();
    Promotion(QString,QString,int,QDate,QString);
    QString get_nom();
    int get_pourc();
    QString get_id();
    QString get_id_p();

    QDate get_date();
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    bool modifier();
    bool test_pourc(int);
    QSqlQueryModel *displayClause(QString cls);
    QSqlQueryModel *trideccroissant();
    QSqlQueryModel *tricroissant();


private:
    QString nom,id,id_p;
    int pourc;
    QDate datee;
};

#endif // Promotion_H
