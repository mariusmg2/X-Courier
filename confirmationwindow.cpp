#include "confirmationwindow.h"
#include "ui_confirmationwindow.h"

ConfirmationWindow::ConfirmationWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ConfirmationWindow)
{
    ui->setupUi(this);
}

ConfirmationWindow::~ConfirmationWindow()
{
    delete ui;
}
