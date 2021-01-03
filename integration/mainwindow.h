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

     void on_pushButton_7_clicked();

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

};
#endif // MAINWINDOW_H
