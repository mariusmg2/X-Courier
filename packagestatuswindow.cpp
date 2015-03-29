#include "packagestatuswindow.h"
#include "ui_packagestatuswindow.h"

PackageStatusWindow::PackageStatusWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PackageStatusWindow)
{
    ui->setupUi(this);
}

PackageStatusWindow::~PackageStatusWindow()
{
    delete ui;
}
