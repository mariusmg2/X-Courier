#include <QDate>
#include <QString>

#ifndef SCHEDULE_H
#define SCHEDULE_H

class Schedule {
public:
    Schedule(): from(QDate::currentDate().year(), QDate::currentDate().month(), QDate::currentDate().year()),
        to(QDate::currentDate().year(), QDate::currentDate().month(), QDate::currentDate().year()) {}
    Schedule(QDate& from, QDate& to): from(from), to(to) {}
    ~Schedule() {}
    QString getScheduleToString() const;
private:
    QDate from;
    QDate to;
};

#endif // SCHEDULE_H
