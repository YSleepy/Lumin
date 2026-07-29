import QtQuick
import QtQuick.Window
import "../Theme"

Row {
    id: root

    property Window targetWindow: null
    property int buttonWidth: 40
    property int buttonHeight: 28

    readonly property bool isMaximized: targetWindow
                                        && targetWindow.visibility === Window.Maximized

    spacing: 0

    LuminToolButton {
        width: root.buttonWidth
        height: root.buttonHeight
        iconText: "─"
        iconSize: 16
        buttonRadius: 0
        onClicked: if (root.targetWindow) root.targetWindow.showMinimized()
    }

    LuminToolButton {
        width: root.buttonWidth
        height: root.buttonHeight
        iconText: root.isMaximized ? "❐" : "☐"
        iconSize: 16
        buttonRadius: 0
        onClicked: {
            if (!root.targetWindow)
                return
            if (root.isMaximized)
                root.targetWindow.showNormal()
            else
                root.targetWindow.showMaximized()
        }
    }

    LuminToolButton {
        width: root.buttonWidth
        height: root.buttonHeight
        iconText: "✕"
        iconSize: 16
        buttonRadius: 0
        hoverColor: LuminTheme.closeRed
        onClicked: if (root.targetWindow) root.targetWindow.close()
    }
}
