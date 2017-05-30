#ifndef CITY_H
#define CITY_H
#include <QObject>
#include <QString>
#include <QQmlListProperty>
#include <QList>
#include "hotel.h"

class Hotel;
class City : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString cityName READ cityName WRITE setCityName NOTIFY cityNameChanged)
    Q_PROPERTY(QList<QObject*> listHotels READ listHotels WRITE setListHotels NOTIFY listHotelsChanged)
public:
    QString cityName() const;
    QList<QObject*> listHotels() const;
    void setCityName(QString &name);
    void setListHotels(const QList<QObject*> &l);
    City(QString name);
    City(QObject *parent, QString name);
    City(QObject *parent);
signals:
    void cityNameChanged();
    void listHotelsChanged();
private:
    QString _cityName;
    QList<QObject*> _listHotels;
};

#endif // CITY_H
