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


    //QMenu* fileMenu = ui->menuBar->addMenu("FIle");
    QMenu* insertMenu = ui->menuBar->addMenu("Insert");
    QMenu* viewMenu = ui->menuBar->addMenu("View");
    QMenu* modifyMenu = ui->menuBar->addMenu("Modify");
    QMenu* printingMenu = ui->menuBar->addMenu("Printing");

    insertMenu->addActions(QList<QAction*>{action[ADD_PATIENT], action[ADD_APPOINTMENT]});
    viewMenu->addActions(QList<QAction*>{action[SEARCH_PATIENT],action[SEARCH_APPOINTMENT_BY_DATE],action[SEARCH_APPOINTMENT_BY_PATIENT]});
    modifyMenu->addActions(QList<QAction*>{action[MODIFY_APPOINTMENT]});
    printingMenu->addActions(QList<QAction*>{action[PRINT]});


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
