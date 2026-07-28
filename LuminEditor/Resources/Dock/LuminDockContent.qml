import QtQuick
import QtQuick.Controls

Rectangle {
    id: root
    color: "#1e1e1e"

    property var descriptor
    property string panelTitle: ""

    Text {
        anchors.centerIn: parent
        text: root.panelTitle || "Panel"
        color: "#cccccc"
        font.pixelSize: 14
    }
}
