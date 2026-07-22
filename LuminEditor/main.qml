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
    readonly property int dockNone: 0
    readonly property int dockTop: 1
    readonly property int dockBottom: 2
    readonly property int dockLeft: 3
    readonly property int dockRight: 4

    property var dockedTopPanel: null
    property var dockedBottomPanel: null
    property var dockedLeftPanel: null
    property var dockedRightPanel: null
    readonly property int dockThreshold: 60
    property bool dockHintVisible: false
    property int activeDockHint: 0  // dockNone

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        TitleBar {}

        // 上方停靠区 + 停靠提示
        Item {
            Layout.fillWidth: true
            Layout.preferredHeight: dockedTopPanel ? dockedTopPanel.prefHeight : 0

            Loader {
                anchors.fill: parent
                visible: dockedTopPanel !== null
                sourceComponent: dockedTopPanel ? dockedTopPanel.component : null
            }

            // 停靠提示
            DockHintOverlay {
                anchors.fill: parent
                visible: dockHintVisible
                active: activeDockHint === mainWindow.dockTop
                hintPosition: "top"
            }
        }

        RowLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true
            spacing: 0

            // 左侧
            Item {
                Layout.preferredWidth: dockedLeftPanel ? dockedLeftPanel.prefWidth : 0
                Layout.fillHeight: true

                Loader {
                    anchors.fill: parent
                    visible: dockedLeftPanel !== null
                    sourceComponent: dockedLeftPanel ? dockedLeftPanel.component : null
                }

                DockHintOverlay {
                    anchors.fill: parent
                    visible: dockHintVisible
                    active: activeDockHint === mainWindow.dockLeft
                    hintPosition: "left"
                }
            }

            ColumnLayout {
                Layout.fillWidth: true
                Layout.fillHeight: true
                spacing: 0

                // 中央编辑区
                Item {
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    Rectangle {
                        anchors.fill: parent
                        color: "#1e1e1e"

                        Text {
                            anchors.centerIn: parent
                            text: qsTr("编辑视口区域")
                            color: "#555555"
                            font.pixelSize: 24
                        }
                    }

                    // 中央停靠提示
                    DockHintOverlay {
                        anchors.centerIn: parent
                        width: 120; height: 120
                        visible: dockHintVisible
                        active: activeDockHint === mainWindow.dockNone
                        hintPosition: "center"
                    }
                }

                // 下方
                Item {
                    Layout.fillWidth: true
                    Layout.preferredHeight: dockedBottomPanel ? dockedBottomPanel.prefHeight : 0

                    Loader {
                        anchors.fill: parent
                        visible: dockedBottomPanel !== null
                        sourceComponent: dockedBottomPanel ? dockedBottomPanel.component : null
                    }

                    DockHintOverlay {
                        anchors.fill: parent
                        visible: dockHintVisible
                        active: activeDockHint === mainWindow.dockBottom
                        hintPosition: "bottom"
                    }
                }
            }

            // 右侧
            Item {
                Layout.preferredWidth: dockedRightPanel ? dockedRightPanel.prefWidth : 0
                Layout.fillHeight: true

                Loader {
                    anchors.fill: parent
                    visible: dockedRightPanel !== null
                    sourceComponent: dockedRightPanel ? dockedRightPanel.component : null
                }

                DockHintOverlay {
                    anchors.fill: parent
                    visible: dockHintVisible
                    active: activeDockHint === mainWindow.dockRight
                    hintPosition: "right"
                }
            }
        }
    }

    function checkDockPosition(winX, winY, winW, winH) {
        var mx = x, my = y, mw = width, mh = height;
        var threshold = dockThreshold;

        if (Math.abs(winY + winH - my) < threshold &&
            winX + winW > mx + 100 && winX < mx + mw - 100) {
            return mainWindow.dockTop;
        }
        if (Math.abs(my + mh - winY) < threshold &&
            winX + winW > mx + 100 && winX < mx + mw - 100) {
            return mainWindow.dockBottom;
        }
        if (Math.abs(winX + winW - mx) < threshold &&
            winY + winH > my + 30 && winY < my + mh - 30) {
            return mainWindow.dockLeft;
        }
        if (Math.abs(mx + mw - winX) < threshold &&
            winY + winH > my + 30 && winY < my + mh - 30) {
            return mainWindow.dockRight;
        }
        return mainWindow.dockNone;
    }

    function showDockHint(position) {
        dockHintVisible = true;
        activeDockHint = position;
    }

    function hideDockHint() {
        dockHintVisible = false;
        activeDockHint = mainWindow.dockNone;
    }

    function dockPanel(win, position, component, prefWidth, prefHeight) {
        var panel = {
            window: win,
            component: component,
            prefWidth: prefWidth || 400,
            prefHeight: prefHeight || 300
        };

        switch (position) {
        case mainWindow.dockTop:
            dockedTopPanel = panel; break;
        case mainWindow.dockBottom:
            dockedBottomPanel = panel; break;
        case mainWindow.dockLeft:
            dockedLeftPanel = panel; break;
        case mainWindow.dockRight:
            dockedRightPanel = panel; break;
        }
    }

    function undockPanel(position) {
        var panel = null;
        switch (position) {
        case mainWindow.dockTop:
            panel = dockedTopPanel; dockedTopPanel = null; break;
        case mainWindow.dockBottom:
            panel = dockedBottomPanel; dockedBottomPanel = null; break;
        case mainWindow.dockLeft:
            panel = dockedLeftPanel; dockedLeftPanel = null; break;
        case mainWindow.dockRight:
            panel = dockedRightPanel; dockedRightPanel = null; break;
        }
        return panel;
    }

    function isPositionDocked(position) {
        switch (position) {
        case mainWindow.dockTop: return dockedTopPanel !== null;
        case mainWindow.dockBottom: return dockedBottomPanel !== null;
        case mainWindow.dockLeft: return dockedLeftPanel !== null;
        case mainWindow.dockRight: return dockedRightPanel !== null;
        }
        return false;
    }

    function openMathDoc() {
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
        } else {
            console.error("Failed to create MathDocWindow: " + comp.errorString());
        }
    }
}
