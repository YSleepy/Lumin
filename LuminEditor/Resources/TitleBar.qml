import QtQuick
import QtQuick.Layouts

Rectangle {
    id: titleBar
    Layout.fillWidth: true
    Layout.preferredHeight: 32
    color: "#323233"

    MouseArea {
        anchors.fill: parent
        property point lastPos: Qt.point(0, 0)
        onPressed: function(mouse) {
            lastPos = Qt.point(mouse.x, mouse.y)
        }
        onPositionChanged: function(mouse) {
            if (pressed) {
                mainWindow.x += mouse.x - lastPos.x
                mainWindow.y += mouse.y - lastPos.y
            }
        }
        onDoubleClicked: function(mouse) {
            if (mainWindow.visibility === Window.Maximized) {
                mainWindow.visibility = Window.Windowed
            } else {
                mainWindow.visibility = Window.Maximized
            }
        }
    }

    RowLayout {
        anchors.fill: parent
        anchors.leftMargin: 4
        anchors.rightMargin: 0
        spacing: 0

        Rectangle {
            Layout.leftMargin: 8
            Layout.preferredWidth: 16
            Layout.preferredHeight: 16
            color: "#569cd6"
            radius: 2
        }

        EditorMenuBar {
            Layout.fillWidth: true
            onOpenMathDocRequested: mainWindow.openMathDoc()
        }

        WindowButtons {
            Layout.preferredWidth: 138
            Layout.preferredHeight: 32
        }
    }
}
