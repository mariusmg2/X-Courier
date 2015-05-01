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

void ConfirmationWindow::setData(const Client &client_p, const Client &recipient_p, const Route &route_p) {
    client.setFirstName(client_p.getFirstName()); // TODO: Overload operator= for Client objects...
    client.setLastName(client_p.getLastName());
    client.setEmail(client_p.getEmail());
    client.setPhone(client_p.getPhone());
    client.setGender(client_p.getGender());
    client.getPackage().setCode(client_p.getPackage().getCode());
    client.getPackage().setPackageName(client_p.getPackage().getPackageName());
    client.getPackage().setPrice(client_p.getPackage().getPrice());
    //client.getPackage().setStatus(client_p.getPackage().getStatus());
    //client.getPackage().setType(client_p.getPackage().getType());
    client.getPackage().setWeight(client_p.getPackage().getWeight());

    recipient.setFirstName(recipient_p.getFirstName()); // TODO: Overload operator= for Client objects...
    recipient.setLastName(recipient_p.getLastName());
    recipient.setEmail(recipient_p.getEmail());
    recipient.setPhone(recipient_p.getPhone());
    recipient.setGender(recipient_p.getGender());

    route.setSource(route_p.getDestination());
    route.setDestination(route_p.getDestination());
    route.setDistance(route_p.getDistance());

    // Print data in window.
    ui->fname->setText(client.getFirstName());
    ui->lname->setText(client.getLastName());
    ui->email->setText(client.getEmail());
    ui->phone->setText(client.getPhone());

    ui->weight->setText(QString::number(client.getPackage().getWeight()));
    ui->type->setText(client.getPackage().getType());

    ui->code->setText(QString::number(client.getPackage().getCode()));
    //ui->code->setText(client.getPackage().getWeight());

}
