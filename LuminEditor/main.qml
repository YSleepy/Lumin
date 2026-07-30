import QtQuick
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Dialogs

import "Resources/Dock"
import "Resources/Bar"
import "Resources/Panel"
import "Resources/Theme"
import "qrc:/qml/Dock"

ApplicationWindow {
    id: mainWindow
    visible: true
    width: 1280
    height: 720
    title: "LuminEditor"
    color: LuminTheme.bg0

    flags: Qt.FramelessWindowHint | Qt.Window

    // Content component registered for all dock panels
    Component {
        id: luminContent
        LuminDockContent {}
    }

    // Markdown 编辑器组件工厂
    property var markdownFiles: ({})

    Component {
        id: markdownEditorComponent
        LuminMarkdownEditor {
            id: mdEditor

            // 监听 descriptor 变化并设置文件信息
            onDescriptorChanged: {
                if (descriptor && mainWindow.markdownFiles[descriptor.id]) {
                    var info = mainWindow.markdownFiles[descriptor.id]
                    filePath = info.filePath
                    fileName = info.fileName
                }
            }

            onCloseRequested: {
                if (descriptor) {
                    delete mainWindow.markdownFiles[descriptor.id]
                }
            }
        }
    }

    // 标题栏中的菜单栏
    Component {
        id: mainMenuBarComponent
        LuminMainMenuBar {
            onOpenMarkdownFile: fileDialog.open()
        }
    }

    // 文件打开对话框
    FileDialog {
        id: fileDialog
        title: "打开 Markdown 文件"
        nameFilters: ["Markdown 文件 (*.md *.markdown)", "所有文件 (*)"]
        onAccepted: {
            openMarkdownFile(selectedFile)
        }
    }

    Component.onCompleted: {
        // Register content types
        FlexManager.registerContent("file", luminContent)
        FlexManager.registerContent("tool", luminContent)

        // Create main FlexWindow
        FlexManager.createFlexWindow(Enums.viewMode.HybridView, "Main", false)
        var fw = FlexManager.flexWindow("Main")
        if (fw) {
            fw.parent = central
            fw.anchors.fill = central
        }

        // Create default layout
        addPanel("Editor", "file", Enums.viewMode.FileView, Enums.dockArea.M)
        addPanel("Editor", "file", Enums.viewMode.FileView, Enums.dockArea.M)
        addPanel("Explorer", "tool", Enums.viewMode.ToolView, Enums.dockArea.L0)
        addPanel("Output", "tool", Enums.viewMode.ToolView, Enums.dockArea.B0)

        // Handle window recreation (e.g., after layout restore)
        FlexManager.onWindowRecreated = function(name, win) {
            if (name === "Main") {
                win.parent = central
                win.anchors.fill = central
            }
        }
    }

    // Helper to add a panel
    property int fileIdx: 0
    property int toolIdx: 0

    function addPanel(prefix, contentId, viewMode, area) {
        var idx = (contentId === "file") ? (++fileIdx) : (++toolIdx)
        var name = prefix + "-" + idx
        var desc = FlexManager.createDockWidget(viewMode, contentId, name, prefix + " " + idx)
        FlexManager.addDockWidget("Main", desc, area)
    }

    function openMarkdownFile(fileUrl) {
        var filePath = fileUrl.toString().replace("file:///", "")
        var fileName = filePath.split('/').pop()

        // 注册 Markdown 内容组件（首次调用）
        if (!FlexManager.content("markdown")) {
            FlexManager.registerContent("markdown", markdownEditorComponent)
        }

        // 创建唯一的 widget 名称
        var widgetName = "Markdown-" + (++fileIdx)

        // 保存文件信息到映射
        markdownFiles[widgetName] = {
            filePath: filePath,
            fileName: fileName
        }

        // 创建 Markdown 编辑器面板
        var desc = FlexManager.createDockWidget(Enums.viewMode.FileView, "markdown", widgetName, fileName)
        FlexManager.addDockWidget("Main", desc, Enums.dockArea.M)
    }

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        LuminWidgetBar {
            id: titleBar
            Layout.fillWidth: true
            title: "Lumin"
            iconSource: ""
            targetWindow: mainWindow
            menuBarComponent: mainMenuBarComponent
        }

        LuminToolBar {
            id: toolBar
            Layout.fillWidth: true
            toolItems: [
                { type: "button", icon: "▤", tooltip: "New", action: function() { console.log("New") } },
                { type: "button", icon: "▥", tooltip: "Open", action: function() { fileDialog.open() } },
                { type: "button", icon: "▦", tooltip: "Save", action: function() { console.log("Save") } },
                { type: "separator" },
                { type: "button", icon: "↶", tooltip: "Undo", action: function() { console.log("Undo") } },
                { type: "button", icon: "↷", tooltip: "Redo", action: function() { console.log("Redo") } },
                { type: "separator" },
                { type: "button", icon: "▶", tooltip: "Run", action: function() { console.log("Run") } },
                { type: "button", icon: "■", tooltip: "Stop", action: function() { console.log("Stop") } }
            ]
        }

        Item {
            id: central
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }
}
