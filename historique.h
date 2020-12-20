#ifndef HISTORIQUE_H
#define HISTORIQUE_H
#include <QMainWindow>
#include <iostream>
#include <QString>
#include <QObject>
#include <QFile>
#include <QDebug>
#include <QTextStream>
#include <QTimer>
#include <QDateTime>
class historique
{
public:
    historique();
    void write(QString);
    QString read();
    void write1(QString);
    QString read1();
private:
    QString mFilename;
  QString mFilename1;
};

#endif // HISTORIQUE_H
