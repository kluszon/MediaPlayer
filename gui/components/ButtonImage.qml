import QtQuick 2.15
import QtGraphicalEffects 1.15
import QtQuick.Controls.Material 2.15

Image{
    id: control
    signal released()
    width: 50
    height: width
    source: "qrc:/icons/next"
    ColorOverlay {
        anchors.fill: parent
        source: parent
        color: Material.color(Material.Purple, Material.Shade200)
    }
    states: State{
        name: "pressed"
        when: areaImage.pressed
        PropertyChanges {
            target: control
            scale: 0.90
        }
    }
    MouseArea{
        id: areaImage
        anchors.fill: parent
        onReleased: {
            control.released()
        }
    }
}
