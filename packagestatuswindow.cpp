#include "packagestatuswindow.h"
#include "ui_packagestatuswindow.h"

PackageStatusWindow::PackageStatusWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PackageStatusWindow)
{
    ui->setupUi(this);
    connect(ui->quitButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->recipientCode, SIGNAL(textChanged(QString)), this, SLOT(recipientCodeTextChanged()));
    connect(ui->recipientName, SIGNAL(textChanged(QString)), this, SLOT(recipientNameTextChanged()));
}

PackageStatusWindow::~PackageStatusWindow()
{
    delete ui;
}

void PackageStatusWindow::recipientCodeTextChanged() {
    if(ui->recipientName->text().isEmpty() && !ui->recipientCode->text().isEmpty()) {
        ui->recipientName->setDisabled(true);
    }
    else {
        ui->recipientName->setEnabled(true);
    }
}

void PackageStatusWindow::recipientNameTextChanged() {
    if(ui->recipientCode->text().isEmpty() && !ui->recipientName->text().isEmpty()) {
        ui->recipientCode->setDisabled(true);
    }
    else {
        ui->recipientCode->setEnabled(true);
    }
}
