import QtQuick
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Layouts

import "Resources/Dock"
import "Resources/Bar"
import "qrc:/qml/Dock"

ApplicationWindow {
    id: mainWindow
    visible: true
    width: 1280
    height: 720
    title: "LuminEditor"
    color: Theme.bg0

    flags: Qt.FramelessWindowHint | Qt.Window

    // Content component registered for all dock panels
    Component {
        id: luminContent
        LuminDockContent {}
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
            id: luminWidgetBar
            Layout.fillWidth: true
            title: "Lumin"
            targetWindow: mainWindow
            menuBar: LuminMainMenuBar {}
        }

        LuminToolBar {
            id: luminToolBar
            Layout.fillWidth: true
        }

        Item {
            id: central
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }
}
