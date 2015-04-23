#ifndef CONFIRMATIONWINDOW_H
#define CONFIRMATIONWINDOW_H

#include <QMainWindow>
#include <QSharedPointer>
#include <QDebug>

namespace Ui {
    class ConfirmationWindow;
}

class ConfirmationWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit ConfirmationWindow(QWidget *parent = 0);
    ~ConfirmationWindow();

private:
    QSharedPointer<Ui::ConfirmationWindow> ui;
};

#endif // CONFIRMATIONWINDOW_H
