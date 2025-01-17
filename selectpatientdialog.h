#ifndef SELECTPATIENTDIALOG_H
#define SELECTPATIENTDIALOG_H

#include <QDialog>
#include <QSqlQueryModel>

namespace Ui {
class SelectPatientDialog;
}

class SelectPatientDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SelectPatientDialog(QSqlQueryModel *model, QWidget *parent = 0);
    ~SelectPatientDialog();
    qint32 getSelectedPatient();
    qint32 getSelectedRow();
private:
    Ui::SelectPatientDialog *ui;
};

#endif // SELECTPATIENTDIALOG_H
