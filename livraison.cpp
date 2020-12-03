#include "livraison.h"

livraison::livraison(int cin,QString add,QString ref,QString nom1)
{
this->cin=cin;
this->add=add;
this->nom1=nom1;
this->ref=ref;

}
bool livraison::ajouter()
{
  QSqlQuery query ;
query.prepare("INSERT INTO livraison (name1,cin,ref,addd) VALUES (:nom1,:cin,:ref,:add) ") ;
QString l = QString::number(cin);
query.bindValue(":nom1",nom1);
query.bindValue(":cin",l);
query.bindValue(":ref",ref);
query.bindValue(":add",add);
return query.exec();
}
QSqlQueryModel * livraison::afficher()
{
QSqlQueryModel * model = new QSqlQueryModel();
model->setQuery("select * from livraison");
model->setHeaderData(0,Qt::Horizontal,"ref");
model->setHeaderData(1,Qt::Horizontal,"nom");
model->setHeaderData(2,Qt::Horizontal,"cin");
model->setHeaderData(3,Qt::Horizontal,"add");
return model ;
}
bool livraison::supprimer(QString ref)
{
    QSqlQuery query ;
    query.prepare("DELETE FROM livraison WHERE ref=:ref  ") ;
    QString l = QString::number(cin);
    query.bindValue(":nom1",nom1);
    query.bindValue(":cin",l);
    query.bindValue(":ref",ref);
    query.bindValue(":add",add);
    return query.exec();

}
bool livraison::modifier()
{
  QSqlQuery query ;
query.prepare("update produit set cin=:cin,name1=:nom1,addd=:add,ref=:ref where ref=:ref ");
QString l = QString::number(cin);
query.bindValue(":nom1",nom1);
query.bindValue(":cin",l);
query.bindValue(":add",add);
query.bindValue(":ref",ref);
return query.exec();
}
QSqlQueryModel * livraison::trilivraison(const QString &arg1)
{
    QSqlQueryModel * model = new QSqlQueryModel();
   model->setQuery("select * from livraison where(ref LIKE '"+arg1+"%')");
   model->setHeaderData(0, Qt::Horizontal, QObject::tr("ref"));
   model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
   model->setHeaderData(2, Qt::Horizontal, QObject::tr("cin"));
   model->setHeaderData(3, Qt::Horizontal, QObject::tr("add"));

        return model;
}
QSqlQueryModel * livraison::cherchernom1(const QString &arg1)
{
    QSqlQueryModel * model = new QSqlQueryModel();
    QSqlQuery query;
   model->setQuery("select ref,nom1,cin,add from livraison where ref like '"+arg1+"%' or nom1 like '"+arg1+"%'  or cin like '"+arg1+"%' or add like '"+arg1+"%' ;");
  query.bindValue(":arg1",arg1);
  model->setHeaderData(0, Qt::Horizontal, QObject::tr("ref"));
  model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
  model->setHeaderData(2, Qt::Horizontal, QObject::tr("cin"));
  model->setHeaderData(3, Qt::Horizontal, QObject::tr("add"));

        return model;
}
