#ifndef PACKAGESTATUSWINDOW_H
#define PACKAGESTATUSWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QSharedPointer>

#include "statusinfowindow.h"

namespace Ui {
    class PackageStatusWindow;
}

class PackageStatusWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit PackageStatusWindow(QWidget *parent = 0);
    ~PackageStatusWindow();
private slots:
    void recipientCodeTextChanged();
    void recipientNameTextChanged();
    void check_clicked(); // Funny thing: on_check_clicked() will not work, unless I use Qt Ui tools.
private:
    QSharedPointer<Ui::PackageStatusWindow> ui;
    QSharedPointer<StatusInfoWindow> status_ui;
};

#endif // PACKAGESTATUSWINDOW_H
