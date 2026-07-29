import QtQuick
import QtQuick.Window
import QtQuick.Controls

import "Resources/Theme"
import "Resources/Common"

Window {
    id: testWindow
    visible: true
    width: 800
    height: 600
    title: "Component Test"
    color: LuminTheme.bg0

    Column {
        anchors.fill: parent
        spacing: 20

        // Test LuminButton
        Row {
            spacing: 10
            padding: 10

            Text {
                text: "LuminButton:"
                color: LuminTheme.textMain
                anchors.verticalCenter: parent.verticalCenter
                width: 120
            }

            LuminButton {
                text: "Click Me"
                onClicked: console.log("Button clicked")
            }

            LuminButton {
                text: "Disabled"
                enabled: false
            }
        }

        // Test LuminToolButton
        Row {
            spacing: 10
            padding: 10

            Text {
                text: "LuminToolButton:"
                color: LuminTheme.textMain
                anchors.verticalCenter: parent.verticalCenter
                width: 120
            }

            LuminToolButton {
                iconText: "▶"
                ToolTip.text: "Play"
                ToolTip.visible: hovered
                onClicked: console.log("Play clicked")
            }

            LuminToolButton {
                iconText: "■"
                ToolTip.text: "Stop"
                ToolTip.visible: hovered
                onClicked: console.log("Stop clicked")
            }

            LuminToolButton {
                iconText: "▦"
                ToolTip.text: "Save"
                ToolTip.visible: hovered
                onClicked: console.log("Save clicked")
            }
        }

        // Test LuminSeparator
        Row {
            spacing: 10
            padding: 10

            Text {
                text: "LuminSeparator:"
                color: LuminTheme.textMain
                anchors.verticalCenter: parent.verticalCenter
                width: 120
            }

            LuminSeparator {
                anchors.verticalCenter: parent.verticalCenter
                horizontal: false
                length: 30
            }

            LuminSeparator {
                anchors.verticalCenter: parent.verticalCenter
                horizontal: true
                length: 100
            }
        }

        // Test LuminMenuBar
        Row {
            spacing: 10
            padding: 10

            Text {
                text: "LuminMenuBar:"
                color: LuminTheme.textMain
                anchors.verticalCenter: parent.verticalCenter
                width: 120
            }

            LuminMenuBar {
                LuminMenu {
                    title: "File"
                    LuminMenuItem {
                        text: "Open"
                        onTriggered: console.log("Open")
                    }
                    LuminMenuItem {
                        text: "Save"
                        onTriggered: console.log("Save")
                    }
                }

                LuminMenu {
                    title: "Edit"
                    LuminMenuItem {
                        text: "Copy"
                        onTriggered: console.log("Copy")
                    }
                    LuminMenuItem {
                        text: "Paste"
                        onTriggered: console.log("Paste")
                    }
                }
            }
        }

        // Test LuminWindowButtons
        Row {
            spacing: 10
            padding: 10

            Text {
                text: "LuminWindowButtons:"
                color: LuminTheme.textMain
                anchors.verticalCenter: parent.verticalCenter
                width: 120
            }

            LuminWindowButtons {
                targetWindow: testWindow
            }
        }
    }
}
