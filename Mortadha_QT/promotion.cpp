#include "promotion.h"
#include <QDebug>
#include "connexion.h"
Promotion::Promotion()
{
id="";
nom="";
pourc=0;
id_p="";
}
Promotion::Promotion(QString id,QString nom,int pourc,QDate datee,QString id_p)
{
  this->id=id;
  this->nom=nom;
  this->pourc=pourc;
  this->datee=datee;
  this->id_p=id_p;

}
QString Promotion::get_nom(){return  nom;}
int Promotion::get_pourc(){return pourc;}
QString Promotion::get_id(){return  id;}
QDate Promotion::get_date(){return  datee;}
QString Promotion::get_id_p(){return  id_p;}



bool Promotion::ajouter()
{
QSqlQuery query;
query.prepare("INSERT INTO PROMOTION (ID,NOM,POURCENTAGE,DATEE,ID_P) "
                    "VALUES (:id, :nom, :pourc,:datee,:id_p)");
query.bindValue(":id", id);
query.bindValue(":nom", nom);
query.bindValue(":pourc", pourc);
query.bindValue(":datee", datee);
query.bindValue(":id_p", id_p);



return    query.exec();
}

QSqlQueryModel * Promotion::afficher()
{QSqlQueryModel * model= new QSqlQueryModel();
model->setQuery("select * from PROMOTION");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Pourcentage %"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("id_p"));


    return model;
}

bool Promotion::supprimer(int idd)
{
QSqlQuery query;
QString res= QString::number(idd);
query.prepare("Delete from PROMOTION where ID = :id ");
query.bindValue(":id", res);
return    query.exec();
}

bool Promotion::modifier()
{   QSqlQuery query;
    query.prepare( "UPDATE PROMOTION SET ID=:id,NOM=:nom,POURCENTAGE=:pourc,DATEE=:datee,ID_P=:id_p WHERE ID=:id");
    query.bindValue(":id",id);
    query.bindValue(":nom",nom);
    query.bindValue(":pourc",pourc);
    query.bindValue(":datee",datee);
    query.bindValue(":id_p", id_p);



 return query.exec();
}
bool Promotion::test_pourc(int pourcentage)
{

if ((pourcentage>0)&&(pourcentage<100))
    return true ;

    return false;

}

QSqlQueryModel *Promotion::displayClause(QString cls)
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("SELECT * FROM PROMOTION " +cls);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Pourcentage %"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("id_p"));

    return model;
}


QSqlQueryModel * Promotion::tricroissant()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * FROM PROMOTION ORDER BY POURCENTAGE ASC");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Pourcentage %"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("id_p"));

    return model;
}
QSqlQueryModel * Promotion::trideccroissant()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * FROM PROMOTION ORDER BY POURCENTAGE DESC");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Pourcentage %"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("id_p"));

    return model;
}
