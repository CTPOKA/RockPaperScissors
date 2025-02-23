import QtQuick 2.15
import QtQuick.Controls 2.15

Page {
    title: "Подключение к комнате"

    Column {
        anchors.centerIn: parent
        spacing: 20

        CustomTextField {
            id: ipField
            placeholderText: "Введите IP сервера"
            anchors.horizontalCenter: parent.horizontalCenter

            CustomText {
                id: statusText
                font.pixelSize: 16
                font.bold: true
                text: ""
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.bottom
            }
        }

        CustomButton {
            text: "Подключиться"
            onClicked: {
                networkManager.connectToServer(ipField.text)
            }
        }

        Connections {
            target: networkManager
            function onPlayerConnected() {
                statusText.text = ""
                stackView.push(gamePage)
            }
            function onConnectionFailed() {
                statusText.text = "Ошибка подключения!"
                statusText.color = "pink"
            }
            function onPlayerDisconnected() {
                statusText.text = "Потеряно соединение"
                statusText.color = "pink"
            }
        }

        CustomButton {
            text: "Назад"
            onClicked: stackView.pop()
        }
    }
}
