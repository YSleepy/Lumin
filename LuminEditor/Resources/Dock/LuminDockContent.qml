import QtQuick
import QtQuick.Controls
import "../Theme"

Rectangle {
    id: root
    color: LuminTheme.bg2

    property var descriptor
    property string panelTitle: ""

    Text {
        anchors.centerIn: parent
        text: root.panelTitle || "Panel"
        color: LuminTheme.textSoft
        font.pixelSize: 14
    }
}
