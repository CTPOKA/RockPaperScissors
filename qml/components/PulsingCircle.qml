import QtQuick 2.15

Item {
    id: root
    property bool active: false
    property color circleColor: "lightblue"
    property int minSize: 60
    property int maxSize: 100
    property real minOpacity: 0.2
    property real maxOpacity: 0.5

    width: maxSize
    height: maxSize

    Rectangle {
        id: circle
        width: size
        height: size
        radius: size / 2
        color: circleColor
        opacity: maxOpacity
        anchors.centerIn: parent
        visible: active

        property int size: minSize

        SequentialAnimation {
            id: pulseAnimation
            running: active
            loops: Animation.Infinite

            ParallelAnimation {
                NumberAnimation { target: circle; property: "size"; from: minSize; to: maxSize; duration: 500; easing.type: Easing.InOutQuad }
                NumberAnimation { target: circle; property: "opacity"; from: maxOpacity; to: minOpacity; duration: 500; easing.type: Easing.InOutQuad }
            }
            ParallelAnimation {
                NumberAnimation { target: circle; property: "size"; from: maxSize; to: minSize; duration: 500; easing.type: Easing.InOutQuad }
                NumberAnimation { target: circle; property: "opacity"; from: minOpacity; to: maxOpacity; duration: 500; easing.type: Easing.InOutQuad }
            }
        }
    }
}
