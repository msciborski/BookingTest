import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.1
import QtGraphicalEffects 1.0

Item {
    id: confirmRoot
    visible: true
    width: 640
    height: 600
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

    Row{
        id: appBar
        width: confirmRoot.width
        height: confirmRoot.height/10
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
                text: robotMedium.status == FontLoader.Ready ? "Booking Hotel" : ""
            }
        }
    }

    Column{
        id: inputSection
        anchors.top: appBar.bottom
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.topMargin: 10
        anchors.rightMargin: 10
        anchors.bottomMargin: 10
        width: confirmRoot.width/2-20
        height: confirmRoot.height - appBar.height-20
        Pane{
            width: parent.width
            height: parent.height
            Material.elevation: 3
            spacing: 5
            Label{
                anchors.topMargin: 15
                anchors.bottomMargin: 10
                id: inputSectionLabel
                font.family: robotoLight
                font.pixelSize: 20
                text: robotoLight.status == FontLoader.Ready ? "Dane:" : ""
                Component.onCompleted: print(width, height)
            }
            EditedTextField{
                id: nameTextField
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top : inputSectionLabel.bottom
                widthProperty: confirmRoot.width/3.1
                heightPropert: confirmRoot.height/15
                placeHolder: qsTr("Imie")
                textProperty: viewModel.userName
                regex: qsTr("[^\\000-\\037\\041-@]+")
            }

//            TextField{
//                id: nameTextField
//                anchors.horizontalCenter: parent.horizontalCenter
//                anchors.top: inputSectionLabel.bottom
//                width: confirmRoot.width/3.1
//                height: confirmRoot.height/15
//                placeholderText: qsTr("Nazwisko");
//                text: viewModel.userName
//                validator: RegExpValidator{
//                    regExp: /\D+/
//                }
//            }
            EditedTextField{
                id:surnameTextField
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: nameTextField.bottom
                widthProperty: confirmRoot.width/3.1
                heightPropert: confirmRoot.height/15
                placeHolder: qsTr("Nazwisko")
                textProperty: viewModel.userSurname
                regex: qsTr("[^\\000-\\037\\041-@]+")
            }

//            TextField{
//                id: surnameTextField
//                anchors.horizontalCenter: parent.horizontalCenter
//                anchors.top: nameTextField.bottom
//                width: confirmRoot.width/3.1
//                height: confirmRoot.height/15
//                placeholderText: qsTr("Nazwisko");
//                text: viewModel.userSurname
//                validator: RegExpValidator{
//                    regExp: /\D+/
//                }
//            }
            EditedTextField{
                id: emailTextField
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: surnameTextField.bottom
                widthProperty: confirmRoot.width/3.1
                heightPropert: confirmRoot.height/15
                placeHolder: qsTr("Email")
                textProperty: viewModel.userEmail
                regex: qsTr("\\w+([-+.']\\w+)*@\\w+([-.]\\w+)*\\.\\w+([-.]\\w+)*")
            }
            EditedTextField{
                id:phoneNumberTextField
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: emailTextField.bottom
                widthProperty: confirmRoot.width/3.1
                heightPropert: confirmRoot.height/15
                placeHolder: qsTr("Numer")
                textProperty: viewModel.userPhoneNumber
                regex: qsTr("^[(]{0,1}[0-9]{3}[)]{0,1}[-\\s\\.]{0,1}[0-9]{3}[-\\s\\.]{0,1}[0-9]{4}$")
            }

            Row{
                id: buttons
                anchors.top: phoneNumberTextField.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                spacing: 10
                Button{
                    id:confirmButton
                    text: qsTr("Akceptuj");
                    width: 100
                    highlighted: true
                    Material.accent: Material.Pink
                    enabled: nameTextField.check() && surnameTextField.check() && emailTextField.check() && phoneNumberTextField.check()
                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            viewModel.createReservation();
                            viewModel.indexView = 0
                        }
                    }
                }
                Button{
                    id: backButon
                    text: qsTr("Powrót");
                    width:100
                    highlighted: true
                    Material.accent: Material.Pink
                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            viewModel.indexView = 0
                        }
                    }
                }
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
        anchors.left: inputSection.right
        anchors.right: parent.right
        width: confirmRoot.width/2-10
        height: confirmRoot.height - appBar.height-20
        Pane{
            width: parent.width
            height: parent.height
            Material.elevation: 10
            Label{
                anchors.topMargin: 15
                anchors.bottomMargin: 10
                id: infoSectionLabel
                font.family: robotoLight
                font.pixelSize: 20
                text: robotoLight.status == FontLoader.Ready ? qsTr("Podsumowanie:") : ""
                Component.onCompleted: print(width, height)
            }
            Grid{
                id: infoHotelGrid
                anchors.top: infoSectionLabel.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.topMargin:10
                columns:2
                rows: 3
                spacing:20
                Label{
                    id:hotelName
                    text: robotMedium.status == FontLoader.Ready ? qsTr("Hotel:") : ""
                }
                Label{
                    id:hotelNameValue
                    text: robotMedium.status == FontLoader.Ready ? qsTr(viewModel.listCities[viewModel.cityIndex].listHotels[viewModel.hotelIndex].name) : ""
                }
                Label{
                    id:roomName
                    text: robotMedium.status == FontLoader.Ready ? qsTr("Pokój:") : ""
                }

                Label{
                    id: roomNameValue
                    text: robotMedium.status == FontLoader.Ready ? qsTr(viewModel.listCities[viewModel.cityIndex].listHotels[viewModel.hotelIndex].listRooms[viewModel.roomIndex].name) : ""
                }
            }
            Grid{
                id: userInfoGrid
                anchors.top: infoHotelGrid.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.topMargin: 10
                columns: 1
                rows: 3
                Label{
                    id: nameSurnameLabel
                    text: robotoRegular.status == FontLoader.Ready ? qsTr(nameTextField.textProperty + " " + surnameTextField.textProperty) : ""
                }
                Label{
                    id: emailLabel
                    text: robotoRegular.status == FontLoader.Ready ? qsTr(emailTextField.textProperty) : ""
                }
                Label{
                    id: numberLabel
                    text: robotoRegular.status == FontLoader.Ready ? qsTr(phoneNumberTextField.textProperty) : ""
                }
            }
            Grid{
                id: bookingInfoGrid
                anchors.top: userInfoGrid.bottom
                anchors.topMargin:5
                anchors.horizontalCenter: parent.horizontalCenter
                columns: 2
                rows:3
                Label{
                    text: robotoRegular.status == FontLoader.Ready ? qsTr("Data rozpoczęcia:") : ""
                }
                Label{
                    text: robotoRegular.status == FontLoader.Ready ? qsTr(viewModel.startDates[viewModel.startDateIndex]) : ""
                }
                Label{
                    text: robotoRegular.status == FontLoader.Ready ? qsTr("Data zakończenia:") : ""
                }
                Label{
                    text: robotoRegular.status == FontLoader.Ready ? qsTr(viewModel.endDates[viewModel.endDateIndex]) : ""
                }

                Label{
                    text: robotoRegular.status == FontLoader.Ready ? "Do zapłaty:" : ""
                }

                Label{
                    id:priceLabel
                    text: robotoRegular.status == FontLoader.Ready ? viewModel.totalPrice : ""
                }
            }


        }
    }
}
