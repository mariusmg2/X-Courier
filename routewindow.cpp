#include "routewindow.h"
#include "ui_routewindow.h"

RouteWindow::RouteWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(QSharedPointer<Ui::RouteWindow>(new Ui::RouteWindow)),
    database(QSharedPointer<CourierDatabase>(new CourierDatabase("QSQLITE", "database.sqlite3", "Route window connection")))
{
    ui->setupUi(this);
    connect(ui->exitButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->addButton, SIGNAL(clicked()), this, SLOT(onAddButtonClicked()));
    connect(ui->addButton, SIGNAL(clicked()), this, SLOT(close()));

    QVector<QString> temp = database->getAllDestinations();
    for(auto i : temp) {
        ui->sourceComboBox->addItem(i);
        ui->destComboBox->addItem(i);
    }
}

RouteWindow::~RouteWindow() {
    qDebug() << "~RouteWindow()";
    //delete ui;
}

/**
 * @brief RouteWindow::onAddButtonClicked Method that is called when user clicks on 'add' button,
 *        the method will retrive data from comboBox, and call the appropriate **database** method,
 *        for adding that data into db.
 */

void RouteWindow::onAddButtonClicked() {
    Route temp;

    temp.setSource(ui->sourceComboBox->currentText());
    temp.setDestination(ui->destComboBox->currentText());
    temp.setDistance(ui->spinBox->text().toInt());

    database->addRoute(temp.getSource(), temp.getDestination(), temp.getDistance());
}
