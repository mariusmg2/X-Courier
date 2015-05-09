#ifndef ROUTEWINDOW_H
#define ROUTEWINDOW_H

#include <QMainWindow>
#include <QSharedPointer>
#include <QDebug>

#include "courierdatabase.h"
#include "route.h"

namespace Ui {
    class RouteWindow;
}

class RouteWindow : public QMainWindow {
private:
    Q_OBJECT

public:
    explicit RouteWindow(QWidget *parent = 0);
    ~RouteWindow();

private slots:
    void onAddButtonClicked();

private:
    QSharedPointer<Ui::RouteWindow> ui;
    QSharedPointer<CourierDatabase> database;
};

#endif // ROUTEWINDOW_H
