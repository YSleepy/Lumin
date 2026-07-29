import QtQuick
import "../Theme"

Rectangle {
    id: root

    property bool horizontal: false
    property color separatorColor: LuminTheme.separator
    property int thickness: 1
    property int length: 20

    width: horizontal ? length : thickness
    height: horizontal ? thickness : length
    color: separatorColor
}
