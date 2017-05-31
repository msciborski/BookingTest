#include "helper.h"
/*Static class, which creates cities, hotels, rooms, and some reservations. Every method is static, cuz class dosent contain infomration.
This is typicall utilty class.*/
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
//Creating Cities
QList<QObject*> Helper::createCity(QObject *parent){
    QList<QObject*> tempCity;
    City *poznan = new City(parent, "Poznań");
    poznan->setListHotels(Helper::temporaryHotels(parent, poznan->cityName()));
//    poznan->listHotels().append(Helper::temporaryRooms(poznan->cityName()));
    City *warszawa = new City(parent, "Warszawa");
    warszawa->setListHotels(Helper::temporaryHotels(parent, warszawa->cityName()));
    //warszawa->listHotels().append(Helper::temporaryRooms(warszawa->cityName()));
    City *krakow = new City(parent, "Kraków");
    krakow->setListHotels(Helper::temporaryHotels(parent, krakow->cityName()));
    //krakow->listHotels().append(Helper::temporaryRooms(krakow->cityName()));
    City *gdansk = new City(parent, "Gdańsk");
    gdansk->setListHotels(Helper::temporaryHotels(parent, gdansk->cityName()));
    //gdansk->listHotels().append(Helper::temporaryRooms(gdansk->cityName()));
    City *sopot = new City(parent, "Sopot");
    sopot->setListHotels(Helper::temporaryHotels(parent, sopot->cityName()));
    //sopot->listHotels().append(Helper::temporaryRooms(sopot->cityName()));
    City *lodz = new City(parent, "Łódź");
    lodz->setListHotels(Helper::temporaryHotels(parent, lodz->cityName()));
    //lodz->listHotels().append(Helper::temporaryRooms(lodz->cityName()));
    tempCity.append(poznan);
    tempCity.append(warszawa);
    tempCity.append(krakow);
    tempCity.append(gdansk);
    tempCity.append(sopot);
    tempCity.append(lodz);

    return tempCity;
}
//Creating hotels
QList<QObject*> Helper::temporaryHotels(QObject *parent, QString cityName){
    QList<QObject*> tempHotels;
    for(int i=1;i<=5;i++){
        QString hotelName = QString(cityName + "%1").arg(i);
        QString address = QString("ul. %1 %2").arg(cityName).arg(i);
        Hotel *hotel = new Hotel(parent, hotelName,address);
        hotel->setListRooms(Helper::temporaryRooms(parent, hotelName));
        tempHotels.append(hotel);
    }
    return tempHotels;
}
//Refactor, bo QDate ma funckje daysInMonth-
QVector<Reservation*> Helper::createReservations(QObject *parent){
   QVector<Reservation*> reservations;
   QDate currentDate = QDate::currentDate();
   QDate endOfTheYear = QDate(currentDate.year(),12,31);
   int daysToEnd = currentDate.daysTo(endOfTheYear);
   for(int i=0;i<15;i++){
       QDate startDate;
       QDate endDate;
       int daysRange;
       do{
           daysRange = rand() % ((8+1)-1)+1;
           int daysToAddToCurrent = rand() % ((daysToEnd-0)-0) + 0;
           startDate = currentDate.addDays(daysToAddToCurrent);
           endDate = startDate.addDays(daysRange);

       }while(!avaiable(reservations,startDate,endDate));
       User *user = new User(parent, "Test","Test","Test@test.pl","123123123");
       Reservation *reserv = new Reservation(parent, startDate,endDate,user);
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

QList<QObject*> Helper::temporaryRooms(QObject *parent, QString hotelName){
    QList<QObject*> tempRooms;
    for(int i=1;i<=10;i++){
        QString roomName = QString(hotelName + "%1").arg(i);
        Room *room = new Room(parent, roomName,100.0,5);
        //qDebug() << room->name() << '\n';
        room->setDesc("Lorem ipsum dolor sit amet, consectetur adipiscing elit. \
                       Integer diam nibh, molestie aliquet gravida quis, pellentesque quis diam. Nunc pretium diam tristique ante vestibulum bibendum. \
                       Morbi enim nibh, maximus a neque vitae, tempor finibus lectus. Curabitur ac arcu vestibulum, vulputate ligula eget, blandit ligula");
        QVector<Reservation*> reservations = createReservations(parent);
        for(Reservation* reserv : reservations){
            qDebug() << reserv->startDate().toString("dd/MM/yyyy") << " " << reserv->endDate().toString("dd/MM/yyyy") << '\n';
            room->addReservation(reserv);
        }
        tempRooms.append(room);
    }
    return tempRooms;
}
