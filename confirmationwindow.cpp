#include "confirmationwindow.h"
#include "ui_confirmationwindow.h"

ConfirmationWindow::ConfirmationWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ConfirmationWindow)
{
    ui->setupUi(this);
    connect(ui->denyButton, SIGNAL(clicked()), this, SLOT(close()));
}

ConfirmationWindow::~ConfirmationWindow()
{
    delete ui;
}
