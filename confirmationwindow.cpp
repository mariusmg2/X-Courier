#include "confirmationwindow.h"
#include "ui_confirmationwindow.h"

ConfirmationWindow::ConfirmationWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(QSharedPointer<Ui::ConfirmationWindow>(new Ui::ConfirmationWindow))
{
    ui->setupUi(this);
    connect(ui->denyButton, SIGNAL(clicked()), this, SLOT(close()));
}

ConfirmationWindow::~ConfirmationWindow()
{
    qDebug().nospace() << "~ConfirmationWindow()";
    //ui.clear();
}
