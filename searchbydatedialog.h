#ifndef SEARCHBYDATEDIALOG_H
#define SEARCHBYDATEDIALOG_H

#include <QDialog>
#include <QDate>

namespace Ui {
class SearchByDateDialog;
}

class SearchByDateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SearchByDateDialog(QWidget *parent = 0);
    ~SearchByDateDialog();
    QDate getDate();

private:
    Ui::SearchByDateDialog *ui;
};

#endif // SEARCHBYDATEDIALOG_H
