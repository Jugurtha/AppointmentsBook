#include "searchpatientdialog.h"
#include "ui_searchpatientdialog.h"

SearchPatientDialog::SearchPatientDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SearchPatientDialog)
{
    ui->setupUi(this);
    setWindowTitle("Search For Patient");
}

SearchPatientDialog::~SearchPatientDialog()
{
    delete ui;
}

QString SearchPatientDialog::getFirstName()
{
    return ui->lineEditFirstName->text();
}

QString SearchPatientDialog::getFamilyName()
{
    return ui->lineEditFamilyName->text();
}
