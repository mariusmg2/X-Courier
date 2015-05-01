#ifndef CONFIRMATIONWINDOW_H
#define CONFIRMATIONWINDOW_H

#include <QMainWindow>
#include <QSharedPointer>
#include <QDebug>

#include "courierdatabase.h"
#include "client.h"
#include "route.h"
#include "package.h"

namespace Ui {
    class ConfirmationWindow;
}

class ConfirmationWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit ConfirmationWindow(QWidget *parent = 0);
    ~ConfirmationWindow();
    void setData(const Client&, const Client&, const Route&);
    void printDataToWindow() const;
private slots:
    void insertDataInDB();
private:
    QSharedPointer<Ui::ConfirmationWindow> ui;
    QSharedPointer<CourierDatabase> database;
    Client client;
    Client recipient;
    Route route;
};

#endif // CONFIRMATIONWINDOW_H
