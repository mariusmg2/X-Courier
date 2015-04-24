#include "packagestatuswindow.h"
#include "ui_packagestatuswindow.h"

PackageStatusWindow::PackageStatusWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(QSharedPointer<Ui::PackageStatusWindow>(new Ui::PackageStatusWindow)),
    status_ui(QSharedPointer<StatusInfoWindow>(new StatusInfoWindow))
{
    ui->setupUi(this);
    connect(ui->quitButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->recipientCode, SIGNAL(textChanged(QString)), this, SLOT(recipientCodeTextChanged()));
    connect(ui->recipientName, SIGNAL(textChanged(QString)), this, SLOT(recipientNameTextChanged()));
    connect(ui->checkButton, SIGNAL(clicked()), this, SLOT(check_clicked()));
    connect(this, SIGNAL(buttonCheckClicked(const QString&)), status_ui.data(), SLOT(newDataEntered(const QString&)));
}

PackageStatusWindow::~PackageStatusWindow() {
    qDebug().nospace() << "~PackageStatusWindow()";
    //ui.clear();
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

void PackageStatusWindow::check_clicked() {
    if(!ui->recipientCode->text().isEmpty() || !ui->recipientName->text().isEmpty()) { // We don't work for void clients :))
        if(!ui->recipientName->text().isEmpty()) {
           emit buttonCheckClicked(ui->recipientName->text());
        }
        else {
           emit buttonCheckClicked(ui->recipientCode->text());
        }

        status_ui->show();
    }
}
