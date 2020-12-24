#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QString>
#include "historique.h"
#include"QPdfWriter"
#include"QtPrintSupport/QPrinter"
#include"QPainter"
#include <QPrintDialog>
#include <QTextDocument>
#include "smtp.h"
#include <QtWidgets>
#include <QPrinter>
#include <QPixmap>
#include <QSound>
#include <QtMultimedia/QMediaPlayer>
#include"employee.h"
#include"contrat.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)


{
    // music

    player= new QMediaPlayer(this) ;
           player->setMedia(QUrl::fromLocalFile("C:/Users/Molka/Desktop/validation2/Chillout-downtempo-music-loop.mp3")) ;
           player->play() ;

    ui->setupUi(this);
    ui->tabclient_7->setModel(tmpclient.afficherclient());
    ui->tabcarte_8->setModel(tmpcarte.afficher());

    //background
     QPixmap pix("qrc:/../desk/fdaffiche.jpg");
    //quitter
    connect(ui->exitBtn, SIGNAL(clicked()),this, SLOT(close()));
    /* ////////////////////////////////////////////// */
   int ret=A.connect_arduino(); // lancer la connexion à arduino
    switch(ret){
    case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
        break;
    case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
       break;
    case(-1):qDebug() << "arduino is not available";
    }

     QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label())); // permet de lancer
     //le slot update_label suite à la reception du signal readyRead (reception des données).






}

MainWindow::~MainWindow()
{
    delete ui;
}
// gestion client

void MainWindow::on_ajouter_7_clicked()//ajouter client
{

    QString prenom=ui->le_prenom->text();
    QString nom=ui->le_nom->text();
    int cin=ui->le_cin->text().toInt();
    int numero=ui->le_nbrcarte->text().toInt();
    QString email=ui->le_email->text();
    int idR;
    QString textajouter;//historique
    historique h;

client c(prenom,nom,cin,numero,email);

    qDebug()<< email ;
//controle de saisie pour cin et numero
  if(cin>100000 && cin<999999 && numero >1000 && numero <9999)
  {

    bool added=c.ajouterclient();
    QMessageBox msgBox;

     if(added)
            {
     msgBox.setText("Ajout avec succes.");

    ui->tabclient_7->setModel(c.afficherclient());//refresh
            }

    else
     msgBox.setText("Echec d'ajout cin  ");

     msgBox.exec();
   }

if (cin <100000 || cin>999999) {
    QMessageBox::critical(nullptr, QObject::tr("Ajouter une carte"),
    QObject::tr("Erreur cin <100000 Ou >999999 !.\n"
                  "Click Cancel to exit."), QMessageBox::Cancel);
}
if(numero <1000 || numero > 9999){
    QMessageBox::critical(nullptr, QObject::tr("Ajouter une carte"),
    QObject::tr("Erreur numero <1000 Ou >9999 !.\n"
                  "Click Cancel to exit."), QMessageBox::Cancel);
}

   //ajout historique
     QSqlQuery qry;
     qry.prepare("select * from client");
     if (qry.exec())
     {
         while (qry.next())
         {
 idR =qry.value(3).toInt();
         }
     }

     textajouter="L'ajout d'un client dans la base de donnees de nom = "+QString::number(idR)+" a ete effectuee avec succees";
     h.write(textajouter);



}


void MainWindow::on_ajouter_11_clicked()//supprimer client
{
    QString mail=ui->emailasupprimer_2->text();
    client c;
    bool t=c.supprimerclient(mail);
    if(t)
    {
        ui->tabclient_7->setModel(tmpclient.afficherclient());

        QMessageBox::information(nullptr, QObject::tr("Supprimer client"),
                    QObject::tr("client supprimé.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Supprimer client"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
     }   QString textajouter;
int idR;
        historique h;
        QSqlQuery qry;
        qry.prepare("select * from client");
        if (qry.exec())
        {

            while (qry.next())
            {
    idR =qry.value(3).toInt();
            }
        }

        textajouter="La supression d'un client de la base de donnees de nom = "+QString::number(idR)+" a ete effectuee avec succees";
        h.write(textajouter);



}


void MainWindow::on_ajouter_10_clicked()//modifier client
{
int numero=ui->modif_nbrcarte->text().toInt();
QString nom=ui->nom_modifier->text();
QString prenom=ui->prenom_modifier->text();
QString email = ui->comboBox->currentText();
client c;
bool t=c.modifierclient(email,nom,prenom,numero);
if(numero >1000 && numero <9999){
if(t)
{
   ui->tabclient_7->setModel(tmpclient.afficherclient());

   QMessageBox::information(nullptr, QObject::tr("modifier client"),
               QObject::tr("client modifie.\n"
                           "Click Cancel to exit."), QMessageBox::Cancel);


}
else
{
    QMessageBox::critical(nullptr, QObject::tr("client modifie"),
                QObject::tr("Erreur !.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
}}
if(numero <1000 || numero > 9999){
    QMessageBox::critical(nullptr, QObject::tr("Ajouter une carte"),
    QObject::tr("Erreur numero <1000 Ou >9999 !.\n"
                  "Click Cancel to exit."), QMessageBox::Cancel);
}

QString textajouter;
int idR;
historique h;
QSqlQuery qry;
qry.prepare("select * from client");
if (qry.exec())
{
    while (qry.next())
    {
idR =qry.value(3 ).toInt();
    }
}

textajouter="La modification d'un client de la base de donnees de reference = "+QString::number(idR)+" a ete effectuee avec succees";
h.write(textajouter);

}



//chercher et trier client
void MainWindow::on_lineEdit_chercher_textChanged(const QString &arg1)
{
    ui->tabclient_7->setModel(tmpclient.chercher_client_email(arg1));
}

void MainWindow::on_lineEdit_2_textChanged(const QString &arg1)
{
    ui->tabclient_7->setModel(tmpclient.chercher_client_nom(arg1));
}


void MainWindow::on_lineEdit_chercher_2_textChanged(const QString &arg1)
{
  ui->tabclient_7->setModel(tmpclient.chercher_client_prenom(arg1));
}


void MainWindow::on_pushButton_tri_clicked()//tri ordre alpha
{
    ui->pushButton_tri->setIcon(QIcon(":/desk/sortascend256_25201.png")); // Icône du bouton
    ui->tabclient_7->setModel(tmpclient.afficher_tri_email());

}

void MainWindow::on_pushButton_tricin_clicked()//tri selon cin desce
{
    ui->tabclient_7->setModel(tmpclient.afficher_tri_cin());
}


//music pas encore
void MainWindow::on_pushButton_26_clicked()
{

    //son->play();
    //t=t-1;
    //   playlist->setCurrentIndex(t);

}

void MainWindow::on_pushButton_27_clicked()
{ //son->stop();
  // t=t+1;
  // playlist->setCurrentIndex(t);
}

void MainWindow::on_Gestio_des_clients_4_currentChanged(int index)//afficher tab
{
    ui->tabclient_7->setModel(tmpclient.afficherclient());
}

void MainWindow::on_pushButton_25_clicked()//historique

    {
    historique h;

        ui->textBrowser_2->show();
        ui->textBrowser_2->setPlainText(h.read());

    }


//gestion carte

void MainWindow::on_ajouter_carte_clicked()//ajouter carte
{

    QString ref=ui->lineeditajouteref->text();
    int CIN =ui->comboBox_CinClientA->currentText().toInt();
    int nbpoints = ui->lineEdit_nbPoints->text().toUInt();
    Carte ca(ref,CIN,nbpoints);
//refer et nmbre de point controle de saisie
    int lengthreference=ref.length();

    qDebug()<< lengthreference ;
    qDebug()<< CIN ;
if(lengthreference>0 && nbpoints>0)
{


    bool test= ca.ajouter(ca);
  if(test)

{
      ui->tabcarte_8->setModel(ca.afficher());//refresh
QMessageBox::information(nullptr, QObject::tr("Ajouter une carte "),
                  QObject::tr("carte ajouté.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);


}
  else
      QMessageBox::information(nullptr, QObject::tr("Ajouter une carte"),
                  QObject::tr("Erreur !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);
}
// test refer et nbpoint
if(ref<=0)
{
    QMessageBox::critical(nullptr, QObject::tr("Ajouter une carte"),
                QObject::tr("Erreur Reference est Null Ou negative !.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
}
if(nbpoints<=0)
{
    QMessageBox::critical(nullptr, QObject::tr("Ajouter une carte"),
                QObject::tr("Erreur nbpoints est Null Ou negative !.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
}
}



void MainWindow::on_modifiercarte_clicked()//modifier carte
{
    QString REF=ui->lineEdit_refCarteM->text();
    int cinClient = ui->comboBox_cinM->currentText().toInt();
    int nbpoints = ui->lineEdit_nbPointM_2->text().toUInt();

    Carte ca(REF,cinClient,nbpoints);

  int lengthreference=REF.length();

  if(lengthreference>0 && nbpoints>0)
  {
    bool test= ca.modifier(REF,ca);
  if(test)

{
      ui->tabcarte_8->setModel(ca.afficher());//refresh
QMessageBox::information(nullptr, QObject::tr("Modifier un carte"),
                  QObject::tr("carte Modifié.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);


}
  else
      QMessageBox::information(nullptr, QObject::tr("Modifier un carte"),
                  QObject::tr("Erreur !.\n"

                              "Click Cancel to exit."), QMessageBox::Cancel);

}

  if(REF<=0)
  {
      QMessageBox::critical(nullptr, QObject::tr("Ajouter une carte"),
                  QObject::tr("Erreur Reference est Null Ou negative !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);
  }
  if(nbpoints<=0)
  {
      QMessageBox::critical(nullptr, QObject::tr("Ajouter une carte"),
                  QObject::tr("Erreur nbpoints est Null Ou negative !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);
  }


}

void MainWindow::on_supprimercarte_clicked()//supprimer carte
{
    QString reff=ui->input_cinClient->text();
    Carte ca;
    bool test= ca.supprimer(reff);
    if(test)

  {
      ui->tabcarte_8->setModel(ca.afficher());//refresh
  QMessageBox::information(nullptr, QObject::tr("Supprimer un client"),
                    QObject::tr("client supprimé.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);


  }
    else
        QMessageBox::information(nullptr, QObject::tr("Supprimer un client"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}



void MainWindow::on_Gestio_des_clients_5_currentChanged(int index)//afficher tabcarte
{ Carte ca;
    ui->tabcarte_8->setModel(ca.afficher());
}

void MainWindow::on_comboBox_currentTextChanged(const QString &arg1)
{


     QString mail=arg1;
     QSqlQuery query;
     query.prepare("select * from client where email='"+mail+"'");
     query.exec();
     while(query.next())
     {   ui->prenom_modifier->setText(query.value(0).toString());
         ui->nom_modifier->setText(query.value(1).toString());
         ui->modif_nbrcarte->setText(query.value(3).toString());
     }

}

//envoyer un mail
void MainWindow::on_sendBtn_clicked()
{
    smtp = new Smtp("fleur.express1@gmail.com" , "molka123molka", "smtp.gmail.com",465);
        connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

        msg=ui->plainTextEdit->toPlainText();

        smtp->sendMail("fleur.express1@gmail@gmail.com",ui->lineEdit_Email->text(),ui->lineEdit_Subject->text(),msg);

        QMessageBox::information(nullptr, QObject::tr("SENT"),
                                 QObject::tr("Email Sended Successfully.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);


}


//imprimer historique

void MainWindow::on_ajouter_12_clicked(){


    QPrinter printer(QPrinter::HighResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);

        printer.setPageMargins(12, 16, 12, 20, QPrinter::Millimeter);
        printer.setFullPage(false);
        QPdfWriter pdf1("C:/Users/Molka/Desktop/validation2/Exportation.pdf");
        QPainter painter (&pdf1);


        double xscale = printer.pageRect().width() / double(ui->textBrowser_2->width());
        double yscale = printer.pageRect().height() / double(ui->textBrowser_2->height());
        double scale = qMin(xscale, yscale);
        painter.translate(printer.pageRect().width() / 2,
                                printer.pageRect().height() / 2);
        painter.scale(scale, scale);
        painter.translate(-ui->textBrowser_2->width()/2, -ui->textBrowser_2->height()/2);
        ui->textBrowser_2->render(&painter);
        painter.drawText(printer.pageRect(), Qt::TextWordWrap, ui->textBrowser_2->toPlainText());



   }
//imprimer client
void MainWindow::on_ajouter_13_clicked()
{

 QString strStream;
                QTextStream out(&strStream);

                const int rowCount = ui->tabclient_7->model()->rowCount();
                const int columnCount = ui->tabclient_7->model()->columnCount();
                QString TT = QDate::currentDate().toString("yyyy/MM/dd");


                out <<"<html>\n"
                      "<head>\n"
                       "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                    << "<title> - Client LIST<title>\n "
                    << "</head>\n"
                     "<body bgcolor=#ffffff link=#5000A0>\n"
                    "<h1 style=\"text-align=center;\"><strong> *****LISTE DES CLIENTS ***** "+TT+"</strong></h1>"
                    "<table style=\"text-align: center; font-size: 150px;\" border=1>\n "
                      "</br> </br>";

                // headers
                //out << "<thead><tr bgcolor=#E6E6FA>";
                out << "<tr bgcolor=#d6e5ff>";//couleur bleu
                for (int column = 0; column < columnCount; column++)
                    if (!ui->tabclient_7->isColumnHidden(column))
                        out << QString("<th>%1</th>").arg(ui->tabclient_7->model()->headerData(column, Qt::Horizontal).toString());
                out << "</tr></thead>\n";

                // data table
                for (int row = 0; row < rowCount; row++) {
                    out << "<tr>";
                    for (int column = 0; column < columnCount; column++) {
                        if (!ui->tabclient_7->isColumnHidden(column)) {
                            QString data =ui->tabclient_7->model()->data(ui->tabclient_7->model()->index(row, column)).toString().simplified();
                            out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                        }
                    }
                    out << "</tr>\n";
                }
                out <<  "</table>\n"
                    "</body>\n"
                    "</html>\n";

               QTextDocument *document = new QTextDocument();
                document->setHtml(strStream);
    QPrinter printer(QPrinter::HighResolution);
    QMessageBox::information(nullptr, QObject::tr("pdf is  open"),
                QObject::tr("imprimer success.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
    printer.setOutputFileName("output1");
                QPrintDialog *baba = new QPrintDialog(&printer, NULL);
                if (baba->exec() == QDialog::Accepted) {
                    document->print(&printer);
                }

                delete document;


    }


void MainWindow::on_lineEdit_referrecher_textChanged(const QString &arg1)//rechercher carte
{

    Carte ca;

   ui->tabcarte_8->setModel(ca.rechercherrefcarte(arg1));

}

void MainWindow::on_connecter_clicked()
{
    bool test=false;

          if(ui->id_edit->text().isEmpty())
          {ui->id_edit->setStyleSheet("border: 1px solid red");

          }
          else {
          ui->id_edit->setStyleSheet("border: 1px solid blue");
          }

          if(ui->mdp_edit->text().isEmpty())
          {ui->mdp_edit->setStyleSheet("border: 1px solid red");

          }
          else {
          ui->mdp_edit->setStyleSheet("border: 1px solid blue");
      }



          if(ui->id_edit->text().isEmpty()||ui->mdp_edit->text().isEmpty())
          { test=true;
             QMessageBox::warning(this,"we deliver","Veuillez remplir les champs obligatoires marqués en rouge");
          }
          if(test==false)
          {QString id=ui->id_edit->text();
          QString mdp=ui->mdp_edit->text();
      if(id=="mmm" && mdp=="mmm")
          ui->stackedWidget->setCurrentIndex(1); // thezek l page num n
      else
         { QMessageBox::warning(this,"we deliver","Veuillez vérifier votre mot de passe ou votre identifiant");}
          }

}

void MainWindow::on_pushButton_7_clicked()
{
     ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_pushButton_12_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pushButton_8_clicked()
{
     ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_pushButton_13_clicked()
{
     ui->stackedWidget->setCurrentIndex(1);
}
 void MainWindow::on_ajouter_prod_4_clicked()
{

    int ID= ui->edit_id_prod_5->text().toInt();
    QString NOM= ui->edit_id_prod_7->text();
    int age=ui->edit_qtt_prod_6->text().toInt();
    QString prenom= ui->edit_qtt_prod_5->text();
    QString poste = ui->edit_id_prod_6->text();

   employee  *p =new employee( ID,  NOM, age,  prenom,   poste);

     p->ajouter_employee();



}







void MainWindow::on_supprimer_prod_3_clicked()
{
    employee*q=new employee();
       q->delateemployee(ui->sup_id_prod_3->text().toInt());
}






void MainWindow::on_tabWidget_4_tabBarClicked(int index)
{
    employee *a = new employee();
     ui->tableView_course_3->setModel(a->getAllemployee());
}




void MainWindow::on_modif_prod_6_clicked()
{
    int ID= ui->modif_id_prod_3->text().toInt();
    QString NOM= ui->modif_nom_prod_3->text();
    int age= ui->modif_qtt_prod_3->text().toInt();
    QString prenom=ui->modif_qtt_prod_4->text();
    QString poste = ui->modif_nom_prod_4->text();
    employee *p=new employee( ID,  NOM, age,  prenom,   poste);
    //if (){
    p->modifier_employee(ID);
  //  }
   // else (QDebug<>);
}

void MainWindow::on_trouv_prod_3_clicked()
{


    int cin = ui->trouv_prod_5->text().toInt();

    tmpm.getemployee(cin);

    QString cinn= QString::number(tmpm.getcin());

        QString age= QString::number(tmpm.getage());
    ui->modif_id_prod_3->setText(cinn);
      ui->modif_nom_prod_3->setText(tmpm.getNOM());
      ui->modif_qtt_prod_3->setText(age);
      ui->modif_qtt_prod_4->setText(tmpm.getPrenom());
      ui->modif_nom_prod_4->setText(tmpm.getposte());
}



void MainWindow::on_ajouter_prod_5_clicked()
{


    int ID = ui->edit_id_prod_9->text().toInt();
    QString salaire= ui->edit_id_prod_10->text();
    int duree=ui->edit_id_prod_12->text().toInt() ;
    QString datedeb= ui->edit_id_prod_11->text();
    QString EMAIL = ui->edit_id_prod_13->text();

   contrat  *p =new contrat( ID,  salaire, duree,  datedeb,   EMAIL);

      p->ajouter_contrat() ;
}

void MainWindow::on_tabWidget_5_tabBarClicked()
{
    contrat *a = new contrat();
     ui->tableView_course_4->setModel(a->getAllcontrat());
}

void MainWindow::on_supprimer_prod_4_clicked()
{
    contrat *c=new contrat();
       c->delatecontrat(ui->sup_id_prod_4->text().toInt());
}

void MainWindow::on_modif_prod_7_clicked()
{
    int ID= ui->modif_id_prod_4->text().toInt();
    QString salaire= ui->modif_qtt_prod_7->text();
    int datedeb= ui->modif_qtt_prod_8->text().toInt();
    QString duree=ui->modif_qtt_prod_6->text();
    QString EMAIL = ui->modif_qtt_prod_9->text();
    contrat  *p =new contrat( ID,  salaire, datedeb,  duree,   EMAIL);
    p->modifier_contrat(ID);

}

void MainWindow::on_trouv_prod_4_clicked()
{

    int cin = ui->trouv_id_prod_4->text().toInt();

    tmp.getcontrat(cin);

    QString cinn= QString::number(tmp.getcin());

        QString duree= QString::number(tmp.getduree());
    ui->modif_id_prod_4->setText(cinn);
      ui->modif_qtt_prod_7->setText(tmp.getsalaire());
      ui->modif_qtt_prod_8->setText(duree);
      ui->modif_qtt_prod_6->setText(tmp.getdatedeb());
      ui->modif_qtt_prod_9->setText(tmp.getEMAIL());
}





void MainWindow::on_edit_rechavanc_prod_3_textChanged(const QString &arg1)
{
    QString ch = ui->edit_rechavanc_prod_3->text();


    employee *p=new employee();
    ui->tableView_course_3->setModel(p->getAllemployeeavance(ch));
}




void MainWindow::on_tri_1_activated(const QString &arg1)
{
    if (arg1 == "Cin"){
    ui->tableView_course_3->setModel(tmpm.getemployeestriid());
    }
    else if (arg1 == "Nom"){
    ui->tableView_course_3->setModel(tmpm.getemployeestrinom());
    }
    else if (arg1 == "prenom"){
    ui->tableView_course_3->setModel(tmpm.getemployeestriprenom());
    }

    else if (arg1 == "age"){
    ui->tableView_course_3->setModel(tmpm.getemployeestriage());
    }

    else if (arg1 == "poste"){
    ui->tableView_course_3->setModel(tmpm.getemployeestriposte());
}
}


void MainWindow::sendMail()
{
    Smtp* smtp = new Smtp(ui->uname->text(), ui->paswd->text(), ui->server->text(), ui->port->text().toInt(), 30000);
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));


    smtp->sendMail(ui->uname->text(), ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText());
}

void MainWindow::mailSent(QString status)
{
    if(status == "Message sent")
        QMessageBox::warning( 0, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
}

void MainWindow::on_pushButton_39_clicked()
{
   int cin = ui->edit_rechavanc_prod_4->text().toInt();

    QSqlQuery  query=tmp.exporter(cin);
   while (query.next())
             {
               QString SALAIRE = query.value(0).toString();
               QString DUREE = query.value(1).toString();
               QString DATEDEB = query.value(2).toString();
               QString EMAIL = query.value(3).toString();
               QString CIN = query.value(4).toString();
               QPdfWriter pdf1("C:/Users/ASUS/Documents/PROJET_2A11_RH/Exportation.pdf");
               QPainter painter (&pdf1);
               painter.drawText(2200,3500,SALAIRE);
               painter.drawText(2200,4000,DUREE);
               painter.drawText(2200,4500,DATEDEB);
               painter.drawText(2200,5000,EMAIL);
               painter.drawText(2200,5500,CIN);
             painter.setPen(Qt::blue);
             painter.drawText(4500,2000,"Contrat");
             painter.setPen(Qt::blue);
             painter.drawText(500,3500,"salaire :");
             painter.drawText(500,4000,"duree :");
             painter.drawText(500,4500,"Date deb:");
             painter.drawText(500,5000,"EMAIL :");
             painter.drawText(500,5500,"CIN :");
   }

}




void MainWindow::on_edit_rechavanc_prod_4_textChanged(const QString &arg1)
{
    QString ch = ui->edit_rechavanc_prod_4->text();


    contrat *p=new contrat();
    ui->tableView_course_4->setModel(p->getAllcontratavance(ch));
}

//***********************






