import QtQuick 2.15
import QtQuick.Controls 2.15
import RockPaperScissors 1.0

Page {
    title: "Главное меню"

    Column {
        anchors.centerIn: parent
        spacing: 20

        CustomButton {
            text: "Создать комнату"
            onClicked: stackView.push(createRoom)
        }

        CustomButton {
            text: "Подключиться к комнате"
            onClicked: stackView.push(joinRoom)
        }
    }
}
