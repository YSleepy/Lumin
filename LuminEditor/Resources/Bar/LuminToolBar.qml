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

        ToolButton {
            text: "\u25A4"
            implicitWidth: 32
            implicitHeight: 28
            ToolTip.text: "New"
            ToolTip.visible: hovered
            ToolTip.delay: 500
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
        }

        ToolButton {
            text: "\u25A5"
            implicitWidth: 32
            implicitHeight: 28
            ToolTip.text: "Open"
            ToolTip.visible: hovered
            ToolTip.delay: 500
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
        }

        ToolButton {
            text: "\u25A6"
            implicitWidth: 32
            implicitHeight: 28
            ToolTip.text: "Save"
            ToolTip.visible: hovered
            ToolTip.delay: 500
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
        }

        Rectangle {
            Layout.leftMargin: 4
            Layout.rightMargin: 4
            width: 1
            height: 20
            color: "#404040"
        }

        ToolButton {
            text: "\u21B6"
            implicitWidth: 32
            implicitHeight: 28
            ToolTip.text: "Undo"
            ToolTip.visible: hovered
            ToolTip.delay: 500
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
        }

        ToolButton {
            text: "\u21B7"
            implicitWidth: 32
            implicitHeight: 28
            ToolTip.text: "Redo"
            ToolTip.visible: hovered
            ToolTip.delay: 500
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
        }

        Rectangle {
            Layout.leftMargin: 4
            Layout.rightMargin: 4
            width: 1
            height: 20
            color: "#404040"
        }

        ToolButton {
            text: "\u25B6"
            implicitWidth: 32
            implicitHeight: 28
            ToolTip.text: "Run"
            ToolTip.visible: hovered
            ToolTip.delay: 500
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
        }

        ToolButton {
            text: "\u25A0"
            implicitWidth: 32
            implicitHeight: 28
            ToolTip.text: "Stop"
            ToolTip.visible: hovered
            ToolTip.delay: 500
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
        }

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
