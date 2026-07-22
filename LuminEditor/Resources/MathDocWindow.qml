import QtQuick
import QtQuick.Window
import QtQuick.Layouts

Window {
    id: docWindow
    width: 800
    height: 600
    title: qsTr("Lumin数学文档")
    color: "#1e1e1e"

    flags: Qt.FramelessWindowHint | Qt.Window

    property int dockPosition: 0
    property bool dragging: false

    Timer {
        id: hintTimer
        interval: 100
        running: dragging
        repeat: true
        onTriggered: updateHint()
    }

    onClosing: {
        mainWindow.hideDockHint();
    }

    TitleBar{
    
    }

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        // 标题栏
        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: 28
            color: "#323233"

            MouseArea {
                anchors.fill: parent
                property point lastPos: Qt.point(0, 0)
                onPressed: function(mouse) {
                    lastPos = Qt.point(mouse.x, mouse.y);
                    dragging = true;
                }
                onReleased: function(mouse) {
                    dragging = false;
                    mainWindow.hideDockHint();
                    var pos = mainWindow.checkDockPosition(docWindow.x, docWindow.y, docWindow.width, docWindow.height);
                    if (pos !== 0 && !mainWindow.isPositionDocked(pos)) {
                        var comp = Qt.createComponent("MathDocPanel.qml");
                        if (comp.status === Component.Ready) {
                            dockPosition = pos;
                            mainWindow.dockPanel(docWindow, pos, comp, docWindow.width, docWindow.height);
                            docWindow.hide();
                        } else {
                            console.error("Failed to create MathDocPanel: " + comp.errorString());
                        }
                    }
                }
                onPositionChanged: function(mouse) {
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

                // 关闭按钮
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
            Layout.fillWidth: true
            Layout.fillHeight: true
            dockPosition: docWindow.dockPosition
        }
    }

    function updateHint() {
        var pos = mainWindow.checkDockPosition(docWindow.x, docWindow.y, docWindow.width, docWindow.height);
        if (pos !== 0 && !mainWindow.isPositionDocked(pos)) {
            mainWindow.showDockHint(pos);
        } else {
            mainWindow.hideDockHint();
        }
    }
}
