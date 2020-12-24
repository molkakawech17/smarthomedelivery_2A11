#include "carte.h"
#include <QDebug>
#include "connexion.h"
Carte::Carte()
{
    ref ="";
    cinClient=0;
    nombredespoints=0;
}
Carte::Carte(QString ref,int cinClient,int nombredespoints)
{
    this->ref=ref;
    this->nombredespoints=nombredespoints;
    this->cinClient=cinClient ;
}
bool Carte::ajouter(Carte Ca)
{
    QSqlQuery query;
    QString res= QString::number(cinClient);
    query.prepare("INSERT INTO carte (REF,CINCLIENT,NOMBREDESPOINTS) "
                        "VALUES (:ref, :cinClient ,:nombredespoints)");
    query.bindValue(":ref",Ca.get_ref());
    query.bindValue(":cinClient",res);
    query.bindValue(":nombredespoints",Ca.get_nombredespoints());
    return query.exec();
}

QSqlQueryModel * Carte::afficher()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from CARTE");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ref"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("cinClient"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("nombredespoints"));

    return model;
}

bool Carte::supprimer(QString reff)
{
QSqlQuery query;
//QString ref= QString::number(ref);
query.prepare("Delete from carte where ref = :ref ");
query.bindValue(":ref", reff);
return    query.exec();
}
bool Carte::modifier(QString REF,Carte Ca)
{
    QSqlQuery query;

       query.prepare("UPDATE CARTE SET  CINCLIENT =:cinClient ,NOMBREDESPOINTS =:nombredespoints WHERE REF =:ref ");
       query.bindValue(":ref", Ca.get_ref());
       query.bindValue(":cinClient", Ca.get_cinClient());
       query.bindValue(":nombredespoints",Ca.get_nombredespoints());

    return query.exec();
}
/*
QSqlQueryModel *Carte::tri()
{
QSqlQuery *q = new QSqlQuery();
QSqlQueryModel *model = new QSqlQueryModel();
q->prepare("SELECT * FROM CARTE ORDER BY NOMBREDESPOINTS");
q->exec();
model->setQuery(*q);
return model;
}
*/

QSqlQueryModel *Carte::rechercherrefcarte(const QString &id)
{

//QString reff= QString::number(ref);
QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("SELECT * FROM CARTE WHERE (ref LIKE '"+id+"%')");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ref"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("cinClient"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("nombredespoints"));

return model;

}
