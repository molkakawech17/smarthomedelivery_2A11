#include "fourni_comand.h"
#include "smtp.h"
#include "ui_fourni_comand.h"
#include<QMessageBox>
#include <QComboBox>
#include <QPainter>
#include <QPdfWriter>
#include <QDesktopServices>
#include <QUrl>
#include <QPrinter>
#include <QPrintDialog>
#include <QPieSlice>
#include <QPieSeries>
#include <QtCharts/QChartView>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include"QSortFilterProxyModel"
QT_CHARTS_USE_NAMESPACE



Fourni_comand::Fourni_comand(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Fourni_comand)
{
ui->setupUi(this);

refresh();



}
void Fourni_comand::refresh(){
    ui->Fournisseur_affichage->setModel(tmp_Fournisseur.afficher());
    ui->Commande_affichage->setModel(tmp_commande.afficher());
    ui->comboBox_idf->setModel(tmp_Fournisseur.afficher());
    ui->comboBox_idf1->setModel(tmp_Fournisseur.afficher());
}


Fourni_comand::~Fourni_comand()
{
    delete ui;
}




//Crud Fournisseur

void Fourni_comand::on_pb_ajouter_pr_clicked()
{
    QString cin= ui->lineEdit_cin->text();

    QString prenom = ui->lineEdit_prenom->text();
    QString nom= ui->lineEdit_nom->text();
    QString mail= ui->lineEdit_mail->text();
    long tel= ui->lineEdit_tel->text().toLong();
  Fournisseur f(cin,prenom,nom,mail,tel);

  if (f.testCin(ui->lineEdit_cin->text())==false)
       {

           QMessageBox::information(this," ERREUR "," Veuillez s'il vous plait vérifier CIN ! ") ;
           QMessageBox::critical(0, qApp->tr("Ajout"),

                           qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

       }
              else if (ui->lineEdit_nom->text().isEmpty())
               {

                   QMessageBox::information(this," ERREUR "," Veuillez s'il vous plait vérifier Nom ! ") ;
                   QMessageBox::critical(0, qApp->tr("Ajout"),

                                   qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

               }
                else if (ui->lineEdit_prenom->text().isEmpty())
                 {

                     QMessageBox::information(this," ERREUR "," Veuillez s'il vous plait vérifier Prenom !") ;
                     QMessageBox::critical(0, qApp->tr("Ajout"),

                                     qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

                 }
            else if (ui->lineEdit_tel->text().isEmpty())
             {

                 QMessageBox::information(this," ERREUR "," Veuillez s'il vous plait vérifier tel !") ;
                 QMessageBox::critical(0, qApp->tr("Ajout"),

                                 qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

             }

            else if (f.testnumber(ui->lineEdit_tel->text())==false)
                  {

                      QMessageBox::information(this," ERREUR "," Veuillez s'il vous plait vérifier tel !") ;
                      QMessageBox::critical(0, qApp->tr("Ajout"),

                                      qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

                  }

          else if (f.testmail(ui->lineEdit_mail->text())==false)
                 {

                     QMessageBox::information(this," ERREUR "," Veuillez s'il vous plait vérifier Mail ! ") ;
                     QMessageBox::critical(0, qApp->tr("Ajout"),

                                     qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

                 }






      else {







  bool test=f.ajouter();
  if(test)
{

refresh();

N.notification_ajoutFournisseur();

}
  else
      QMessageBox::critical(nullptr, QObject::tr("Ajouter un Fournisseur"),
                  QObject::tr("Erreur !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

}}

void Fourni_comand::on_pb_modifier_pr_clicked()
{
    QString cin= ui->lineEdit_cin1->text();

    QString prenom = ui->lineEdit_prenom1->text();
    QString nom= ui->lineEdit_nom1->text();
    QString mail= ui->lineEdit_mail1->text();
    long tel= ui->lineEdit_tel1->text().toLong();
    Fournisseur f(cin,prenom,nom,mail,tel);

    if (f.testCin(ui->lineEdit_cin1->text())==false)
         {

             QMessageBox::information(this," ERREUR "," Veuillez s'il vous plait vérifier CIN !") ;
             QMessageBox::critical(0, qApp->tr("Ajout"),

                             qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

         }
                else if (ui->lineEdit_nom1->text().isEmpty())
                 {

                     QMessageBox::information(this," ERREUR "," Veuillez s'il vous plait vérifier Nom !") ;
                     QMessageBox::critical(0, qApp->tr("Ajout"),

                                     qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

                 }
                  else if (ui->lineEdit_prenom1->text().isEmpty())
                   {

                       QMessageBox::information(this," ERREUR "," Veuillez s'il vous plait vérifier Prenom !") ;
                       QMessageBox::critical(0, qApp->tr("Ajout"),

                                       qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

                   }
              else if (ui->lineEdit_tel1->text().isEmpty())
               {

                   QMessageBox::information(this," ERREUR "," Veuillez s'il vous plait vérifier tel !") ;
                   QMessageBox::critical(0, qApp->tr("Ajout"),

                                   qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

               }

            else if (f.testmail(ui->lineEdit_mail1->text())==false)
                   {

                       QMessageBox::information(this," ERREUR "," Veuillez s'il vous plait vérifier Mail !") ;
                       QMessageBox::critical(0, qApp->tr("Ajout"),

                                       qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

                   }






        else {





    bool test=f.modifier();
    if(test)
    {



        N.notification_modifierFournisseur();
        refresh();




    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Supprimer Fournisseur"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }

    ui->lineEdit_cin1->clear();
    ui->lineEdit_prenom1->clear();
    ui->lineEdit_nom1->clear();
    ui->lineEdit_mail1->clear();
    ui->lineEdit_tel1->clear();


}}

void Fourni_comand::on_pb_supprimer_pr_clicked()
{
    if(ui->Fournisseur_affichage->currentIndex().row()==-1)
        QMessageBox::information(nullptr, QObject::tr("Suppression"),
                          QObject::tr("Veuillez Choisir une Fournisseur du Tableau.\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);
    else
    {   int cin=ui->Fournisseur_affichage->model()->data(ui->Fournisseur_affichage->model()->index(ui->Fournisseur_affichage->currentIndex().row(),0)).toInt();
        Fournisseur p(ui->Fournisseur_affichage->model()->data(ui->Fournisseur_affichage->model()->index(ui->Fournisseur_affichage->currentIndex().row(),0)).toString(),ui->Fournisseur_affichage->model()->data(ui->Fournisseur_affichage->model()->index(ui->Fournisseur_affichage->currentIndex().row(),1)).toString(),ui->Fournisseur_affichage->model()->data(ui->Fournisseur_affichage->model()->index(ui->Fournisseur_affichage->currentIndex().row(),2)).toString(),ui->Fournisseur_affichage->model()->data(ui->Fournisseur_affichage->model()->index(ui->Fournisseur_affichage->currentIndex().row(),3)).toString(),ui->Fournisseur_affichage->model()->data(ui->Fournisseur_affichage->model()->index(ui->Fournisseur_affichage->currentIndex().row(),4)).toLongLong());



            QString str = " Vous voulez vraiment supprimer \n le Fournisseur :";
                              int ret = QMessageBox::question(this, tr("Fournisseur"),str,QMessageBox::Ok|QMessageBox::Cancel);

                              switch (ret) {
                                case QMessageBox::Ok:
                                    if (p.supprimer(cin)){
                                       N.notification_supprimerFournisseur();
                                            refresh();

                                    }
                                    else
                                      {

                                          QMessageBox::critical(0, qApp->tr("Suppression"),
                                              qApp->tr("Fournisseur non trouvé "), QMessageBox::Cancel);
      }



                                  break;
                                case QMessageBox::Cancel:

                                    break;
                                default:
                                    // should never be reached
                                    break;
                              }


}

}

void Fourni_comand::on_Fournisseur_affichage_activated(const QModelIndex &index)
{
    QString cin=ui->Fournisseur_affichage->model()->data(index).toString();
        QSqlQuery query;
        query.prepare("SELECT * FROM FOURNISSEUR WHERE CIN='"+cin+"'");
        if(query.exec())
        {
            while(query.next())
            {
                ui->lineEdit_cin1->setText(query.value(0).toString());
                ui->lineEdit_prenom1->setText(query.value(1).toString());
                ui->lineEdit_nom1->setText(query.value(2).toString());
                ui->lineEdit_mail1->setText(query.value(3).toString());
                ui->lineEdit_tel1->setText(query.value(4).toString());




            }

        }
        else
        {
            QObject::tr("Veuillez Choisir Un ID Du Tableau SVP");
        }
}



//Fin Crud Fournisseur


//Crud Commandes










void Fourni_comand::on_pb_ajouter_c_clicked()
{
    QString id= ui->lineEdit_id->text();
    QString id_f=ui->comboBox_idf->currentText();
    QString id_p= ui->lineEdit_idp->text();
    int prix= ui->lineEdit_prix->text().toInt();
    QDate datee= ui->dateEdit->date();
    int quantite= ui->lineEdit_quantite->text().toInt();
    QString etat = ui->lineEdit_etat->text();
  Commande c(id,id_f,id_p,quantite,prix,datee,etat);


    if (ui->lineEdit_id->text().isEmpty())
       {

           QMessageBox::information(this," ERREUR "," Veuillez s'il vous plait vérifier Identifiant !") ;
           QMessageBox::critical(0, qApp->tr("Ajout"),

                           qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

       }

    else if (ui->lineEdit_idp->text().isEmpty())
     {

         QMessageBox::information(this," ERREUR "," Veuillez s'il vous plait vérifier id produit !") ;
         QMessageBox::critical(0, qApp->tr("Ajout"),

                         qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

     }
    else if (ui->lineEdit_prix->text().isEmpty())
     {

         QMessageBox::information(this," ERREUR "," Veuillez s'il vous plait vérifier champ Prix !") ;
         QMessageBox::critical(0, qApp->tr("Ajout"),

                         qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

     }
    else if (ui->lineEdit_quantite->text().isEmpty())
     {

         QMessageBox::information(this," ERREUR "," Veuillez s'il vous plait vérifier champ Quantite !") ;
         QMessageBox::critical(0, qApp->tr("Ajout"),

                         qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

     }
    else if (ui->lineEdit_etat->text().isEmpty())
     {

         QMessageBox::information(this," ERREUR "," Veuillez s'il vous plait vérifier champ Etat !") ;
         QMessageBox::critical(0, qApp->tr("Ajout"),

                         qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

     }









    else{
  bool test=c.ajouter();
  if(test)
{
      N.notification_ajoutCommande();

refresh();


}
  else
      QMessageBox::critical(nullptr, QObject::tr("Ajouter une Commande"),
                  QObject::tr("Erreur !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

}}

void Fourni_comand::on_pb_modifier_c_clicked()
{
    QString id= ui->lineEdit_id1->text();
    QString id_f=ui->comboBox_idf1->currentText();
    QString id_p= ui->lineEdit_idp1->text();
    int prix= ui->lineEdit_prix1->text().toInt();
    QDate datee= ui->dateEdit1->date();
    int quantite= ui->lineEdit_quantite1->text().toInt();
    QString etat = ui->lineEdit_etat1->text();

    Commande c(id,id_f,id_p,quantite,prix,datee,etat);
    if (ui->lineEdit_id1->text().isEmpty())
       {

           QMessageBox::information(this," ERREUR "," Veuillez s'il vous plait vérifier champ Identifiant !") ;
           QMessageBox::critical(0, qApp->tr("Ajout"),

                           qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

       }

    else if (ui->lineEdit_idp1->text().isEmpty())
     {

         QMessageBox::information(this," ERREUR "," Veuillez s'il vous plait vérifier champ id produit !") ;
         QMessageBox::critical(0, qApp->tr("Ajout"),

                         qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

     }
    else if (ui->lineEdit_prix1->text().isEmpty())
     {

         QMessageBox::information(this," ERREUR "," Veuillez s'il vous plait vérifier champ Prix ! ") ;
         QMessageBox::critical(0, qApp->tr("Ajout"),

                         qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

     }
    else if (ui->lineEdit_quantite1->text().isEmpty())
     {

         QMessageBox::information(this," ERREUR "," Veuillez s'il vous plait vérifier champ Quantitè !") ;
         QMessageBox::critical(0, qApp->tr("Ajout"),

                         qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

     }
    else if (ui->lineEdit_etat1->text().isEmpty())
     {

         QMessageBox::information(this," ERREUR "," Veuillez s'il vous plait vérifier champ Etat ! ") ;
         QMessageBox::critical(0, qApp->tr("Ajout"),

                         qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

     }









    else{



    bool test=c.modifier();
    if(test)
    {



        refresh();
        N.notification_modifierCommande();



    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Supprimer Commande"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }

    ui->lineEdit_id1->clear();
    ui->lineEdit_idp1->clear();
    ui->lineEdit_prix1->clear();
    ui->lineEdit_quantite1->clear();
    ui->lineEdit_etat1->clear();

}}

void Fourni_comand::on_pb_supprimer_c_clicked()
{
    if(ui->Commande_affichage->currentIndex().row()==-1)
        QMessageBox::information(nullptr, QObject::tr("Suppression"),
                          QObject::tr("Veuillez Choisir une Commande du Tableau.\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);
    else
    {   QString id=ui->Commande_affichage->model()->data(ui->Commande_affichage->model()->index(ui->Commande_affichage->currentIndex().row(),0)).toString();
        Commande c(ui->Commande_affichage->model()->data(ui->Commande_affichage->model()->index(ui->Commande_affichage->currentIndex().row(),0)).toString(),ui->Commande_affichage->model()->data(ui->Commande_affichage->model()->index(ui->Commande_affichage->currentIndex().row(),1)).toString(),ui->Commande_affichage->model()->data(ui->Commande_affichage->model()->index(ui->Commande_affichage->currentIndex().row(),2)).toString(),ui->Commande_affichage->model()->data(ui->Commande_affichage->model()->index(ui->Commande_affichage->currentIndex().row(),3)).toInt(),ui->Commande_affichage->model()->data(ui->Commande_affichage->model()->index(ui->Commande_affichage->currentIndex().row(),4)).toInt(),ui->Commande_affichage->model()->data(ui->Commande_affichage->model()->index(ui->Commande_affichage->currentIndex().row(),5)).toDate(),ui->Commande_affichage->model()->data(ui->Commande_affichage->model()->index(ui->Commande_affichage->currentIndex().row(),6)).toString());



            QString str = " Vous voulez vraiment supprimer \n le Commande :";
                              int ret = QMessageBox::question(this, tr("Commande"),str,QMessageBox::Ok|QMessageBox::Cancel);

                              switch (ret) {
                                case QMessageBox::Ok:
                                    if (c.supprimer(id)){
N.notification_supprimerCommande();
                                        refresh();

                                    }
                                    else
                                      {

                                          QMessageBox::critical(0, qApp->tr("Suppression"),
                                              qApp->tr("Commande non trouvé "), QMessageBox::Cancel);
      }



                                  break;
                                case QMessageBox::Cancel:

                                    break;
                                default:
                                    // should never be reached
                                    break;
                              }


}
}

void Fourni_comand::on_Commande_affichage_activated(const QModelIndex &index)
{

    QString id=ui->Commande_affichage->model()->data(index).toString();
        QSqlQuery query;
        query.prepare("SELECT * FROM COMMANDES WHERE ID='"+id+"'");
        if(query.exec())
        {
            while(query.next())
            {
                ui->lineEdit_id1->setText(query.value(0).toString());
                ui->lineEdit_idp1->setText(query.value(2).toString());

                ui->lineEdit_quantite1->setText(query.value(3).toString());
                ui->lineEdit_prix1->setText(query.value(4).toString());
                ui->lineEdit_etat1->setText(query.value(6).toString());




            }

        }
        else
        {
            QObject::tr("Veuillez Choisir Un ID Du Tableau SVP !");
        }

}
//Fin Crud Commandes



void Fourni_comand::on_recherche_fournisseur_textChanged()
{
    if(ui->recherche_fournisseur->text()!="")
        {        QString b=ui->comboBox_recherche_fournisseur->currentText();
                QString a=ui->recherche_fournisseur->text();
                ui->Fournisseur_affichage->setModel(tmp_Fournisseur.displayClause("WHERE ("+b+" LIKE '%"+a+"%')"));
            }
             else
             ui->Fournisseur_affichage->setModel(tmp_Fournisseur.afficher());

}

void Fourni_comand::on_recherche_commande_textChanged()
{
    if(ui->recherche_commande->text()!="")
        {        QString b=ui->comboBox_recherche_commande->currentText();
                QString a=ui->recherche_commande->text();
                ui->Commande_affichage->setModel(tmp_commande.displayClause("WHERE ("+b+" LIKE '%"+a+"%')"));
            }
             else
             ui->Commande_affichage->setModel(tmp_commande.afficher());
}

void Fourni_comand::on_tri_croissant_Fournisseur_clicked()
{
    ui->Fournisseur_affichage->setModel(tmp_Fournisseur.tricroissant());

}

void Fourni_comand::on_tri_deccroissant_Fournisseur_clicked()
{
    ui->Fournisseur_affichage->setModel(tmp_Fournisseur.trideccroissant());

}

void Fourni_comand::on_tri_croissant_Commande_clicked()
{
    ui->Commande_affichage->setModel(tmp_commande.tricroissant());

}

void Fourni_comand::on_tri_deccroissant_Commande_clicked()
{
    ui->Commande_affichage->setModel(tmp_commande.trideccroissant());

}



void Fourni_comand::on_stat_commande_clicked()
{
    QSqlQueryModel * model= new QSqlQueryModel();
                model->setQuery("select * from COMMANDES where PRIX < 500 ");
                float tel=model->rowCount();
                model->setQuery("select * from COMMANDES where PRIX  between 500 and 1000 ");
                float tele=model->rowCount();
                model->setQuery("select * from COMMANDES where PRIX>1000 ");
                float telee=model->rowCount();
                float total=tel+tele+telee;
                QString a=QString("moins de 500 Dinars "+QString::number((tel*100)/total,'f',2)+"%" );
                QString b=QString("entre 500 et 1000 Dinars "+QString::number((tele*100)/total,'f',2)+"%" );
                QString c=QString("+1000 Dinars "+QString::number((telee*100)/total,'f',2)+"%" );
                QPieSeries *series = new QPieSeries();
                series->append(a,tel);
                series->append(b,tele);
                series->append(c,telee);
        if (tel!=0)
        {QPieSlice *slice = series->slices().at(0);
         slice->setLabelVisible();
         slice->setPen(QPen());}
        if ( tele!=0)
        {
                 // Add label, explode and define brush for 2nd slice
                 QPieSlice *slice1 = series->slices().at(1);
                 //slice1->setExploded();
                 slice1->setLabelVisible();
        }
        if(telee!=0)
        {
                 // Add labels to rest of slices
                 QPieSlice *slice2 = series->slices().at(2);
                 //slice1->setExploded();
                 slice2->setLabelVisible();
        }
                // Create the chart widget
                QChart *chart = new QChart();
                // Add data to chart with title and hide legend
                chart->addSeries(series);
                chart->setTitle("Pourcentage Par Prix :Nombre Des Commandes "+ QString::number(total));
                chart->legend()->hide();
                // Used to display the chart
                QChartView *chartView = new QChartView(chart);
                chartView->setRenderHint(QPainter::Antialiasing);
                chartView->resize(1000,500);
                chartView->show();
}


void Fourni_comand::on_pdf_commandes_clicked()
{
    QPdfWriter pdf("C:/Users/Lenovo/Desktop/PdfCommandes.pdf");
               QPainter painter(&pdf);
              int i = 4000;
                   painter.setPen(Qt::blue);
                   painter.setFont(QFont("Arial", 30));
                   painter.drawText(2300,1200,"Liste Des Commandes");
                   painter.setPen(Qt::black);
                   painter.setFont(QFont("Arial", 50));
                  // painter.drawText(1100,2000,afficheDC);
                   painter.drawRect(1500,200,7300,2600);
                   //painter.drawPixmap(QRect(7600,70,2000,2600),QPixmap("C:/Users/RH/Desktop/projecpp/image/logopdf.png"));
                   painter.drawRect(0,3000,9600,500);
                   painter.setFont(QFont("Arial", 9));
                   painter.drawText(300,3300,"ID");
                   painter.drawText(1633,3300,"IDF");
                   painter.drawText(2966,3300,"IDP");
                   painter.drawText(4299,3300,"QUANTITE");
                   painter.drawText(5632,3300,"PRIX");
                   painter.drawText(6965,3300,"DATE");
                   painter.drawText(9000,3300,"ETAT");


                   QSqlQuery query;
                   query.prepare("select * from COMMANDES");
                   query.exec();
                   while (query.next())
                   {
                       painter.drawText(300,i,query.value(0).toString());
                       painter.drawText(1633,i,query.value(1).toString());
                       painter.drawText(2966,i,query.value(2).toString());
                       painter.drawText(4299,i,query.value(3).toString());
                       painter.drawText(5632,i,query.value(4).toString());
                       painter.drawText(6965,i,query.value(5).toString());
                       painter.drawText(9000,i,query.value(6).toString());



                      i = i +500;
                   }
                   int reponse = QMessageBox::question(this, "Génerer PDF", "<PDF Enregistré>...Vous Voulez Affichez Le PDF ?", QMessageBox::Yes |  QMessageBox::No);
                       if (reponse == QMessageBox::Yes)
                       {
                           QDesktopServices::openUrl(QUrl::fromLocalFile("C:/Users/Lenovo/Desktop/PdfCommandes.pdf"));

                           painter.end();
                       }
                       if (reponse == QMessageBox::No)
                       {
                            painter.end();
                       }
}

void Fourni_comand::mailSent(QString status)
{
    if(status == "Message sent")
        N.mail_Publicite();
}


void Fourni_comand::on_mail_clicked()
{
    Smtp* smtp = new Smtp("farmeresprit414@gmail.com","farmer1919","smtp.gmail.com",465);
           connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

           smtp->sendMail("farmeresprit414@gmail.com",ui->rcpt->text(),ui->subject->text(),ui->msg->toPlainText());
}
