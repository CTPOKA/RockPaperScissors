import QtQuick 2.15
import QtQuick.Controls 2.15
import Qt5Compat.GraphicalEffects

Text {
    id: textElement
    property color outlineColor: "black"
    property int outlineRadius: 3
    property real outlineSpread: 1
    property int outlineSamples: 8

    font.pixelSize: 24
    font.bold: true
    color: "white"

    layer.enabled: true
    layer.effect: DropShadow {
        color: textElement.outlineColor
        radius: textElement.outlineRadius
        spread: textElement.outlineSpread
        samples: textElement.outlineSamples
    }
}
