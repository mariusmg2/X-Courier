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

/**
 * @brief PackageStatusWindow::recipientCodeTextChanged Method that will be called when some user
 *        inserts something in the code QLine from PackageStatusWindow window. This will disable
 *        (QLine will be inactive) the name QLine.
 *        It is used because we only need just one information (name or code), and not both!
 */

void PackageStatusWindow::recipientCodeTextChanged() {
    if(ui->recipientName->text().isEmpty() && !ui->recipientCode->text().isEmpty()) {
        ui->recipientName->setDisabled(true);
    }
    else {
        ui->recipientName->setEnabled(true);
    }
}

/**
 * @brief PackageStatusWindow::recipientNameTextChanged Method that will be called when some user
 *        inserts something in the name QLine from PackageStatusWindow window. This will disable
 *        (QLine will be inactive) the code QLine.
 *        It is used because we only need just one information (name or code), and not both!
 */

void PackageStatusWindow::recipientNameTextChanged() {
    if(ui->recipientCode->text().isEmpty() && !ui->recipientName->text().isEmpty()) {
        ui->recipientCode->setDisabled(true);
    }
    else {
        ui->recipientCode->setEnabled(true);
    }
}

/**
 * @brief PackageStatusWindow::check_clicked Signal that will be emited when 'check' button is
 *        pressed. It will emit the inserted name or code, and show the StatusInfoWindow window.
 *        At that other side, in StatusInfoWindow is a method that will be called with the data
 *        emited by this signal.
 */

void PackageStatusWindow::check_clicked() {
    if(!ui->recipientCode->text().isEmpty() || !ui->recipientName->text().isEmpty()) {
        if(!ui->recipientName->text().isEmpty()) {
           emit buttonCheckClicked(ui->recipientName->text());
        }
        else {
           emit buttonCheckClicked(ui->recipientCode->text());
        }

        status_ui->show();
    }
}
