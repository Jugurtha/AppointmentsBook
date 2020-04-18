#include "addappointmentdialog.h"
#include "ui_addappointmentdialog.h"

AddAppointmentDialog::AddAppointmentDialog(QSqlQueryModel *patientsModel, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddAppointmentDialog),
    idPatient(-1),
    patientsModel(patientsModel)
{
    ui->setupUi(this);
}

QDate AddAppointmentDialog::getDate()
{
    return ui->date->date();
}

QTime AddAppointmentDialog::getTime()
{
    return ui->time->time();
}

QString AddAppointmentDialog::getObject()
{
    return ui->ObjectTextEdit->toPlainText();
}

qint32 AddAppointmentDialog::getIdPatient()
{
    return idPatient;
}

bool AddAppointmentDialog::isValide()
{
    return idPatient!=-1 && getDate().isValid() && getTime().isValid() && !getObject().isEmpty();
}

AddAppointmentDialog::~AddAppointmentDialog()
{
    delete ui;
}

void AddAppointmentDialog::on_selectPatientButton_clicked()
{
    SelectPatientDialog selectPatient(patientsModel,this);
    if(selectPatient.exec()==QDialog::Accepted)
    {
        idPatient = selectPatient.getSelectedPatient();
        ui->selectPatientButton->setText("Id Pateint : " + QString::number(idPatient));
    }
    else
        idPatient = -1;
}
