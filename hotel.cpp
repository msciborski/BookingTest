#include "hotel.h"
/*constructors*/
Hotel::Hotel(QObject *parent) : QObject(parent) {

}
Hotel::Hotel(QObject *parent, QString name, QString address) : QObject(parent){
    _name = name;
    _address = address;
}
Hotel::Hotel(QString name, QString address){
    _name = name;
    _address = address;
}

/*getters/setters*/
QString Hotel::name() const{
    return _name;
}
QString Hotel::address() const{
    return _address;
}
QList<QObject*> Hotel::listRooms() const{
    return _listRooms;
}

void Hotel::setName(const QString &n){
    _name = n;
    emit nameChanged();
}
void Hotel::setAddress(const QString &a){
    _address = a;
    emit addressChanged();
}

void Hotel::setListRooms(const QList<QObject*> &l){
    _listRooms = l;
    emit listRoomsChanged();
}
