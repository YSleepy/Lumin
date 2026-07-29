import QtQuick
import QtQuick.Controls
import "../Theme"

Menu {
    id: control

    property color backgroundColor: LuminTheme.bg2
    property color borderColor: LuminTheme.frame
    property int menuRadius: LuminTheme.radius
    property int menuBorderWidth: 1

    implicitWidth: Math.max(implicitBackgroundWidth + leftInset + rightInset,
                            contentWidth + leftPadding + rightPadding)
    implicitHeight: Math.max(implicitBackgroundHeight + topInset + bottomInset,
                             contentHeight + topPadding + bottomPadding)

    margins: 0
    padding: 4

    delegate: LuminMenuItem {}

    background: Rectangle {
        implicitWidth: 180
        implicitHeight: 32
        color: control.backgroundColor
        radius: control.menuRadius
        border.width: control.menuBorderWidth
        border.color: control.borderColor
    }
}
