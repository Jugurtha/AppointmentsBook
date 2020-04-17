#ifndef SEARCHPATIENTDIALOG_H
#define SEARCHPATIENTDIALOG_H

#include <QDialog>
#include <QString>

namespace Ui {
class SearchPatientDialog;
}

class SearchPatientDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SearchPatientDialog(QWidget *parent = 0);
    ~SearchPatientDialog();
    QString getFirstName();
    QString getFamilyName();

private:
    Ui::SearchPatientDialog *ui;
};

#endif // SEARCHPATIENTDIALOG_H
