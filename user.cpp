#include "user.h"

User::User(QObject *parent) : QObject(parent)
{

}
User::User(QObject *parent, QString name, QString surname, QString email, QString number) : QObject(parent){
    _name = name;
    _surname = surname;
    _email = email;
    _number = number;
}
User::User(QString name, QString surname, QString email, QString number){
    _name = name;
    _surname = surname;
    _email = email;
    _number = number;
}

void User::setName(QString name){
    _name = name;
    emit nameChanged();
}
void User::setSurname(QString surname){
    _surname = surname;
    emit surnameChanged();
}
void User::setEmail(QString email){
    _email = email;
    emit emailChanged();
}
void User::setNumber(QString number){
    _number = number;
    emit numberChanged();
}

QString User::name() const{
    return _name;
}
QString User::surname() const{
    return _surname;
}
QString User::email() const{
    return _email;
}
QString User::number() const{
    return _number;
}
