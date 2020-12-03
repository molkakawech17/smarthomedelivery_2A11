#ifndef LIVRAISON_H
#define LIVRAISON_H
#include<QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class livraison
{
    QString add,ref,nom1 ;
    int cin ;
public:
    livraison(){};
    livraison(int,QString,QString,QString);
    QString getAdd() {return add;}
    QString getNom1() {return nom1;}
    QString getref() {return ref;}
    int getCIN() {return cin;}
  //Setters
    void setAdd(QString a) {add=a;}
    void setNom1(QString n1) {nom1=n1;}
    void setref(QString r) {ref=r;}
    void setCIN(int cin) {this->cin=cin;}
    bool ajouter () ;
    QSqlQueryModel * afficher();
    bool supprimer(QString);
    bool modifier ();
    QSqlQueryModel * trilivraison(const QString &arg1);
    QSqlQueryModel * cherchernom1(const QString &bb);


};

#endif // LIVRAISON_H
