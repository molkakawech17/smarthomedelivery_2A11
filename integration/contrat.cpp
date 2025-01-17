#include "contrat.h"
#include <QApplication>
#include <QString>
#include <QSqlQueryModel>
#include<QSqlQuery>
#include <QDebug>
#include "QMessageBox"


contrat::contrat()
{

};
contrat::contrat(int a , QString b, int c, QString d,QString e)
{
    this->cin=a;
    this->salaire=b;
    this->duree=c;
    this->datedeb=d;
    this->EMAIL=e;

}
int contrat::getcin()
{
    return cin;
}
QString contrat::getsalaire()
{
    return salaire;
}
int contrat::getduree()
{
    return duree;
}
QString contrat::getdatedeb()
{
    return datedeb;
}
QString contrat::getEMAIL()
{
    return EMAIL;
}
bool contrat::ajouter_contrat()
{
    qDebug()<<"rao dkhal ";

    QSqlQuery q;
    q.prepare("INSERT into contrat (salaire, duree, datedeb, EMAIL, cin)" "VALUES (:salaire, :duree, :datedeb, :EMAIL, :cin)");
     q.bindValue(":salaire", this->salaire);
     q.bindValue(":duree", this->duree);

    q.bindValue(":datedeb",this->datedeb);


    q.bindValue(":EMAIL", this->EMAIL);
    q.bindValue(":cin", this->cin);

    if (q.exec())
    {
        qDebug()<<"contrat ajoute";
        QMessageBox ::information(nullptr, QObject::tr("ajouter un contrat"),
                                 QObject::tr(" contrat ajouté.\n"
                                             "Click to cancel."), QMessageBox::Cancel);

        return true;
    }
    else{
        qDebug()<<"contrat n'est pas ajoute";
        QMessageBox::information(nullptr, QObject::tr("ajouter un contrat"),
                                 QObject::tr(" contrat blcin.\n"
                                             "Click to cancel."), QMessageBox::Cancel);
        return false;
    }}

bool contrat::delatecontrat(int cin)
 {

     QSqlQuery q;
     q.prepare("DELETE from contrat where cin=:cin");
     q.bindValue(":cin",cin);
     q.exec();
     if(q.exec())
     {
         qDebug()<<"contrat supprimer";
         QMessageBox::information(nullptr, QObject::tr("supprimer un contrat"),
                                  QObject::tr(" contrat supprimé.\n"
                                              "Click to cancel."), QMessageBox::Cancel);
         return true;
     }
     else
         {
         qDebug()<<"contrat blcin";
         QMessageBox::information(nullptr, QObject::tr("supprimer un contrat"),
                                  QObject::tr(" contrat blcin.\n"
                                              "Click to cancel."), QMessageBox::Cancel);
         return false;
     }

 }

void contrat::modifier_contrat(int cin )
{
    QSqlQuery q;
    q.prepare("UPDATE contrat  SET salaire=:salaire,duree=:duree,datedeb=:datedeb,EMAIL=:EMAIL where cin=:cin");

    q.bindValue(":salaire", this->salaire);
    q.bindValue(":duree", this->duree);
    q.bindValue(":datedeb", this->datedeb);
    q.bindValue(":EMAIL", this->EMAIL);
    q.bindValue(":cin",cin);

q.exec();
if(q.exec())
qDebug()<<"contrat modifie";
}
bool contrat::cherchercontrat(int cin)
{


    QSqlQuery q;
    q.prepare("SELECT * from contrat where cin=:cin");
    q.bindValue(":cin",cin);
    q.exec();
   bool v= q.next();
     if(v)
   {
    return true;

   }
    return false;
}
QSqlQueryModel *contrat::getAllcontrat() //affichduree de la base de données
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM  contrat");
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("datedeb "));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("duree"));
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("salaire"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("EMAIL"));
    return model;
}
QSqlQueryModel *contrat::getAllcontratcin() //affichduree de la base de données
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT cin  FROM  contrat");
    return model;

}
contrat contrat::getcontrat(int cin)
 {
     contrat *p = new contrat();
    QSqlQuery q;
     q.prepare("SELECT * from contrat where cin=:cin");
     q.bindValue(":cin",cin);
     q.exec();
    // qDebug()<<cin;
     while (q.next()) {
         qDebug()<<q.value(4).toString();

         setcin(q.value(4).toInt());
         setsalaire(q.value(0).toString());
         setduree(q.value(1).toInt()) ;
         setdatedeb(q.value(2).toString());
         setEMAIL(q.value(3).toString());

     }
 return *p;}

QSqlQuery contrat::exporter(int cin)
{
    QSqlQuery query;

    query.prepare("select * from contrat where cin=:cin");
    query.bindValue(":cin",cin);
    query.exec();

    return query;
}
QSqlQueryModel *contrat::getAllcontratavance(QString ch)
{
    QSqlQueryModel *model=new QSqlQueryModel();
    QSqlQuery *q=new QSqlQuery();
    q->prepare("SELECT * FROM contrat WHERE EMAIL LIKE '%"+ch+"%' or SALAIRE LIKE '%"+ch+"%'or CIN LIKE '%"+ch+"%'");
    q->exec();
    model->setQuery(*q);
    return model;
}









