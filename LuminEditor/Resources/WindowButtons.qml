import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

RowLayout {
    spacing: 0

    // 最小化
    Rectangle {
        id: minBtn
        Layout.preferredWidth: 46
        Layout.preferredHeight: parent.height
        color: minMouse.containsMouse ? "#3e3e3e" : "transparent"

        Text {
            anchors.centerIn: parent
            text: "─"
            color: "#cccccc"
            font.pixelSize: 14
        }

        MouseArea {
            id: minMouse
            anchors.fill: parent
            hoverEnabled: true
            onClicked: mainWindow.visibility = Window.Minimized
        }
    }

    // 最大化/还原
    Rectangle {
        id: maxBtn
        Layout.preferredWidth: 46
        Layout.preferredHeight: parent.height
        color: maxMouse.containsMouse ? "#3e3e3e" : "transparent"

        Text {
            anchors.centerIn: parent
            text: mainWindow.visibility === Window.Maximized ? "⧉" : "□"
            color: "#cccccc"
            font.pixelSize: 12
        }

        MouseArea {
            id: maxMouse
            anchors.fill: parent
            hoverEnabled: true
            onClicked: {
                if (mainWindow.visibility === Window.Maximized) {
                    mainWindow.visibility = Window.Windowed
                } else {
                    mainWindow.visibility = Window.Maximized
                }
            }
        }
    }

    // 关闭
    Rectangle {
        id: closeBtn
        Layout.preferredWidth: 46
        Layout.preferredHeight: parent.height
        color: closeMouse.containsMouse ? "#e81123" : "transparent"

        Text {
            anchors.centerIn: parent
            text: "✕"
            color: closeMouse.containsMouse ? "#ffffff" : "#cccccc"
            font.pixelSize: 14
        }

        MouseArea {
            id: closeMouse
            anchors.fill: parent
            hoverEnabled: true
            onClicked: Qt.quit()
        }
    }
}
