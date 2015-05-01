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
    QRegExp re("\\d*");  // a digit (\d), zero or more times (*)
    if(ui->client_fname_line->text().isEmpty() || ui->client_lname_line->text().isEmpty()
            || ui->client_email_line->text().isEmpty() || ui->client_phone_line->text().isEmpty()
            || ui->recipient_fname_line->text().isEmpty() || ui->recipient_lname_line->text().isEmpty()
            || ui->recipient_email_line->text().isEmpty() || ui->recipient_phone_line->text().isEmpty()
            || ui->package_weight_line->text().isEmpty() || !re.exactMatch(ui->client_phone_line->text())
            || !re.exactMatch(ui->recipient_phone_line->text())) {
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
        Client client;
        Client recipient;
        Route route;

        recipient.setFirstName(ui->recipient_fname_line->text());
        recipient.setLastName(ui->recipient_lname_line->text());
        recipient.setPhone(ui->recipient_phone_line->text());
        recipient.setEmail(ui->recipient_email_line->text());

        client.setFirstName(ui->client_fname_line->text());
        client.setLastName(ui->client_lname_line->text());
        client.setPhone(ui->client_phone_line->text());
        client.setEmail(ui->client_email_line->text());

        client.getPackage().setCode(23321);
        client.getPackage().setPackageName("peste");
        client.getPackage().setPrice(333);
        client.getPackage().setStatus(StatusType::inTransit);
        client.getPackage().setType(PkgType::fragile);

        route.setSource("Timisoara");
        route.setDestination(ui->client_destination_combo->currentText());
        route.setDistance(20);

        confirmation_ui->setData(client, recipient, route);

        confirmation_ui->show();
    }
}
