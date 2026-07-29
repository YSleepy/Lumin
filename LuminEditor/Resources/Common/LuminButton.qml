import QtQuick
import QtQuick.Controls
import "../Theme"

Button {
    id: control

    property color textColor: LuminTheme.textSoft
    property color textHoverColor: LuminTheme.textMain
    property color backgroundColor: "transparent"
    property color hoverColor: LuminTheme.hoverBg
    property color pressedColor: Qt.darker(hoverColor, 1.1)
    property int buttonRadius: LuminTheme.radius

    implicitWidth: Math.max(implicitBackgroundWidth + leftInset + rightInset,
                            implicitContentWidth + leftPadding + rightPadding)
    implicitHeight: Math.max(implicitBackgroundHeight + topInset + bottomInset,
                             implicitContentHeight + topPadding + bottomPadding)

    padding: 6
    spacing: 4

    contentItem: Text {
        text: control.text
        font: control.font
        color: control.hovered ? control.textHoverColor : control.textColor
        opacity: control.enabled ? 1.0 : 0.5
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        elide: Text.ElideRight
    }

    background: Rectangle {
        implicitWidth: 80
        implicitHeight: 28
        color: control.pressed ? control.pressedColor :
               (control.hovered ? control.hoverColor : control.backgroundColor)
        radius: control.buttonRadius

        Behavior on color {
            ColorAnimation { duration: 100 }
        }
    }
}
