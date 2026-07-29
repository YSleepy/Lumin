import QtQuick
import QtQuick.Controls
import "../Theme"

MenuBar {
    id: control

    property int itemSpacing: LuminTheme.menuSpacing
    property color textColor: LuminTheme.textSoft
    property color textHoverColor: LuminTheme.textMain
    property color hoverColor: LuminTheme.hoverBg
    property int itemRadius: LuminTheme.radius

    spacing: itemSpacing

    delegate: MenuBarItem {
        id: menuBarItem

        contentItem: Text {
            text: menuBarItem.text
            font: menuBarItem.font
            color: menuBarItem.hovered ? control.textHoverColor : control.textColor
            opacity: menuBarItem.hovered ? 1.0 : 0.8
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }

        background: Rectangle {
            color: menuBarItem.hovered ? control.hoverColor : "transparent"
            radius: control.itemRadius

            Behavior on color {
                ColorAnimation { duration: 100 }
            }
        }
    }

    background: Rectangle {
        color: "transparent"
    }
}
