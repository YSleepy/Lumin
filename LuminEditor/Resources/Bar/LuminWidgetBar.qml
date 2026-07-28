import QtQuick 2.3
import QtQuick.Controls

Rectangle {
    id: root
    height: heightBar
    color: colorBar !== "" ? colorBar : "#2d2d30"
    z: 1

    property string title: ""
    property string iconSource: ""
    property string colorBar: ""
    property int heightBar: 30

    property Window targetWindow: null
    property LuminMainMenuBar menuBar: null

    Row {
        id: leftRow
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter
        Row {
            Image {
                id: iconImg
                anchors.verticalCenter: parent.verticalCenter
                visible: root.iconSource !== ""
                source: root.iconSource
                width: 24
                height: 24
                fillMode: Image.PreserveAspectFit
            }

            Text {
                id: titleText
                anchors.verticalCenter: parent.verticalCenter
                visible: root.title !== ""
                text: root.title
                color: "white"
                font.pixelSize: 16
                font.bold: false
            }
        }
    }

    Row {
        id: rightRow
        anchors.right: parent.right
        anchors.rightMargin: 8
        anchors.verticalCenter: parent.verticalCenter
        spacing: 2

        ToolButton {
            text: "─"
            font.pixelSize: 18
            onClicked: {
                if (root.targetWindow)
                    root.targetWindow.showMinimized();
            }
            background: Rectangle {
                color: parent.hovered ? "#34495e" : "transparent"
                radius: 2
            }
        }

        ToolButton {
            id: maxBtn
            text: {
                if (!root.targetWindow)
                    return "☐";
                return root.targetWindow.visibility === Window.Maximized ? "❐" : "☐";
            }
            font.pixelSize: 18
            onClicked: {
                if (!root.targetWindow)
                    return;
                if (root.targetWindow.visibility === Window.Maximized)
                    root.targetWindow.showNormal();
                else
                    root.targetWindow.showMaximized();
            }
            background: Rectangle {
                color: parent.hovered ? "#34495e" : "transparent"
                radius: 2
            }

            Connections {
                target: root.targetWindow
                function onVisibilityChanged() {
                    if (root.targetWindow) {
                        maxBtn.text = root.targetWindow.visibility === Window.Maximized ? "❐" : "☐";
                    }
                }
            }
        }

        ToolButton {
            text: "✕"
            font.pixelSize: 18
            onClicked: {
                if (root.targetWindow)
                    root.targetWindow.close();
            }
            background: Rectangle {
                color: parent.hovered ? "#e74c3c" : "transparent"
                radius: 2
            }
        }
    }

    MouseArea {
        anchors.right: rightRow.left
        anchors.left: leftRow.right
        anchors.top: leftRow.top
        anchors.bottom: leftRow.bottom
        onPressed: targetWindow?.startSystemMove()
        onDoubleClicked: {
            if (!targetWindow)
                return;
            if (targetWindow.visibility === Window.Maximized)
                targetWindow.showNormal();
            else
                targetWindow.showMaximized();
        }
    }

    Row {
        id: menuBarContainer
        anchors.left: leftRow.right
        anchors.verticalCenter: root.top
        anchors.leftMargin: 8
        Component.onCompleted: {
            if (root.menuBar) {
                root.menuBar.parent = menuBarContainer;
                root.menuBar.anchors.fill = menuBarContainer;
                root.menuBar.anchors.verticalCenter = menuBarContainer.verticalCenter;
                root.menuBar.anchors.topMargin = 2;
            }
        }
    }
}
