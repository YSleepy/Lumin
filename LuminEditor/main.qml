import QtQuick
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Layouts

import "Resources"
import "Resources/Bar"

ApplicationWindow {
    id: mainWindow
    visible: true
    width: 1280
    height: 720
    title: "LuminEditor"
    color: "#1e1e1e"

    flags: Qt.FramelessWindowHint | Qt.Window

    LuminWidgetBar {
        title: "Lumin"
        targetWindow: mainWindow
        menuBar: LuminMainMenuBar{}
    }
}
