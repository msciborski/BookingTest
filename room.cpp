#include "room.h"

Room::Room(QObject *parent) : QObject(parent) {
    QDate current = QDate::currentDate();
    QDate endYear(current.year(),12,31);
    int days = current.daysTo(endYear);
    _ava.resize(days+1);
}
Room::Room(QString desc, QString name, double cost, int capacity){
    _desc = desc;
    _name = name;
    _cost = cost;
    _capacity = capacity;

    QDate current = QDate::currentDate();
    QDate endYear(current.year(),12,31);

    int days = current.daysTo(endYear);
    _ava.resize(days);
}
Room::Room(QObject *parent, QString desc, QString name, double cost, int capacity) : QObject(parent){
    _desc = desc;
    _name = name;
    _cost = cost;
    _capacity = capacity;

    QDate current = QDate::currentDate();
    QDate endYear(current.year(),12,31);
    int days = current.daysTo(endYear);
    _ava.resize(days+1);
}
Room::Room(QString name, double cost, int capacity){
    _name = name;
    _cost = cost;
    _capacity = capacity;

    QDate current = QDate::currentDate();
    QDate endYear(current.year(),12,31);
    int days = current.daysTo(endYear);
    _ava.resize(days+1);
}

QString Room::desc() const{
    return _desc;
}
QString Room::name() const{
    return _name;
}
double Room::cost() const{
    return _cost;
}
int Room::capacity() const{
    return _capacity;
}
QList<QObject*> Room::listReservations() const{
    return _listReservations;
}
QVector<bool> Room::ava() const{
    return _ava;
}
void Room::setDesc(const QString &desc){
    _desc = desc;
    emit descChanged();
}
void Room::setName(const QString &name){
    _name = name;
    emit nameChanged();
}
void Room::setCost(const double &cost){
    _cost = cost;
    emit costChanged();
}
void Room::setCapacity(const int &c){
    _capacity = c;
    emit capacityChanged();
}
void Room::setListReservations(const QList<QObject*> &rl){
    _listReservations = rl;
    emit listReservationsChanged();
}
//Adds reservation to the list, and complement ava QVector, which contains information about...
void Room::addReservation(Reservation *reservation){
      QDate startReserv = reservation->startDate();
      QDate endReserv = reservation->endDate();
      QDate current = QDate::currentDate();
      QDate endOfTheYear = QDate(current.year(),12,31);
      int daysBetweenStartEnd = startReserv.daysTo(endReserv);
      int startReservToEndYear = startReserv.daysTo(endOfTheYear);
      int currentToEndYear = current.daysTo(endOfTheYear);
      int index = currentToEndYear - startReservToEndYear;
      qDebug() << _name << '\n';
      qDebug() << index << "\n";
      while(daysBetweenStartEnd >= 0){
          _ava[index] = true;
          index++;
          //qDebug() << index << "\n";
          daysBetweenStartEnd--;
      }
      _listReservations.append(reservation);
//    QDate start = reservation->startDate();
//    QDate end = reservation->endDate();
//    QDate currentDate = QDate::currentDate();
//    QDate endOfTheYear(currentDate.year(),12,31);
//    int daysToEnd = currentDate.daysTo(endOfTheYear);
//    int daysBetweenStartEnd = start.daysTo(end);
//    int startToEndYear = start.daysTo(endOfTheYear);
//    int index = daysToEnd - startToEndYear;
//    while(daysBetweenStartEnd>0){
//        _avaiabilty[index] = true;
//        index++;
//        daysBetweenStartEnd--;
//    }

}
