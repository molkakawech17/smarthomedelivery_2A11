#include "client.h"
//#include "carte.h"
#include <QDebug>


client::client()
{
cin=0;
nom="";
prenom="";
email="";
numero=0;
}

client::client(QString prenom,QString nom,int cin,int numero,QString email)
{
    this->email=email;
    this->nom=nom;
    this->prenom=prenom;
    this->numero=numero;
    this->cin=cin;
}
QString client::getprenom(){return prenom;}
QString client::getnom(){return nom;}
int client::getcin(){return cin;}
int client::getnumero(){return numero;}
QString client::getemail(){return email;}

bool client::ajouterclient()
{
    QSqlQuery query;
    QString cin_string= QString::number(cin);
    QString abo_string= QString::number(numero);
    query.prepare("INSERT INTO client( PRENOM, NOM, CIN, NUMERO, EMAIL)"
                  "VALUES (:prenom, :nom, :cin, :numero, :email)");

    query.bindValue(":prenom",prenom);
    query.bindValue(":nom",nom);
    query.bindValue(":cin",cin_string);
    query.bindValue(":numero",abo_string);
    query.bindValue(":email",email);

    return query.exec();
}



bool client::modifierclient(QString email ,QString nom,QString prenom , int numero)
{
    QSqlQuery query;
    query.prepare(" UPDATE client set NOM=:nom ,PRENOM=:prenom,NUMERO=:numero where EMAIL='"+email+"'");
    query.bindValue(":email",email);
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":numero",numero);
    return query.exec();
}



QSqlQueryModel *client::afficherclient()
{
    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("select *from client");

    model->setHeaderData(0,Qt::Horizontal,QObject::tr("PRENOM"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("CIN"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("NUMERO"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("EMAIL"));

    return model;
}

bool client:: supprimerclient(QString email)
{
    QSqlQuery query;

    query.prepare("delete from client where EMAIL=:email");
    query.bindValue(":email",email);

    return query.exec();
}


QSqlQueryModel * client::chercher_client_email(QString nom)
{

    QSqlQueryModel * model= new QSqlQueryModel();
    QSqlQuery query;
    nom='%'+nom+'%';
    query.prepare(" select * from client where email like :nom order by email ");
    query.bindValue(":nom",nom);
    query.exec();
    model->setQuery(query);
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("EMAIL"));
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("NOM "));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("NUMERO"));
        return model;

}

QSqlQueryModel * client::chercher_client_nom(QString nomcher)
{

    QSqlQueryModel * model= new QSqlQueryModel();
    QSqlQuery query;
    nomcher='%'+nomcher+'%';
    query.prepare(" select * from client where nom like :nomcher order by nom ");
    query.bindValue(":nomcher",nomcher);
    query.exec();
    model->setQuery(query);
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("EMAIL"));
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("NOM "));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("NUMERO"));
        return model;

}

QSqlQueryModel * client::chercher_client_prenom(QString prenomcher)
{

    QSqlQueryModel * model= new QSqlQueryModel();
    QSqlQuery query;
    prenomcher='%'+prenomcher+'%';
    query.prepare(" select * from client where nom like :prenomcher order by prenom ");
    query.bindValue(":prenomcher",prenomcher);
    query.exec();
    model->setQuery(query);
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("EMAIL"));
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("NOM "));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("NUMERO"));
        return model;

}
QSqlQueryModel * client::afficher_tri_email()
{
    QSqlQueryModel * model= new QSqlQueryModel();
model->setQuery("select * from client order by email");
model->setHeaderData(4, Qt::Horizontal, QObject::tr("EMAIL"));
model->setHeaderData(0, Qt::Horizontal, QObject::tr("NOM "));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("PRENOM"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("NUMERO"));
return model;
}

QSqlQueryModel * client::afficher_tri_cin()
{
    QSqlQueryModel * model= new QSqlQueryModel();
model->setQuery("select * from client order by cin");
model->setHeaderData(4, Qt::Horizontal, QObject::tr("EMAIL"));
model->setHeaderData(0, Qt::Horizontal, QObject::tr("NOM "));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("PRENOM"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("NUMERO"));
return model;

}























