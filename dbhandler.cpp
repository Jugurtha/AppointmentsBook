#include "dbhandler.h"

DBHandler::DBHandler(QObject *parent, QString filePath) : parent(parent)
{

    if(! QSqlDatabase::isDriverAvailable(DRIVER))
    {
        qWarning() << DRIVER << " not available.";
        qApp->quit();
    }
    db = QSqlDatabase::addDatabase(DRIVER);
    db.setDatabaseName(filePath);
    if(!db.open())
        qWarning() << "ERROR: " << db.lastError();

    QSqlQuery query("PRAGMA foreign_keys = ON");
    if(!query.isActive())
        qWarning() << "ERROR: " << query.lastError().text();

    QSqlQuery query_create_patient("CREATE TABLE patient (id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, nom VARCHAR(50), prenom VARCHAR(50), adresse VARCHAR(50), telephone  VARCHAR(15), mail  VARCHAR(50), information_medicale TEXT)");
    if(!query_create_patient.isActive())
        qWarning() << "ERROR: " << query_create_patient.lastError().text();

    QSqlQuery query_create_rdv("CREATE TABLE rdv (id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, id_patient INTEGER NOT NULL, date DATE, heure TIME, objet TEXT, FOREIGN KEY(id_patient) REFERENCES patient(id))");
    if(!query_create_rdv.isActive())
      qWarning() << "ERROR: " << query_create_rdv.lastError().text();

}

bool DBHandler::addPatient(QString nom, QString prenom, QString adresse, QString telephone, QString mail, QString information)
{
    QSqlQuery query;
    query.prepare("INSERT INTO patient (nom, prenom, adresse, telephone, mail, information_medicale) "
                        "VALUES (:nom, :prenom, :adresse, :telephone, :mail, :information_medicale)");
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":adresse", adresse);
    query.bindValue(":telephone", telephone);
    query.bindValue(":mail", mail);
    query.bindValue(":information_medicale", information);

    if(!query.exec())
    {
        qWarning() << "ERROR: " << query.lastError().text();
        qDebug() << "INSERT IN TABLE patient failed";
        return false;
    }

    return true;
}

QSqlQueryModel* DBHandler::getPatients(QString nom, QString prenom)
{
    QSqlQuery query;
    QString str;

    if(!nom.isEmpty() && !prenom.isEmpty())
        str = "SELECT * FROM patient WHERE nom = :nom AND prenom = :prenom";
    else{
        if(!nom.isEmpty() && prenom.isEmpty())
            str = "SELECT * FROM patient WHERE nom = :nom";
        else if(nom.isEmpty() && !prenom.isEmpty())
            str = "SELECT * FROM patient WHERE prenom = :prenom";
    }
    query.prepare(str);

    if(!nom.isEmpty())
        query.bindValue(":nom", nom);
    if(!prenom.isEmpty())
        query.bindValue(":prenom", prenom);
    if(!query.exec())
    {
        qWarning() << "ERROR: " << query.lastError().text();
        qDebug() << "SELECT ON TABLE patient failed";
        return NULL;
    }

    QSqlQueryModel *model = new QSqlQueryModel(parent);
    model->setQuery(query);
    if (model->lastError().isValid())
    {
        qWarning() << "ERROR: " << model->lastError().text();
    }

    return model;
}

QSqlQueryModel *DBHandler::getPatients()
{
    QSqlQuery query("SELECT id, nom, prenom, adresse, telephone, mail FROM patient");
    if(!query.exec())
    {
        qWarning() << "ERROR: " << query.lastError().text();
        qDebug() << "SELECT ON TABLE patient failed";
        return NULL;
    }

    QSqlQueryModel *model = new QSqlQueryModel(parent);
    model->setQuery(query);
    if (model->lastError().isValid())
    {
        qWarning() << "ERROR: " << model->lastError().text();
    }

    return model;
}

bool DBHandler::modifyPatient(qint32 id, QString nom, QString prenom, QString adresse, QString telephone, QString mail, QString information)
{
    QSqlQuery query;
    query.prepare("UPDATE patient SET nom = :nom, prenom = :prenom, adresse = :adresse, telephone = :telephone, mail = :mail, information_medicale = :information_medicale WHERE id = :id");

    query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":adresse", adresse);
    query.bindValue(":telephone", telephone);
    query.bindValue(":mail", mail);
    query.bindValue(":information_medicale", information);

    if(!query.exec())
    {
        qWarning() << "ERROR: " << query.lastError().text();
        qDebug() << "UPDATE ON TABLE patient failed";
        return false;
    }

    return true;
}

bool DBHandler::addAppointment(qint32 patient, QDate date, QTime heure, QString objet)
{
    QSqlQuery query;
    query.prepare("INSERT INTO rdv (id_patient, date, heure, objet) "
                        "VALUES (:id_patient, :date, :heure, :objet)");
    query.bindValue(":id_patient", patient);
    query.bindValue(":date", date);
    query.bindValue(":heure", heure);
    query.bindValue(":objet", objet);

    if(!query.exec())
    {
        qWarning() << "ERROR: " << query.lastError().text();
        qDebug() << "INSERT IN TABLE rdv failed";
        return false;
    }

    return true;
}

QSqlQueryModel* DBHandler::getAppointments(QDate date)
{
    QSqlQuery query;
    query.prepare("SELECT rdv.id, id_patient, nom, prenom, date, heure, objet FROM rdv INNER JOIN patient ON patient.id=id_patient WHERE date = :date");
    query.bindValue(":date", date);
    if(!query.exec())
    {
        qWarning() << "ERROR: " << query.lastError().text();
        qDebug() << "SELECT ON TABLE rdv failed";
        return NULL;
    }

    QSqlQueryModel *model = new QSqlQueryModel(parent);
    model->setQuery(query);
    if (model->lastError().isValid())
    {
        qWarning() << "ERROR: " << model->lastError().text();
    }

    return model;
}

QSqlQueryModel *DBHandler::getAppointments(qint32 patient)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM rdv WHERE id_patient = :id_patient");
    query.bindValue(":id_patient", patient);
    if(!query.exec())
    {
        qWarning() << "ERROR: " << query.lastError().text();
        qDebug() << "SELECT ON TABLE rdv failed";
        return NULL;
    }

    QSqlQueryModel *model = new QSqlQueryModel(parent);
    model->setQuery(query);
    if (model->lastError().isValid())
    {
        qWarning() << "ERROR: " << model->lastError().text();
    }

    return model;
}

bool DBHandler::modifyAppointment(qint32 id, QDate date, QTime heure, QString objet)
{
    QSqlQuery query;
    query.prepare("UPDATE rdv SET date = :date, heure = :heure, objet = :objet WHERE id = :id");

    query.bindValue(":id", id);
    query.bindValue(":date", date);
    query.bindValue(":heure", heure);
    query.bindValue(":objet", objet);

    if(!query.exec())
    {
        qWarning() << "ERROR: " << query.lastError().text();
        qDebug() << "UPDATE ON TABLE rdv failed";
        return false;
    }

    return true;
}

bool DBHandler::deleteAppointment(qint32 id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM rdv WHERE id = :id");

    query.bindValue(":id", id);

    if(!query.exec())
    {
        qWarning() << "ERROR: " << query.lastError().text();
        qDebug() << "UPDATE ON TABLE rdv failed";
        return false;
    }

    return true;
}






