#include "commandes.h"
#include<QMessageBox>
#include "connexion.h"

Commande::Commande()
{
    id="";
    id_f="";
    id_p="";
    datee=QDate();
    prix=0;
    quantite=0;
    etat="";
}
Commande::Commande(QString id,QString id_f,QString id_p,int quantite,int prix,QDate datee,QString etat)
{
    this->id=id;
     this->id_f=id_f;
    this->id_p=id_p;

    this->quantite=quantite;
    this->etat=etat;


    this->datee=datee;
    this->prix=prix;


}
int Commande::get_prix(){return prix;}
int Commande::get_quantite(){return quantite;}
QDate Commande::get_datee(){return datee;}
QString Commande::get_id(){return id;}
QString Commande::get_idp(){return id_p;}
QString Commande::get_idf(){return id_f;}
QString Commande::get_etat(){return etat;}











bool Commande::ajouter()
{   QSqlQuery query;
    query.prepare("INSERT INTO COMMANDES (ID,ID_F,ID_P,QUANTITE,PRIX,DATEE,ETAT)""VALUES(:id,:id_f,:id_p,:quantite,:prix,:datee,:etat)");
    query.bindValue(":id",id);
    query.bindValue(":id_f",id_f);
    query.bindValue(":id_p",id_p);
    query.bindValue(":quantite",quantite);
    query.bindValue(":datee",datee);
    query.bindValue(":etat",etat);
    query.bindValue(":prix",prix);

 return query.exec();
}


bool Commande::supprimer(QString id)
{
    QSqlQuery query;
    query.prepare("Delete from COMMANDES WHERE (ID LIKE '"+id+"')");
    return    query.exec();
}
bool Commande::modifier()
{   QSqlQuery query;
    query.prepare( "UPDATE COMMANDES SET ID=:id,ID_F=:id_f,ID_P=:id_p,QUANTITE=:quantite,PRIX=:prix,DATEE=:datee,ETAT=:etat WHERE ID=:id");
    query.bindValue(":id",id);
    query.bindValue(":id_f",id_f);
    query.bindValue(":id_p",id_p);
    query.bindValue(":quantite",quantite);
    query.bindValue(":datee",datee);
    query.bindValue(":etat",etat);
    query.bindValue(":prix",prix);


 return query.exec();
}
QSqlQueryModel * Commande::afficher()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from COMMANDES");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("ID_F"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("ID_P"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("QUANTITE"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("PRIX"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("DATE"));
model->setHeaderData(6, Qt::Horizontal, QObject::tr("ETAT"));


    return model;
}


QSqlQueryModel *Commande::displayClause(QString cls)
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("SELECT * FROM COMMANDES " +cls);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("ID_F"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("ID_P"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("QUANTITE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("PRIX"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("DATE"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("ETAT"));

    return model;
}

QSqlQueryModel * Commande::tricroissant()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * FROM COMMANDES ORDER BY PRIX ASC");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("ID_F"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("ID_P"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("QUANTITE"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("PRIX"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("DATE"));
model->setHeaderData(6, Qt::Horizontal, QObject::tr("ETAT"));

    return model;
}
QSqlQueryModel * Commande::trideccroissant()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * FROM COMMANDES ORDER BY PRIX DESC");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("ID_F"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("ID_P"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("QUANTITE"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("PRIX"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("DATE"));
model->setHeaderData(6, Qt::Horizontal, QObject::tr("ETAT"));

    return model;
}






