import QtQuick
import QtQuick.Controls

SplitView {
    id: root

    readonly property string dockType: "split"
    property QtObject parentSplit: null
    // orientation is inherited from SplitView

    function childCount() { return contentChildren.length }
    function childAt(idx) { return (idx >= 0 && idx < contentChildren.length) ? contentChildren[idx] : null }
    function indexOfChild(c) { return contentChildren.indexOf(c) }

    function addChildDirect(item) {
        item.parent = root
    }

    function removeChildDirect(item) {
        item.parent = null
    }

    handle: Rectangle {
        implicitWidth: 4
        implicitHeight: 4
        color: "#3f3f46"
        Rectangle {
            anchors.centerIn: parent
            width: root.orientation === Qt.Horizontal ? 2 : parent.width - 4
            height: root.orientation === Qt.Vertical ? 2 : parent.height - 4
            color: "#555555"
        }
    }
}
