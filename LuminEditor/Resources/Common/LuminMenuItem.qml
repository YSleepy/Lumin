import QtQuick
import QtQuick.Controls
import "../Theme"

MenuItem {
    id: control

    property color textColor: LuminTheme.textSoft
    property color textHighlightColor: LuminTheme.textMain
    property color highlightColor: LuminTheme.accent
    property int itemRadius: 3

    implicitWidth: Math.max(implicitBackgroundWidth + leftInset + rightInset,
                            implicitContentWidth + leftPadding + rightPadding)
    implicitHeight: Math.max(implicitBackgroundHeight + topInset + bottomInset,
                             implicitContentHeight + topPadding + bottomPadding)

    padding: 6
    spacing: 6

    contentItem: Text {
        text: control.text
        font.pointSize: 10
        color: control.highlighted ? control.textHighlightColor : control.textColor
        horizontalAlignment: Text.AlignLeft
        verticalAlignment: Text.AlignVCenter
        elide: Text.ElideRight
    }

    background: Rectangle {
        implicitWidth: 120
        implicitHeight: 28
        color: control.highlighted ? control.highlightColor : "transparent"
        radius: control.itemRadius

        Behavior on color {
            ColorAnimation { duration: 100 }
        }
    }
}
