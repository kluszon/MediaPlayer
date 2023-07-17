import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.15

import "components"
import "mian_view_elements"

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
        PlayerControl{
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
        PlayListArea{
            id: playlist
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }
}
