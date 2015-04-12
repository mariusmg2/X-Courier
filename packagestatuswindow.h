#ifndef PACKAGESTATUSWINDOW_H
#define PACKAGESTATUSWINDOW_H

#include <QMainWindow>
#include <QDebug>

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
    QSharedPointer<Ui::PackageStatusWindow> ui;
private slots:
    void recipientCodeTextChanged();
    void recipientNameTextChanged();
};

#endif // PACKAGESTATUSWINDOW_H
