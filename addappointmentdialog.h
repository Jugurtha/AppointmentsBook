#ifndef ADDAPPOINTMENTDIALOG_H
#define ADDAPPOINTMENTDIALOG_H

#include <QDialog>
#include <QSqlQueryModel>
#include <QDate>
#include <QTime>
#include <QString>
#include <selectpatientdialog.h>

namespace Ui {
class AddAppointmentDialog;
}

class AddAppointmentDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddAppointmentDialog(QSqlQueryModel* patientsModel, QWidget *parent = 0);
    QDate getDate();
    QTime getTime();
    QString getObject();
    qint32 getIdPatient();
    bool isValide();
    ~AddAppointmentDialog();

private slots:
    void on_selectPatientButton_clicked();

private:
    Ui::AddAppointmentDialog *ui;
    qint32 idPatient;
    QSqlQueryModel* patientsModel;
};

#endif // ADDAPPOINTMENTDIALOG_H
