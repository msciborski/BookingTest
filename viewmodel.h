#ifndef VIEWMODEL_H
#define VIEWMODEL_H
#include <QObject>
#include <QStringList>
#include <QObjectList>
#include <QList>
#include <QDebug>
#include <QVector>
#include "helper.h"
#include "city.h"

class ViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int startDateIndex READ startDateIndex WRITE setStartDateIndex NOTIFY startDateIndexChanged)
    Q_PROPERTY(int endDateIndex READ endDateIndex WRITE setEndDateIndex NOTIFY endDateIndexChanged)
    Q_PROPERTY(int  cityIndex READ cityIndex WRITE setCityIndex NOTIFY cityIndexChanged)
    Q_PROPERTY(int hotelIndex READ hotelIndex WRITE setHotelIndex NOTIFY hotelIndexChanged)
    Q_PROPERTY(int roomIndex READ roomIndex WRITE setRoomIndex NOTIFY roomIndexChanged)
    Q_PROPERTY(QString  label READ label WRITE setLabel NOTIFY labelChanged)
    Q_PROPERTY(QStringList startDates READ startDates WRITE setStartDates NOTIFY startDatesChanged)
    Q_PROPERTY(QStringList endDates READ endDates WRITE setEndDates NOTIFY endDatesChanged)
    Q_PROPERTY(QList<QObject*> listCities READ listCities WRITE setListCities NOTIFY listCitiesChanged)
    Q_PROPERTY(int indexView READ indexView WRITE setIndexView NOTIFY indexViewChanged)
    Q_PROPERTY(double totalPrice READ totalPrice WRITE setTotalPrice NOTIFY totalPriceChanged)
    Q_PROPERTY(bool buttonVisibility READ buttonVisibility WRITE setButtonVisibility NOTIFY buttonVisibilityChanged)
    Q_PROPERTY(QString userName READ userName WRITE setUserName NOTIFY userNameChanged)
    Q_PROPERTY(QString userSurname READ userSurname WRITE setUserSurname NOTIFY userSurnameChanged)
    Q_PROPERTY(QString userEmail READ userEmail WRITE setUserEmail NOTIFY userEmailChanged)
    Q_PROPERTY(QString userPhoneNumber READ userPhoneNumber WRITE setUserPhoneNumber NOTIFY userPhoneNumberChanged)
public:
    ViewModel();
    void setStartDates(QStringList &startDates);
    void setEndDates(QStringList &endDates);
    void setListCities(QList<QObject*> &cityL);
    void setStartDateIndex(int &index);
    void setEndDateIndex(int &index);
    void setCityIndex(int &index);
    void setHotelIndex(int &index);
    void setRoomIndex(int &index);
    void setLabel(QString &label);
    void setIndexView(int index);
    void setTotalPrice(double price);
    void setButtonVisibility(bool visibile);
    void setUserName(QString userName);
    void setUserSurname(QString surname);
    void setUserEmail(QString email);
    void setUserPhoneNumber(QString phoneNumber);

    QStringList startDates() const;
    QStringList endDates() const;
    QList<QObject*> listCities() const;
    int startDateIndex() const;
    int endDateIndex() const;
    int cityIndex() const;
    int hotelIndex() const;
    int roomIndex() const;
    int indexView() const;
    QString label() const;
    double totalPrice();
    bool buttonVisibility() const;
    QString userName() const;
    QString userSurname() const;
    QString userEmail() const;
    QString userPhoneNumber() const;

    Q_INVOKABLE void checkAvailability();
    Q_INVOKABLE void setEndDate();
    Q_INVOKABLE QString nearestFree(Room *room, QDate startDate, QDate endDate);
    Q_INVOKABLE void calculateTotalPrice();
    Q_INVOKABLE void test();
    Q_INVOKABLE void createReservation();

private:
    QStringList _startDates;
    QStringList _endDates;
    QList<QObject*> _listCities;
    double _totalPrice;
    bool _buttonVisibility;
    int _starDateIndex;
    int _endDateIndex;
    int _cityIndex;
    int _hotelIndex;
    int _roomIndex;
    int _indexView;
    QString _label;
    QString _userName;
    QString _userSurname;
    QString _userEmail;
    QString _userPhoneNumber;
    bool isAvaiable(QList<QObject*>& reservations, const QDate &startDate, const QDate &endDate);
signals:
    void startDatesChanged();
    void endDatesChanged();
    void listCitiesChanged();
    void startDateIndexChanged();
    void endDateIndexChanged();
    void cityIndexChanged();
    void hotelIndexChanged();
    void roomIndexChanged();
    void labelChanged();
    void indexViewChanged();
    void totalPriceChanged();
    void buttonVisibilityChanged();
    void userNameChanged();
    void userSurnameChanged();
    void userEmailChanged();
    void userPhoneNumberChanged();
};

#endif // VIEWMODEL_H
