#ifndef PRODUIT_H
#define PRODUIT_H
#include<QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
class produit
{
    QString nom,type,pays ;
    int qt ;
public:
    produit(){}
    produit(int,QString,QString,QString);
    QString getNom() {return nom;}
    QString getType() {return type;}
    QString getPays() {return pays;}
    int getQT() {return qt;}
  //Setters
    void setNom(QString n) {nom=n;}
    void setType(QString t) {nom=t;}
    void setPays(QString b) {nom=b;}
    void setQT(int qt) {this->qt=qt;}
    bool ajouter () ;
    bool modifier ();
    QSqlQueryModel * afficher();
    bool supprimer(QString);
  QSqlQueryModel * triproduit(const QString &arg1);
  QSqlQueryModel * cherchernom(const QString &arg1);

};

#endif // PRODUIT_H
