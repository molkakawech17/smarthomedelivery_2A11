#include "mail.h"
#include "ui_mail.h"
#include <src/SmtpMime>

Mail::Mail(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Mail)
{
    ui->setupUi(this);
}

Mail::~Mail()
{
    delete ui;
}

void Mail::on_pushButton_clicked()
{
    SmtpClient smtp("smtp.gmail.com", 465, SmtpClient::SslConnection);
       smtp.setUser("eya.souissi@esprit.tn");
       smtp.setPassword("eyaeyaeya");
       MimeMessage message;
       message.setSender(new EmailAddress("eya.souissi@esprit.tn", "Eya"));
       message.addRecipient(new EmailAddress(ui->lineEdit->text(), "Recipient's Name"));
       message.setSubject(ui->lineEdit_2->text());
       MimeText text;
       text.setText(ui->label_3->text());
       message.addPart(&text);
       smtp.connectToHost();
       smtp.login();
       smtp.sendMail(message);
       smtp.quit();
}
