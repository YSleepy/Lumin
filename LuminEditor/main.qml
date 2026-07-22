import QtQuick
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Layouts
import "Resources"

ApplicationWindow {
    id: mainWindow
    visible: true
    width: 1280
    height: 720
    title: "LuminEditor"
    color: "#1e1e1e"

    flags: Qt.FramelessWindowHint | Qt.Window

    // 停靠状态
    property var dockedTopPanel: null
    property var dockedBottomPanel: null
    property var dockedLeftPanel: null
    property var dockedRightPanel: null
    readonly property int dockThreshold: 60

    // 停靠位置枚举
    enum DockPosition { None, Top, Bottom, Left, Right }

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        TitleBar {}

        // 上部停靠区
        Loader {
            id: topDock
            Layout.fillWidth: true
            Layout.preferredHeight: dockedTopPanel ? dockedTopPanel.prefHeight : 0
            visible: dockedTopPanel !== null
            sourceComponent: dockedTopPanel ? dockedTopPanel.component : null
        }

        RowLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true
            spacing: 0

            // 左侧停靠区
            Loader {
                id: leftDock
                Layout.preferredWidth: dockedLeftPanel ? dockedLeftPanel.prefWidth : 0
                Layout.fillHeight: true
                visible: dockedLeftPanel !== null
                sourceComponent: dockedLeftPanel ? dockedLeftPanel.component : null
            }

            // 中央编辑区 + 底部停靠区
            ColumnLayout {
                Layout.fillWidth: true
                Layout.fillHeight: true
                spacing: 0

                Rectangle {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    color: "#1e1e1e"

                    Text {
                        anchors.centerIn: parent
                        text: qsTr("编辑视口区域")
                        color: "#555555"
                        font.pixelSize: 24
                    }
                }

                Loader {
                    id: bottomDock
                    Layout.fillWidth: true
                    Layout.preferredHeight: dockedBottomPanel ? dockedBottomPanel.prefHeight : 0
                    visible: dockedBottomPanel !== null
                    sourceComponent: dockedBottomPanel ? dockedBottomPanel.component : null
                }
            }

            // 右侧停靠区
            Loader {
                id: rightDock
                Layout.preferredWidth: dockedRightPanel ? dockedRightPanel.prefWidth : 0
                Layout.fillHeight: true
                visible: dockedRightPanel !== null
                sourceComponent: dockedRightPanel ? dockedRightPanel.component : null
            }
        }
    }

    // 检测浮动窗口是否靠近主窗口边缘，返回停靠位置
    function checkDockPosition(winX, winY, winW, winH) {
        var mx = x, my = y, mw = width, mh = height;
        var threshold = dockThreshold;

        // 上边缘
        if (Math.abs(winY + winH - my) < threshold &&
            winX + winW > mx + 100 && winX < mx + mw - 100) {
            return MainWindow.DockPosition.Top;
        }
        // 下边缘
        if (Math.abs(my + mh - winY) < threshold &&
            winX + winW > mx + 100 && winX < mx + mw - 100) {
            return MainWindow.DockPosition.Bottom;
        }
        // 左边缘
        if (Math.abs(winX + winW - mx) < threshold &&
            winY + winH > my + 30 && winY < my + mh - 30) {
            return MainWindow.DockPosition.Left;
        }
        // 右边缘
        if (Math.abs(mx + mw - winX) < threshold &&
            winY + winH > my + 30 && winY < my + mh - 30) {
            return MainWindow.DockPosition.Right;
        }
        return MainWindow.DockPosition.None;
    }

    function dockPanel(win, position, component, prefWidth, prefHeight) {
        var panel = {
            window: win,
            component: component,
            prefWidth: prefWidth || 400,
            prefHeight: prefHeight || 300
        };

        switch (position) {
        case MainWindow.DockPosition.Top:
            dockedTopPanel = panel; break;
        case MainWindow.DockPosition.Bottom:
            dockedBottomPanel = panel; break;
        case MainWindow.DockPosition.Left:
            dockedLeftPanel = panel; break;
        case MainWindow.DockPosition.Right:
            dockedRightPanel = panel; break;
        }
    }

    function undockPanel(position) {
        var panel = null;
        switch (position) {
        case MainWindow.DockPosition.Top:
            panel = dockedTopPanel; dockedTopPanel = null; break;
        case MainWindow.DockPosition.Bottom:
            panel = dockedBottomPanel; dockedBottomPanel = null; break;
        case MainWindow.DockPosition.Left:
            panel = dockedLeftPanel; dockedLeftPanel = null; break;
        case MainWindow.DockPosition.Right:
            panel = dockedRightPanel; dockedRightPanel = null; break;
        }
        return panel;
    }

    function isPositionDocked(position) {
        switch (position) {
        case MainWindow.DockPosition.Top: return dockedTopPanel !== null;
        case MainWindow.DockPosition.Bottom: return dockedBottomPanel !== null;
        case MainWindow.DockPosition.Left: return dockedLeftPanel !== null;
        case MainWindow.DockPosition.Right: return dockedRightPanel !== null;
        }
        return false;
    }

    function openMathDoc() {
        // 如果已停靠则聚焦
        if (dockedBottomPanel && dockedBottomPanel.window &&
            dockedBottomPanel.window.title && dockedBottomPanel.window.title.indexOf("数学文档") >= 0) {
            return;
        }
        if (dockedTopPanel && dockedTopPanel.window &&
            dockedTopPanel.window.title && dockedTopPanel.window.title.indexOf("数学文档") >= 0) {
            return;
        }
        if (dockedLeftPanel && dockedLeftPanel.window &&
            dockedLeftPanel.window.title && dockedLeftPanel.window.title.indexOf("数学文档") >= 0) {
            return;
        }
        if (dockedRightPanel && dockedRightPanel.window &&
            dockedRightPanel.window.title && dockedRightPanel.window.title.indexOf("数学文档") >= 0) {
            return;
        }

        var comp = Qt.createComponent("Resources/MathDocWindow.qml");
        if (comp.status === Component.Ready) {
            var win = comp.createObject(mainWindow);
            win.show();
        }
    }
}
