#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QString>
#include <QPushButton>
#include <QSharedPointer>
#include <QDebug>

#include "packagestatuswindow.h"
#include "confirmationwindow.h"
#include "transtype.h"
#include "pkgtype.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void on_status_clicked();
    void on_send_clicked();

private:
    QSharedPointer<Ui::MainWindow> ui;
    QSharedPointer<PackageStatusWindow> status_ui;
    QSharedPointer<ConfirmationWindow> confirmation_ui;
};

#endif // MAINWINDOW_H
