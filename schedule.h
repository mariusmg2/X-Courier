#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <QDateTime>
#include <QString>

class Schedule {
public:
    Schedule(): from(QDate::currentDate(), QTime::currentTime()), to(QDate::currentDate(), QTime::currentTime()) {}
    Schedule(QDateTime& from, QDateTime& to): from(from), to(to) {}
    ~Schedule() {}
    QString getScheduleToString() const;
private:
    QDateTime from;
    QDateTime to;
};

#endif // SCHEDULE_H
