#ifndef USER_H
#define USER_H
#include <QString>
#include <QObject>

class User : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString surname READ surname WRITE setSurname NOTIFY surnameChanged)
    Q_PROPERTY(QString email READ email WRITE setEmail NOTIFY emailChanged)
    Q_PROPERTY(QString number READ number WRITE setNumber NOTIFY numberChanged)
public:
    User(QObject *parent);
    User(QObject *parent,QString name, QString surname, QString email, QString number);
    User(QString name, QString surname, QString email, QString number);

    void setName(QString name);
    void setSurname(QString surname);
    void setEmail(QString email);
    void setNumber(QString number);

    QString name() const;
    QString surname() const;
    QString email() const;
    QString number() const;
private:
    QString _name;
    QString _surname;
    QString _email;
    QString _number;
signals:
    void nameChanged();
    void surnameChanged();
    void emailChanged();
    void numberChanged();
};

#endif // USER_H
