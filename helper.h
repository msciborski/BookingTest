#ifndef HELPER_H
#define HELPER_H
#include <QStringList>
#include <QObjectList>
#include <QList>
#include <QStringList>
#include <QDate>
#include <QDebug>
#include "city.h"
#include "hotel.h"
#include "room.h"
#include "reservation.h"

class Helper
{
public:
    Helper();
    static QStringList createStartDate();
    static QList<QObject*> createCity(QObject *parent);
    static QList<QObject*> temporaryHotels(QObject *parent, QString cityName);
    static QList<QObject*> temporaryRooms(QObject *parent, QString hotelName);
    static QVector<Reservation*> createReservations(QObject *parent);
private:
    static bool avaiable(QVector<Reservation*> reservations, QDate start, QDate end);

};

#endif // HELPER_H
