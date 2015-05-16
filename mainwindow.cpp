#include "mainwindow.h"
#include "packagestatuswindow.h"
#include "ui_mainwindow.h"
#include "client.h"
#include "statustype.h"
#include "pkgtype.h"
#include "route.h"
#include "transtype.h"

/**
 * @brief MainWindow::MainWindow Constructor, will initialize all MainWindow objects.
 *        Initialization consists in: setting member objects with default values (ui, database),
 *        connecting all buttons (with specific signals) to specific
 *        slots (methods), and filling all comboBoxes with specific data.
 */

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(QSharedPointer<Ui::MainWindow>(new Ui::MainWindow)),
    database(QSharedPointer<CourierDatabase>(new CourierDatabase))
{
    ui->setupUi(this);
    connect(ui->quit, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->status, SIGNAL(clicked()), this, SLOT(on_status_clicked()), Qt::UniqueConnection);
    connect(ui->send, SIGNAL(clicked(bool)), this, SLOT(on_send_clicked()), Qt::UniqueConnection);
    connect(ui->actionAdd_route, SIGNAL(triggered(bool)), this, SLOT(onAddRouteClicked()));

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

    ui->status_2->setText("Welcome to X-Courier!");

    ui->client_fname_line->setPlaceholderText("e.g. Brian");
    ui->client_lname_line->setPlaceholderText("e.g. Griffin");
    ui->client_email_line->setPlaceholderText("e.g. brian.grf@php.net");
    ui->client_phone_line->setPlaceholderText("e.g. 0213199054");
    ui->recipient_fname_line->setPlaceholderText("e.g. Amanda");
    ui->recipient_lname_line->setPlaceholderText("e.g. Seyfried");
    ui->recipient_email_line->setPlaceholderText("e.g. amanda@frnet.com");
    ui->recipient_phone_line->setPlaceholderText("e.g. 0355009777");
    ui->package_name_line->setPlaceholderText("e.g. guns");
    ui->package_value_line->setPlaceholderText("e.g. 128");
    ui->package_weight_line->setPlaceholderText("e.g. 211");
}

MainWindow::~MainWindow() {
    qDebug().nospace() << "~MainWindow()";
    //ui.clear();
}

/**
 * @brief MainWindow::allDataValid Method that checks if all input data is valid data (eg. email
 *       fields contain at least one '@' and '.' character, phone numbers are only digits, etc).
 * @return Will return true if all data is valid, and it can be safetly added into database.
 *         Otherwisw, false will be returned.
 */

bool MainWindow::allDataValid() const {
    QRegExp digitRegExp("\\d");
    QRegExp mailRegExp("\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}\\b");
    QRegExp phoneRegExp("^[0-9]{8,12}$");
    QRegExp valueRegExp("^[0-9]{1,5}$");

    mailRegExp.setCaseSensitivity(Qt::CaseInsensitive);
    mailRegExp.setPatternSyntax(QRegExp::RegExp);

    QString clientFirstName = ui->client_fname_line->text();
    QString clientLastName = ui->client_lname_line->text();
    QString clientEmail = ui->client_email_line->text();
    QString clientPhone = ui->client_phone_line->text();

    QString recipientFirstName = ui->recipient_fname_line->text();
    QString recipientLastName = ui->recipient_lname_line->text();
    QString recipientEmail = ui->recipient_email_line->text();
    QString recipientPhone = ui->recipient_phone_line->text();

    QString packageName = ui->package_name_line->text();

    QVector<QString> names;
    QVector<QString> emails;
    QVector<QString> phones;

    names.push_back(clientFirstName);
    names.push_back(clientLastName);
    names.push_back(recipientFirstName);
    names.push_back(recipientLastName);

    emails.push_back(clientEmail);
    emails.push_back(recipientEmail);

    phones.push_back(clientPhone);
    phones.push_back(recipientPhone);

    // Validating names.
    for(auto i : names) {
        if(i.isEmpty()) {
            ui->status_2->setText("Sorry, names can't be empty!");
            return false;
        }
    }

    for(auto i : names) {
        if(i.count() < 3) {
            ui->status_2->setText("One of names is too short!");
            return false;
        }
    }

    for(auto i : names) {
        if(i.count() > 20) {
            ui->status_2->setText("One of names is too long!");
            return false;
        }
    }

    for(auto i : names) {
        if(i.contains(digitRegExp)) {
            ui->status_2->setText("Names can't contain digits, m8!");
            return false;
        }
    }

    // Validating emails.
    for(auto i : emails) {
        if(i.isEmpty()) {
            ui->status_2->setText("Sorry, emails can't be empty!");
        }
    }

    for(auto i : emails) {
        if(i.count() < 8) {
            ui->status_2->setText("One of emails is too short!");
            return false;
        }
    }

    for(auto i : emails) {
        if(i.count() > 50) {
            ui->status_2->setText("Hmm, one of emails is too way long!");
            return false;
        }
    }

    for(auto i : emails) {
        if(!mailRegExp.exactMatch(i)) {
            ui->status_2->setText("One of emails is not an email...");
            return false;
        }
    }

    // Validating phone numbers.
    for(auto i : phones) {
        if(i.isEmpty()) {
            ui->status_2->setText("Sorry, number phones can't be empty!");
            return false;
        }
    }

    for(auto i : phones) {
        if(i.count() < 8) {
            ui->status_2->setText("One of number phone is too short!");
            return false;
        }
    }

    for(auto i : phones) {
        if(i.count() > 12) {
            ui->status_2->setText("One of number phone is too long!");
            return false;
        }
    }

    for(auto i : phones) {
        if(!phoneRegExp.exactMatch(i)) {
            ui->status_2->setText("Hmm, that's not a number! only digits.");
            return false;
        }
    }

    // Validating package details:
    if(packageName.isEmpty()) {
        ui->status_2->setText("Package name can't be empty...");
        return false;
    }

    if(packageName.count() < 3) {
        ui->status_2->setText("Package name is too short!");
        return false;
    }

    if(packageName.count() > 30) {
        ui->status_2->setText("Package name is too long!");
        return false;
    }

    if(ui->package_value_line->text().isEmpty()) {
        ui->status_2->setText("Sorry, package value can't be empty!");
        return false;
    }

    if(!valueRegExp.exactMatch(ui->package_value_line->text())) {
        ui->status_2->setText("Package value can be only digits!");
        return false;
    }

    if(ui->package_weight_line->text().isEmpty()) {
        ui->status_2->setText("Sorry, package weight can't be empty!");
        return false;
    }

    if(!valueRegExp.exactMatch(ui->package_weight_line->text())) {
        ui->status_2->setText("Package weight can be only digits!");
        return false;
    }

    auto distance = database->getShortestRouteDistance("Timisoara", ui->client_destination_combo->currentText());

    if(distance == -1) {
        ui->status_2->setText("Sorry, no such route :(");
        return false;
    }

    return true;
}

/**
 * @brief MainWindow::on_status_clicked Method that will be called when the 'status' button will
 *        be clicked, then it will call show() method on **status_ui** window.
 */

void MainWindow::on_status_clicked() {
    if(!status_ui) {
        status_ui = QSharedPointer<PackageStatusWindow>(new PackageStatusWindow);
    }
    status_ui->show();
}

/**
 * @brief MainWindow::on_send_clicked Method that will be called when 'send' button will be clicked.
 *        If all data is valid (from MainWindow QLines), then it will retrive all info from them,
 *        and store it into specific objects. After all of this, it will send all this new objects
 *        to a confirmation window (using setData() method from that class).
 */

void MainWindow::on_send_clicked() {
    if(this->allDataValid()) {
        if(!confirmation_ui) {
            confirmation_ui = QSharedPointer<ConfirmationWindow>(new ConfirmationWindow);
        }

        TransType trans;
        QString transaux = ui->transportComboBox->currentText();

        if(transaux == "Fast") {
            trans = TransType::fast;
        }
        else if(transaux == "Medium") {
            trans = TransType::medium;
        }
        else {
            trans = TransType::slow;
        }

        Client client(ui->client_fname_line->text(), ui->client_lname_line->text(),
                      ui->client_phone_line->text(), ui->client_email_line->text());

        Client recipient(ui->recipient_fname_line->text(), ui->recipient_lname_line->text(),
                         ui->recipient_phone_line->text(), ui->recipient_email_line->text());

        auto distance = database->getShortestRouteDistance("Timisoara", ui->client_destination_combo->currentText());

        Route route("Timisoara", ui->client_destination_combo->currentText(), trans, distance);
        PkgType aux;
        QString temp = ui->typeComboBox->currentText();

        if(temp == "Fragile") {
            aux = PkgType::fragile;
        }
        else if(temp == "Precious") {
            aux = PkgType::precious;
        }
        else {
            aux = PkgType::dangerous;
        }

        Package package(ui->package_weight_line->text().toUInt(), database->getUniqueShippingID(),
                        ui->package_value_line->text().toUInt(), StatusType::inTransit, ui->package_name_line->text(), aux);

        client.setPackage(package);
        confirmation_ui->setData(client, recipient, route);

        ui->status_2->setText("Wow, such valid data, so small price...");

        confirmation_ui->show();
    }
}

/**
 * @brief MainWindow::onAddRouteClicked Method that will be called when the 'Add route' menu option will
 *        be clicked, then it will call show() (to display that window) method on **addroute_ui** window.
 */

void MainWindow::onAddRouteClicked() {
    if(!addroute_ui) {
        addroute_ui = QSharedPointer<RouteWindow>(new RouteWindow);
    }

    addroute_ui->show();
}
