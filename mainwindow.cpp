#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    dbhandler(parent, "./local")
{
    ui->setupUi(this);
    ui->mainToolBar->setIconSize(QSize(32,32));

    for(int i = 0; i< NBR_ACTIONS ; i++)
        action[i] = ui->mainToolBar->addAction(QIcon(QString("../icons/") + icon[i] + ".png"), actionName[i]);


    QMenu* insertMenu = ui->menuBar->addMenu("Insert");
    QMenu* viewMenu = ui->menuBar->addMenu("View");
    QMenu* modifyMenu = ui->menuBar->addMenu("Modify");
    QMenu* printingMenu = ui->menuBar->addMenu("Printing");

    insertMenu->addActions(QList<QAction*>{action[ADD_PATIENT], action[ADD_APPOINTMENT]});
    viewMenu->addActions(QList<QAction*>{action[SEARCH_PATIENT],action[SEARCH_APPOINTMENT_BY_DATE],action[SEARCH_APPOINTMENT_BY_PATIENT]});
    modifyMenu->addActions(QList<QAction*>{action[MODIFY_APPOINTMENT]});
    printingMenu->addActions(QList<QAction*>{action[PRINT]});

    action[MODIFY_APPOINTMENT]->setEnabled(false);
    action[PRINT]->setEnabled(false);

    connect(action[ADD_PATIENT],SIGNAL(triggered(bool)),this, SLOT(on_AddPatient()));
    connect(action[ADD_APPOINTMENT],SIGNAL(triggered(bool)),this, SLOT(on_AddAppointment()));
    connect(action[MODIFY_APPOINTMENT],SIGNAL(triggered(bool)),this, SLOT(on_ModifyAppointment()));
    connect(action[SEARCH_APPOINTMENT_BY_DATE],SIGNAL(triggered(bool)),this, SLOT(on_SearchAppointmentByDate()));
    connect(action[SEARCH_APPOINTMENT_BY_PATIENT],SIGNAL(triggered(bool)),this, SLOT(on_SearchAppointmentByPatient()));
    connect(action[SEARCH_PATIENT],SIGNAL(triggered(bool)),this, SLOT(on_SearchPatient()));
    connect(action[PRINT],SIGNAL(triggered(bool)),this, SLOT(on_Print()));

    date_selector = new QDateEdit(QDate::currentDate());
    ui->mainToolBar->addSeparator();
    ui->mainToolBar->addWidget(date_selector);
    showTodaysAppointments();

    dbhandler.addPatient("CHAKER", "Tinhinane", "24 Amara 2 Cheraga, ALger", "666222772", "ej_chaker@esi.dz", "blablalbal...");
    dbhandler.addAppointment(36,QDate::currentDate(),QTime::currentTime(),"Lorem ipsum");
    //ui->dayAppointmentsView->setModel(dbhandler.getPatients("CHAKER", "Jugurtha"));
    //ui->dayAppointmentsView->show();
    showTodaysAppointments();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showAppointments(QSqlQueryModel *model)
{
    ui->dayAppointmentsView->setModel(model);
}

void MainWindow::showTodaysAppointments()
{
   showAppointments(dbhandler.getAppointments(QDate::currentDate()));
}

void MainWindow::on_AddPatient()
{

}

void MainWindow::on_AddAppointment()
{

}

void MainWindow::on_ModifyAppointment()
{

}

void MainWindow::on_SearchAppointmentByDate()
{
    dbhandler.getAppointments(QDate());//Code this
}

void MainWindow::on_SearchAppointmentByPatient()
{
    SearchPatientDialog searchPatientDialog;
    if(searchPatientDialog.exec() == QDialog::Accepted)
    {
        quint32 idPatient = 0;
        if(searchPatientDialog.getFamilyName().isEmpty() && searchPatientDialog.getFirstName().isEmpty())
            QMessageBox::information(this, "Information","You did not provide a first or last name.");
        else{
            QSqlQueryModel *model = dbhandler.getPatients(searchPatientDialog.getFamilyName(), searchPatientDialog.getFirstName());
            if(model->rowCount()==0)
                QMessageBox::information(this, "Search result", "No patient with this name found.");
            else if (model->rowCount()>1){
                SelectPatientDialog selectPatientDialog(model, this);
                if(selectPatientDialog.exec()==QDialog::Accepted)
                    idPatient = selectPatientDialog.getSelectedPatient();//Show this...
            }
            else//only one
                idPatient = model->data(model->index(0,0)).toInt();
            showAppointments(dbhandler.getAppointments(idPatient));
        }
    }

}

void MainWindow::on_SearchPatient()
{
    SearchPatientDialog searchDialog;
    if(searchDialog.exec() == QDialog::Accepted)
    {
        if(searchDialog.getFamilyName().isEmpty() && searchDialog.getFirstName().isEmpty())
            QMessageBox::information(this, "Information","You did not provide a first or last name.");
        else{
            QSqlQueryModel *model = dbhandler.getPatients(searchDialog.getFamilyName(), searchDialog.getFirstName());
            if(model->rowCount()==0)
                QMessageBox::information(this, "Search result", "No patient with this name found.");
            else if (model->rowCount()==1){
                //Show this...
            }
            else{
                SelectPatientDialog selectPatientDialog(model, this);
                if(selectPatientDialog.exec()==QDialog::Accepted)
                    selectPatientDialog.getSelectedPatient();//Show this...
            }

        }
    }
}

void MainWindow::on_Print()
{

}


