#include "produit.h"
produit::produit(int qt,QString nom,QString type,QString pays)
{
this->qt=qt;
this->nom=nom;
this->pays=pays;
this->type=type;

}
bool produit::ajouter()
{
  QSqlQuery query ;
query.prepare("INSERT INTO produit (nom,pays,type,qt) VALUES (:nom,:pays,:type,:qt) ") ;
QString r = QString::number(qt);
query.bindValue(":nom",nom);
query.bindValue(":qt",r);
query.bindValue(":pays",pays);
query.bindValue(":type",type);
return query.exec();
}
QSqlQueryModel * produit::afficher()
{
QSqlQueryModel * model = new QSqlQueryModel();
model->setQuery("select * from produit");
model->setHeaderData(0,Qt::Horizontal,"nom");
model->setHeaderData(1,Qt::Horizontal,"type");
model->setHeaderData(2,Qt::Horizontal,"pays");
model->setHeaderData(3,Qt::Horizontal,"qt-stock");
return model ;
}
bool produit::supprimer(QString nom)
{
    QSqlQuery query ;
    query.prepare("DELETE FROM PRODUIT WHERE nom=:nom  ") ;
    QString r = QString::number(qt);
    query.bindValue(":nom",nom);
    query.bindValue(":qt",r);
    query.bindValue(":pays",pays);
    query.bindValue(":type",type);
    return query.exec();

}
bool produit::modifier()
{
  QSqlQuery query ;
query.prepare("update produit set qt=:qt,nom=:nom,pays=:pays,type=:type where nom=:nom ");
QString r = QString::number(qt);
query.bindValue(":nom",nom);
query.bindValue(":qt",r);
query.bindValue(":pays",pays);
query.bindValue(":type",type);
return query.exec();
}
QSqlQueryModel * produit::triproduit(const QString &arg1)
{
    QSqlQueryModel * model = new QSqlQueryModel();
   model->setQuery("select * from produit where(nom LIKE '"+arg1+"%')");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("type"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("pays"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("qt_stock"));

        return model;
}
QSqlQueryModel * produit::cherchernom(const QString &arg1)
{
    QSqlQueryModel * model = new QSqlQueryModel();
    QSqlQuery query;
   model->setQuery("select nom,type,pays,qt from produit where nom like '"+arg1+"%' or type like '"+arg1+"%'  or pays like '"+arg1+"%' or qt like '"+arg1+"%' ;");
  query.bindValue(":arg1",arg1);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("type"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("pays"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("qt_stock"));

        return model;
}

