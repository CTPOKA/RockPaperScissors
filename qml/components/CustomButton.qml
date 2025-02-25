import QtQuick 2.15
import QtQuick.Controls 2.15

Button {
    id: button
    width: 300
    height: 50

    background: Rectangle {
        radius: 10
        border.color: "white"
        border.width: 2

        gradient: Gradient {
            GradientStop { position: 0.0; color: button.pressed ? "#004BA0" : "#2196F3" }
            GradientStop { position: 1.0; color: button.pressed ? "#002F6C" : "#1976D2" }
        }
    }

    contentItem: Text {
        text: button.text
        font.pixelSize: 16
        font.bold: true
        color: "white"
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

    onClicked: {
        clickSound.play()
    }
}
