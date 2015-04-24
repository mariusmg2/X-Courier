#ifndef STATUSINFOWINDOW_H
#define STATUSINFOWINDOW_H

#include <QDialog>
#include <QSharedPointer>
#include <QDebug>

#include "courierdatabase.h"

namespace Ui {
    class StatusInfoWindow;
}

class StatusInfoWindow : public QDialog {
private:
    Q_OBJECT
public:
    explicit StatusInfoWindow(QWidget *parent = 0);
    ~StatusInfoWindow();
public slots:
    void newDataEntered(const QString&);
private:
    QSharedPointer<Ui::StatusInfoWindow> ui;
    CourierDatabase db;
};

#endif // STATUSINFOWINDOW_H
