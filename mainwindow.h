#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "smtp.h"
#include <QMainWindow>
#include "employee.h"
#include "contrat.h"
#include "smtp.h"
#include <QtWidgets/QMessageBox>

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
    void on_ajouter_prod_4_clicked();
    void sendMail();
    void mailSent(QString);

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


    void on_tableView_course_3_activated(const QModelIndex &index);

  //  void on_sendBtn_clicked();

    void on_pushButton_39_clicked();

    void on_edit_rechavanc_prod_4_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
employee tmpm ;
contrat tmp ;
};
#endif // MAINWINDOW_H
