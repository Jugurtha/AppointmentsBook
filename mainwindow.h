#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDateEdit>
#include <dbhandler.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    enum {ADD_PATIENT, ADD_APPOINTMENT, MODIFY_APPOINTMENT, SEARCH_PATIENT, PRINT, NBR_ACTIONS};

private:
    Ui::MainWindow *ui;
    QDateEdit *date_selector;
    QAction* action[NBR_ACTIONS];
    QStringList icon{"Add patient", "Add appointment", "Modify appointment", "Search patient", "Print"};
    QStringList actionName{"Add patient", "Add appointment", "Modify appointment", "Search patient", "Print"};
    DBHandler dbhandler;

};

#endif // MAINWINDOW_H
