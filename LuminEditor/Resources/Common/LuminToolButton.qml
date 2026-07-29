import QtQuick
import QtQuick.Controls
import "../Theme"

ToolButton {
    id: control

    property color textColor: LuminTheme.textSoft
    property color textHoverColor: LuminTheme.textMain
    property color backgroundColor: "transparent"
    property color hoverColor: LuminTheme.hoverBg
    property color pressedColor: Qt.darker(hoverColor, 1.1)
    property int buttonRadius: 2
    property string iconText: text
    property int iconSize: 14

    implicitWidth: 32
    implicitHeight: 28

    contentItem: Text {
        text: control.iconText
        color: control.hovered ? control.textHoverColor : control.textColor
        font.pixelSize: control.iconSize
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        opacity: control.enabled ? 1.0 : 0.5
    }

    background: Rectangle {
        color: control.pressed ? control.pressedColor :
               (control.hovered ? control.hoverColor : control.backgroundColor)
        radius: control.buttonRadius

        Behavior on color {
            ColorAnimation { duration: 100 }
        }
    }
}
