#include "statusinfowindow.h"
#include "ui_statusinfowindow.h"

StatusInfoWindow::StatusInfoWindow(QWidget *parent) :
    QDialog(parent),
    ui(QSharedPointer<Ui::StatusInfoWindow>(new Ui::StatusInfoWindow)),
    db("QSQLITE", "database.sqlite3", "Status Window Connection")
{
    ui->setupUi(this);
    connect(ui->exitButton, SIGNAL(clicked()), this, SLOT(close()));

    QVector<QString> infoData = db.checkStatus("Marusanici");

    for(auto i : infoData) {
        qDebug() << i;
    }
}

StatusInfoWindow::~StatusInfoWindow() {
    //ui.clear();
    qDebug().nospace() << "~StatusInfoWindow()";
}
