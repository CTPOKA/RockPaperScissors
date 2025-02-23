import QtQuick 2.15
import QtQuick.Controls 2.15
import Qt5Compat.GraphicalEffects

Page {
    title: "Игра"
    property string lastChoice: ""

    Column {
        anchors.centerIn: parent
        spacing: 20

        CustomText {
            id: scoreText
            text: gameLogic.playerScore + " - " + gameLogic.opponentScore
            font.pixelSize: 22
            font.bold: true
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Item {
            width: 80
            height: 80
            anchors.horizontalCenter: parent.horizontalCenter

            Image {
                id: opponentChoiceImage
                source: ""
                width: parent.width
                height: parent.height
                smooth: true
                opacity: 0

                layer.enabled: true
                layer.effect: DropShadow {
                    color: "red"
                    radius: 3
                    spread: 0.3
                    samples: 8
                }
            }
        }

        Item {
            id: vsIcon
            width: 40
            height: 40
            opacity: 0
            anchors.horizontalCenter: parent.horizontalCenter

            Rectangle {
                anchors.fill: parent
                radius: 20
                color: "blue"
            }

            CustomText {
                anchors.centerIn: parent
                text: "VS"
                font.pixelSize: 22
                color: "white"
                font.bold: true
            }
        }

        Row {
            spacing: 20
            anchors.horizontalCenter: parent.horizontalCenter

            Repeater {
                model: ListModel {
                    ListElement { name: "rock"; source: "qrc:/images/rock" }
                    ListElement { name: "scissors"; source: "qrc:/images/scissors" }
                    ListElement { name: "paper"; source: "qrc:/images/paper" }
                }

                delegate: Item {
                    width: 80
                    height: 80

                    PulsingCircle {
                        objectName: model.name
                        anchors.centerIn: parent
                        active: lastChoice === model.name
                    }

                    Image {
                        id: choiceImage
                        source: model.source
                        width: parent.width
                        height: parent.height
                        smooth: true

                        layer.enabled: lastChoice === model.name
                        layer.effect: DropShadow {
                            color: "blue"
                            radius: 3
                            spread: 0.3
                            samples: 8
                        }
                    }

                    MouseArea {
                        anchors.fill: parent
                        enabled: !networkManager.choiceMade
                        onClicked: {
                            networkManager.sendChoice(model.name)
                            clickSound.play()
                        }
                    }
                }
            }
        }

        CustomText {
            id: resultText
            text: " "
            font.pixelSize: 18
            color: "lightblue"
            anchors.horizontalCenter: parent.horizontalCenter
        }

        CustomText {
            id: statusText
            text: networkManager.choiceMade ? "Ожидание хода соперника..." : "Выберите свой ход"
            font.pixelSize: 16
            anchors.horizontalCenter: parent.horizontalCenter
        }

        CustomButton {
            text: "Выйти"
            anchors.horizontalCenter: parent.horizontalCenter
            onClicked: {
                networkManager.disconnect()
                stackView.pop()
            }
        }
    }

    Connections {
        target: gameLogic

        function onGameResult(result) {
            resultText.text = result
        }

        function onFinalWinner(isPlayerWinner) {
            if (isPlayerWinner) {
                resultText.text = "Вы выиграли матч!"
                resultText.color = "lightgreen"
                winSound.play()
            } else {
                resultText.text = "Вы проиграли матч!"
                resultText.color = "pink"
                loseSound.play()
            }
            statusText.text = "Игра завершена!"
        }

        function onScoreUpdated() {
            opponentChoiceImage.source = "qrc:/images/" + networkManager.opponentChoice
            opponentChoiceImage.opacity = 1
            vsIcon.opacity = 1
        }
    }

    Connections {
        target: networkManager

        function onPlayerDisconnected() {
            stackView.pop()
        }

        function onChoiceUpdated() {
            if (networkManager.playerChoice) {
                resultText.text = " "
                vsIcon.opacity = 0
                opponentChoiceImage.opacity = 0
                lastChoice = networkManager.playerChoice
            }
        }
    }
}
