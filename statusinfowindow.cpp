#include "statusinfowindow.h"
#include "ui_statusinfowindow.h"
#include "client.h"
#include "package.h"

StatusInfoWindow::StatusInfoWindow(QWidget *parent) :
    QDialog(parent),
    ui(QSharedPointer<Ui::StatusInfoWindow>(new Ui::StatusInfoWindow)),
    db("QSQLITE", "database.sqlite3", "Status Window Connection")
{
    ui->setupUi(this);
    connect(ui->exitButton, SIGNAL(clicked()), this, SLOT(close()));
}

StatusInfoWindow::~StatusInfoWindow() {
    //ui.clear();
    qDebug().nospace() << "~StatusInfoWindow()";
}

/**
 * @brief StatusInfoWindow::clearWindowData Method used to clear all labels from the StatusInfoWindow.
 */

void StatusInfoWindow::clearWindowData() const {
    ui->label->clear();
    ui->label_2->clear();
    ui->label_3->clear();
    ui->label_4->clear();

    ui->label_5->clear();
    ui->label_6->clear();
    ui->label_7->clear();
    ui->label_8->clear();

    ui->label_9->clear();
    ui->label_10->clear();
    ui->label_11->clear();
    ui->label_12->clear();
    ui->label_13->clear();
    ui->label_14->clear();

    ui->status1->clear();
    ui->status2->clear();
    ui->shippingprice->clear();
}

/**
 * @brief StatusInfoWindow::newDataEntered Method that will be called when the bbuttonCheckClicked()
 *        signal is emited (from PackageStatusWindow), it will retrive the data from database
 *        (based on the data emited), and print it on the window.
 * @param data - QString representing a name/code.
 */

void StatusInfoWindow::newDataEntered(const QString& data) {
    db.updateDatabaseStatus();
    QVector<QString> infoData = db.getPackageStatus(data);

    for(auto i : infoData) {
        qDebug() << i;
    }

    this->clearWindowData();

    if(infoData.size() > 2) {

        Client sender;
        Client reciver;

        sender.setFirstName(infoData[7]);
        sender.setLastName(infoData[8]);
        sender.setPhone(infoData[10]);
        sender.setEmail(infoData[9]);
        sender.setGender(false);

        reciver.setFirstName(infoData[11]);
        reciver.setLastName(infoData[12]);
        reciver.setPhone(infoData[14]);
        reciver.setEmail(infoData[13]);
        reciver.setGender(false);

        ui->senderBox->setEnabled(true);
        ui->recipientBox->setEnabled(true);
        ui->packageBox->setEnabled(true);

        ui->label->setText(sender.getFirstName());      // Sender first name.
        ui->label_2->setText(sender.getLastName());     // Sender last name.
        ui->label_3->setText(sender.getPhone());        // Sender phone number.
        ui->label_4->setText(sender.getEmail());        // Sender email address.

        ui->label_5->setText(reciver.getFirstName());   // Reciver first name.
        ui->label_6->setText(reciver.getLastName());    // Reciver last name.
        ui->label_7->setText(reciver.getPhone());       // Reciver phone number.
        ui->label_8->setText(reciver.getEmail());       // Reciver email address.

        ui->label_9->setText(infoData[1]);  // Package content.
        ui->label_10->setText(infoData[2]); // Package weight.
        ui->label_11->setText(infoData[6]); // Package price.
        ui->label_12->setText(infoData[4]); // Package source.
        ui->label_13->setText(infoData[0]); // Package status.
        ui->label_14->setText(infoData[3]); // Package code.

        if(infoData[17].toFloat() == 0.0) {
            ui->shippingprice->setText("PAID");
        }
        else {
            ui->shippingprice->setText(infoData[17]);
        }
    }
    else {
        ui->status1->setStyleSheet("QLabel { color : red; }");
        ui->status2->setStyleSheet("QLabel { color : red; }");

        ui->status1->setText("Sorry, no such client :(");
        ui->status2->setText("Sorry, no such client :(");

        ui->senderBox->setEnabled(false);
        ui->recipientBox->setEnabled(false);
        ui->packageBox->setEnabled(false);
    }
}
