#ifndef Fourni_comand_H
#define Fourni_comand_H
#include "fournisseur.h"
#include "notification.h"
#include "publicite.h"
#include "promotion.h"
#include "notification.h"
#include <QMediaPlayer>
#include "commandes.h"
#include "arduino.h"
#include <QDialog>
#include "notification1.h"



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

    void on_stat_fournisseur_clicked();

    void on_pdf_commandes_clicked();


    void on_mail_clicked();
    void mailSent(QString );
    void readTemp();


    void on_normalBtn_clicked();
    void on_urgentBtn_clicked();
    //********************** mortadha
    void on_pb_ajouter_mortadha_clicked();




    QString ConvertirTime();
    void on_Publicite_affichage_activated(const QModelIndex &index);


    void on_pb_supprimer_mortadha_clicked();

    void on_modifier_3_mortadha_clicked();

    void on_pb_modifier_pr_mortadha_clicked();

    void on_pb_supprimer_pr_mortadha_clicked();

    void on_Promotion_affichage_activated(const QModelIndex &index);

    void on_pb_ajouter_pr_mortadha_clicked();
   void refresh_mortadha();

    void on_recherche_Promotion_textChanged();

    void on_recherche_Publicite_textChanged();

    void on_tri_croissant_promotion_mortadha_clicked();

    void on_tri_deccroissant_promotion_mortadha_clicked();

    void on_tri_croissant_publicite_clicked();

    void on_tri_deccroissant_publicite_clicked();

    void on_stat_promotion_clicked();

    void on_stat_publicite_clicked();

    void on_pdf_publicite_clicked();

    void on_send_mail_mortadha_clicked();
    //void mailSent_mortadha(QString ); mortadha



private:
    Ui::Fourni_comand *ui;
    Fournisseur tmp_Fournisseur;
    Commande tmp_commande;
    Notification N;
    Arduino smartTools;
    //**********
    Publicite tmp_publicite;
    Promotion tmp_promotion;
 Notification1 N1 ;
    QMediaPlayer *musicAdd =new QMediaPlayer();



};

#endif // Fourni_comand_H
