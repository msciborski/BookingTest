#include "helper.h"

Helper::Helper()
{

}
//Static method, which creates string list with dates. I have to do it like that, becouse QML dosen't deliver EditDate widget.
QStringList Helper::createStartDate(){
    QStringList tempStartDates;
    QDate today = QDate::currentDate();
    QDate endOfTheYear(QDate::currentDate().year(),12,31);
    auto dayToTheEnd = today.daysTo(endOfTheYear);
    for(int i=0;i<=dayToTheEnd;i++){
        tempStartDates.append(today.addDays(i).toString("dd.MM.yyyy"));
    }
    return tempStartDates;
}

QList<QObject*> Helper::createCity(){
    QList<QObject*> tempCity;
    City *poznan = new City("Poznań");
    poznan->setListHotels(Helper::temporaryHotels(poznan->cityName()));
//    poznan->listHotels().append(Helper::temporaryRooms(poznan->cityName()));
    City *warszawa = new City("Warszawa");
    warszawa->setListHotels(Helper::temporaryHotels(warszawa->cityName()));
    //warszawa->listHotels().append(Helper::temporaryRooms(warszawa->cityName()));
    City *krakow = new City("Kraków");
    krakow->setListHotels(Helper::temporaryHotels(krakow->cityName()));
    //krakow->listHotels().append(Helper::temporaryRooms(krakow->cityName()));
    City *gdansk = new City("Gdańsk");
    gdansk->setListHotels(Helper::temporaryHotels(gdansk->cityName()));
    //gdansk->listHotels().append(Helper::temporaryRooms(gdansk->cityName()));
    City *sopot = new City("Sopot");
    sopot->setListHotels(Helper::temporaryHotels(sopot->cityName()));
    //sopot->listHotels().append(Helper::temporaryRooms(sopot->cityName()));
    City *lodz = new City("Łódź");
    lodz->setListHotels(Helper::temporaryHotels(lodz->cityName()));
    //lodz->listHotels().append(Helper::temporaryRooms(lodz->cityName()));
    tempCity.append(poznan);
    tempCity.append(warszawa);
    tempCity.append(krakow);
    tempCity.append(gdansk);
    tempCity.append(sopot);
    tempCity.append(lodz);

    return tempCity;
}
QList<QObject*> Helper::temporaryHotels(QString cityName){
    QList<QObject*> tempHotels;
    for(int i=1;i<=5;i++){
        QString hotelName = QString(cityName + "%1").arg(i);
        QString address = QString("ul. %1 %2").arg(cityName).arg(i);
        Hotel *hotel = new Hotel(hotelName,address);
        hotel->setListRooms(Helper::temporaryRooms(hotelName));
        tempHotels.append(hotel);
    }
    return tempHotels;
}
//Refactor, bo QDate ma funckje daysInMonth-
QVector<Reservation*> Helper::createReservations(){
   QVector<Reservation*> reservations;
   QDate current = QDate::currentDate();
   int day = current.day();
   int month = current.month();
   int year = current.year();
   for(int i=0;i<10;i++){
       QDate startDate;
       QDate endDate;
       int daysRange;
       int sMonth;
       int sDay;
       do{
            daysRange = rand() % ((8+1)-1) + 1;
            sMonth = rand() % ((12+1)-month) + month;
            if(sMonth == 1 || sMonth == 3 || sMonth == 5 || sMonth == 7 || sMonth == 8 || sMonth == 10 || sMonth == 12){
                sDay = rand() % ((31+1)-day) + day;
            }else if(sMonth == 2){
                if((year % 4 == 0 ) && (year % 100 == 0) || (year % 400 == 0)){
                    sDay = rand() % ((29+1)-day) + day;
                }else{
                    sDay = rand() % ((28+1)-day) + day;
                }
            }else{
                sDay = rand() % ((30+1)-day) + day;
            }
            //qDebug() << "Days range: " << daysRange << ", day: " << sDay << ", sMonth: " << sMonth << '\n';
            startDate = QDate(year,sMonth,sDay);
            endDate = startDate.addDays(daysRange);
            //qDebug() << "Start date: " << startDate.toString("dd/MM/yyyy") << ", end date: " << endDate.toString("dd/MM/yyyy") << '\n';
       }while(!avaiable(reservations,startDate,endDate));
       User *user = new User("Test","Test","Test@test.pl","123123123");
       Reservation *reserv = new Reservation(startDate,endDate,user);
       reservations.push_back(reserv);
   }
   return reservations;
}

//17.05.2017 do napisania na oknie
bool Helper::avaiable(QVector<Reservation*> reservations, QDate start, QDate end){
    bool availability = false;
    if(start.year() != end.year()){
        return false;
    }
    if(!reservations.empty()){
        QDate endOfTheYear(QDate::currentDate().year(),12,31);
        int startDateDaysToEnd = start.daysTo(endOfTheYear);
        int endDateDaysToEnd = end.daysTo(endOfTheYear);
        for(Reservation *reservation : reservations){
            QDate startDateReserv = reservation->startDate();
            QDate endDateReserv = reservation->endDate();
            if(start == endDateReserv){
                availability = true;
            }else{
                int reservationStartDateDays = startDateReserv.daysTo(endOfTheYear);
                int reservationEndDateDays = endDateReserv.daysTo(endOfTheYear);
                if((reservationStartDateDays >= startDateDaysToEnd) && (reservationEndDateDays < startDateDaysToEnd) ||
                        (reservationStartDateDays > endDateDaysToEnd) && (reservationEndDateDays <= endDateDaysToEnd)){
                    availability = false;
                    break;
                }else{
                    availability = true;
                }
            }
        }
    }else{
        availability = true;
    }
    return availability;
}

QList<QObject*> Helper::temporaryRooms(QString hotelName){
    QList<QObject*> tempRooms;
    for(int i=1;i<=10;i++){
        QString roomName = QString(hotelName + "%1").arg(i);
        Room *room = new Room(roomName,100.0,5);
        //qDebug() << room->name() << '\n';
        room->setDesc("Lorem ipsum dolor sit amet, consectetur adipiscing elit. \
                       Integer diam nibh, molestie aliquet gravida quis, pellentesque quis diam. Nunc pretium diam tristique ante vestibulum bibendum. \
                       Morbi enim nibh, maximus a neque vitae, tempor finibus lectus. Curabitur ac arcu vestibulum, vulputate ligula eget, blandit ligula");
        QVector<Reservation*> reservations = createReservations();
        for(Reservation* reserv : reservations){
            qDebug() << reserv->startDate().toString("dd/MM/yyyy") << " " << reserv->endDate().toString("dd/MM/yyyy") << '\n';
            room->addReservation(reserv);
        }
        tempRooms.append(room);
    }
    return tempRooms;
}
