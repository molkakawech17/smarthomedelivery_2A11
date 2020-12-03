#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "stati.h"
#include "SmtpMime"
#include "QSslSocket"
#include"QPdfWriter"
#include"QtPrintSupport/QPrinter"
#include"QPainter"
#include <QPrintDialog>
#include <QTextDocument>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tabproduit->setModel(tempProd.afficher());
     ui->tablivraison->setModel(templivr.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_18_clicked()
{
    int qt=ui->qt_e->text().toInt() ;
    QString nom=ui->nom_e->text();
    QString type=ui->type_e->text();
    QString pays=ui->pays_e->text();
    produit p(qt,nom,type,pays);
    bool test=p.ajouter();
    if(test)
    {
        ui->tabproduit->setModel(tempProd.afficher());
        QMessageBox::information(nullptr,"Ajout effectue ","Click Cancel to exit.");
    }
                                 else {
            QMessageBox::warning(nullptr,"Ajout non effectue","Click Cancel to exit.");
                                 }
}

void MainWindow::on_pushButton_23_clicked()
{
  QString nom=ui->nom_e->text();
 bool test= tempProd.supprimer(nom);
 if(test)
 {
     ui->tabproduit->setModel(tempProd.afficher());
     QMessageBox::information(nullptr,"suppression produit","produit supprimé.");
 }
                              else {
         QMessageBox::warning(nullptr,"suppression produit","produit non suppprimé.");
                              }

}


void MainWindow::on_pushButton_32_clicked()
{
    int cin=ui->cin->text().toInt() ;
    QString nom1=ui->nom1->text();
    QString add=ui->adresse->text();
    QString ref=ui->ref_2->text();
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


void MainWindow::on_pushButton_37_clicked()
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

void MainWindow::on_pushButton_22_clicked()
{
    int qt=ui->qt_m->text().toInt() ;
    QString nom=ui->nom_m->text();
    QString type=ui->type_m->text();
    QString pays=ui->pays_m->text();
    produit p(qt,nom,type,pays);
    bool test=p.modifier();
    if(test)
    {
        ui->tabproduit->setModel(tempProd.afficher());
        QMessageBox::information(nullptr,"modification effectue ","Click Cancel to exit.");
    }
                                 else {
            QMessageBox::warning(nullptr,"modification non effectue","Click Cancel to exit.");
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





void MainWindow::on_comboBox_activated(const QString &arg1)
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

   ui->tabproduit->setModel(model);
}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    if(arg1 == ""){
        ui->tabproduit->setModel(tempProd.afficher());//naabi m tab l je m base de donée te3i
    }else{
        ui->tabproduit->setModel(tempProd.cherchernom(arg1));//naabi m tab l je m base de donée te3i
    }


}

void MainWindow::on_pushButton_7_clicked()
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

void MainWindow::on_lineEdit_2_textChanged(const QString &arg1)
{
    if(arg1 == ""){
        ui->tablivraison->setModel(templivr.afficher());
    }else{
        ui->tablivraison->setModel(templivr.cherchernom1(arg1));
    }
}

void MainWindow::on_pushButton_24_clicked()
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


}
void MainWindow::on_pushButton_8_clicked()
{
    QString strStream;
            QTextStream out(&strStream);

            const int rowCount = ui->tabproduit->model()->rowCount();
            const int columnCount = ui->tabproduit->model()->columnCount();
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
                if (!ui->tabproduit->isColumnHidden(column))
                    out << QString("<th>%30</th>").arg(ui->tabproduit->model()->headerData(column, Qt::Horizontal).toString());
            out << "</tr></thead>\n";

            // data table
            for (int row = 0; row < rowCount; row++) {
                out << "<tr>";
                for (int column = 0; column < columnCount; column++) {
                    if (!ui->tabproduit->isColumnHidden(column)) {
                        QString data =ui->tabproduit->model()->data(ui->tabproduit->model()->index(row, column)).toString().simplified();
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
