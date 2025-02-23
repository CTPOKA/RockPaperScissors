import QtQuick 2.15
import QtQuick.Controls 2.15
import QtMultimedia 6.8

ApplicationWindow {
    visible: true
    width: 400
    height: 600
    title: "Камень, ножницы, бумага"

    StackView {
        id: stackView
        anchors.fill: parent
        initialItem: mainMenu
    }

    Component {
        id: mainMenu
        MainMenu { }
    }

    Component {
        id: createRoom
        CreateRoom { }
    }

    Component {
        id: joinRoom
        JoinRoom { }
    }

    Component {
        id: gamePage
        Game { }
    }

    SoundEffect {
        id: winSound
        source: "qrc:/sounds/win"
        volume: 0.5
    }

    SoundEffect {
        id: loseSound
        source: "qrc:/sounds/lose"
        volume: 0.5
    }

    SoundEffect {
        id: clickSound
        source: "qrc:/sounds/click"
        volume: 0.5
    }
}
