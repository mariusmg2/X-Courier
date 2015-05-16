#include "confirmationwindow.h"
#include "ui_confirmationwindow.h"

/**
 * @brief ConfirmationWindow::ConfirmationWindow Class constructor, will initialize all data members
 *        OBS: client, recipient, and route will all be default-constructed (they all have one default
 *        constructor).
 */

ConfirmationWindow::ConfirmationWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(QSharedPointer<Ui::ConfirmationWindow>(new Ui::ConfirmationWindow)),
    database(QSharedPointer<CourierDatabase>(new CourierDatabase("QSQLITE", "database.sqlite3", "Confirmation window connection"))),
    client(),
    recipient(),
    route()
{
    ui->setupUi(this);
    connect(ui->denyButton, SIGNAL(clicked(bool)), this, SLOT(close()));
    connect(ui->acceptButton, SIGNAL(clicked(bool)), this, SLOT(insertDataInDB()));
    connect(ui->acceptButton, SIGNAL(clicked(bool)), this, SLOT(close()));
    connect(ui->generate, SIGNAL(clicked(bool)), this, SLOT(generateInvoice()));
    connect(ui->generate, SIGNAL(clicked(bool)), this, SLOT(disableGenerateInvoiceButton()));
}

ConfirmationWindow::~ConfirmationWindow() {
    qDebug().nospace() << "~ConfirmationWindow()";
    //ui.clear();
}

/**
 * @brief ConfirmationWindow::setData Method used to store information from MainWindow class in
 *        ConfirmationWindow class, there are actually 3 members that will recive values.
 * @param client_p - Will store data about one client.
 * @param recipient_p - Will store data about the recipient.
 * @param route_p - Data about route.
 */

void ConfirmationWindow::setData(const Client& client_p, const Client& recipient_p, const Route& route_p) {
    client = client_p;
    recipient = recipient_p;
    route = route_p;

    // Print data in window.
    this->printDataToWindow();
}

/**
 * @brief ConfirmationWindow::printDataToWindow Method used to print information from ConfirmationWindow
 *        class data members, to the user-interface window.
 */

void ConfirmationWindow::printDataToWindow() const {
    ui->fname->setText(client.getFirstName());
    ui->lname->setText(client.getLastName());
    ui->email->setText(client.getEmail());
    ui->phone->setText(client.getPhone());

    ui->weight->setText(QString::number(client.getPackage().getWeight()));
    ui->type->setText(client.getPackage().getType());
    ui->destination->setText(route.getDestination());
    ui->arrivetime->setText(QDate::currentDate().addDays(route.getTransitTime()).toString("dd.MMM.yyyy"));

    ui->code->setText(QString::number(client.getPackage().getCode()));
    ui->date->setText(QDate::currentDate().addDays(route.getTransitTime()).toString());
    ui->price->setText(QString::number(route.getTotalPriceWithPackage(client.getPackage())));

    ui->status->clear();
    ui->generate->setEnabled(1);
}

/**
 * @brief ConfirmationWindow::insertDataInDB Method used for inserting one shipping into database.
 *        This is done by using the **database** member variable (calling insertShippingIntoDatabase()
 *        from CourierDatabase class).
 */

void ConfirmationWindow::insertDataInDB() const {
    bool temp = false;

    if(ui->yes->isChecked()) {
        temp = true; // If is true it means that the package sender will pay. Otherwise, the recipient will pay.
    }

    bool ok = database->insertShippingIntoDatabase(client, recipient, route, temp);

    ui->status->setText(ok ? "  Succesfully added in DB! Exiting..." : "  There was an error :(. Exiting... ");
    qApp->processEvents(); // This is for updating the QLabel imediatlly after setText() method.
    QThread::sleep(2);

    qDebug() << (ok ? "insertDataInDB(): Successfully inserted into DB!" : "insertDataInDB(): Failed inserting into DB :(");
}

void ConfirmationWindow::generateInvoice() const {
    auto aux = client;
    auto aux2 = client.getPackage(); // TODO: setter and getters methods (setName(), setPackage(), setWhatewer()) should return refferences to the new modifyed objects, and not an copy of that value.
    aux2.setPrice(0);

    aux.setPackage(aux2);

    if(ui->yes->isChecked()) {
        Invoice::generateInvoice(aux, recipient, route);
    }
    else {
        Invoice::generateInvoice(client, recipient, route);
    }

    ui->status->setText("  Successfully generated!");
}

void ConfirmationWindow::disableGenerateInvoiceButton() const {
    ui->generate->setDisabled(1);
}
