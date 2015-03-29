#ifndef PACKAGESTATUSWINDOW_H
#define PACKAGESTATUSWINDOW_H

#include <QMainWindow>

namespace Ui {
class PackageStatusWindow;
}

class PackageStatusWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PackageStatusWindow(QWidget *parent = 0);
    ~PackageStatusWindow();

private:
    Ui::PackageStatusWindow *ui;
};

#endif // PACKAGESTATUSWINDOW_H
