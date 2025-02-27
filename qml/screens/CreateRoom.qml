import QtQuick 2.15
import QtQuick.Controls 2.15
import RockPaperScissors 1.0

Page {
    title: "Создание комнаты"

    Component.onCompleted: {
        networkManager.startServer()
    }

    Column {
        anchors.centerIn: parent
        spacing: 20

        Item {
            width: statusText.width
            height: statusText.height + 5
            anchors.horizontalCenter: parent.horizontalCenter

            CustomText {
                id: statusText
                text: "Ожидание подключения"
                font.pixelSize: 16
                font.bold: true
            }

            LoadingDots {
                id: loadingDots
                anchors.horizontalCenter: statusText.horizontalCenter
                anchors.top: statusText.bottom
            }
        }

        Column {
            CustomText {
                text: "IP сервера:"
                font.pixelSize: 16
                font.bold: true
                color: "lightblue"
                anchors.horizontalCenter: parent.horizontalCenter
            }

            CustomTextField {
                text: networkManager.getLocalIp()
                readOnly: true
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }

        Connections {
            target: networkManager
            function onServerError(Message) {
                statusText.text = Message
                loadingDots.visible = false
                statusText.color = "pink"
            }
            function onPlayerConnected() {
                statusText.text = ""
                stackView.push(gamePage)
            }
            function onDisconnected() {
                statusText.text = "Игрок отключился"
                loadingDots.visible = false
                statusText.color = "pink"
            }
        }

        CustomButton {
            text: "Назад"
            onClicked: {
                networkManager.disconnect()
                stackView.pop()
            }
        }
    }
}
