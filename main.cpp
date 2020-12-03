#include "mainwindow.h"
#include "connexion.h"
#include <QApplication>
#include <QDebug>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    connexion c;
    bool test=c.createConnection();
     MainWindow w;
     w.setStyleSheet("background-images:url(:aziz.jpg)");
    if(test)
    {qDebug() <<"connexion reussite";
    w.show();}
    else
       qDebug()<<"erreur de connexion";
    return a.exec();
}
