import QtQuick
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Layouts

import "Resources"
import "Resources/Bar"
import "Resources/Dock"

ApplicationWindow {
    id: mainWindow
    visible: true
    width: 1280
    height: 720
    title: "LuminEditor"
    color: "#1e1e1e"

    flags: Qt.FramelessWindowHint | Qt.Window

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

        LuminDockContainer {
            id: dockContainer
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }

    Component.onCompleted: {
        // Create dock items with placeholder content
        var explorer = dockContainer.createItem("Explorer")
        var editor = dockContainer.createItem("Editor")
        var output = dockContainer.createItem("Output")

        // Add colored placeholders so we can see the panels
        var r1 = Qt.createQmlObject(
            'import QtQuick; Rectangle { anchors.fill: parent; color: "#252526" }',
            explorer.contentHost)
        var r2 = Qt.createQmlObject(
            'import QtQuick; Rectangle { anchors.fill: parent; color: "#1e1e1e" }',
            editor.contentHost)
        var r3 = Qt.createQmlObject(
            'import QtQuick; Rectangle { anchors.fill: parent; color: "#252526" }',
            output.contentHost)

        // Layout: Editor as initial center
        dockContainer.addDockItem(editor, "center", null)

        // Dock Explorer to the left of Editor's pane
        dockContainer.addDockItem(explorer, "left", editor.pane)

        // Dock Output below Editor's pane
        dockContainer.addDockItem(output, "bottom", editor.pane)
    }
}
