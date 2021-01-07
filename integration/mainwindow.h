#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "client.h"
#include "connexion.h"
#include "carte.h"
#include "arduino.h"
#include <QString>
#include "QMediaPlaylist"
#include <QMediaPlayer>
#include <QDialog>
#include <QPrinter>
#include <QPrintDialog>
#include <QPrinterInfo>
#include "smtp.h"
#include <QSound>
#include"employee.h"
#include"contrat.h"
#include <produit.h>
#include <livraison.h>
#include <scenario1.h>
#include "fournisseur.h"
#include "notification.h"
#include "publicite.h"
#include "promotion.h"
#include "notification.h"
#include "commandes.h"
#include <QTimer>
#include "notification1.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:

    void on_ajouter_7_clicked();

    void on_ajouter_10_clicked();

    void on_ajouter_11_clicked();

    void on_pushButton_26_clicked();

    void on_pushButton_27_clicked();

    void on_lineEdit_chercher_textChanged(const QString &arg1);

    void on_pushButton_tri_clicked();

    void on_pushButton_tricin_clicked();

    void on_pushButton_25_clicked();

    void on_Gestio_des_clients_4_currentChanged(int index);

    void on_lineEdit_2_textChanged(const QString &arg1);

     void on_ajouter_12_clicked();

     void on_ajouter_carte_clicked();

     void on_modifiercarte_clicked();

     void on_supprimercarte_clicked();

     void on_Gestio_des_clients_5_currentChanged(int index);

    void on_sendBtn_clicked();

     void on_comboBox_currentTextChanged(const QString &arg1);

     void on_lineEdit_chercher_2_textChanged(const QString &arg1);


     void on_ajouter_13_clicked();


     void on_lineEdit_referrecher_textChanged(const QString &arg1);


     void on_connecter_clicked();

     void on_pushButton_70_clicked();

     void on_pushButton_12_clicked();

     void on_pushButton_8_clicked();

     void on_pushButton_13_clicked();

     void on_ajouter_prod_4_clicked();
   //  void sendMail();
     //void mailSent(QString);

    // void on_sendBtn_clicked();

     void on_tabWidget_4_tabBarClicked(int index);

     void on_supprimer_prod_3_clicked();

    // void on_tabWidget_2_currentChanged(int index);

     void on_ajouter_prod_5_clicked();

     void on_modif_prod_6_clicked();

     void on_trouv_prod_3_clicked();

     void on_tabWidget_5_tabBarClicked();

     void on_supprimer_prod_4_clicked();

     void on_modif_prod_7_clicked();

     void on_trouv_prod_4_clicked();

  //   void on_pushButton_3_clicked();

 //    void on_tri_prod_3_clicked();

   //  void on_tri_prod_3_pressed();

     void on_edit_rechavanc_prod_3_textChanged(const QString &arg1);

    // void on_pushButton_39_clicked();

    // void on_supprimer_prod_5_clicked();

     void on_tri_1_activated(const QString &arg1);


     //void on_tableView_course_3_activated(const QModelIndex &index);

   //  void on_sendBtn_clicked();

     void on_pushButton_39_clicked();

     void on_edit_rechavanc_prod_4_textChanged(const QString &arg1);

    // void on_connecter_clicked(bool checked);

     void on_sendBtn_3_clicked();

    // void on_sendBtn_2_clicked();

    // void on_edit_rechavanc_prod_4_cursorPositionChanged(int arg1, int arg2);

     void on_edit_rechavanc_prod_7_textChanged(const QString &arg1);

   //  void on_pushButton_41_clicked();

     void on_pushButton_41_clicked();
     void on_pushButton_34_clicked();

     void on_commandLinkButton_6_clicked();

     void on_commandLinkButton_8_clicked();

     void on_commandLinkButton_9_clicked();

     void on_commandLinkButton_10_clicked();

     void on_commandLinkButton_7_clicked();
/**********************/

     void on_pushButton_18_clicked();

     void on_pushButton_32_clicked();

     void on_pushButton_38_clicked();

     void on_pushButton_33_clicked();



     void on_comboBox_7_activated(const QString &arg1);

     void on_lineEdit_4_textChanged(const QString &arg1);

     void on_pushButton_46_clicked();

     void on_radioButton_20_clicked();

     void on_comboBox_14_activated(const QString &arg1);

     void on_lineEdit_3_textChanged(const QString &arg1);

     void on_pushButton_24_clicked();

     void on_pushButton_30_clicked();
     void update_label();

     void on_pushButton_52_clicked();

     void on_pushButton_55_clicked();

     void on_pushButton_53_clicked();

     void on_pushButton_54_clicked();
     void myfunction();

     void on_pushButton_14_clicked();

     void on_sendBtn_4_clicked();

     void on_pushButton_9_clicked();
/****************/
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


     void on_pb_supprimer_mortadha_2_clicked();

     void on_modifier_3_mortadha_2_clicked();

     void on_pb_modifier_pr_mortadha_2_clicked();

     void on_pb_supprimer_pr_mortadha_2_clicked();

     void on_Promotion_affichage_activated(const QModelIndex &index);

     void on_pb_ajouter_clicked();

     void refresh_mortadha();


     void on_recherche_Promotion_textChanged();

     void on_recherche_Publicite_textChanged();

     void on_tri_croissant_promotion_mortadha_2_clicked();

     void on_tri_deccroissant_promotion_mortadha_2_clicked();

     void on_tri_croissant_publicite_clicked();

     void on_tri_deccroissant_publicite_clicked();



     void on_stat_publicite_clicked();

     void on_pdf_publicite_clicked();

  //   void on_send_mail_mortadha_clicked();
     //void mailSent_mortadha(QString ); mortadha
     void on_stat_publicite_2_clicked();

     void on_pushButton_10_clicked();

     void on_pushButton_11_clicked();


     void on_stat_promotion_2_clicked();

     void on_pb_ajouter_pr_mortadha_2_clicked();
     void on_pb_ajouter_mortadha_2_clicked();

     void on_pb_ajouter_mortadha_3_clicked();

     void on_supprimer23_clicked();

     void on_modifier_2_clicked();

private:
    Ui::MainWindow *ui;
    QSound *son;
      client tmpclient;
      Carte tmpcarte;
     QMediaPlaylist *playlist =new QMediaPlaylist();
    int t=0,etat1;
    QString msg;
     QString mail;
     Smtp* smtp;
     QMediaPlayer *player;
     Arduino A;//objet temporaire
     QByteArray data="";// variable contenant les doneees recues
     employee tmpm ;
     contrat tmp ;
     QString languee;
     produit tempProd ;
     livraison templivr ;

    QTimer* timer;
    Fournisseur tmp_Fournisseur;
    Commande tmp_commande;
    Notification N;
    Arduino smartTools;
    //**********
    Publicite tmp_publicite;
    Promotion tmp_promotion;
 Notification1 N1 ;
    QMediaPlayer *musicAdd =new QMediaPlayer();

    /* QTranslator translatorFa;
     QTranslator translatorGe;*/

};
#endif // MAINWINDOW_H
