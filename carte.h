 #ifndef CARTE_H
#define CARTE_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDialog>
#include <QDate>

class Carte
{
public:
    Carte();
    Carte(QString , int,int);
    QString get_ref( ){return ref ;}
    int get_cinClient() {return cinClient ;}
    int get_nombredespoints(){return nombredespoints; }
    void setcinClient(int);
    void setref(int);
    bool ajouter(Carte ca);
    bool modifier (QString ref,Carte Ca );
    bool supprimer(QString reff);
    QSqlQueryModel * afficher();
   QSqlQueryModel *rechercherrefcarte(const QString &);
 // QSqlQueryModel *tri();
private:
    QString ref;
    int cinClient , nombredespoints ;
};

#endif // CARTE_H
