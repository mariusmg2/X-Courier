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

void StatusInfoWindow::clearWindowData() const {
    ui->label->setText("");
    ui->label_2->setText("");
    ui->label_3->setText("");
    ui->label_4->setText("");

    ui->label_5->setText("");
    ui->label_6->setText("");
    ui->label_7->setText("");
    ui->label_8->setText("");

    ui->label_9->setText("");
    ui->label_10->setText("");
    ui->label_11->setText("");
    ui->label_12->setText("");
    ui->label_13->setText("");
    ui->label_14->setText("");
}

void StatusInfoWindow::newDataEntered(const QString& data) {
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
        ui->label_14->setText(infoData[3]); // Pachage code.
    }
    else {
        ui->label->setText("No such client...");
    }
}
