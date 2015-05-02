#include "mainwindow.h"
#include "packagestatuswindow.h"
#include "ui_mainwindow.h"
#include "client.h"
#include "statustype.h"
#include "pkgtype.h"
#include "route.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(QSharedPointer<Ui::MainWindow>(new Ui::MainWindow)),
    database(QSharedPointer<CourierDatabase>(new CourierDatabase))
{
    ui->setupUi(this);
    connect(ui->quit, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->status, SIGNAL(clicked()), this, SLOT(on_status_clicked()));
    connect(ui->send, SIGNAL(clicked()), this, SLOT(on_send_clicked()));

    for(auto i : {"Fast", "Medium", "Slow"}) {
        ui->transportComboBox->addItem(i);
    }

    for(auto i : {"Fragile", "Precious", "Dangerous"}) {
        ui->typeComboBox->addItem(i);
    }

    QVector<QString> temp = database->getAllDestinations();

    for(auto i : temp) {
        ui->client_destination_combo->addItem(i);
    }
}

MainWindow::~MainWindow() {
    qDebug().nospace() << "~MainWindow()";
    //ui.clear();
}

bool MainWindow::allDataValid() const {
    QRegExp phoneREX("\\d*");  // a digit (\d), zero or more times (*)
    QRegExp mailREX("\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}\\b");
    mailREX.setCaseSensitivity(Qt::CaseInsensitive);
    mailREX.setPatternSyntax(QRegExp::RegExp);
    if(ui->client_fname_line->text().isEmpty() || ui->client_lname_line->text().isEmpty()
            || ui->client_email_line->text().isEmpty() || ui->client_phone_line->text().isEmpty()
            || ui->recipient_fname_line->text().isEmpty() || ui->recipient_lname_line->text().isEmpty()
            || ui->recipient_email_line->text().isEmpty() || ui->recipient_phone_line->text().isEmpty()
            || ui->package_weight_line->text().isEmpty() || !phoneREX.exactMatch(ui->client_phone_line->text())
            || !phoneREX.exactMatch(ui->recipient_phone_line->text()) || ui->recipient_phone_line->text().count() < 8
            || ui->client_phone_line->text().count() < 8 || !mailREX.exactMatch(ui->client_email_line->text())
            || !mailREX.exactMatch(ui->recipient_email_line->text()) || ui->package_name_line->text().isEmpty()
            || !phoneREX.exactMatch(ui->package_weight_line->text())) {
        return false;
    }
    return true;
}

void MainWindow::on_status_clicked() {
    if(!status_ui) {
        status_ui = QSharedPointer<PackageStatusWindow>(new PackageStatusWindow);
    }
    status_ui->show();
}

void MainWindow::on_send_clicked() {
    if(!confirmation_ui && this->allDataValid()) {
        confirmation_ui = QSharedPointer<ConfirmationWindow>(new ConfirmationWindow);
    }
    if(this->allDataValid()) {
        Client client(ui->client_fname_line->text(), ui->client_lname_line->text(),
                      ui->client_phone_line->text(), ui->client_email_line->text());

        Client recipient(ui->recipient_fname_line->text(), ui->recipient_lname_line->text(),
                         ui->recipient_phone_line->text(), ui->recipient_email_line->text());

        Route route("Timisoara", ui->client_destination_combo->currentText(),
                    database->getShortestRouteDistance("Timisoara", ui->client_destination_combo->currentText()));

        Package package(ui->package_weight_line->text().toUInt(), database->getUniqueShippingID(),
                        10, StatusType::inTransit, ui->package_name_line->text(),
                        PkgType::precious); //TODO Get package type from UI.

        client.setPackage(package);
        confirmation_ui->setData(client, recipient, route);

        confirmation_ui->show();
    }
}
