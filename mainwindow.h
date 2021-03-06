#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QString>
#include <QPushButton>
#include <QSharedPointer>
#include <QDebug>
#include <QRegExp>

#include "packagestatuswindow.h"
#include "confirmationwindow.h"
#include "transtype.h"
#include "pkgtype.h"
#include "courierdatabase.h"
#include "routewindow.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    bool allDataValid() const;
private slots:
    void on_status_clicked();
    void on_send_clicked();
    void onAddRouteClicked();
private:
    QSharedPointer<Ui::MainWindow> ui;
    QSharedPointer<PackageStatusWindow> status_ui;
    QSharedPointer<ConfirmationWindow> confirmation_ui;
    QSharedPointer<RouteWindow> addroute_ui;
    QSharedPointer<CourierDatabase> database;
};

#endif // MAINWINDOW_H
