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
#include <QDateTime>
#include <QtMultimedia/QMediaPlayer>
#include"employee.h"
#include"contrat.h"
#include"stati.h"
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

 MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
   ,  ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(myfunction()));
    timer->start(1000);
    connect(ui->sendBtn, SIGNAL(clicked()),this, SLOT(sendMail()));
    connect(ui->exitBtn, SIGNAL(clicked()),this, SLOT(close()));
ui->stackedWidget->setCurrentIndex(0);
refresh();
refresh_mortadha();
smartTools.connect_arduino();

connect(smartTools.getserial(), SIGNAL(readyRead()), this, SLOT(readTemp()));
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
    smtp = new Smtp("gestionrh.2a11@gmail.com" , "22620837cA", "smtp.gmail.com",465);
        connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

        msg=ui->plainTextEdit->toPlainText();

        smtp->sendMail("gestionrh.2a11@gmail.com",ui->lineEdit_Email->text(),ui->lineEdit_Subject->text(),msg);

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
         { ui->stackedWidget->setCurrentIndex(1); // thezek l page num n
       ui->progressBar->setValue(100);}
    //  t.load("../integration/validation2_en.qmn");
//   qApp->installTranslator(&t);
      else
         { QMessageBox::warning(this,"we deliver","Veuillez vérifier votre mot de passe ou votre identifiant");}
          }

}

void MainWindow::on_pushButton_70_clicked()
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


/*void MainWindow::sendMail()
{
    Smtp* smtp = new Smtp(ui->uname->text(), ui->paswd->text(), ui->server->text(), ui->port->text().toInt(), 30000);
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));


    smtp->sendMail(ui->uname->text(), ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText());
}

void MainWindow::mailSent(QString status)
{
    if(status == "Message sent")
        QMessageBox::warning( 0, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
}*/

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
               QPdfWriter pdf1("C:/Users/ASUS/Desktop/Nouveau dossier/smarthomedelivery_2A11/integration/contrat.pdf");
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







void MainWindow::on_sendBtn_3_clicked()
{

    smtp = new Smtp("gestionrh.2a11@gmail.com" , "22620837cA", "smtp.gmail.com",465);
        connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

        msg=ui->plainTextEdit->toPlainText();

        smtp->sendMail("gestionrh.2a11@gmail.com",ui->lineEdit_Email_2->text(),ui->lineEdit_Subject_2->text(),msg);
        QMessageBox::information(nullptr, QObject::tr("SENT"),
                                 QObject::tr("Email Sended Successfully.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_edit_rechavanc_prod_7_textChanged(const QString &arg1)
{
    QString ch = ui->edit_rechavanc_prod_7->text();


    employee *p=new employee();
    ui->tableView_course_7->setModel(p->getAllemployeeavance(ch));
    contrat *d=new contrat();
    ui->tableView_course_8->setModel(d->getAllcontratavance(ch));
}

void MainWindow::on_pushButton_41_clicked()
{ employee e;

       int cin = ui->edit_rechavanc_prod_7->text().toInt();

        QSqlQuery  query=e.exporterpdf1(cin);

       while (query.next())
                 {
                   QString SALAIRE = query.value(5).toString();
                   QString DUREE = query.value(6).toString();
                   QString DATEDEB = query.value(7).toString();
                   QString EMAIL = query.value(8).toString();
                   QString CIN = query.value(0).toString();
                   QString nom= query.value(1).toString();
                   QString prenom= query.value(2).toString();




                   QString poste= query.value(4).toString();
                   QString age= query.value(3).toString();
                   QPdfWriter pdf2("C:/Users/ASUS/Desktop/Nouveau dossier/smarthomedelivery_2A11/integration/ficha.pdf");
                   QPainter painter (&pdf2);


                   painter.drawText(2200,3500,CIN);
                   painter.drawText(2200,4000,nom);
                   painter.drawText(2200,4500,prenom);
                   painter.drawText(2200,5000,age);
                   painter.drawText(2200,5500,poste);
                   painter.drawText(2200,6000,SALAIRE);
                   painter.drawText(2200,6500,DUREE);
                   painter.drawText(2200,7000,DATEDEB);
                   painter.drawText(2200,7500,EMAIL);



                 painter.setPen(Qt::blue);
                 painter.drawText(4500,2000,"fiche personelle");
                 painter.setPen(Qt::darkGreen);
                 painter.drawText(500,3500,"cin :");
                 painter.drawText(500,4000,"nom :");
                 painter.drawText(500,4500,"prenom:");
                 painter.drawText(500,5000,"age :");
                 painter.drawText(500,5500,"poste :");
                 painter.drawText(500,6000,"salaire :");
                 painter.drawText(500,6500,"duree  :");
                 painter.drawText(500,7000,"date deb :");
                 painter.drawText(500,7500,"email :");


}
}
//**************************
void MainWindow::on_pushButton_34_clicked()// excel

{
    QTableView *table;
    table = ui->tabclient_7;

    QString filters("CSV files (*.csv);;All files (*.*)");
    QString defaultFilter("CSV files (*.csv)");
    QString fileName = QFileDialog::getSaveFileName(0, "Save file", QCoreApplication::applicationDirPath(),
                       filters, &defaultFilter);
    QFile file(fileName);

    QAbstractItemModel *model =  table->model();
    if (file.open(QFile::WriteOnly | QFile::Truncate)) {
        QTextStream data(&file);
        QStringList strList;
        for (int i = 0; i < model->columnCount(); i++) {
            if (model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString().length() > 0)
                strList.append("\"" + model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString() + "\"");
            else
                strList.append("");
        }
        data << strList.join(";") << "\n";
        for (int i = 0; i < model->rowCount(); i++) {
            strList.clear();
            for (int j = 0; j < model->columnCount(); j++) {

                if (model->data(model->index(i, j)).toString().length() > 0)
                    strList.append("\"" + model->data(model->index(i, j)).toString() + "\"");
                else
                    strList.append("");
            }
            data << strList.join(";") + "\n";
        }
        file.close();
        QMessageBox::information(this,"Exporter To Excel","Exporter En Excel Avec Succées ");
    }

}
//*********
void MainWindow::on_commandLinkButton_6_clicked()
{
    QString link = "https://www.google.com/";
    QDesktopServices :: openUrl(QUrl(link));
}

void MainWindow::on_commandLinkButton_8_clicked()
{   QString link = "https://www.linkedin.com/login?fromSignIn=true&trk=guest_homepage-basic_nav-header-signin";
    QDesktopServices :: openUrl(QUrl(link));

}

void MainWindow::on_commandLinkButton_9_clicked()
{
    QString link = "https://www.instagram.com/";
    QDesktopServices :: openUrl(QUrl(link));
}

void MainWindow::on_commandLinkButton_10_clicked()
{
     QString link = "https://www.facebook.com/";
    QDesktopServices :: openUrl(QUrl(link));
}

void MainWindow::on_commandLinkButton_7_clicked()
{ QString link = "https://www.youtube.com/";
    QDesktopServices :: openUrl(QUrl(link));

}
//************************************************************
/*
void MainWindow::changeEvent(QEvent* event)
{
    if(event->type() == QEvent::LanguageChange)
    {
        ui->retranslateUi(this);
        qDebug()<<"event";


    }

    QWidget::changeEvent(event);
}

void MainWindow::on_btnEnglish_clicked()
{   qApp->installTranslator(&translatorFa);
    qDebug()<<"successfully load translation_fa file.";


 //   QTranslator translator;
  //      translator.load("C:/Users/Molka/Desktop/validation2/validation2_en.qm");
 //
     //  a.installTranslator(&translator);
}

void MainWindow::on_btnGerman_clicked()
{
     qApp->removeTranslator(&translatorFa);
     qDebug()<<"ssuususu load translation_fa file.";

}*/
/********************/
void MainWindow::on_pushButton_18_clicked()
{
    int idR=0;
       QString textajouter;//historique
       historique h;
    int qt=ui->qt_e->text().toInt() ;
    QString nom=ui->nom_e->text();
    QString type=ui->type_e->text();
    QString pays=ui->pays_e->text();
    if( qt<2||qt>100 || qt==0 ){

           { if(qt==0 )
                   ui->qt_e->setText("   *champ obligatoire");
               else{
                   ui->qt_e->setText("   quantite non valide");


                   QMessageBox::critical(nullptr, QObject::tr("Ajouter un emploi"),
                               QObject::tr("Erreur d'ajout !.\n"
                                           "Click Cancel to exit."), QMessageBox::Cancel);

               }
           }
    }
    else
    {
    produit p(qt,nom,type,pays);
    bool test=p.ajouter();
    if(test)
    {
        ui->tabproduit_2->setModel(tempProd.afficher());
        QMessageBox::information(nullptr,"Ajout effectue ","Click Cancel to exit.");
    }
                                 else {
            QMessageBox::warning(nullptr,"Ajout non effectue","Click Cancel to exit.");
                                 }
}
    QSqlQuery qry;
       qry.prepare("select * from produit");
       if (qry.exec())
       {
           while (qry.next())
           {
   idR =qry.value(3).toInt();
           }
       }

       textajouter="L'ajout d'un Produit dans la base de donnees de nom = "+QString::number(idR)+" a ete effectuee avec succees";
       h.write(textajouter);
       ui->textBrowser2->show();
       ui->textBrowser2->setPlainText(h.read());
}

void MainWindow::on_supprimer23_clicked()
{
    QString nom=ui->laylay->text();
   bool test= tempProd.supprimer(nom);
   if(test)
   {
       ui->tabproduit_2->setModel(tempProd.afficher());
       QMessageBox::information(nullptr,"suppression produit","produit supprimé.");
   }
                                else {
           QMessageBox::warning(nullptr,"suppression produit","produit non suppprimé.");
                                }
   QString textajouter;
   int idR=0;
           historique h;
           QSqlQuery qry;
           qry.prepare("select * from produit");
           if (qry.exec())
           {

               while (qry.next())
               {
       idR =qry.value(3).toInt();
               }
           }

           textajouter="La supression d'un produit de la base de donnees de nom = "+QString::number(idR)+" a ete effectuee avec succees";
           h.write(textajouter);
}

void MainWindow::on_pushButton_32_clicked()
{
    int cin=ui->cin->text().toInt() ;
    QString nom1=ui->nom1->text();
    QString add=ui->adresse->text();
    QString ref=ui->ref_2->text();
    if( cin<100000||cin>999999 || cin==0 ){

           { if(cin==0 )
                   ui->cin->setText("   *champ obligatoire");
               else{
                   ui->cin->setText("   id non valide");


                   QMessageBox::critical(nullptr, QObject::tr("Ajouter un emploi"),
                               QObject::tr("Erreur d'ajout !.\n"
                                           "Click Cancel to exit."), QMessageBox::Cancel);

               }
           }
    }
    else {
    livraison d(cin,nom1,add,ref);
    bool test=d.ajouter();
    if(test)
    {
        ui->tablivraison->setModel(templivr.afficher());
        QMessageBox::information(nullptr,"Ajout effectue ","Click Cancel to exit.");
    }
                                 else {
            QMessageBox::warning(nullptr,"Ajout non effectue","Click Cancel to exit.");
                                 }
}
}
void MainWindow::on_pushButton_38_clicked()
{
    QString ref=ui->ref->text();
   bool test= templivr.supprimer(ref);
   if(test)
   {
       ui->tablivraison->setModel(templivr.afficher());
       QMessageBox::information(nullptr,"suppression commande","commande supprimé.");
   }
                                else {
           QMessageBox::warning(nullptr,"suppression commande","commande non suppprimé.");
                                }
}

void MainWindow::on_modifier_2_clicked()
{
    int qt=ui->qt_m_2->text().toInt() ;
    QString nom=ui->nom_m_2->text();
    QString type=ui->type_m_4->text();
    QString pays=ui->pays_m_2->text();
    produit p(qt,nom,type,pays);
    bool test=p.modifier();
    if(test)
    {
        ui->tabproduit_2->setModel(tempProd.afficher());
        QMessageBox::information(nullptr,"modification effectue ","Click Cancel to exit.");
    }
                                 else {
            QMessageBox::warning(nullptr,"modification non effectue","Click Cancel to exit.");
            QString textajouter;
            int idR=0;
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

            textajouter="La modification d'un produit de la base de donnees de reference = "+QString::number(idR)+" a ete effectuee avec succees";
            h.write(textajouter);
}
}
void MainWindow::on_pushButton_33_clicked()
{
    int cin=ui->cin_m_2->text().toInt() ;
    QString nom1=ui->nom_m_2->text();
    QString add=ui->adresse_m_2->text();
    QString ref=ui->ref_m_2->text();
    livraison d(cin,nom1,add,ref);
    bool test=d.modifier();
    if(test)
    {
        ui->tablivraison->setModel(templivr.afficher());
        QMessageBox::information(nullptr,"modification effectue ","Click Cancel to exit.");
    }
                                 else {
            QMessageBox::warning(nullptr,"modification non effectue","Click Cancel to exit.");
                                 }
}





void MainWindow::on_comboBox_7_activated(const QString &arg1)
{
    QSqlQueryModel *model=new QSqlQueryModel();
        if (arg1=="nom")
            model->setQuery("select * from produit order by nom");
       else if (arg1=="pays")
            model->setQuery("select * from produit order by pays");
       if (arg1=="type")
            model->setQuery("select * from produit order by type");
       if (arg1=="qt")
            model->setQuery("select * from produit order by qt");

       model->setHeaderData(0, Qt::Horizontal, QObject::tr("nom"));
       model->setHeaderData(1, Qt::Horizontal, QObject::tr("type"));
       model->setHeaderData(2, Qt::Horizontal, QObject::tr("pays"));
       model->setHeaderData(3, Qt::Horizontal, QObject::tr("qt_stock"));

   ui->tabproduit_2->setModel(model);
}

void MainWindow::on_lineEdit_4_textChanged(const QString &arg1)
{
    if(arg1 == ""){
        ui->tabproduit_2->setModel(tempProd.afficher());//naabi m tab l je m base de donée te3i
    }else{
        ui->tabproduit_2->setModel(tempProd.cherchernom(arg1));//naabi m tab l je m base de donée te3i
    }


}

void MainWindow::on_pushButton_46_clicked()
{
    stati stati ;
    stati.setModal(true);
    stati.exec();
}



void MainWindow::on_comboBox_14_activated(const QString &bb)
{

    QSqlQueryModel *model=new QSqlQueryModel();
        if (bb=="ref")
            model->setQuery("select * from livraison order by ref");
       else if (bb=="nom1")
            model->setQuery("select * from livraison order by nom1");
       if (bb=="cin")
            model->setQuery("select * from livraison order by cin");
       if (bb=="add")
            model->setQuery("select * from livraison order by add");
       model->setHeaderData(0, Qt::Horizontal, QObject::tr("ref"));
       model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom1"));
       model->setHeaderData(2, Qt::Horizontal, QObject::tr("cin"));
       model->setHeaderData(3, Qt::Horizontal, QObject::tr("add"));
     ui->tablivraison->setModel(model);

}

void MainWindow::on_lineEdit_3_textChanged(const QString &arg1)
{
    if(arg1 == ""){
        ui->tablivraison->setModel(templivr.afficher());
    }else{
        ui->tablivraison->setModel(templivr.cherchernom1(arg1));
    }
}

/*void MainWindow::on_pushButton_24_clicked()
{
    // This is a first demo application of the SmtpClient for Qt project

      // First we need to create an SmtpClient object
      // We will use the Gmail's smtp server (smtp.gmail.com, port 465, ssl)

      SmtpClient smtp("smtp.gmail.com", 465, SmtpClient::SslConnection);

      // We need to set the username (your email address) and the password
      // for smtp authentification.

      smtp.setUser("aziz.zarkaoui12388@gmail.com");
      smtp.setPassword("lionelzizou12388");

      // Now we create a MimeMessage object. This will be the email.

      MimeMessage message;

      message.setSender(new EmailAddress("aziz.zarkaoui12388@gmail.com", "aziz"));
      message.addRecipient(new EmailAddress(ui->rcpt->text(), "Recipient's Name"));
      message.setSubject(ui->subject->text());

      // Now add some text to the email.
      // First we create a MimeText object.

      MimeText text;

      text.setText(ui->lineEdit_7->text() );

      // Now add it to the mail

      message.addPart(&text);

      // Now we can send the mail

      smtp.connectToHost();
      smtp.login();
      smtp.sendMail(message);
      smtp.quit();


}*/
void MainWindow::on_pushButton_30_clicked()
{
    QString strStream;
            QTextStream out(&strStream);

            const int rowCount = ui->tabproduit_2->model()->rowCount();
            const int columnCount = ui->tabproduit_2->model()->columnCount();
            QString TT = QDate::currentDate().toString("yyyy/MM/dd");


            out <<"<html>\n"
                  "<head>\n"
                   "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                << "<title> - Client LIST<title>\n "
                << "</head>\n"
                 "<body bgcolor=#ffffff link=#5000A0>\n"
                "<h1 style=\"text-align=center;\"><strong> ****LISTE DES CLIENTS **** "+TT+"</strong></h1>"
                "<table style=\"text-align: center; font-size: 140px;\" border=1>\n "
                  "</br> </br>";

            // headers
            //out << "<thead><tr bgcolor=#E6E6FA>";
            out << "<tr bgcolor=#d6e5ff>";//couleur bleu
            for (int column = 0; column < columnCount; column++)
                if (!ui->tabproduit_2->isColumnHidden(column))
                    out << QString("<th>%30</th>").arg(ui->tabproduit_2->model()->headerData(column, Qt::Horizontal).toString());
            out << "</tr></thead>\n";

            // data table
            for (int row = 0; row < rowCount; row++) {
                out << "<tr>";
                for (int column = 0; column < columnCount; column++) {
                    if (!ui->tabproduit_2->isColumnHidden(column)) {
                        QString data =ui->tabproduit_2->model()->data(ui->tabproduit_2->model()->index(row, column)).toString().simplified();
                        out << QString("<td bkcolor=0>%30</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
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
QMessageBox::critical(nullptr, QObject::tr("pdf is  open"),
            QObject::tr("pdf success.\n"
                        "Click Cancel to exit."), QMessageBox::Cancel);
printer.setOutputFileName("output1");
            QPrintDialog *baba = new QPrintDialog(&printer, NULL);
            if (baba->exec() == QDialog::Accepted) {
                document->print(&printer);
            }

            delete document;


}
void MainWindow::update_label()
{
data=A.read_from_arduino();
if(data=="1")
{
  ui->label_40->setText("ON");
}
if(data=="2")
{
  ui->label_40->setText("OFF");
}
}

void MainWindow::on_pushButton_52_clicked()
{
    A.write_to_arduino("1");
}


void MainWindow::on_pushButton_55_clicked()
{
    A.write_to_arduino("2");
}

void MainWindow::on_pushButton_53_clicked()
{
  A.write_to_arduino("3");
}

void MainWindow::on_pushButton_54_clicked()
{
   A.write_to_arduino("4");
}
void MainWindow::myfunction()
{
    QTime time = QTime::currentTime();
    QString time_text = time.toString("hh: mm : ss");
    ui->label_183->setText(time_text);
}

void MainWindow::on_pushButton_14_clicked()
{
    historique h;

            ui->textBrowser2->show();
            ui->textBrowser2->setPlainText(h.read());
}

void MainWindow::on_sendBtn_4_clicked()
{
    smtp = new Smtp("gestionrh.2a11@gmail.com" , "22620837cA", "smtp.gmail.com",465);
        connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

        msg=ui->plainTextEdit->toPlainText();

        smtp->sendMail("gestionrh.2a11@gmail.com",ui->lineEdit_Email_3->text(),ui->lineEdit_Subject_3->text(),msg);
        QMessageBox::information(nullptr, QObject::tr("SENT"),
                                 QObject::tr("Email Sended Successfully.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
}
/*aziiiiiiiiiiiiiiiz*/
void MainWindow::on_pushButton_9_clicked()
{

        ui->stackedWidget->setCurrentIndex(4);

}
/************************/

void MainWindow::refresh(){
    ui->Fournisseur_affichage->setModel(tmp_Fournisseur.afficher());
    ui->Commande_affichage->setModel(tmp_commande.afficher());
    ui->comboBox_idf->setModel(tmp_Fournisseur.afficher());
    ui->comboBox_idf1->setModel(tmp_Fournisseur.afficher());
}






//Crud Fournisseur

void MainWindow::on_pb_ajouter_pr_clicked()
{
    QString cin= ui->lineEdit_cin->text();

    QString prenom = ui->lineEdit_prenom->text();
    QString nom= ui->lineEdit_nom->text();
    QString mail= ui->lineEdit_mail->text();
    int salaire= ui->lineEdit_salaire->text().toInt();
    Fournisseur f(cin,prenom,nom,mail,salaire);

    if (f.testCin(ui->lineEdit_cin->text())==false)
    {

        QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP CIN!!!!") ;
        QMessageBox::critical(0, qApp->tr("Ajout"),

                              qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

    }
    else if (ui->lineEdit_nom->text().isEmpty())
    {

        QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP NOM!!!!") ;
        QMessageBox::critical(0, qApp->tr("Ajout"),

                              qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

    }
    else if (ui->lineEdit_prenom->text().isEmpty())
    {

        QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP PRENOM!!!!") ;
        QMessageBox::critical(0, qApp->tr("Ajout"),

                              qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

    }
    else if (ui->lineEdit_salaire->text().isEmpty())
    {

        QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP salaire!!!!") ;
        QMessageBox::critical(0, qApp->tr("Ajout"),

                              qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

    }

    else if (f.testmail(ui->lineEdit_mail->text())==false)
    {

        QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP MAIL!!!!") ;
        QMessageBox::critical(0, qApp->tr("Ajout"),

                              qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

    }

    else {

        bool test=f.ajouter();
        if(test)
        {

            refresh();

            N1.notification_ajoutFournisseur();

        }
        else
            QMessageBox::critical(nullptr, QObject::tr("Ajouter un Fournisseur"),
                                  QObject::tr("Erreur !.\n"
                                              "Click Cancel to exit."), QMessageBox::Cancel);

    }}

void MainWindow::on_pb_modifier_pr_clicked()
{
    QString cin= ui->lineEdit_cin1->text();

    QString prenom = ui->lineEdit_prenom1->text();
    QString nom= ui->lineEdit_nom1->text();
    QString mail= ui->lineEdit_mail1->text();
    int salaire= ui->lineEdit_salaire1->text().toInt();
    Fournisseur f(cin,prenom,nom,mail,salaire);

    if (f.testCin(ui->lineEdit_cin1->text())==false)
    {

        QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP CIN!!!!") ;
        QMessageBox::critical(0, qApp->tr("Ajout"),

                              qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

    }
    else if (ui->lineEdit_nom1->text().isEmpty())
    {

        QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP NOM!!!!") ;
        QMessageBox::critical(0, qApp->tr("Ajout"),

                              qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

    }
    else if (ui->lineEdit_prenom1->text().isEmpty())
    {

        QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP PRENOM!!!!") ;
        QMessageBox::critical(0, qApp->tr("Ajout"),

                              qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

    }
    else if (ui->lineEdit_salaire1->text().isEmpty())
    {

        QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP salaire!!!!") ;
        QMessageBox::critical(0, qApp->tr("Ajout"),

                              qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

    }

    else if (f.testmail(ui->lineEdit_mail1->text())==false)
    {

        QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP MAIL!!!!") ;
        QMessageBox::critical(0, qApp->tr("Ajout"),

                              qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

    }

    else {
        bool test=f.modifier();
        if(test)
        {
            N1.notification_modifierFournisseur();
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
        ui->lineEdit_salaire1->clear();


    }}

void MainWindow::on_pb_supprimer_pr_clicked()
{
    if(ui->Fournisseur_affichage->currentIndex().row()==-1)
        QMessageBox::information(nullptr, QObject::tr("Suppression"),
                                 QObject::tr("Veuillez Choisir une Fournisseur du Tableau.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
    else
    {   int cin=ui->Fournisseur_affichage->model()->data(ui->Fournisseur_affichage->model()->index(ui->Fournisseur_affichage->currentIndex().row(),0)).toInt();
        Fournisseur p(ui->Fournisseur_affichage->model()->data(ui->Fournisseur_affichage->model()->index(ui->Fournisseur_affichage->currentIndex().row(),0)).toString(),ui->Fournisseur_affichage->model()->data(ui->Fournisseur_affichage->model()->index(ui->Fournisseur_affichage->currentIndex().row(),1)).toString(),ui->Fournisseur_affichage->model()->data(ui->Fournisseur_affichage->model()->index(ui->Fournisseur_affichage->currentIndex().row(),2)).toString(),ui->Fournisseur_affichage->model()->data(ui->Fournisseur_affichage->model()->index(ui->Fournisseur_affichage->currentIndex().row(),3)).toString(),ui->Fournisseur_affichage->model()->data(ui->Fournisseur_affichage->model()->index(ui->Fournisseur_affichage->currentIndex().row(),4)).toInt());



        QString str = " Vous voulez vraiment supprimer \n le Fournisseur :";
        int ret = QMessageBox::question(this, tr("Fournisseur"),str,QMessageBox::Ok|QMessageBox::Cancel);

        switch (ret) {
        case QMessageBox::Ok:
            if (p.supprimer(cin)){
                N1.notification_supprimerFournisseur();
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

void MainWindow::on_Fournisseur_affichage_activated(const QModelIndex &index)
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
            ui->lineEdit_salaire1->setText(query.value(4).toString());




        }

    }
    else
    {
        QObject::tr("Veuillez Choisir Un ID Du Tableau SVP");
    }
}



//Fin Crud Fournisseur


//Crud Commandes



void MainWindow::on_pb_ajouter_c_clicked()
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

        QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP IDENTIFIANT!!!!") ;
        QMessageBox::critical(0, qApp->tr("Ajout"),

                              qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

    }

    else if (ui->lineEdit_idp->text().isEmpty())
    {

        QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP id produit!!!!") ;
        QMessageBox::critical(0, qApp->tr("Ajout"),

                              qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

    }
    else if (ui->lineEdit_prix->text().isEmpty())
    {

        QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP PRIX!!!!") ;
        QMessageBox::critical(0, qApp->tr("Ajout"),

                              qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

    }
    else if (ui->lineEdit_quantite->text().isEmpty())
    {

        QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP quantite!!!!") ;
        QMessageBox::critical(0, qApp->tr("Ajout"),

                              qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

    }
    else if (ui->lineEdit_etat->text().isEmpty())
    {

        QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP etat !!!!") ;
        QMessageBox::critical(0, qApp->tr("Ajout"),

                              qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

    }

    else{
        bool test=c.ajouter();
        if(test)
        {
            N1.notification_ajoutCommande();

            refresh();


        }
        else
            QMessageBox::critical(nullptr, QObject::tr("Ajouter une Commande"),
                                  QObject::tr("Erreur !.\n"
                                              "Click Cancel to exit."), QMessageBox::Cancel);

    }}

void MainWindow::on_pb_modifier_c_clicked()
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

        QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP IDENTIFIANT!!!!") ;
        QMessageBox::critical(0, qApp->tr("Ajout"),

                              qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

    }

    else if (ui->lineEdit_idp1->text().isEmpty())
    {

        QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP id produit!!!!") ;
        QMessageBox::critical(0, qApp->tr("Ajout"),

                              qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

    }
    else if (ui->lineEdit_prix1->text().isEmpty())
    {

        QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP PRIX!!!!") ;
        QMessageBox::critical(0, qApp->tr("Ajout"),

                              qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

    }
    else if (ui->lineEdit_quantite1->text().isEmpty())
    {

        QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP quantite!!!!") ;
        QMessageBox::critical(0, qApp->tr("Ajout"),

                              qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

    }
    else if (ui->lineEdit_etat1->text().isEmpty())
    {

        QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP etat !!!!") ;
        QMessageBox::critical(0, qApp->tr("Ajout"),

                              qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

    }









    else{



        bool test=c.modifier();
        if(test)
        {



            refresh();
            N1.notification_modifierCommande();



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

void MainWindow::on_pb_supprimer_c_clicked()
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
                N1.notification_supprimerCommande();
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

void MainWindow::on_Commande_affichage_activated(const QModelIndex &index)
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
        QObject::tr("Veuillez Choisir Un ID Du Tableau SVP");
    }

}
//Fin Crud Commandes



void MainWindow::on_recherche_fournisseur_textChanged()
{
    if(ui->recherche_fournisseur->text()!="")
    {        QString b=ui->comboBox_recherche_fournisseur->currentText();
        QString a=ui->recherche_fournisseur->text();
        ui->Fournisseur_affichage->setModel(tmp_Fournisseur.displayClause("WHERE ("+b+" LIKE '%"+a+"%')"));
    }
    else
        ui->Fournisseur_affichage->setModel(tmp_Fournisseur.afficher());

}

void MainWindow::on_recherche_commande_textChanged()
{
    if(ui->recherche_commande->text()!="")
    {        QString b=ui->comboBox_recherche_commande->currentText();
        QString a=ui->recherche_commande->text();
        ui->Commande_affichage->setModel(tmp_commande.displayClause("WHERE ("+b+" LIKE '%"+a+"%')"));
    }
    else
        ui->Commande_affichage->setModel(tmp_commande.afficher());
}

void MainWindow::on_tri_croissant_Fournisseur_clicked()
{
    ui->Fournisseur_affichage->setModel(tmp_Fournisseur.tricroissant());

}

void MainWindow::on_tri_deccroissant_Fournisseur_clicked()
{
    ui->Fournisseur_affichage->setModel(tmp_Fournisseur.trideccroissant());

}

void MainWindow::on_tri_croissant_Commande_clicked()
{
    ui->Commande_affichage->setModel(tmp_commande.tricroissant());

}

void MainWindow::on_tri_deccroissant_Commande_clicked()
{
    ui->Commande_affichage->setModel(tmp_commande.trideccroissant());

}



void MainWindow::on_stat_commande_clicked()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from COMMANDES where PRIX < 500 ");
    float salaire=model->rowCount();
    model->setQuery("select * from COMMANDES where PRIX  between 500 and 1000 ");
    float salairee=model->rowCount();
    model->setQuery("select * from COMMANDES where PRIX>1000 ");
    float salaireee=model->rowCount();
    float total=salaire+salairee+salaireee;
    QString a=QString("moins de 500 Dinars "+QString::number((salaire*100)/total,'f',2)+"%" );
    QString b=QString("entre 500 et 1000 Dinars "+QString::number((salairee*100)/total,'f',2)+"%" );
    QString c=QString("+1000 Dinars "+QString::number((salaireee*100)/total,'f',2)+"%" );
    QPieSeries *series = new QPieSeries();
    series->append(a,salaire);
    series->append(b,salairee);
    series->append(c,salaireee);
    if (salaire!=0)
    {QPieSlice *slice = series->slices().at(0);
        slice->setLabelVisible();
        slice->setPen(QPen());}
    if ( salairee!=0)
    {
        // Add label, explode and define brush for 2nd slice
        QPieSlice *slice1 = series->slices().at(1);
        //slice1->setExploded();
        slice1->setLabelVisible();
    }
    if(salaireee!=0)
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

void MainWindow::on_stat_fournisseur_clicked()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from FOURNISSEUR where SALAIRE < 500 ");
    float salaire=model->rowCount();
    model->setQuery("select * from FOURNISSEUR where SALAIRE  between 500 and 1000 ");
    float salairee=model->rowCount();
    model->setQuery("select * from FOURNISSEUR where SALAIRE>1000 ");
    float salaireee=model->rowCount();
    float total=salaire+salairee+salaireee;
    QString a=QString("moins de 500 Dinars "+QString::number((salaire*100)/total,'f',2)+"%" );
    QString b=QString("entre 500 et 1000 Dinars "+QString::number((salairee*100)/total,'f',2)+"%" );
    QString c=QString("+1000 Dinars "+QString::number((salaireee*100)/total,'f',2)+"%" );
    QPieSeries *series = new QPieSeries();
    series->append(a,salaire);
    series->append(b,salairee);
    series->append(c,salaireee);
    if (salaire!=0)
    {QPieSlice *slice = series->slices().at(0);
        slice->setLabelVisible();
        slice->setPen(QPen());}
    if ( salairee!=0)
    {
        // Add label, explode and define brush for 2nd slice
        QPieSlice *slice1 = series->slices().at(1);
        //slice1->setExploded();
        slice1->setLabelVisible();
    }
    if(salaireee!=0)
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
    chart->setTitle("Pourcentage Par Salaire :Nombre Des Fournisseur "+ QString::number(total));
    chart->legend()->hide();
    // Used to display the chart
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->resize(1000,500);
    chartView->show();
}

void MainWindow::on_pdf_commandes_clicked()
{
    QPdfWriter pdf("C:/Users/SeifBS/Desktop/PdfCommandes.pdf");
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
        QDesktopServices::openUrl(QUrl::fromLocalFile("C:/Users/SeifBS/Desktop/PdfCommandes.pdf"));

        painter.end();
    }
    if (reponse == QMessageBox::No)
    {
        painter.end();
    }
}
/*
void MainWindow::mailSent(QString status)
{
    if(status == "Message sent")
        N.mail_Publicite();
}
*/

void MainWindow::on_mail_clicked()
{
    Smtp* smtp = new Smtp("yousefksouri1122@gmail.com","youssefksouri01","smtp.gmail.com",465);
           connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

           smtp->sendMail("yousefksouri1122@gmail.com","onesdiouani@gmail.com",ui->subject->text(),ui->msg->toPlainText());
}

void MainWindow::readTemp(){
    QByteArray data = smartTools.read_from_arduino();
    data.replace("temperature :", "");
    data.replace("C", "");
    data.replace(" ", "");
    if(data.toInt() >= 25){
        smartTools.write_to_arduino("URG\n");
    }else {
        smartTools.write_to_arduino("NORMAL\n");
    }
}

void MainWindow::on_normalBtn_clicked()
{
    smartTools.write_to_arduino("NORMAL\n");
}

void MainWindow::on_urgentBtn_clicked()
{
    smartTools.write_to_arduino("URG\n");
}
//*********************mortadha




void MainWindow::refresh_mortadha(){
    ui->Publicite_affichage_2->setModel(tmp_publicite.afficher());
    ui->Promotion_affichage_2->setModel(tmp_promotion.afficher());

}


QString MainWindow::ConvertirTime(){
    QTime duree =ui->lineEdit_datec_2->time();
    QString h1=QString((duree.toString()[0]));
    QString h2=QString((duree.toString()[1]));
    QString m1=QString((duree.toString()[3]));
    QString m2=QString((duree.toString()[4]));
    QString heure=h1.append(h2);
    heure=heure.append(":");
    heure=heure.append(m1);
    heure=heure.append(m2);
    return heure;
}


void MainWindow::on_pb_supprimer_mortadha_2_clicked()
{

    if(ui->Publicite_affichage_2->currentIndex().row()==-1)
        QMessageBox::information(nullptr, QObject::tr("Suppression"),
                                 QObject::tr("Veuillez Choisir une Publicite du Tableau.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
    else
    {   int id=ui->Publicite_affichage_2->model()->data(ui->Publicite_affichage_2->model()->index(ui->Publicite_affichage_2->currentIndex().row(),0)).toInt();
        Publicite pub(ui->Publicite_affichage_2->model()->data(ui->Publicite_affichage_2->model()->index(ui->Publicite_affichage_2->currentIndex().row(),0)).toInt(),ui->Publicite_affichage_2->model()->data(ui->Publicite_affichage_2->model()->index(ui->Publicite_affichage_2->currentIndex().row(),1)).toString(),ui->Publicite_affichage_2->model()->data(ui->Publicite_affichage_2->model()->index(ui->Publicite_affichage_2->currentIndex().row(),2)).toInt(),ui->Publicite_affichage_2->model()->data(ui->Publicite_affichage_2->model()->index(ui->Publicite_affichage_2->currentIndex().row(),3)).toString(),ui->Publicite_affichage_2->model()->data(ui->Publicite_affichage_2->model()->index(ui->Publicite_affichage_2->currentIndex().row(),4)).toString());



        QString str = " Vous voulez vraiment supprimer \n la publicite :";
        int ret = QMessageBox::question(this, tr("Publicite"),str,QMessageBox::Ok|QMessageBox::Cancel);

        switch (ret) {
        case QMessageBox::Ok:
            if (pub.supprimer(id)){
                N.notification_supprimerPublicite();
                musicAdd->setMedia(QUrl("C:/sound/supp succ.mp3"));

                 musicAdd->play();
                refresh_mortadha();
                QMessageBox::information(0, qApp->tr("Suppression"),

                                         qApp->tr("Publicite Supprimée"), QMessageBox::Cancel);

            }
            else
            {

                QMessageBox::critical(0, qApp->tr("Suppression"),
                                      qApp->tr("Publicite non trouvé "), QMessageBox::Cancel);
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
void MainWindow::on_modifier_3_mortadha_2_clicked()
{

    int id=ui->lineEdit_id1->text().toInt();
    int prix = ui->lineEdit_prix1->text().toInt();
    QString nom = ui->lineEdit_nom1->text();
    QString duree = ui->lineEdit_duree1_2->text();
    QString id_p= ui->lineEdit_idp1->text();
    Publicite pub (id,nom,prix,duree,id_p);



    if (ui->lineEdit_id1->text().isEmpty())
    {

        QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP IDENTIFIANT!!!!") ;
        QMessageBox::critical(0, qApp->tr("Ajout"),

                              qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

    }

    else if (ui->lineEdit_nom1->text().isEmpty())
    {

        QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP nom!!!!") ;
        QMessageBox::critical(0, qApp->tr("Ajout"),

                              qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

    }
    else if (ui->lineEdit_prix1->text().isEmpty())
    {

        QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP prix!!!!") ;
        QMessageBox::critical(0, qApp->tr("Ajout"),

                              qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

    }
    else if (ui->lineEdit_idp1->text().isEmpty())
    {

        QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP id produit!!!!") ;
        QMessageBox::critical(0, qApp->tr("Ajout"),

                              qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

    }
    else if (ui->lineEdit_duree1_2->text().isEmpty())
    {

        QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP DUREE!!!!") ;
        QMessageBox::critical(0, qApp->tr("Ajout"),

                              qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

    }

    else{

      bool test=pub.modifier();
        if(test)
        {
            //QMessageBox::information(this," Modifier "," Votre Publicite est modifiée") ;
            QMessageBox::information(0, qApp->tr("Modification"),

                                     qApp->tr("Publicite Modifiée"), QMessageBox::Cancel);


            N.notification_modifierPublicite();
            musicAdd->setMedia(QUrl("C:/sound/modif succ.mp3"));

             musicAdd->play();
            refresh_mortadha();


        }
        else
        {
            QMessageBox::critical(nullptr, QObject::tr("Supprimer Publicite"),
                                  QObject::tr("Erreur !.\n"
                                              "Click Cancel to exit."), QMessageBox::Cancel);
        }

        ui->lineEdit_id1->clear();
        ui->lineEdit_nom1->clear();
        ui->lineEdit_prix1->clear();
        ui->lineEdit_duree1_2->clear();
        ui->lineEdit_idp1->clear();

    }}



void MainWindow::on_Publicite_affichage_activated(const QModelIndex &index)
{
    QString id=ui->Publicite_affichage_2->model()->data(index).toString();
    QSqlQuery query;
    query.prepare("SELECT * FROM PUBLICITE WHERE ID='"+id+"'");
    if(query.exec())
    {
        while(query.next())
        {
            ui->lineEdit_id1->setText(query.value(0).toString());
            ui->lineEdit_nom1->setText(query.value(1).toString());
            ui->lineEdit_prix1->setText(query.value(2).toString());
            ui->lineEdit_duree1_2->setText(query.value(3).toString());
            ui->lineEdit_idp1->setText(query.value(4).toString());


        }

    }
    else
    {
        QObject::tr("Veuillez Choisir Un ID Du Tableau SVP");
    }
}
//Fin Crud Publicite



//Crud Promotion



void MainWindow::on_pb_modifier_pr_mortadha_2_clicked()
{
    QString id = ui->lineEdit_id_pr_2->text();
    QString nom= ui->lineEdit_nom_pr_2->text();
    int pourc= ui->lineEdit_pourc_2->text().toInt();
    QDate datee =ui->dateEdit_3->date();
    QString id_p= ui->lineEdit_idp_pr_2->text();

    Promotion p (id,nom,pourc,datee,id_p);


    if (ui->lineEdit_id_pr_2->text().isEmpty())
    {

        QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP IDENTIFIANT!!!!") ;
        QMessageBox::critical(0, qApp->tr("Ajout"),

                              qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

    }

    else if (ui->lineEdit_nom_pr_2->text().isEmpty())
    {

        QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP Nom!!!!") ;
        QMessageBox::critical(0, qApp->tr("Ajout"),

                              qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

    }
    else if (ui->lineEdit_idp_pr_2->text().isEmpty())
    {

        QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP ID PRODUIT!!!!") ;
        QMessageBox::critical(0, qApp->tr("Ajout"),

                              qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

    }
    else if ((p.test_pourc(pourc)==false)||(ui->lineEdit_pourc_2->text().isEmpty()))
    {

        QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP Pourcentage!!!!") ;
        QMessageBox::critical(0, qApp->tr("Ajout"),

                              qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

    }






    else{




        bool test=p.modifier();
        if(test)
        {



            N.notification_modifierPromotion();
            refresh_mortadha();
            musicAdd->setMedia(QUrl("C:/sound/modif succ.mp3"));

             musicAdd->play();
            QMessageBox::information(nullptr, QObject::tr("Modifier une Promotion"),
                                     QObject::tr("Promotion modifiee.\n"
                                                 "Click Cancel to exit."), QMessageBox::Cancel);



        }
        else
        {
            QMessageBox::critical(nullptr, QObject::tr("Supprimer Promotion"),
                                  QObject::tr("Erreur !.\n"
                                              "Click Cancel to exit."), QMessageBox::Cancel);
        }

        ui->lineEdit_id_pr_2->clear();
        ui->lineEdit_nom_pr_2->clear();
        ui->lineEdit_pourc_2->clear();
        ui->lineEdit_idp1->clear();

    }}

void MainWindow::on_pb_supprimer_pr_mortadha_2_clicked()
{
    if(ui->Promotion_affichage_2->currentIndex().row()==-1)
        QMessageBox::information(nullptr, QObject::tr("Suppression"),
                                 QObject::tr("Veuillez Choisir une Promotion du Tableau.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
    else
    {   int id=ui->Promotion_affichage_2->model()->data(ui->Promotion_affichage_2->model()->index(ui->Promotion_affichage_2->currentIndex().row(),0)).toInt();
        Promotion p(ui->Promotion_affichage_2->model()->data(ui->Promotion_affichage_2->model()->index(ui->Promotion_affichage_2->currentIndex().row(),0)).toString(),ui->Promotion_affichage_2->model()->data(ui->Promotion_affichage_2->model()->index(ui->Promotion_affichage_2->currentIndex().row(),1)).toString(),ui->Promotion_affichage_2->model()->data(ui->Promotion_affichage_2->model()->index(ui->Promotion_affichage_2->currentIndex().row(),2)).toInt(),ui->Promotion_affichage_2->model()->data(ui->Promotion_affichage_2->model()->index(ui->Promotion_affichage_2->currentIndex().row(),3)).toDate(),ui->Promotion_affichage_2->model()->data(ui->Promotion_affichage_2->model()->index(ui->Promotion_affichage_2->currentIndex().row(),4)).toString());



        QString str = " Vous voulez vraiment supprimer \n la Promotion :";
        int ret = QMessageBox::question(this, tr("Promotion"),str,QMessageBox::Ok|QMessageBox::Cancel);

        switch (ret) {
        case QMessageBox::Ok:
            if (p.supprimer(id)){
                N.notification_supprimerPromotion();
                musicAdd->setMedia(QUrl("C:/Users/Lenovo/Desktop/onsss/ONS/sound/supp succ.mp3"));

                 musicAdd->play();
                refresh_mortadha();

                QMessageBox::information(0, qApp->tr("Suppression"),

                                         qApp->tr("Publicite suprimée"), QMessageBox::Cancel);

            }
            else
            {

                QMessageBox::critical(0, qApp->tr("Suppression"),
                                      qApp->tr("Promotion non trouvé "), QMessageBox::Cancel);
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

void MainWindow::on_Promotion_affichage_activated(const QModelIndex &index)
{
    QString id=ui->Promotion_affichage_2->model()->data(index).toString();
    QSqlQuery query;
    query.prepare("SELECT * FROM PROMOTION WHERE ID='"+id+"'");
    if(query.exec())
    {
        while(query.next())
        {
            ui->lineEdit_id_pr_2->setText(query.value(0).toString());
            ui->lineEdit_nom_pr_2->setText(query.value(1).toString());
            ui->lineEdit_pourc_2->setText(query.value(2).toString());
            ui->lineEdit_idp_pr_2->setText(query.value(4).toString());


        }

    }
    else
    {
        QObject::tr("Veuillez Choisir Un ID Du Tableau SVP");
    }

}


//Fin Crud Promotion


void MainWindow::on_recherche_Promotion_textChanged()
{
    if(ui->recherche_Promotion_2->text()!="")
    {       // QString b=ui->comboBox_recherche_Promotion_2_2->currentText();
        QString a=ui->recherche_Promotion_2->text();
        ui->Promotion_affichage_2->setModel(tmp_promotion.displayClause("WHERE (ID LIKE '%"+a+"%' OR NOM LIKE '%"+a+"%' OR POURCENTAGE LIKE '%"+a+"%' OR DATEE LIKE '%"+a+"%' OR ID_P LIKE '%"+a+"%' )"));
    }
    else
        ui->Promotion_affichage_2->setModel(tmp_promotion.afficher());

}

void MainWindow::on_recherche_Publicite_textChanged()
{
    if(ui->recherche_Publicite_2->text()!="")
    {        //QString b=ui->comboBox_recherche_Publicite_2->currentText();
        QString a=ui->recherche_Publicite_2->text();
        ui->Publicite_affichage_2->setModel(tmp_publicite.displayClause("WHERE (ID LIKE '%"+a+"%' OR NOM LIKE '%"+a+"%' OR PRIX LIKE '%"+a+"%' OR DUREE LIKE '%"+a+"%' OR ID_P LIKE '%"+a+"%') "));
    }
    else
        ui->Publicite_affichage_2->setModel(tmp_publicite.afficher());

}


void MainWindow::on_tri_deccroissant_promotion_mortadha_2_clicked()
{
    ui->Promotion_affichage_2->setModel(tmp_promotion.trideccroissant());

}

void MainWindow::on_tri_croissant_publicite_clicked()
{
    ui->Publicite_affichage_2->setModel(tmp_publicite.tricroissant());

}

void MainWindow::on_tri_deccroissant_publicite_clicked()
{
    ui->Publicite_affichage_2->setModel(tmp_publicite.trideccroissant());

}


void MainWindow::on_pdf_publicite_clicked()
{
    QPdfWriter pdf("C:/PdfPublicite.pdf");
    QPainter painter(&pdf);
    int i = 4000;
    painter.setPen(Qt::blue);
    painter.setFont(QFont("Arial", 30));
    painter.drawText(2300,1200,"Liste Des Publicite");
    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 50));
    // painter.drawText(1100,2000,afficheDC);
    painter.drawRect(1500,200,7300,2600);
    //painter.drawPixmap(QRect(7600,70,2000,2600),QPixmap("C:/Users/RH/Desktop/projecpp/image/logopdf.png"));
    painter.drawRect(0,3000,9600,500);
    painter.setFont(QFont("Arial", 9));
    painter.drawText(300,3300,"ID");
    painter.drawText(2300,3300,"NOM");
    painter.drawText(4300,3300,"PRIX");
    painter.drawText(6300,3300,"DUREE");
    painter.drawText(8000,3300,"IDP");



    QSqlQuery query;
    query.prepare("select * from PUBLICITE");
    query.exec();
    while (query.next())
    {
        painter.drawText(300,i,query.value(0).toString());
        painter.drawText(2300,i,query.value(1).toString());
        painter.drawText(4300,i,query.value(2).toString());
        painter.drawText(6300,i,query.value(3).toString());
        painter.drawText(8000,i,query.value(4).toString());



        i = i +500;
    }
    int reponse = QMessageBox::question(this, "Génerer PDF", "<PDF Enregistré>...Vous Voulez Affichez Le PDF ?", QMessageBox::Yes |  QMessageBox::No);
    if (reponse == QMessageBox::Yes)
    {
        QDesktopServices::openUrl(QUrl::fromLocalFile("C:/Users/Admin/Desktop/PdfPublicite.pdf"));

        painter.end();
    }
    if (reponse == QMessageBox::No)
    {
        painter.end();
    }
}




/*void MainWindow::mailSent(QString status)
{
    if(status == "Message sent")
        N.mail_Publicite();
}

void MainWindow::on_send_mail_mortadha_clicked()
{

    Smtp* smtp = new Smtp("youssefksouri1122@gmail.com","youssefksouri01","smtp.gmail.com",465);
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

    smtp->sendMail("youssefksouri1122@gmail.com","bouzgarrou.mortadha2000@gmail.com",ui->subject->text(),ui->msg->toPlainText());
}


*/




void MainWindow::on_pushButton_10_clicked()
{ ui->stackedWidget->setCurrentIndex(5);
}

void MainWindow::on_pushButton_11_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
}

void MainWindow::on_stat_promotion_2_clicked()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from PROMOTION where POURCENTAGE < 10 ");
    float salaire=model->rowCount();
    model->setQuery("select * from PROMOTION where POURCENTAGE  between 10 and 50 ");
    float salairee=model->rowCount();
    model->setQuery("select * from PROMOTION where POURCENTAGE>50 ");
    float salaireee=model->rowCount();
    float total=salaire+salairee+salaireee;
    QString a=QString("moins de 10% "+QString::number((salaire*100)/total,'f',2)+"%" );
    QString b=QString("entre 10% et 50%  "+QString::number((salairee*100)/total,'f',2)+"%" );
    QString c=QString("+50%"+QString::number((salaireee*100)/total,'f',2)+"%" );
    QPieSeries *series = new QPieSeries();
    series->append(a,salaire);
    series->append(b,salairee);
    series->append(c,salaireee);
    if (salaire!=0)
    {QPieSlice *slice = series->slices().at(0);
        slice->setLabelVisible();
        slice->setPen(QPen());}
    if ( salairee!=0)
    {
        // Add label, explode and define brush for 2nd slice
        QPieSlice *slice1 = series->slices().at(1);
        //slice1->setExploded();
        slice1->setLabelVisible();
    }
    if(salaireee!=0)
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
    chart->setTitle("Pourcentage Par Pourcentage de promotion :Nombre Des Promotions "+ QString::number(total));
    chart->legend()->hide();
    // Used to display the chart
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->resize(1000,500);
    chartView->show();
}

void MainWindow::on_stat_publicite_2_clicked()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from PUBLICITE where PRIX < 100 ");
    float salaire=model->rowCount();
    model->setQuery("select * from PUBLICITE where PRIX  between 100 and 500 ");
    float salairee=model->rowCount();
    model->setQuery("select * from PUBLICITE where PRIX>500 ");
    float salaireee=model->rowCount();
    float total=salaire+salairee+salaireee;
    QString a=QString("moins de 100 Dinars "+QString::number((salaire*100)/total,'f',2)+"%" );
    QString b=QString("entre 100 et 500 Dinars "+QString::number((salairee*100)/total,'f',2)+"%" );
    QString c=QString("+500 Dinars "+QString::number((salaireee*100)/total,'f',2)+"%" );
    QPieSeries *series = new QPieSeries();
    series->append(a,salaire);
    series->append(b,salairee);
    series->append(c,salaireee);
    if (salaire!=0)
    {QPieSlice *slice = series->slices().at(0);
        slice->setLabelVisible();
        slice->setPen(QPen());}
    if ( salairee!=0)
    {
        // Add label, explode and define brush for 2nd slice
        QPieSlice *slice1 = series->slices().at(1);
        //slice1->setExploded();
        slice1->setLabelVisible();
    }
    if(salaireee!=0)
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
    chart->setTitle("Pourcentage Par Prix :Nombre Des PUBLICITE "+ QString::number(total));
    chart->legend()->hide();
    // Used to display the chart
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->resize(1000,500);
    chartView->show();
}

void MainWindow::on_tri_croissant_promotion_mortadha_2_clicked()
{
 ui->Promotion_affichage_2->setModel(tmp_promotion.tricroissant());
}

void MainWindow::on_pb_ajouter_pr_mortadha_2_clicked()//ajouter promo
{
    QString id = ui->lineEdit_id_pr_2->text();
    QString nom= ui->lineEdit_nom_pr_2->text();
    int pourc= ui->lineEdit_pourc_2->text().toInt();
    QDate datee =ui->dateEdit->date();
    QString id_p= ui->lineEdit_idp_pr_2->text();
    Promotion p(id,nom,pourc,datee,id_p);

    if (ui->lineEdit_id_pr_2->text().isEmpty())
    {

        QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP IDENTIFIANT!!!!") ;

        QMessageBox::critical(0, qApp->tr("Ajout"),

                              qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);


    }

    else if (ui->lineEdit_nom_pr_2->text().isEmpty())
    {

        QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP Nom!!!!") ;
        QMessageBox::critical(0, qApp->tr("Ajout"),

                              qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

    }
    else if (ui->lineEdit_idp_pr_2->text().isEmpty())
    {

        QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP ID PRODUIT!!!!") ;
        QMessageBox::critical(0, qApp->tr("Ajout"),

                              qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

    }

    else if ((p.test_pourc(pourc)==false)||(ui->lineEdit_pourc_2->text().isEmpty()))
    {

        QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP Pourcentage!!!!") ;
        QMessageBox::critical(0, qApp->tr("Ajout"),

                              qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

    }






    else{
        bool test=p.ajouter();
        if(test)
        {

            refresh_mortadha();
            musicAdd->setMedia(QUrl("C:/sound/ajout succe.mp3"));

             musicAdd->play();
            N.notification_ajoutPromotion();

            QMessageBox::information(nullptr, QObject::tr("Ajouter une Promotion"),
                                     QObject::tr("Promotion ajoutée.\n"
                                                 "Click Cancel to exit."), QMessageBox::Cancel);

        }
        else
            QMessageBox::critical(nullptr, QObject::tr("Ajouter une Promotion"),
                                  QObject::tr("Erreur !.\n"
                                              "Click Cancel to exit."), QMessageBox::Cancel);

    }}









































void MainWindow::on_pb_ajouter_mortadha_2_clicked()//ajouter publi
{
    int id = ui->lineEdit_id_3->text().toInt();
    QString nom= ui->lineEdit_nom_3->text();
    int prix= ui->lineEdit_prix_3->text().toInt();
    QString duree=ConvertirTime();
    QString id_p= ui->lineEdit_idp_3->text();
    Publicite e(id,nom,prix,duree,id_p);



    if (ui->lineEdit_id_3->text().isEmpty())
    {

        QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP IDENTIFIANT!!!!") ;
        QMessageBox::critical(0, qApp->tr("Ajout"),

                              qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

    }

    else if (ui->lineEdit_nom_3->text().isEmpty())
    {

        QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP nom!!!!") ;
        QMessageBox::critical(0, qApp->tr("Ajout"),

                              qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

    }
    else if (ui->lineEdit_prix_3->text().isEmpty())
    {

        QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP prix!!!!") ;
        QMessageBox::critical(0, qApp->tr("Ajout"),

                              qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

    }
    else if (ui->lineEdit_idp_3->text().isEmpty())
    {

        QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP id produit!!!!") ;
        QMessageBox::critical(0, qApp->tr("Ajout"),

                              qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

    }
    else{

        bool test=e.ajouter();
        if(test)
        {

            refresh_mortadha();
            N.notification_ajoutPublicite();
            musicAdd->setMedia(QUrl("C:/sound/ajout succe.mp3"));

             musicAdd->play();

            QMessageBox::information(0, qApp->tr("Ajout"),

                                     qApp->tr("Publicite ajoutée"), QMessageBox::Cancel);

        }
        else
            QMessageBox::critical(nullptr, QObject::tr("Ajouter une Publicite"),
                                  QObject::tr("Erreur !.\n"
                                              "Click Cancel to exit."), QMessageBox::Cancel);
    }

}

//BBBBBBBBBBBBBBBBBBBBBBBB


