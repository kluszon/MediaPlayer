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
                    anchors.fill: parent
                    elide: Text.ElideRight
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    clip: true
                    text: mediaManager.currentPlayingMediaIndex >= 0 ? mediaManager.currentTitle + "\n- " + mediaManager.currentArtist : "Album\nImage"
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
            id: slrMediaTimePosition
            property int sliderScale: 1000

            function calculateNewPosition(){
                return value * sliderScale
            }

            anchors.left: parent.left
            anchors.right: parent.right
            anchors.verticalCenter: parent.verticalCenter
            value: mediaManager.mediaPlayer.currentMediaTimePosition / sliderScale
            from: 0
            to: mediaManager.currentMediaDuration / sliderScale
            onPressedChanged: {
                if(!pressed){
                    mediaManager.setNewPosition(calculateNewPosition())
                }
            }
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
                        enabled: (mediaManager.currentPlayingMediaIndex > 0) ? true : false
                        onReleased: {
                            mediaManager.previoseMedia()
                        }
                    }
                    ButtonImage{
                        id: btnPlayPause
                        source: mediaManager.mediaPlayer.currentState ? "qrc:/icons/pause" : "qrc:/icons/play"
                        enabled: mediaManager.mediaListModel.rowCount > 0 ? true : false
                        onReleased: {
                            if(mediaManager.mediaPlayer.currentState){
                                mediaManager.pauseMedia()
                            }else{
                                mediaManager.playCurrentMedia()
                            }
                        }
                    }
                    ButtonImage{
                        id: btnStop
                        source: "qrc:/icons/stop"
                        enabled: mediaManager.mediaListModel.rowCount > 0 ? true : false
                        onReleased: {
                            mediaManager.stopMedia()
                        }
                    }
                    ButtonImage{
                        id: btnNext
                        source: "qrc:/icons/next"
                        enabled: ((mediaManager.mediaListModel.rowCount > 1) && (mediaManager.currentPlayingMediaIndex + 1 < mediaManager.mediaListModel.rowCount)) ? true : false
                        onReleased: {
                            mediaManager.nextMedia()
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
                        id: slrVolume

                        property int volume: mediaManager.mediaPlayer.currentVolume

                        Layout.fillWidth: true
                        Layout.fillHeight: true                       
                        from: 0
                        to: 100
                        value: volume
                        onValueChanged: mediaManager.mediaPlayer.setCurrentVolume(value)
                        enabled: parent.enabled
                    }
                }
            }
        }
    }
}
