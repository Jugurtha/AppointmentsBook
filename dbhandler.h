#ifndef DBHANDLER_H
#define DBHANDLER_H
#include <QString>
#include <QSqlDatabase>
#include <QDebug>
#include <QSQl>
#include <QApplication>
#include <QSqlError>
#include <QSqlQuery>
#include <QString>
#include <QTime>
#include <QSqlQueryModel>

const QString DRIVER("QSQLITE");

class DBHandler
{
public:
    DBHandler(QObject *parent, QString filePath);
    bool addPatient(QString nom, QString prenom, QString adresse,QString telephone, QString mail,QString information);
    QSqlQueryModel* getPatients(QString nom, QString prenom);
    QSqlQueryModel* getPatients();
    bool modifyPatient(qint32 id, QString nom, QString prenom, QString adresse,QString telephone, QString mail,QString information);
    bool addAppointment(qint32 patient, QDate date, QTime heure, QString objet);
    QSqlQueryModel* getAppointments(QDate date);
    QSqlQueryModel* getAppointments(qint32 patient);
    bool modifyAppointment(qint32 id, QDate date, QTime heure = QTime()/*QTime::isNull()*/, QString objet = "");
    bool deleteAppointment(qint32 id);
private :
    QObject *parent;
    QSqlDatabase db;
};

#endif // DBHANDLER_H
