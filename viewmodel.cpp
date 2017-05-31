#include "viewmodel.h"

/*constructors*/
ViewModel::ViewModel()
{
    _startDates = Helper::createStartDate();
    _endDates = Helper::createStartDate();
    _listCities = Helper::createCity(this);
    _starDateIndex = 0;
    _endDateIndex = 0;
    _cityIndex = 0;
    _hotelIndex = 0;
    _roomIndex = 0;
    _indexView = 0;
    _buttonVisibility = false;
}

/*getters/setters*/
QStringList ViewModel::startDates() const{
    return _startDates;
}
QStringList ViewModel::endDates() const{
    return _endDates;
}
QList<QObject*> ViewModel::listCities() const{
    return _listCities;
}
int ViewModel::startDateIndex() const{
    return _starDateIndex;
}
int ViewModel::endDateIndex() const{
    return _endDateIndex;
}
int ViewModel::cityIndex() const{
    return _cityIndex;
}
int ViewModel::hotelIndex() const{
    return _hotelIndex;
}
int ViewModel::roomIndex() const{
    return _roomIndex;
}
int ViewModel::indexView() const{
    return _indexView;
}
QString ViewModel::label() const{
    return _label;
}
double ViewModel::totalPrice(){
    return _totalPrice;
}
bool ViewModel::buttonVisibility() const{
    return _buttonVisibility;
}
QString ViewModel::userName() const{
    return _userName;
}
QString ViewModel::userSurname() const{
    return _userSurname;
}
QString ViewModel::userEmail() const{
    return _userEmail;
}
QString ViewModel::userPhoneNumber() const{
    return _userPhoneNumber;
}

void ViewModel::setStartDates(QStringList &startDates){
        _startDates = startDates;
        emit startDatesChanged();
}
void ViewModel::setEndDates(QStringList &endDates){
    _endDates = endDates;
    emit endDatesChanged();
}
void ViewModel::setListCities(QList<QObject*> &cityL){
    _listCities = cityL;
    emit listCitiesChanged();
}

void ViewModel::setStartDateIndex(int &index){
    _starDateIndex = index;
    emit startDateIndexChanged();
}
void ViewModel::setEndDateIndex(int &index){
    _endDateIndex = index;
    emit endDateIndexChanged();
}
void ViewModel::setCityIndex(int &index){
    _cityIndex = index;
    emit cityIndexChanged();
}
void ViewModel::setHotelIndex(int &index){
    _hotelIndex = index;
    emit hotelIndexChanged();
}
void ViewModel::setRoomIndex(int &index){
    _roomIndex = index;
    emit roomIndexChanged();
}
void ViewModel::setLabel(QString &label){
    _label = label;
    emit labelChanged();
}
void ViewModel::setIndexView(int index){
    _indexView = index;
    emit indexViewChanged();
}
void ViewModel::setTotalPrice(double price){
    _totalPrice = price;
    emit totalPriceChanged();
}
void ViewModel::setButtonVisibility(bool visibile){
    _buttonVisibility = visibile;
    emit buttonVisibilityChanged();
}
void ViewModel::setUserName(QString userName){
    _userName = userName;
    emit userNameChanged();
}
void ViewModel::setUserSurname(QString surname){
    _userSurname = surname;
    emit userSurnameChanged();
}
void ViewModel::setUserEmail(QString email){
    _userEmail = email;
    emit userEmailChanged();
}
void ViewModel::setUserPhoneNumber(QString phoneNumber){
    _userPhoneNumber = phoneNumber;
    emit userPhoneNumberChanged();
}

/*methods*/
//Do poprawy jest ta funkcja//Na askach zrób
bool ViewModel::isAvaiable(QList<QObject*> &reservations, const QDate &startDate, const QDate &endDate){
    bool avaiability = false;
    QDate endOfTheYear(QDate::currentDate().year(),12,31);
    auto startDateDaysToEnd = startDate.daysTo(endOfTheYear); // ilosc dni od wybranej daty rozpoczecia do konca roku
    auto endDateDaysToEnd = endDate.daysTo(endOfTheYear); // ilosc dni od wybranej daty zakonczenia do konca roku
    for(auto reservation : reservations){
        QDate reservationStartDate = reservation->property("startDate").toDate(); // Data rozpoczecia rezerwacji z listy rezerwacji
        QDate reservationEndDate = reservation->property("endDate").toDate(); //Data zakończenia rezerwacji z listy rererwacji

        if(startDate == reservationEndDate){ // jeśli wybrana data rozpoczecia == zakonczenie rezerwacji true
            avaiability = true;
        }else{
            auto reservationStartDateDaysToEnd = reservationStartDate.daysTo(endOfTheYear); //
            auto reservationEndDateDaysToEnd = reservationEndDate.daysTo(endOfTheYear);
            if(((reservationStartDateDaysToEnd >= startDateDaysToEnd) && (reservationEndDateDaysToEnd < startDateDaysToEnd)) ||
                    (reservationStartDateDaysToEnd > endDateDaysToEnd) && (reservationEndDateDaysToEnd <= endDateDaysToEnd) ){
                avaiability = false;
                break;
            }else{
                avaiability = true;
            }
        }
    }
    return avaiability;
}

void ViewModel::checkAvailability(){
    qDebug() << "Dziala" << "\n";
    qDebug() << _starDateIndex << "\n";
    _label = "";
    QString avaiable = "";
    bool visibility;
    QDate startDate = QDate::fromString(_startDates[_starDateIndex], Qt::SystemLocaleDate);
    QDate endDate = QDate::fromString(_endDates[_endDateIndex],Qt::SystemLocaleDate);
    City *city = qobject_cast<City*>(_listCities[_cityIndex]);
    Hotel *hotel = qobject_cast<Hotel*>(city->listHotels()[_hotelIndex]);
    Room *room = qobject_cast<Room*>(hotel->listRooms()[_roomIndex]);
    QVariant reservationsVariant = room->property("listReservations");
    QList<QObject*> reservations = reservationsVariant.value<QList<QObject*>>();
    if(!reservations.empty()){
        if(!isAvaiable(reservations, startDate, endDate)){
            avaiable = "Pokój zajęty, wybierz inną datę.";
            avaiable += nearestFree(room,startDate,endDate);
            setLabel(avaiable);
            visibility = false;
            setButtonVisibility(visibility);
        }else{
            avaiable = "";
            setLabel(avaiable);
            visibility = true;
            setButtonVisibility(visibility);
        }
    }else{
        avaiable = "";
        setLabel(avaiable);
        visibility = true;
        setButtonVisibility(visibility);
    }
}
void ViewModel::setEndDate(){
    QDate startDate = QDate::fromString(_startDates[_starDateIndex],Qt::SystemLocaleDate);
    QDate endOfTheYear(QDate::currentDate().year(),12,31);
    auto daysToEnd = startDate.daysTo(endOfTheYear);
    QStringList tempEndDates;
    for(int i=1;i<daysToEnd;i++){
        tempEndDates.append(startDate.addDays(i).toString("dd.MM.yyyy"));
    }
    setEndDates(tempEndDates);

}
QString ViewModel::nearestFree(Room *room, QDate startDate, QDate endDate){
    QDate currentDate = QDate::currentDate();
    QDate endOfTheYear(currentDate.year(),12,31);
    int daysBetweenStartEnd = startDate.daysTo(endDate);
    int currentToEndOfTheYear = currentDate.daysTo(endOfTheYear);
    int startToEndOfTheYear = startDate.daysTo(endOfTheYear);
    int index = currentToEndOfTheYear - startToEndOfTheYear;
    QVector<bool> tempAva = room->ava();
    qDebug() << index << '\n';
    qDebug() << "DaysBetweenStartEnd: " << daysBetweenStartEnd << "\n";
    int i;

    for(i = index;i<currentToEndOfTheYear;i++){
        int counter = 0;
        if(tempAva[i] == false){
            i++;
            counter++;
            if(counter == daysBetweenStartEnd){
                break;
            }
            for(int j=1;j<daysBetweenStartEnd;j++){
                if(tempAva[i] == false){
                    i++;
                    counter++;
                }else{
                    break;
                }
            }
            if(counter == daysBetweenStartEnd){
                break;
            }
        }
    }
    qDebug() << i << "\n";
    QDate endNearest = currentDate.addDays(i);
    QDate startNearest = endNearest.addDays(daysBetweenStartEnd*(-1));
    qDebug() << startNearest.toString("dd/MM/yyyy") << " " << endNearest.toString("dd/MM/yyyy");
    int inc = 0;
    for(auto a : tempAva){
        qDebug() << inc << ": " << a << '\n';
        inc++;
    }
    return "\nNajbliższy wolny termin: " + startNearest.toString("dd/MM/yyyy") + " - " + endNearest.toString("dd/MM/yyyy");

}
void ViewModel::calculateTotalPrice(){
    QDate startDate = QDate::fromString(_startDates[_starDateIndex], Qt::SystemLocaleDate);
    QDate endDate = QDate::fromString(_endDates[_endDateIndex],Qt::SystemLocaleDate);
    City *city = qobject_cast<City*>(_listCities[_cityIndex]);
    Hotel *hotel = qobject_cast<Hotel*>(city->listHotels()[_hotelIndex]);
    Room *room = qobject_cast<Room*>(hotel->listRooms()[_roomIndex]);
    double tPrice = startDate.daysTo(endDate) * room->cost();
    setTotalPrice(tPrice);
}

void ViewModel::test(){
    QString test = "TEST TEST TEST TEST TEST";
    setLabel(test);
}

void ViewModel::createReservation(){
    QDate startDate = QDate::fromString(_startDates[_starDateIndex], Qt::SystemLocaleDate);
    QDate endDate = QDate::fromString(_endDates[_endDateIndex],Qt::SystemLocaleDate);
    City *city = qobject_cast<City*>(_listCities[_cityIndex]);
    Hotel *hotel = qobject_cast<Hotel*>(city->listHotels()[_hotelIndex]);
    User *user = new User(_userName,_userSurname,_userEmail,_userPhoneNumber);
    Reservation *reservation = new Reservation(startDate,endDate,user);
    qobject_cast<Room*>(hotel->listRooms()[_roomIndex])->addReservation(reservation);

}




