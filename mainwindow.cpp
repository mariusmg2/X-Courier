#include "mainwindow.h"
#include "packagestatuswindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(QSharedPointer<Ui::MainWindow>(new Ui::MainWindow))
{
    ui->setupUi(this);
    connect(ui->quit, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->status, SIGNAL(clicked()), this, SLOT(on_status_clicked()));
    connect(ui->send, SIGNAL(clicked()), this, SLOT(on_send_clicked()));
}

MainWindow::~MainWindow()
{
    ui.clear();
}

void MainWindow::on_status_clicked()
{
    status_ui = QSharedPointer<PackageStatusWindow>(new PackageStatusWindow);
    status_ui->show();
}

void MainWindow::on_send_clicked()
{
    confirmation_ui = QSharedPointer<ConfirmationWindow>(new ConfirmationWindow);
    confirmation_ui->show();
}
