#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "employee.h"
#include <QDebug>
#include<QMessageBox>
#include<QDesktopServices>
#include<QSystemTrayIcon>
#include <QSqlQueryModel>
#include<QSqlQuery>
#include  "contrat.h"
#include<QPdfWriter>
#include<QPainter>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
   ,  ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
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


     /* employee *p=new employee( ID,  NOM, QTT,  etat,   prix);
     p->ajouter_employee();*/
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
    p->modifier_employee(ID);

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
    QString numero = ui->edit_id_prod_13->text();

   contrat  *p =new contrat( ID,  salaire, duree,  datedeb,   numero);

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
    QString numero = ui->modif_qtt_prod_9->text();
    contrat  *p =new contrat( ID,  salaire, datedeb,  duree,   numero);
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
      ui->modif_qtt_prod_9->setText(tmp.getnumero());
}

/*void MainWindow::on_pushButton_3_clicked()
{
    QString ch = ui->edit_rechavanc_prod_3->text();
    QString sh = ui->edit_rechavanc_prod_4->text();

    employee *p=new employee();
    ui->tableView_course_3->setModel(p->getAllemployeeavance(ch,sh));
} */




void MainWindow::on_edit_rechavanc_prod_3_textChanged(const QString &arg1)
{
    QString ch = ui->edit_rechavanc_prod_3->text();


    employee *p=new employee();
    ui->tableView_course_3->setModel(p->getAllemployeeavance(ch));
}



