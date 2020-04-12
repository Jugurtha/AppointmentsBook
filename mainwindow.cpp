#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    dbhandler(parent, "./local")
{
    ui->setupUi(this);
    ui->mainToolBar->setIconSize(QSize(32,32));

    for(int i = 0; i< NBR_ACTIONS ; i++)
        action[i] = ui->mainToolBar->addAction(QIcon(QString("../icons/") + icon[i] + ".png"), actionName[i]);

    date_selector = new QDateEdit(QDate::currentDate());
    ui->mainToolBar->addSeparator();
    ui->mainToolBar->addWidget(date_selector);

    dbhandler.addPatient("CHAKER", "Jugurtha", "24 Amara 2 Cheraga, ALger", "666222772", "ej_chaker@esi.dz", "blablalbal...");
    ui->dayAppointmentsView->setModel(dbhandler.getPatients("CHAKER", "Jugurtha"));
    ui->dayAppointmentsView->show();

}

MainWindow::~MainWindow()
{
    delete ui;
}
