import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.15

import "../components"

ColumnLayout{
    width: parent.width
    height: parent.height
    spacing: 20
    Rectangle{
        color: Material.color(Material.Grey, Material.Shade800)
        Layout.fillWidth: true
        Layout.preferredHeight: 200
        RowLayout{
            anchors.fill: parent
            anchors.margins: 20
            spacing: 20
            Rectangle{
                Layout.preferredWidth: height
                Layout.fillHeight: true
                color: "transparent"
                border.width: 2
                border.color: "white"
                Label{
                    anchors.centerIn: parent
                    text: "Album\nImage"
                }
            }
            Rectangle{
                Layout.fillWidth: true
                Layout.fillHeight: true
                color: "transparent"
                border.width: 2
                border.color: "white"
                Label{
                    anchors.centerIn: parent
                    text: "Equalizer"
                }
            }
        }
    }
    Item{
        Layout.fillWidth: true
        Layout.preferredHeight: 20
        Slider{
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.verticalCenter: parent.verticalCenter
        }
    }
    Item{
        Layout.fillWidth: true
        Layout.preferredHeight: 50
        RowLayout{
            anchors.fill: parent
            Rectangle{
                id: rctControlSection
                Layout.fillHeight: true
                Layout.preferredWidth: 250
                color: Material.color(Material.Grey, Material.Shade800)
                RowLayout{
                    anchors.fill: parent
                    spacing: 10
                    ButtonImage{
                        id: btnPreviose
                        source: "qrc:/icons/previose"
                        onReleased: {
                            console.log("previose")
                        }
                    }
                    ButtonImage{
                        id: btnPlay
                        source: "qrc:/icons/play"
                        onReleased: {
                            console.log("play")
                        }
                    }
                    ButtonImage{
                        id: btnStop
                        source: "qrc:/icons/stop"
                        onReleased: {
                            console.log("stop")
                        }
                    }
                    ButtonImage{
                        id: btnNext
                        source: "qrc:/icons/next"
                        onReleased: {
                            console.log("next")
                        }
                    }
                }
            }
            Item{
                id: rctVolumeSection
                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.leftMargin: 20
                RowLayout{
                    anchors.fill: parent
                    spacing: 10
                    ButtonImage{
                        Layout.preferredWidth: 40
                        Layout.preferredHeight: 40
                        source: "qrc:/icons/volume-up"
                    }
                    Slider{
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                    }
                }
            }
        }
    }
}
