import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Lumin.Editor 1.0
import "../Common"
import "../Theme"

// Markdown 编辑器：左侧编辑 + 右侧预览
Item {
    id: root

    // QtFlexQml 框架要求的属性
    property var descriptor

    property alias filePath: editorView.filePath
    property string fileName: ""

    signal closeRequested()

    // 分割线拖拽状态
    property real splitRatio: 0.5
    readonly property int minPaneWidth: 200

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        // 工具栏
        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: 36
            color: LuminTheme.panelBg

            RowLayout {
                anchors.fill: parent
                anchors.leftMargin: 8
                anchors.rightMargin: 8
                spacing: 8

                Text {
                    text: root.fileName || "Untitled"
                    color: LuminTheme.textMain
                    font.pixelSize: 13
                    font.bold: true
                    Layout.fillWidth: true
                }

                LuminToolButton {
                    iconText: "💾"
                    iconSize: 16
                    ToolTip.text: "Save"
                    ToolTip.visible: hovered
                    onClicked: saveFile()
                }

                LuminToolButton {
                    iconText: "↻"
                    iconSize: 16
                    ToolTip.text: "Reload"
                    ToolTip.visible: hovered
                    onClicked: editorView.loadFile(root.filePath)
                }

                Rectangle {
                    Layout.preferredWidth: 1
                    Layout.preferredHeight: 20
                    color: LuminTheme.borderColor
                }

                LuminToolButton {
                    iconText: "✕"
                    iconSize: 14
                    ToolTip.text: "Close"
                    ToolTip.visible: hovered
                    onClicked: root.closeRequested()
                }
            }
        }

        // 分栏容器
        Item {
            Layout.fillWidth: true
            Layout.fillHeight: true

            // 左侧编辑器
            Rectangle {
                id: editorPane
                width: Math.max(minPaneWidth, parent.width * root.splitRatio - splitterHandle.width / 2)
                height: parent.height
                color: LuminTheme.editorBg

                LMarkdownView {
                    id: editorView
                    anchors.fill: parent
                    anchors.margins: 4
                    readOnly: false

                    // 文本变化时同步到预览
                    Timer {
                        id: syncTimer
                        interval: 300
                        repeat: false
                        onTriggered: {
                            previewView.setMarkdownText(editorView.getMarkdownText())
                        }
                    }
                }
            }

            // 分割线
            Rectangle {
                id: splitterHandle
                x: editorPane.width
                width: 4
                height: parent.height
                color: splitterArea.containsMouse || splitterArea.pressed ?
                       LuminTheme.accentColor : LuminTheme.borderColor

                Behavior on color {
                    ColorAnimation { duration: 150 }
                }

                MouseArea {
                    id: splitterArea
                    anchors.fill: parent
                    hoverEnabled: true
                    cursorShape: Qt.SplitHCursor

                    property real startX: 0
                    property real startRatio: 0

                    onPressed: (mouse) => {
                        startX = mouse.x
                        startRatio = root.splitRatio
                    }

                    onPositionChanged: (mouse) => {
                        if (pressed) {
                            let delta = (splitterHandle.x + mouse.x - editorPane.x) / parent.width
                            let newRatio = Math.max(0.2, Math.min(0.8, delta))
                            root.splitRatio = newRatio
                        }
                    }
                }
            }

            // 右侧预览
            Rectangle {
                x: splitterHandle.x + splitterHandle.width
                width: parent.width - x
                height: parent.height
                color: LuminTheme.editorBg

                LMarkdownView {
                    id: previewView
                    anchors.fill: parent
                    anchors.margins: 4
                    readOnly: true
                }
            }
        }
    }

    function saveFile() {
        if (root.filePath) {
            // TODO: 实现保存逻辑
            console.log("Save:", root.filePath)
        }
    }

    Component.onCompleted: {
        // 初始化预览内容
        Qt.callLater(function() {
            if (editorView.filePath) {
                previewView.setMarkdownText(editorView.getMarkdownText())
            }
        })
    }

    // 监听文件路径变化
    onFilePathChanged: {
        if (editorView && filePath) {
            // 只在文件路径真正改变时才加载
            if (editorView.filePath !== filePath) {
                editorView.filePath = filePath
                Qt.callLater(function() {
                    var text = editorView.getMarkdownText()
                    previewView.setMarkdownText(text)
                    syncTimer.restart()
                })
            }
        }
    }

    // 添加键盘输入监听
    Connections {
        target: editorView
        function onWidthChanged() { syncTimer.restart() }
        function onHeightChanged() { syncTimer.restart() }
    }
}
