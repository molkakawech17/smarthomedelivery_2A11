#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <produit.h>
#include <livraison.h>
#include <QMainWindow>
#include "QMessageBox"

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


    void on_pushButton_18_clicked();

    void on_pushButton_23_clicked();

    void on_pushButton_32_clicked();

    void on_pushButton_37_clicked();

    void on_pushButton_22_clicked();

    void on_pushButton_33_clicked();



    void on_comboBox_activated(const QString &arg1);

    void on_lineEdit_textChanged(const QString &arg1);

    void on_pushButton_7_clicked();

    void on_radioButton_20_clicked();

    void on_comboBox_14_activated(const QString &arg1);

    void on_lineEdit_2_textChanged(const QString &arg1);

    void on_pushButton_24_clicked();

    void on_pushButton_8_clicked();

private:
    Ui::MainWindow *ui;
    produit tempProd ;
    livraison templivr ;

};
#endif // MAINWINDOW_H
