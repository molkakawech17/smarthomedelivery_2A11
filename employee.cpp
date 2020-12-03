#include "employee.h"
#include <QApplication>
#include <QString>
#include <QSqlQueryModel>
#include<QSqlQuery>
#include <QDebug>
#include "QMessageBox"

employee::employee()
{

};
employee::employee(int a , QString b, int c, QString d,QString e)
{
    this->cin=a;
    this->NOM=b;
    this->age=c;
    this->Prenom=d;
    this->poste=e;

}
int employee::getcin()
{
    return cin;
}
QString employee::getNOM()
{
    return NOM;
}
int employee::getage()
{
    return age;
}
QString employee::getPrenom()
{
    return Prenom;
}
QString employee::getposte()
{
    return poste;
}
bool employee::ajouter_employee()
{
    QSqlQuery q;
    q.prepare("INSERT into employee (cin, Prenom, age, NOM, poste)" "VALUES (:cin, :Prenom, :age, :NOM, :poste)");
    q.bindValue(":cin", this->cin);
    q.bindValue(":Prenom",this->Prenom);
    q.bindValue(":age", this->age);

    q.bindValue(":NOM", this->NOM);
    q.bindValue(":poste", this->poste);
    if (q.exec())
    {
        qDebug()<<"employee ajoute";
        QMessageBox::information(nullptr, QObject::tr("ajouter un employee"),
                                 QObject::tr(" employee ajouté.\n"
                                             "Click to cancel."), QMessageBox::Cancel);

        return true;
    }
    else{
        qDebug()<<"employee n'est pas ajoute";
        QMessageBox::information(nullptr, QObject::tr("ajouter un employee"),
                                 QObject::tr(" employee blcin.\n"
                                             "Click to cancel."), QMessageBox::Cancel);
        return false;
    }}

bool employee::delateemployee(int cin)
 {
     QSqlQuery q;
     q.prepare("DELETE from employee where cin=:cin");
     q.bindValue(":cin",cin);
     q.exec();
     if(q.exec())
     {
         qDebug()<<"employee supprimer";
         QMessageBox::information(nullptr, QObject::tr("supprimer un employee"),
                                  QObject::tr(" employee supprimé.\n"
                                              "Click to cancel."), QMessageBox::Cancel);
         return true;
     }
     else
         {
         qDebug()<<"employee blcin";
         QMessageBox::information(nullptr, QObject::tr("supprimer un employee"),
                                  QObject::tr(" employee blcin.\n"
                                              "Click to cancel."), QMessageBox::Cancel);
         return false;
     }

 }

void employee::modifier_employee(int cin)
{
    QSqlQuery q;
    q.prepare("UPDATE employee  SET NOM=:NOM,age=:age,Prenom=:Prenom,poste=:poste where cin=:cin");

    q.bindValue(":cin",cin);
    q.bindValue(":NOM", this->NOM);
    q.bindValue(":age", this->age);
    q.bindValue(":Prenom", this->Prenom);
    q.bindValue(":poste", this->poste);
q.exec();
if(q.exec())
qDebug()<<"employee modifie";
}
bool employee::chercheremployee(int cin)
{


    QSqlQuery q;
    q.prepare("SELECT * from employee where cin=:cin");
    q.bindValue(":cin",cin);
    q.exec();
   bool v= q.next();
     if(v)
   {
    return true;

   }
    return false;
}
QSqlQueryModel *employee::getAllemployee() //affichage de la base de données
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM  employee");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("PRENOM "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("AGE"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("POSTE"));
    return model;
}
QSqlQueryModel *employee::getAllemployeecin() //affichage de la base de données
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT cin  FROM  employee");
    return model;

}
employee employee::getemployee(int cin)
 {
     employee *p = new employee();
    QSqlQuery q;
     q.prepare("SELECT * from employee where cin=:cin");
     q.bindValue(":cin",cin);
     q.exec();
     qDebug()<<cin;
     while (q.next()) {
         qDebug()<<q.value(0).toString();
         setcin(cin);
         setNOM(q.value(3).toString());
         setage(q.value(2).toInt());
         setPrenom(q.value(1).toString());
         setposte(q.value(4).toString());
         }
 return *p;
 }

QSqlQueryModel *employee::getAllemployeeavance(QString ch)
{
    QSqlQueryModel *model=new QSqlQueryModel();
    QSqlQuery *q=new QSqlQuery();
    q->prepare("SELECT * FROM employee WHERE NOM LIKE '%"+ch+"%' or Prenom LIKE '%"+ch+"%'or poste LIKE '%"+ch+"%'");
    q->exec();
    model->setQuery(*q);
    return model;
}
QSqlQueryModel *employee::getMattri()
{
    QSqlQuery *q=new QSqlQuery();
    QSqlQueryModel *model = new QSqlQueryModel();
    q->prepare("SELECT * FROM  employee ORDER BY CIN ASC");
    q->exec();
    model->setQuery(*q);
    return model;
}


QSqlQueryModel * employee::getemployeestriid()
{
    QSqlQuery *q=new QSqlQuery();
    QSqlQueryModel *model = new QSqlQueryModel();
    q->prepare("SELECT * FROM  employee ORDER BY CIN ASC");
    q->exec();
    model->setQuery(*q);
    return model;
}

QSqlQueryModel * employee::getemployeestriprenom()
{
    QSqlQuery *q=new QSqlQuery();
    QSqlQueryModel *model = new QSqlQueryModel();
    q->prepare("SELECT * FROM  employee ORDER BY Prenom ASC");
    q->exec();
    model->setQuery(*q);
    return model;
}

QSqlQueryModel * employee::getemployeestrinom()
{
    QSqlQuery *q=new QSqlQuery();
    QSqlQueryModel *model = new QSqlQueryModel();
    q->prepare("SELECT * FROM  employee ORDER BY nom ASC");
    q->exec();
    model->setQuery(*q);
    return model;
}

QSqlQueryModel * employee::getemployeestriposte()
{
    QSqlQuery *q=new QSqlQuery();
    QSqlQueryModel *model = new QSqlQueryModel();
    q->prepare("SELECT * FROM  employee ORDER BY poste ASC");
    q->exec();
    model->setQuery(*q);
    return model;
}
QSqlQueryModel * employee::getemployeestriage()
{
    QSqlQuery *q=new QSqlQuery();
    QSqlQueryModel *model = new QSqlQueryModel();
    q->prepare("SELECT * FROM  employee ORDER BY age ASC");
    q->exec();
    model->setQuery(*q);
    return model;
}
