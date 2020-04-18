#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDateEdit>
#include <QSqlQueryModel>
#include <dbhandler.h>
#include <searchpatientdialog.h>
#include <selectpatientdialog.h>
#include <dialogaddpatient.h>
#include <addappointmentdialog.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    enum {ADD_PATIENT, ADD_APPOINTMENT, MODIFY_APPOINTMENT, SEARCH_APPOINTMENT_BY_DATE, SEARCH_APPOINTMENT_BY_PATIENT, SEARCH_PATIENT, PRINT, NBR_ACTIONS};

    void showAppointments(QSqlQueryModel *model);
    void showTodaysAppointments();

public slots:
    void on_AddPatient();
    void on_AddAppointment();
    void on_ModifyAppointment();
    void on_SearchAppointmentByDate();
    void on_SearchAppointmentByPatient();
    void on_SearchPatient();
    void on_Print();
    void on_dateChanged(QDate date);

private:
    Ui::MainWindow *ui;
    QDateEdit *dateSelector;
    QAction* action[NBR_ACTIONS];
    QStringList icon{"Add patient", "Add appointment", "Modify appointment","Search appointment by date", "Search appointment by patient", "Search patient", "Print"};
    QStringList actionName{"Add patient", "Add appointment", "Modify appointment","Search appointment by date", "Search appointment by patient", "Search patient", "Print"};
    DBHandler dbhandler;
    QSqlQueryModel *currentModel;

    void updateAppointmentsView();

};

#endif // MAINWINDOW_H
