import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.15

import "components"

ApplicationWindow {
    id: window

    minimumWidth: 600
    minimumHeight: 600
    width: 600
    height: 800
    visible: true
    title: Qt.application.name + " " + Qt.application.version

    Material.theme: Material.Dark
    Material.accent: Material.Purple
    ColumnLayout{
        anchors.fill: parent
        anchors.margins: 20
        spacing: 20
        ColumnLayout{
            spacing: 20
            Layout.fillWidth: true
            Layout.fillHeight: true
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
        Item{
            Layout.fillWidth: true
            Layout.fillHeight: true
            ColumnLayout{
                anchors.fill: parent
                spacing: 20
                ListView{
                    id: lvPlayList
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    model: 20
                    clip: true
                    delegate: Rectangle{
                        width: lvPlayList.width
                        height: 40
                        color:  Material.color(Material.Grey, Material.Shade800)

                        Label{
                            id: lblMediaNumber
                            anchors.left: parent.left
                            anchors.leftMargin: 20
                            anchors.verticalCenter: parent.verticalCenter
                            text: index
                        }
                        Item{
                            anchors.top: parent.top
                            anchors.left: lblMediaNumber.right
                            anchors.leftMargin: 20
                            anchors.right: lblMediaDuration.left
                            anchors.rightMargin: 20
                            anchors.bottom: parent.bottom
                            Label{
                                id: lblMediaTitleAndAuthor
                                anchors.centerIn: parent
                                text: "Title" + " - " + "Artist"
                            }
                        }
                        Label{
                            id: lblMediaDuration
                            anchors.right: parent.right
                            anchors.rightMargin: 20
                            anchors.verticalCenter: parent.verticalCenter
                            text: "00:00"
                        }
                        Rectangle{
                            anchors.left: parent.left
                            anchors.right: parent.right
                            anchors.bottom: parent.bottom

                            height: 2
                            color: Material.color(Material.Grey, Material.Shade700)
                        }
                    }
                }
                Rectangle{
                    id: rctPlaylistControlSection
                    Layout.fillWidth: true
                    Layout.preferredHeight: 50
                    color: Material.color(Material.Grey, Material.Shade800)
                    RowLayout{
                        anchors.fill: parent
                        spacing: 10
                        Item{
                            Layout.fillWidth: true
                            Layout.fillHeight: true
                        }
                        ButtonImage{
                            id: btnAddMedia
                            source: "qrc:/icons/add"
                            onReleased: {
                                console.log("add")
                            }
                        }
                        ButtonImage{
                            id: btnRemoveMedia
                            source: "qrc:/icons/delete"
                            onReleased: {
                                console.log("delete")
                            }
                        }
                    }
                }
            }
        }
    }
}
