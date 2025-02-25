import QtQuick 2.15
import Qt5Compat.GraphicalEffects

Item {
    width: 30
    height: 10

    Repeater {
        model: 3
        Rectangle {
            width: 5
            height: 5
            radius: width / 2
            color: "white"
            opacity: 0
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: index * 8

            SequentialAnimation on opacity {
                running: true
                loops: Animation.Infinite

                PauseAnimation { duration: index * 300 }
                NumberAnimation { from: 0; to: 1; duration: 500; easing.type: Easing.InOutQuad }
                NumberAnimation { from: 1; to: 0; duration: 500; easing.type: Easing.InOutQuad }
            }

            layer.enabled: true
            layer.effect: DropShadow {
                color: "black"
                radius: 2
                spread: 1
                samples: 8
            }
        }
    }
}
