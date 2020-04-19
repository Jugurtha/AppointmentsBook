#include "selectpatientdialog.h"
#include "ui_selectpatientdialog.h"
#include <QDebug>

SelectPatientDialog::SelectPatientDialog(QSqlQueryModel *model, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectPatientDialog)
{
    ui->setupUi(this);
    setWindowTitle("Select Patient");
    ui->tableView->setModel(model);
    ui->tableView->selectRow(0);
}

SelectPatientDialog::~SelectPatientDialog()
{
    delete ui;
}

qint32 SelectPatientDialog::getSelectedPatient()
{
    if(ui->tableView->selectionModel()->hasSelection())
        return ui->tableView->model()->data(ui->tableView->selectionModel()->selectedRows().at(0)).toInt();

    return -1;
}

qint32 SelectPatientDialog::getSelectedRow()
{
    if(ui->tableView->selectionModel()->hasSelection())
        return ui->tableView->selectionModel()->currentIndex().row();

    return -1;
}

