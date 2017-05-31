import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.1
Item {
    property bool showTooltip
    /*properties*/
    property real widthProperty
    property real heightPropert
    property string placeHolder
    property string textProperty
    property string regex
    width: widthProperty
    height: heightPropert
    function check() {
        if(textField.text == "" && showTooltip) {
            ToolTip.show(qsTr("This field cannot be empty."));

            return false;
        }else if(!textField.text.toString().match(regex) && showTooltip){
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
//        onEditingFinished: {
//            check()
//        }

        onFocusChanged: {
            check()
        }

//        onEditingFinished: {
//            check()
//        }
    }






}
