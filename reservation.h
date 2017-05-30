#ifndef RESERVATION_H
#define RESERVATION_H
#include <QObject>
#include <QDate>
#include <QVector>
#include "user.h"
class Reservation : public QObject
{
    Q_OBJECT
    //User
    Q_PROPERTY(int id READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QDate startDate READ startDate WRITE setStartDate NOTIFY startDateChanged)
    Q_PROPERTY(QDate endDate READ endDate WRITE setEndDate NOTIFY endDateChanged)
    Q_PROPERTY(User* user READ user)

public:
    Reservation(QObject *parent);
    Reservation();
    Reservation(QObject *parent, QDate startDate, QDate endDate, User *user);
    Reservation(QDate startDate, QDate endDate, User *user);
    int id() const;
    QDate startDate() const;
    QDate endDate() const;
    QVector<bool> ava() const;
    void setId(const int &id);
    void setStartDate(const QDate &startDate);
    void setEndDate(const QDate &endDate);
    User* user() const;
signals:
    void idChanged();
    void startDateChanged();
    void endDateChanged();
private:
    QDate _startDate;
    QDate _endDate;
    User *_user;
    int _id;
};

#endif // RESERVATION_H
