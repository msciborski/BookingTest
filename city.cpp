#include "city.h"

City::City(QString name) {
    _cityName = name;
}
City::City(QObject *parent) : QObject(parent){

}
City::City(QObject *parent, QString name) : QObject(parent){
    _cityName = name;
}

QString City::cityName() const{
    return _cityName;
}
QList<QObject*> City::listHotels() const{
    return _listHotels;
}
void City::setCityName(QString &name){
        _cityName = name;
        emit cityNameChanged();
}
void City::setListHotels(const QList<QObject*> &l){
        _listHotels = l;
        emit listHotelsChanged();
}

