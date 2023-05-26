import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.15

import "../components"

ColumnLayout{
    width: parent.width
    height: parent.height
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
