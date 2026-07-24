import QtQuick
import QtQuick.Controls

Item {
    id: root

    property bool active: false
    property int hoveredZone: -1

    enum Zone {
        None = -1,
        Center = 0,
        Left = 1,
        Right = 2,
        Top = 3,
        Bottom = 4
    }

    signal dropped(int zone)

    anchors.fill: parent
    z: 1000
    visible: active

    Rectangle {
        anchors.fill: parent
        color: "#000000"
        opacity: 0.3
    }

    Rectangle {
        id: guide
        anchors.centerIn: parent
        width: col.width + 20
        height: col.height + 20
        color: "transparent"

        Column {
            id: col
            anchors.centerIn: parent
            spacing: 4

            // Top
            Rectangle {
                anchors.horizontalCenter: parent.horizontalCenter
                width: 80; height: 60
                radius: 4
                color: maTop.containsMouse ? Qt.rgba(0.25, 0.66, 1.0, 0.5) : Qt.rgba(0, 0.47, 0.78, 0.15)
                border.color: maTop.containsMouse ? "#40a9ff" : "#007acc"
                border.width: 1
                MouseArea {
                    id: maTop
                    anchors.fill: parent
                    hoverEnabled: true
                    onEntered: root.hoveredZone = LuminDockDropOverlay.Zone.Top
                    onExited: root.hoveredZone = LuminDockDropOverlay.Zone.None
                    onClicked: root.dropped(LuminDockDropOverlay.Zone.Top)
                }
            }

            // Middle row
            Row {
                anchors.horizontalCenter: parent.horizontalCenter
                spacing: 4

                // Left
                Rectangle {
                    width: 60; height: 80
                    radius: 4
                    color: maLeft.containsMouse ? Qt.rgba(0.25, 0.66, 1.0, 0.5) : Qt.rgba(0, 0.47, 0.78, 0.15)
                    border.color: maLeft.containsMouse ? "#40a9ff" : "#007acc"
                    border.width: 1
                    MouseArea {
                        id: maLeft
                        anchors.fill: parent
                        hoverEnabled: true
                        onEntered: root.hoveredZone = LuminDockDropOverlay.Zone.Left
                        onExited: root.hoveredZone = LuminDockDropOverlay.Zone.None
                        onClicked: root.dropped(LuminDockDropOverlay.Zone.Left)
                    }
                }

                // Center
                Rectangle {
                    width: 80; height: 80
                    radius: 4
                    color: maCenter.containsMouse ? Qt.rgba(0.25, 0.66, 1.0, 0.5) : Qt.rgba(0, 0.47, 0.78, 0.15)
                    border.color: maCenter.containsMouse ? "#40a9ff" : "#007acc"
                    border.width: 1
                    MouseArea {
                        id: maCenter
                        anchors.fill: parent
                        hoverEnabled: true
                        onEntered: root.hoveredZone = LuminDockDropOverlay.Zone.Center
                        onExited: root.hoveredZone = LuminDockDropOverlay.Zone.None
                        onClicked: root.dropped(LuminDockDropOverlay.Zone.Center)
                    }
                }

                // Right
                Rectangle {
                    width: 60; height: 80
                    radius: 4
                    color: maRight.containsMouse ? Qt.rgba(0.25, 0.66, 1.0, 0.5) : Qt.rgba(0, 0.47, 0.78, 0.15)
                    border.color: maRight.containsMouse ? "#40a9ff" : "#007acc"
                    border.width: 1
                    MouseArea {
                        id: maRight
                        anchors.fill: parent
                        hoverEnabled: true
                        onEntered: root.hoveredZone = LuminDockDropOverlay.Zone.Right
                        onExited: root.hoveredZone = LuminDockDropOverlay.Zone.None
                        onClicked: root.dropped(LuminDockDropOverlay.Zone.Right)
                    }
                }
            }

            // Bottom
            Rectangle {
                anchors.horizontalCenter: parent.horizontalCenter
                width: 80; height: 60
                radius: 4
                color: maBottom.containsMouse ? Qt.rgba(0.25, 0.66, 1.0, 0.5) : Qt.rgba(0, 0.47, 0.78, 0.15)
                border.color: maBottom.containsMouse ? "#40a9ff" : "#007acc"
                border.width: 1
                MouseArea {
                    id: maBottom
                    anchors.fill: parent
                    hoverEnabled: true
                    onEntered: root.hoveredZone = LuminDockDropOverlay.Zone.Bottom
                    onExited: root.hoveredZone = LuminDockDropOverlay.Zone.None
                    onClicked: root.dropped(LuminDockDropOverlay.Zone.Bottom)
                }
            }
        }
    }
}
