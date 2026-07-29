import QtQuick
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Layouts

import "Resources/Dock"
import "Resources/Bar"
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

    // 标题栏中的菜单栏
    Component {
        id: mainMenuBarComponent
        LuminMainMenuBar {}
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
                { type: "button", icon: "▥", tooltip: "Open", action: function() { console.log("Open") } },
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
