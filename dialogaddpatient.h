#ifndef DIALOGADDPATIENT_H
#define DIALOGADDPATIENT_H

#include <QDialog>
#include <QString>

namespace Ui {
class DialogAddPatient;
}

class DialogAddPatient : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAddPatient(QWidget *parent = 0, QString familyNam = "", QString firstName = "", QString adress = "", QString phoneNumber = "", QString email = "", QString medicalInfo = "");
    ~DialogAddPatient();
    QString getFamilyName();
    QString getFirstName();
    QString getAdress();
    QString getPhoneNumber();
    QString getEmail();
    QString getMedicalInfo();
    bool validEntry();

private:
    Ui::DialogAddPatient *ui;
};

#endif // DIALOGADDPATIENT_H
