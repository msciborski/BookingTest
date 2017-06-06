import QtQuick 2.0
import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.1
import QtGraphicalEffects 1.0
Item {
    FontLoader{
        id: robotoBold
        source: Qt.resolvedUrl("Fonts/Roboto-Bold.ttf")
    }
    FontLoader{
        id: robotoLight
        source: Qt.resolvedUrl("Fonts/Roboto-Light.ttf")
    }
    FontLoader{
        id: robotoRegular
        source: Qt.resolvedUrl("Fonts/Roboto-Regular.ttf")
    }
    FontLoader{
        id: robotMedium
        source: Qt.resolvedUrl("Fonts/Roboto-Medium.ttf")
    }

    id: root
    visible: true
    width: 640
    height: 600
    /*shadows*/
    DropShadow {
        id: appBarShadow
        source: appBar
        anchors.fill: source
        width: source.width
        height: source.height
        cached: true
        radius: 8.0
        samples: 16
        color: "#80000000"
        smooth: true
    }
    DropShadow {
        id: hotelSectionShadow
        source: hotelSearchSection
        verticalOffset: 3
        anchors.fill: source
        width: source.width
        height: source.height
        cached: true
        radius: 8.0
        samples: 16
        color: "#80000000"
        smooth: true
    }
    InnerShadow{
        id: infoSectionInnerShadow
        source: infoSection
        cached: true
        anchors.fill: source
        horizontalOffset: 0
        verticalOffset: 0
        radius: 8
        samples: 16
        color: "#80000000"
        smooth: true
    }

    DropShadow {
        id: infoSectionShadow
        source: infoSection
        verticalOffset: 3
        anchors.fill: source
        width: source.width
        height: source.height
        cached: true
        radius: 8.0
        samples: 16
        color: "#80000000"
        smooth: true
    }
    /*Header app Bar*/
    Row{
        id: appBar
        width: root.width
        height: root.height/10
        Rectangle{
            z:2
            width: parent.width
            height: parent.height
            color: Material.color(Material.Lime, Material.Shade400)
            Label{
                anchors.left: parent.left
                anchors.verticalCenter: parent.verticalCenter
                anchors.leftMargin: 20
                font.family: robotMedium.name
                font.pixelSize: 30
                color: "white"
                text: "Booking Hotel"

            }

        }
    }
    /*Section where we select particular hotel, date, city etc.*/
    Column{
        id: hotelSearchSection
        anchors.top: appBar.bottom
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.topMargin: 10
        anchors.rightMargin: 10
        anchors.bottomMargin: 10
        width: root.width/2-20
        height: root.height - appBar.height-20
        Pane{
            width: parent.width
            height: parent.height
            Material.elevation: 3
            spacing: 5
            Label{
                anchors.topMargin: 15
                anchors.bottomMargin: 10
                id: rootLabel
                font.family: robotoLight.name
                font.pixelSize: 20
                text: qsTr("Wybierz:")
            }

            ComboBox{
                id: cityCB
                width: root.width/5.3
                height: root.height/11
                anchors.top: rootLabel.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                displayText: viewModel.listCities[currentIndex].cityName
                model: viewModel.listCities
                currentIndex: viewModel.cityIndex
                textRole: "cityName"
                onActivated: {
                    viewModel.cityIndex = index
                    console.log("City index: " + viewModel.cityIndex + ", hotel index: " + viewModel.hotelIndex + ", room index: " + viewModel.roomIndex)
                }

            }
            ComboBox{
                id: hotelCB
                width: root.width/5.3
                height: root.height/11
                anchors.top: cityCB.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                model: viewModel.listCities[cityCB.currentIndex].listHotels
                currentIndex: viewModel.hotelIndex
                displayText: viewModel.listCities[cityCB.currentIndex].listHotels[viewModel.hotelIndex].name
                textRole: "name"
                onActivated: {
                    viewModel.hotelIndex = index
                    //console.log("Selected index: " + index + ", hotel name: " + viewModel.listCities[index].cityName + ", " + viewModel.cityIndex)
                    console.log("City index: " + viewModel.cityIndex + ", hotel index: " + viewModel.hotelIndex + ", room index: " + viewModel.roomIndex)
                }
            }
            ComboBox{
                id: roomCB
                width: root.width/5.3
                height: root.height/11
                anchors.top: hotelCB.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                currentIndex: viewModel.roomIndex
                model: viewModel.listCities[viewModel.cityIndex].listHotels[viewModel.hotelIndex].listRooms
                displayText: viewModel.listCities[viewModel.cityIndex].listHotels[viewModel.hotelIndex].listRooms[viewModel.roomIndex].name
                textRole: "name"
                onActivated: {
                    viewModel.roomIndex = index
                    console.log("City index: " + viewModel.cityIndex + ", hotel index: " + viewModel.hotelIndex + ", room index: " + viewModel.roomIndex)
                }
            }
            ComboBox{
                id: startDateCB
                width: root.width/5.3
                height: root.height/11
                anchors.top: roomCB.bottom
                model: viewModel.startDates
                anchors.horizontalCenter: parent.horizontalCenter
                onActivated: {
                    viewModel.startDateIndex = index
                    console.log(viewModel.startDateIndex)
                    viewModel.setEndDate()
                    viewModel.checkAvailability()
                }
            }
            ComboBox{
                id: endDateCB
                width: root.width/5.3
                height: root.height/11
                anchors.top: startDateCB.bottom
                model: viewModel.endDates
                anchors.horizontalCenter: parent.horizontalCenter
                onActivated: {
                    viewModel.endDateIndex = index
                    viewModel.checkAvailability()
                }
            }

            Button{
                id: makeReservationBTN
                anchors.top: endDateCB.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                text: qsTr("REZERWUJ")
                font.family: robotMedium.name
                highlighted: true
                enabled: viewModel.buttonVisibility
                Material.accent: Material.Pink
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        viewModel.indexView = 1
                        viewModel.calculateTotalPrice()
                    }
                }
            }
            Label{
                id: avaiableInformationLabel
                anchors.top: makeReservationBTN.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                font.family: robotoRegular.name
                text: qsTr(viewModel.label)
                font.pixelSize: 10
            }
        }

    }
    Column{
        id: infoSection
        anchors.top: appBar.bottom;
        anchors.topMargin: 10
        anchors.bottomMargin: 10
        anchors.rightMargin: 10
        anchors.leftMargin: 0
        anchors.left: hotelSearchSection.right
        anchors.right: parent.right
        width: root.width/2-10
        height: root.height - appBar.height-20
        Pane{
            width: parent.width
            height: parent.height
            Material.elevation: 10
            Label{
                id: detailsLabel
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.topMargin: 10
                font.family: robotoLight.name
                font.pixelSize: 20
                text: qsTr("Detale:")
            }
            Pane{
                id: hotelImage
                width: parent.width/2
                height: 100
                anchors.top: detailsLabel.bottom
                padding: 0
                anchors.topMargin: 10
                anchors.left: parent.left
                Material.elevation:8
                Rectangle{
                    id: hotelImageContent
                    anchors.fill: parent
                    color: "red"
                }
            }

            Pane{
                id: roomImage
                width: parent.width/2
                height: 100
                padding: 0
                anchors.top: detailsLabel.bottom
                anchors.topMargin: 10
                anchors.left: hotelImage.right
                Material.elevation: 8
                Rectangle{
                    anchors.fill: parent
                    color: "purple"
                }
            }

            Grid{
                id: detailsGrid
                anchors.top: roomImage.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.topMargin: 10
                columns: 2
                rows: 5
                spacing: 20
                Label{
                    id: cityName
                    font.family: robotMedium.name
                    text: qsTr("Miasto:")
                }
                Label{
                    id: cityNameValue
                    font.family: robotoRegular.name
                    text: qsTr(viewModel.listCities[viewModel.cityIndex].cityName)
                }
                Label{
                    id: hotelName
                    font.family: robotMedium.name
                    text: qsTr("Hotel:")
                }
                Label{
                    id:hotelNameValue
                    font.family: robotoRegular.name
                    text: qsTr(viewModel.listCities[viewModel.cityIndex].listHotels[viewModel.hotelIndex].name)
                }
                Label{
                    id: hotelAddress
                    font.family: robotMedium.name
                    text: qsTr("Adres:")
                }
                Label{
                    id: hotelAddressValue
                    font.family: robotoRegular.name
                    text: qsTr(viewModel.listCities[viewModel.cityIndex].listHotels[viewModel.hotelIndex].address)
                }
                Label{
                    id: capacity
                    font.family: robotMedium.name
                    text: qsTr("Ilość miejsc:")
                }
                Label{
                    id: capcityValue
                    font.family: robotoRegular.name
                    text: viewModel.listCities[viewModel.cityIndex].listHotels[viewModel.hotelIndex].listRooms[viewModel.roomIndex].capacity

                }
                Label{
                    id: cost
                    font.family: robotMedium.name
                    text: qsTr("Cena:")
                }
                Label{
                    id: costValue
                    font.family: robotoRegular.name
                    text: viewModel.listCities[viewModel.cityIndex].listHotels[viewModel.hotelIndex].listRooms[viewModel.roomIndex].cost

                }
            }
            Label{
                id: description
                anchors.top: detailsGrid.bottom
                anchors.topMargin: 15
                anchors.left: parent.left
                anchors.horizontalCenter: parent.horizontalCenter
                wrapMode: Text.Wrap
                font.family: robotoRegular.name
                text: qsTr(viewModel.listCities[viewModel.cityIndex].listHotels[viewModel.hotelIndex].listRooms[viewModel.roomIndex].desc)

            }
        }

    }

}
