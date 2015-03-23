#ifndef POSITION_H
#define POSITION_H

#include <QString>

class Position {
public:
    Position(): longitude(0), latitude(0) {}
    Position(int longitude, int latitude): longitude(longitude), latitude(latitude) {}
    ~Position() {}
    QString getPositionAsString() const;
    int getLongitude() const;
    int getLatitude() const;
private:
    int longitude;
    int latitude;
};

#endif // POSITION_H

