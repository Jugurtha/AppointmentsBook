#include "searchbydatedialog.h"
#include "ui_searchbydatedialog.h"

SearchByDateDialog::SearchByDateDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SearchByDateDialog)
{
    ui->setupUi(this);
}

SearchByDateDialog::~SearchByDateDialog()
{
    delete ui;
}

QDate SearchByDateDialog::getDate()
{
    return ui->dateEdit->date();
}
