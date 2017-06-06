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
    property alias text: textField.text
    width: widthProperty
    height: heightPropert
    function check() {
        console.log(text)
        if(textField.text == "") {
            //textField.forceActiveFocus()
            ToolTip.show("Empty field",500)
            return false;
        }
        if(!textField.text.toString().match(regex)){
            //textField.forceActiveFocus()
            ToolTip.show("Incorrect data.",500)
            return false;
        }
        ToolTip.hide();
        return true;
    }
    TextField{
        id: textField
        width: parent.width
        height: parent.height
        placeholderText: placeHolder
        onDisplayTextChanged: {
            check()
        }
    }







}
