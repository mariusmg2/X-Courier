#include "schedule.h"

QString Schedule::getScheduleToString() const {
    return QString::number(this->from.time().hour()) + ":" + QString::number(this->from.time().minute()) +
            " - " + QString::number(this->to.time().hour()) + ":" + QString::number(this->to.time().minute());
}
