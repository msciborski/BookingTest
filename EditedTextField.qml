import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.1
Item {
    /*properties*/
    property real widthProperty
    property real heightPropert
    property string placeHolder
    property string textProperty
    property string regex

    width: widthProperty
    height: heightPropert

    function check() {
        if(textField.text == "") {
            ToolTip.show(qsTr("This field cannot be empty."));
            return false;
        }else if(!textField.text.toString().match(regex)){
            ToolTip.show(qsTr("Wrong data."));
            return false;
        }

        return true;
    }
    TextField{
        id: textField
        width: parent.width
        height: parent.height
        placeholderText: placeHolder
        text: textProperty
//        onFocusChanged: {
//            check()
//        }

//        onEditingFinished: {
//            check()
//        }
    }






}
