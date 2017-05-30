import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.1
Item {
    property real widthProperty
    property real heightPropert
    property string placeHolder
    property string textProperty
    width: widthProperty
    height: heightPropert

    function check() {
        if(textField.text == "") {
            ToolTip.show(qsTr("This field cannot be empty."));
            forceActiveFocus();
            return false;
        }else if(!textField.text.toString().match("[^\\000-\\037\\041-@]+")){
            ToolTip.show(qsTr("Wrong data."));
            return false;
        }

        return true;
    }
    TextField{
        id: textField
        width: parent.width
        height: parent.height
        placeholderText: "Test"
        text: textProperty
        onEditingFinished: {
            check()
        }
    }






}
