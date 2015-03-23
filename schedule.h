#include <QDateTime>
#include <QString>

#ifndef SCHEDULE_H
#define SCHEDULE_H

class Schedule {
public:
    Schedule(): from(QDateTime()), to(QDateTime()) {}
    Schedule(QDateTime& from, QDateTime& to): from(from), to(to) {}
    ~Schedule() {}
    QString getScheduleToString() const;
private:
    QDateTime from;
    QDateTime to;
};

#endif // SCHEDULE_H
