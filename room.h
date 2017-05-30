#ifndef ROOM_H
#define ROOM_H
#include <QObject>
#include <QString>
#include <QList>
#include <QVector>
#include <QDate>
#include <QDebug>
#include "reservation.h"
class Room : public QObject
{
    Q_OBJECT
    //Enum with roomType
    //Picture
    Q_PROPERTY(int capacity READ capacity WRITE setCapacity NOTIFY capacityChanged)
    Q_PROPERTY(QString desc READ desc WRITE setDesc NOTIFY descChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QList<QObject*> listReservations READ listReservations WRITE setListReservations NOTIFY listReservationsChanged)
    Q_PROPERTY(double cost READ cost WRITE setCost NOTIFY costChanged)
    Q_PROPERTY(QVector<bool> ava READ ava)
public:
    Room(QObject *parent);
    Room(QString desc, QString name, double cost, int capacity);
    Room(QObject *parent, QString desc, QString name, double cost, int capacity);
    Room(QString name, double cost, int capacity);
    QVector<bool> ava() const;
    QString desc() const;
    QString name() const;
    double cost() const;
    int capacity() const;
    QList<QObject*> listReservations() const;

    void setCost(const double &cost);
    void setName(const QString &name);
    void setDesc(const QString &desc);
    void setCapacity(const int &c);
    void setListReservations(const QList<QObject*> &rl);

    Q_INVOKABLE void addReservation(Reservation *reservation);
private:
    QList<QObject*> _listReservations;
    QVector<bool> _ava;
    QString _desc;
    QString _name;
    double _cost;
    double _capacity;
signals:
    void costChanged();
    void descChanged();
    void nameChanged();
    void capacityChanged();
    void listReservationsChanged();
};

#endif // ROOM_H
