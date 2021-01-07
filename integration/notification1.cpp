#include "notification1.h"
#include <QSystemTrayIcon>
#include<QString>
Notification1::Notification1()
{

}

void Notification1::notification_ajoutFournisseur()
{

    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;

   // notifyIcon->setIcon(QIcon(":/new/prefix1/MyResources/computer-icons-avatar-user-login-avatar.jpg"));
    notifyIcon->show();
    notifyIcon->showMessage("Gestion des Fournisseurs ","Nouveau Fournisseur ajouté ",QSystemTrayIcon::Information);
}
void Notification1::notification_ajoutCommande()
{

    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;

   // notifyIcon->setIcon(QIcon(":/new/prefix1/MyResources/computer-icons-avatar-user-login-avatar.jpg"));
    notifyIcon->show();
    notifyIcon->showMessage("Gestion des Commandes ","Nouvelle Commande ajoutée ",QSystemTrayIcon::NoIcon,15000);
}
void Notification1::notification_supprimerFournisseur(){
    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;

   // notifyIcon->setIcon(QIcon(":/new/prefix1/MyResources/computer-icons-avatar-user-login-avatar.jpg"));
    notifyIcon->show();
    notifyIcon->showMessage("Gestion des Fournisseurs ","Fournisseur Supprimé",QSystemTrayIcon::Information,15000);
}
void Notification1::notification_supprimerCommande(){
    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;

   // notifyIcon->setIcon(QIcon(":/new/prefix1/MyResources/computer-icons-avatar-user-login-avatar.jpg"));
    notifyIcon->show();
    notifyIcon->showMessage("Gestion des Commandes ","Une Commande est supprimée",QSystemTrayIcon::Information,15000);

}
void Notification1::notification_modifierCommande(){
    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;

   // notifyIcon->setIcon(QIcon(":/new/prefix1/MyResources/computer-icons-avatar-user-login-avatar.jpg"));
    notifyIcon->show();
    notifyIcon->showMessage("Gestion des Commandes ","Une Commande est modifiée",QSystemTrayIcon::Information,15000);

}
void Notification1::notification_modifierFournisseur(){
    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;

   // notifyIcon->setIcon(QIcon(":/new/prefix1/MyResources/computer-icons-avatar-user-login-avatar.jpg"));
    notifyIcon->show();
    notifyIcon->showMessage("Gestion des Fournisseurs ","Un Fournisseur est modifié",QSystemTrayIcon::Information,15000);

}
 /*
void Notification::mail_Publicite(){
    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;

   // notifyIcon->setIcon(QIcon(":/new/prefix1/MyResources/computer-icons-avatar-user-login-avatar.jpg"));
    notifyIcon->show();
    notifyIcon->showMessage("","Votre Mail est envoyé :)",QSystemTrayIcon::Information,15000);

} */



