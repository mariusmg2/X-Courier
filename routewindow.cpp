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

    for(auto i : database->getAllDestinations()) {
        ui->sourceComboBox->addItem(i);
        ui->destComboBox->addItem(i);
    }
}

RouteWindow::~RouteWindow() {
    qDebug() << "~RouteWindow()";
    //delete ui;
}

void RouteWindow::onAddButtonClicked() {
    Route temp;

    temp.setSource(ui->sourceComboBox->currentText());
    temp.setDestination(ui->destComboBox->currentText());
    temp.setDistance(ui->spinBox->text().toInt());

    database->addRoute(temp.getSource(), temp.getDestination(), temp.getDistance());
}
