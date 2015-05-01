#include "confirmationwindow.h"
#include "ui_confirmationwindow.h"

ConfirmationWindow::ConfirmationWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(QSharedPointer<Ui::ConfirmationWindow>(new Ui::ConfirmationWindow)),
    database(QSharedPointer<CourierDatabase>(new CourierDatabase("QSQLITE", "database.sqlite3", "Confirmation window connection"))),
    client(),
    recipient(),
    route()
{
    ui->setupUi(this);
    connect(ui->denyButton, SIGNAL(clicked()), this, SLOT(close()));
}

ConfirmationWindow::~ConfirmationWindow() {
    qDebug().nospace() << "~ConfirmationWindow()";
    //ui.clear();
}

void ConfirmationWindow::setData(const Client& client_p, const Client& recipient_p, const Route& route_p) {
    client = client_p;
    recipient = recipient_p;
    route = route_p;

    // Print data in window.
    this->printDataToWindow();
}

void ConfirmationWindow::printDataToWindow() const {
    ui->fname->setText(client.getFirstName());
    ui->lname->setText(client.getLastName());
    ui->email->setText(client.getEmail());
    ui->phone->setText(client.getPhone());

    ui->weight->setText(QString::number(client.getPackage().getWeight()));
    ui->type->setText(client.getPackage().getType());
    ui->destination->setText(route.getDestination());

    ui->code->setText(QString::number(client.getPackage().getCode()));
    ui->date->setText(QDate::currentDate().addDays(route.getTransitTime()).toString());
    ui->type_2->setText("UNDEFINED");
    ui->price->setText(QString::number(route.getTotalPrice()));
}
