import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import "../Theme"

Rectangle {
    id: root

    height: LuminTheme.toolBarHeight
    color: LuminTheme.bg0

    property alias model: toolRepeater.model

    RowLayout {
        anchors.fill: parent
        anchors.leftMargin: 4
        anchors.rightMargin: 4
        spacing: 2

        ToolButton {
            text: "▤"
            implicitWidth: 32
            implicitHeight: 28
            ToolTip.text: "New"
            ToolTip.visible: hovered
            ToolTip.delay: 500
            contentItem: Text {
                text: parent.text
                color: LuminTheme.textSoft
                font.pixelSize: 14
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
            background: Rectangle {
                color: parent.hovered ? LuminTheme.hoverBg : "transparent"
                radius: 2
            }
        }

        ToolButton {
            text: "▥"
            implicitWidth: 32
            implicitHeight: 28
            ToolTip.text: "Open"
            ToolTip.visible: hovered
            ToolTip.delay: 500
            contentItem: Text {
                text: parent.text
                color: LuminTheme.textSoft
                font.pixelSize: 14
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
            background: Rectangle {
                color: parent.hovered ? LuminTheme.hoverBg : "transparent"
                radius: 2
            }
        }

        ToolButton {
            text: "▦"
            implicitWidth: 32
            implicitHeight: 28
            ToolTip.text: "Save"
            ToolTip.visible: hovered
            ToolTip.delay: 500
            contentItem: Text {
                text: parent.text
                color: LuminTheme.textSoft
                font.pixelSize: 14
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
            background: Rectangle {
                color: parent.hovered ? LuminTheme.hoverBg : "transparent"
                radius: 2
            }
        }

        Rectangle {
            Layout.leftMargin: 4
            Layout.rightMargin: 4
            width: 1
            height: 20
            color: LuminTheme.separator
        }

        ToolButton {
            text: "↶"
            implicitWidth: 32
            implicitHeight: 28
            ToolTip.text: "Undo"
            ToolTip.visible: hovered
            ToolTip.delay: 500
            contentItem: Text {
                text: parent.text
                color: LuminTheme.textSoft
                font.pixelSize: 14
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
            background: Rectangle {
                color: parent.hovered ? LuminTheme.hoverBg : "transparent"
                radius: 2
            }
        }

        ToolButton {
            text: "↷"
            implicitWidth: 32
            implicitHeight: 28
            ToolTip.text: "Redo"
            ToolTip.visible: hovered
            ToolTip.delay: 500
            contentItem: Text {
                text: parent.text
                color: LuminTheme.textSoft
                font.pixelSize: 14
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
            background: Rectangle {
                color: parent.hovered ? LuminTheme.hoverBg : "transparent"
                radius: 2
            }
        }

        Rectangle {
            Layout.leftMargin: 4
            Layout.rightMargin: 4
            width: 1
            height: 20
            color: LuminTheme.separator
        }

        ToolButton {
            text: "▶"
            implicitWidth: 32
            implicitHeight: 28
            ToolTip.text: "Run"
            ToolTip.visible: hovered
            ToolTip.delay: 500
            contentItem: Text {
                text: parent.text
                color: LuminTheme.textSoft
                font.pixelSize: 14
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
            background: Rectangle {
                color: parent.hovered ? LuminTheme.hoverBg : "transparent"
                radius: 2
            }
        }

        ToolButton {
            text: "■"
            implicitWidth: 32
            implicitHeight: 28
            ToolTip.text: "Stop"
            ToolTip.visible: hovered
            ToolTip.delay: 500
            contentItem: Text {
                text: parent.text
                color: LuminTheme.textSoft
                font.pixelSize: 14
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
            background: Rectangle {
                color: parent.hovered ? LuminTheme.hoverBg : "transparent"
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
                    color: LuminTheme.textSoft
                    font.pixelSize: 14
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }

                background: Rectangle {
                    color: parent.hovered ? LuminTheme.hoverBg : "transparent"
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
