import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: root

    height: 36
    color: "#2d2d30"

    property alias model: toolRepeater.model

    RowLayout {
        anchors.fill: parent
        anchors.leftMargin: 4
        anchors.rightMargin: 4
        spacing: 2

        Repeater {
            id: toolRepeater
            model: 0
            delegate: ToolButton {
                text: modelData.text || ""
                implicitWidth: 32
                implicitHeight: 28

                contentItem: Text {
                    text: parent.text
                    color: "#cccccc"
                    font.pixelSize: 14
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }

                background: Rectangle {
                    color: parent.hovered ? "#3e3e3e" : "transparent"
                    radius: 2
                }

                onClicked: {
                    if (modelData.action)
                        modelData.action()
                }
            }
        }

        Item { Layout.fillWidth: true }
    }
}
