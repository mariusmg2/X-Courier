#include "statusinfowindow.h"
#include "ui_statusinfowindow.h"

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

void StatusInfoWindow::newDataEntered(const QString& data) {
    QVector<QString> infoData = db.checkStatus(data);

    for(auto i : infoData) {
        qDebug() << i;
    }

    if(infoData.size() == 15) {
        ui->label->setText(infoData[7]);    // Sender first name.
        ui->label_2->setText(infoData[8]);  // Sender last name.
        ui->label_3->setText(infoData[10]); // Sender phone number.
        ui->label_4->setText(infoData[9]);  // Sender email address.

        ui->label_5->setText(infoData[11]);
        ui->label_6->setText(infoData[12]);
        ui->label_7->setText(infoData[14]);
        ui->label_8->setText(infoData[13]);

        ui->label_9->setText(infoData[1]);
        ui->label_10->setText(infoData[2]);
        ui->label_11->setText(infoData[6]);
        ui->label_12->setText(infoData[4]);
        ui->label_13->setText(infoData[0]);
        ui->label_14->setText(infoData[3]);
    }
    else {
        ui->label->setText("No such client...");
    }
}
