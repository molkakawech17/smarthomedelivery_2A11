#ifndef CLIENT_H
#define CLIENT_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>


class client
{
    QString email,nom,prenom;
    int abonne_carte,cin;
public:
    client();
    client(QString,QString,int,int,QString);

    QString getnom();
    QString getprenom();
    int getcin();
    int getabonne_carte();
    QString getemail();


//crud client
    bool ajouterclient();
    bool modifierclient(QString email,QString nom , QString prenom, int abonne_carte);
    bool supprimerclient(QString email);
    QSqlQueryModel * afficherclient();
//metier client
  QSqlQueryModel * chercher_client_email(QString nom);
  QSqlQueryModel * chercher_client_nom(QString nom);
  QSqlQueryModel * afficher_tri_cin();
  QSqlQueryModel * afficher_tri_email();

};

#endif // CLIENT_H

