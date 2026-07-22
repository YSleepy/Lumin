import QtQuick
import QtQuick.Window
import QtQuick.Layouts
import Lumin.Editor 1.0

Window {
    id: docWindow
    width: 800
    height: 600
    title: qsTr("Lumin数学文档")
    flags: Qt.Window | Qt.WindowCloseButtonHint | Qt.WindowTitleHint
    color: "#1e1e1e"

    property int dockPosition: MainWindow.DockPosition.None
    property bool dragging: false

    onXChanged: { if (!dragging) checkSnap(); }
    onYChanged: { if (!dragging) checkSnap(); }

    onClosing: {
        if (dockPosition !== MainWindow.DockPosition.None) {
            mainWindow.undockPanel(dockPosition);
        }
    }

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        // 自定义标题栏（可拖拽）
        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: 28
            color: "#323233"

            MouseArea {
                anchors.fill: parent
                property point lastPos: Qt.point(0, 0)
                onPressed: {
                    lastPos = Qt.point(mouse.x, mouse.y);
                    dragging = true;
                }
                onReleased: {
                    dragging = false;
                }
                onPositionChanged: {
                    if (pressed) {
                        docWindow.x += mouse.x - lastPos.x;
                        docWindow.y += mouse.y - lastPos.y;
                    }
                }
            }

            RowLayout {
                anchors.fill: parent
                anchors.rightMargin: 4
                spacing: 0

                Text {
                    Layout.fillWidth: true
                    Layout.leftMargin: 8
                    text: qsTr("Lumin数学文档")
                    color: "#cccccc"
                    font.pixelSize: 12
                }

                Rectangle {
                    Layout.preferredWidth: 36
                    Layout.preferredHeight: 28
                    color: closeHover.hovered ? "#e81123" : "transparent"

                    Text {
                        anchors.centerIn: parent
                        text: "✕"
                        color: closeHover.hovered ? "#ffffff" : "#cccccc"
                        font.pixelSize: 12
                    }

                    MouseArea {
                        id: closeHover
                        anchors.fill: parent
                        hoverEnabled: true
                        onClicked: docWindow.close()
                    }
                }
            }
        }

        MathDocPanel {
            id: panel
            Layout.fillWidth: true
            Layout.fillHeight: true
            dockPosition: docWindow.dockPosition
        }
    }

    function checkSnap() {
        if (dragging) return;
        var pos = mainWindow.checkDockPosition(docWindow.x, docWindow.y, docWindow.width, docWindow.height);
        if (pos === MainWindow.DockPosition.None) return;
        if (mainWindow.isPositionDocked(pos)) return;

        dockPosition = pos;
        var comp = Qt.createComponent("MathDocPanel.qml");
        if (comp.status === Component.Ready) {
            mainWindow.dockPanel(docWindow, pos, comp, docWindow.width, docWindow.height);
            docWindow.hide();
        }
    }
}
