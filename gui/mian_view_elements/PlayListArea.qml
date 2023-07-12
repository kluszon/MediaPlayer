import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.15
import QtQuick 2.2
import QtQuick.Dialogs 1.0

import Utils 1.0

import "../components"

ColumnLayout{

    property TimeUtils timeUtils: TimeUtils {}

    width: parent.width
    height: parent.height
    spacing: 20

    ListView{
        id: lvPlayList
        Layout.fillWidth: true
        Layout.fillHeight: true
        model: mediaManager.mediaListModel
        clip: true
        delegate: Rectangle{
            width: lvPlayList.width
            height: 40
            color: (lvPlayList.currentIndex === index) ? Material.color(Material.Purple, Material.Shade200) : Material.color(Material.Grey, Material.Shade800)
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
                    text: mediaTitle + " - " + mediaArtist
                }
            }
            Label{
                id: lblMediaDuration
                anchors.right: parent.right
                anchors.rightMargin: 20
                anchors.verticalCenter: parent.verticalCenter
                text: timeUtils.timeToString(mediaDuration, "mm:ss")
            }
            Rectangle{
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.bottom: parent.bottom

                height: 2
                color: Material.color(Material.Grey, Material.Shade700)
            }
            MouseArea{
                anchors.fill: parent
                onReleased: {
                    lvPlayList.currentIndex = index
                }
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
                    fileDialog.open()
                }
            }
            ButtonImage{
                id: btnRemoveMedia
                source: "qrc:/icons/delete"
                enabled: (lvPlayList.count > 0) ? true : false
                onReleased: {
                    mediaManager.removeMedia(lvPlayList.currentIndex)
                }
            }
        }
    }

    FileDialog {
        id: fileDialog

        title: "Please choose a file"
        folder: shortcuts.home
        nameFilters: [ "Media files (*.mp3 *.wav *.flac)" ]
        onAccepted: {
            var mediaPath = fileDialog.fileUrl.toString()
            mediaPath = mediaPath.replace(/^(file:\/{3})/,"")         ///< Remove prefix file://
            mediaManager.addMedia(mediaPath)
        }
    }
}
