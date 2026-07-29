import QtQuick
import QtQuick.Controls
import "../Theme"

MenuSeparator {
    id: control

    property color separatorColor: LuminTheme.separator
    property int thickness: 1

    padding: 0
    topPadding: 4
    bottomPadding: 4

    contentItem: Rectangle {
        implicitWidth: 160
        implicitHeight: control.thickness
        color: control.separatorColor
    }
}
