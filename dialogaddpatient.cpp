#include "dialogaddpatient.h"
#include "ui_dialogaddpatient.h"

DialogAddPatient::DialogAddPatient(QWidget *parent, QString familyNam, QString firstName, QString adress, QString phoneNumber, QString email, QString medicalInfo) :
    QDialog(parent),
    ui(new Ui::DialogAddPatient)
{
    ui->setupUi(this);
    ui->familyNameLineEdit->setText(familyNam);
    ui->FirstNameLineEdit->setText(firstName);
    ui->adressLineEdit->setText(adress);
    ui->phoneNumberLineEdit->setText(phoneNumber);
    ui->phoneNumberLineEdit->setInputMask("999999999999999");
    ui->emailLineEdit->setText(email);
    ui->medicalInfoTextEdit->setText(medicalInfo);
}

DialogAddPatient::~DialogAddPatient()
{
    delete ui;
}

QString DialogAddPatient::getFamilyName()
{
    return ui->familyNameLineEdit->text();
}

QString DialogAddPatient::getFirstName()
{
    return ui->FirstNameLineEdit->text();
}

QString DialogAddPatient::getAdress()
{
    return ui->adressLineEdit->text();
}

QString DialogAddPatient::getPhoneNumber()
{
    return ui->phoneNumberLineEdit->text();
}

QString DialogAddPatient::getEmail()
{
    return ui->emailLineEdit->text();
}

QString DialogAddPatient::getMedicalInfo()
{
    return ui->medicalInfoTextEdit->toPlainText();
}

bool DialogAddPatient::validEntry()
{
    return !getFamilyName().isEmpty() && !getFirstName().isEmpty() && !getAdress().isEmpty() && !getPhoneNumber().isEmpty() && !getEmail().isEmpty() && !getMedicalInfo().isEmpty();
}
