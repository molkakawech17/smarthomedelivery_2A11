#ifndef Fourni_comand_H
#define Fourni_comand_H
#include "fournisseur.h"
#include "notification.h"

#include "commandes.h"
#include <QDialog>



#include <QMainWindow>

namespace Ui {
class Fourni_comand;
}

class Fourni_comand : public QMainWindow
{
    Q_OBJECT

public:
    explicit Fourni_comand(QWidget *parent = nullptr);
    ~Fourni_comand();

private slots:






    void on_pb_modifier_pr_clicked();

    void on_pb_supprimer_pr_clicked();


    void on_pb_ajouter_pr_clicked();

    void on_Fournisseur_affichage_activated(const QModelIndex &index);


    void on_pb_ajouter_c_clicked();

    void on_pb_modifier_c_clicked();

    void on_pb_supprimer_c_clicked();

    void on_Commande_affichage_activated(const QModelIndex &index);
    void refresh();

    void on_recherche_fournisseur_textChanged();

    void on_recherche_commande_textChanged();

    void on_tri_croissant_Fournisseur_clicked();

    void on_tri_deccroissant_Fournisseur_clicked();

    void on_tri_croissant_Commande_clicked();

    void on_tri_deccroissant_Commande_clicked();


    void on_stat_commande_clicked();


    void on_pdf_commandes_clicked();


    void on_mail_clicked();
    void mailSent(QString );


private:
    Ui::Fourni_comand *ui;
    Fournisseur tmp_Fournisseur;
    Commande tmp_commande;
    Notification N;


};

#endif // Fourni_comand_H
