#ifndef HOTEL_H
#define HOTEL_H
#include <QObject>
#include <QString>
#include <QList>
class Hotel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString address READ address WRITE setAddress NOTIFY addressChanged)
    Q_PROPERTY(QList<QObject*> listRooms READ listRooms WRITE setListRooms NOTIFY listRoomsChanged)

public:
    Hotel(QObject *parent);
    Hotel(QObject *parent,QString name, QString address);
    Hotel(QString name, QString address);
    QString name() const;
    QString address() const;
    QList<QObject*> listRooms() const;
    void setName(const QString &n);
    void setAddress(const QString &a);
    void setListRooms(const QList<QObject*> &l);
private:
    QString _name;
    QString _address;
    QList<QObject*> _listRooms;
signals:
    void nameChanged();
    void listRoomsChanged();
    void addressChanged();
};

#endif // HOTEL_H
