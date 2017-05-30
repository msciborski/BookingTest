#include "reservation.h"

Reservation::Reservation(){
}
Reservation::Reservation(QObject *parent) : QObject(parent){

}
Reservation::Reservation(QObject *parent, QDate startDate, QDate endDate, User *user) : QObject(parent){
    _startDate = startDate;
    _endDate = endDate;
    _user = user;

}
Reservation::Reservation(QDate startDate, QDate endDate, User *user){
    _startDate = startDate;
    _endDate = endDate;
    _user = user;
}

int Reservation::id() const{
    return _id;
}
QDate Reservation::startDate() const{
    return _startDate;
}
QDate Reservation::endDate() const{
    return _endDate;
}
User* Reservation::user() const{
    return _user;
}
//Idk, that i really need to have setter for id, i have to consider it
void Reservation::setId(const int &id){
    _id = id;
    emit idChanged();
}
void Reservation::setStartDate(const QDate &startDate){
    _startDate = startDate;
    emit startDateChanged();
}
void Reservation::setEndDate(const QDate &endDate){
    _endDate = endDate;
    emit endDateChanged();
}
