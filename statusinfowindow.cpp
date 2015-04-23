#include "statusinfowindow.h"
#include "ui_statusinfowindow.h"

StatusInfoWindow::StatusInfoWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StatusInfoWindow)
{
    ui->setupUi(this);
    connect(ui->exitButton, SIGNAL(clicked()), this, SLOT(close()));
}

StatusInfoWindow::~StatusInfoWindow() {
    delete ui;
    qDebug().nospace() << "~StatusInfoWindow()";
}
