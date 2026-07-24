import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Control {
    id: root

    readonly property string dockType: "pane"
    property QtObject parentSplit: null

    property int currentIndex: 0
    property int tabCount: 0
    property Item currentItem: {
        var c = contentArea.children
        return (currentIndex >= 0 && currentIndex < c.length) ? c[currentIndex] : null
    }

    function addItem(item) {
        item.parent = contentArea
        item.anchors.fill = contentArea
        item.visible = false
        item.pane = root
        currentIndex = contentArea.children.length - 1
        tabCount = contentArea.children.length
        updateVisibility()
    }

    function removeItem(index) {
        var children = contentArea.children
        if (index < 0 || index >= children.length)
            return
        var item = children[index]
        item.parent = null
        item.pane = null
        var newLen = contentArea.children.length
        if (currentIndex >= newLen)
            currentIndex = Math.max(0, newLen - 1)
        tabCount = newLen
        updateVisibility()
    }

    function removeItemDirect(item) {
        var children = contentArea.children
        for (var i = 0; i < children.length; i++) {
            if (children[i] === item) {
                removeItem(i)
                return
            }
        }
    }

    function setCurrentIndex(idx) {
        if (idx >= 0 && idx < contentArea.children.length) {
            currentIndex = idx
            updateVisibility()
        }
    }

    function updateVisibility() {
        var children = contentArea.children
        for (var i = 0; i < children.length; i++) {
            children[i].visible = (i === currentIndex)
        }
    }

    implicitWidth: 200
    implicitHeight: 150

    background: Rectangle {
        color: "#1e1e1e"
        border.color: "#3f3f46"
        border.width: 1
    }

    contentItem: ColumnLayout {
        spacing: 0

        Item {
            id: contentArea
            Layout.fillWidth: true
            Layout.fillHeight: true
            clip: true
        }

        TabBar {
            id: tabBar
            Layout.fillWidth: true
            visible: root.tabCount > 1
            Layout.preferredHeight: 30
            position: TabBar.Footer

            Repeater {
                model: root.tabCount
                TabButton {
                    text: {
                        var c = contentArea.children
                        return (index < c.length) ? (c[index].dockTitle || "") : ""
                    }
                    checked: index === root.currentIndex
                    onClicked: root.setCurrentIndex(index)

                    background: Rectangle {
                        color: checked ? "#1e1e1e" : (hovered ? "#3e3e3e" : "#2d2d30")
                    }

                    contentItem: Text {
                        text: parent.text
                        color: checked ? "#ffffff" : "#cccccc"
                        font.pixelSize: 12
                        elide: Text.ElideRight
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                }
            }
        }
    }

    Component.onCompleted: updateVisibility()
}
