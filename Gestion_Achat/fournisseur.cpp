#include "fournisseur.h"
#include <QDebug>
#include "connexion.h"
Fournisseur::Fournisseur()
{
cin="";
prenom="";
nom="";
tel=0;
mail="";
}
Fournisseur::Fournisseur(QString cin,QString prenom,QString nom,QString mail,long tel)
{
  this->cin=cin;
  this->nom=nom;
    this->prenom=prenom;
  this->tel=tel;
  this->mail=mail;

}
QString Fournisseur::get_cin(){return cin;}

QString Fournisseur::get_prenom(){return  prenom;}

QString Fournisseur::get_nom(){return  nom;}
QString Fournisseur::get_mail(){return  mail;}
long Fournisseur::get_tel(){return tel;}



bool Fournisseur::ajouter()
{
QSqlQuery query;
QString res= QString::number(tel);

query.prepare("INSERT INTO FOURNISSEUR (CIN,PRENOM,NOM,MAIL,TEL) "
                    "VALUES (:cin, :prenom, :nom, :mail,:tel)");
query.bindValue(":cin", cin);
query.bindValue(":prenom",prenom);
query.bindValue(":nom",nom);
query.bindValue(":mail",mail);
query.bindValue(":tel",res);



return    query.exec();
}

QSqlQueryModel * Fournisseur::afficher()
{QSqlQueryModel * model= new QSqlQueryModel();
model->setQuery("select * from FOURNISSEUR");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("PRENOM"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("NOM"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("MAIL"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("TEL"));


    return model;
}

bool Fournisseur::supprimer(int cin)
{
QSqlQuery query;
QString res= QString::number(cin);
query.prepare("Delete from FOURNISSEUR where CIN = :cin ");
query.bindValue(":cin", res);
return    query.exec();
}

bool Fournisseur::modifier()

{   QSqlQuery query;
    QString res= QString::number(tel);

    query.prepare( "UPDATE FOURNISSEUR SET CIN=:cin,PRENOM=:prenom,NOM=:nom,MAIL=:mail,TEL=:tel WHERE CIN=:cin");
    query.bindValue(":cin",cin);
    query.bindValue(":prenom",prenom);
    query.bindValue(":nom",nom);
    query.bindValue(":mail",mail);
    query.bindValue(":tel",res);


 return query.exec();
}

bool Fournisseur::testmail(QString mail){
    int test=0;
    for(int i = 0; i < mail.size(); i++) {
if(mail[i]=="@")
{test++;

}}
    for(int i = 0; i < mail.size(); i++) {
if((test==1)&&(mail[i]=="."))
{if(mail.size()>i+1)
    return true;
}}
return false;}


bool Fournisseur::testnumber(QString number){


    if(number.size()==8)
        return true;
    return false;



}
bool Fournisseur::testCin(QString cin){
    if(cin.size()!=8)
    return false;

    for(int i = 0; i < cin.size(); i++) {


    if (!(cin[i] >= '0' && cin[i] <= '9'))
        return false;

}
    return true;


}




QSqlQueryModel *Fournisseur::displayClause(QString cls)
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("SELECT * FROM FOURNISSEUR " +cls);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("MAIL"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("TEL"));

    return model;
}


QSqlQueryModel * Fournisseur::tricroissant()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * FROM Fournisseur ORDER BY NOM ASC");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("PRENOM"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("NOM"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("MAIL"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("TEL"));

    return model;
}
QSqlQueryModel * Fournisseur::trideccroissant()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * FROM Fournisseur ORDER BY NOM DESC");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("PRENOM"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("NOM"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("MAIL"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("TEL"));

    return model;
}





