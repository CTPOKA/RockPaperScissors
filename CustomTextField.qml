import QtQuick 2.15
import QtQuick.Controls 2.15

TextField {
    id: textField
    width: 300
    height: 50
    font.pixelSize: 16
    font.bold: true
    color: "#263238"
    padding: 0

    background: Rectangle {
        radius: 10
        border.width: 2
        border.color: textField.focus ? "#64B5F6" : "#BBDEFB"

        gradient: Gradient {
            GradientStop { position: 0.0; color: "#E3F2FD" }
            GradientStop { position: 1.0; color: "#BBDEFB" }
        }

        Behavior on border.color {
            ColorAnimation { duration: 200 }
        }
    }

    horizontalAlignment: TextInput.AlignHCenter
    verticalAlignment: TextInput.AlignVCenter

    placeholderText: qsTr("Введите текст...")
    placeholderTextColor: "#607D8B"

    cursorDelegate: Rectangle {
        width: 2
        color: "#263238"
    }
}
