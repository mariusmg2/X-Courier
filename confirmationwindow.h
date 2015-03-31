#ifndef CONFIRMATIONWINDOW_H
#define CONFIRMATIONWINDOW_H

#include <QMainWindow>

namespace Ui {
class ConfirmationWindow;
}

class ConfirmationWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ConfirmationWindow(QWidget *parent = 0);
    ~ConfirmationWindow();

private:
    Ui::ConfirmationWindow *ui;
};

#endif // CONFIRMATIONWINDOW_H
