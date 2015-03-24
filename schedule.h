#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <QDateTime>
#include <QString>

/**
 * @brief The Schedule class
 *
 * This class is used for defining a Center schedule (one opening time, and one closing time).
 *
 * Public methods:
 *  QString getScheduleToString() const;
 */

class Schedule {
public:
    Schedule(): from(QDate::currentDate(), QTime::currentTime()), to(QDate::currentDate(), QTime::currentTime()) {}
    Schedule(const QDateTime& from, const QDateTime& to): from(from), to(to) {}
    ~Schedule() {}
    QString getScheduleToString() const;
private:
    QDateTime from;
    QDateTime to;
};

#endif // SCHEDULE_H
