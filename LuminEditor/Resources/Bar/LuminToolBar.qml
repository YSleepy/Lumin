import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import "../Theme"
import "../Common"

pragma ComponentBehavior: Bound

Rectangle {
    id: root

    height: LuminTheme.toolBarHeight
    color: LuminTheme.bg0

    // 数据驱动：[{ type: "button" | "separator", icon, tooltip, action, ... }]
    property alias toolItems: toolRepeater.model
    property int buttonSpacing: 2
    property int sectionSpacing: 4

    RowLayout {
        anchors.fill: parent
        anchors.leftMargin: 4
        anchors.rightMargin: 4
        spacing: root.buttonSpacing

        Repeater {
            id: toolRepeater

            delegate: Loader {
                id: itemLoader

                required property var modelData

                readonly property bool isSeparator: modelData && modelData.type === "separator"

                Layout.alignment: Qt.AlignVCenter
                Layout.leftMargin: isSeparator ? root.sectionSpacing : 0
                Layout.rightMargin: isSeparator ? root.sectionSpacing : 0

                sourceComponent: isSeparator ? separatorComponent : buttonComponent

                // 将 modelData 作为属性传递给动态创建的组件
                onLoaded: {
                    if (item) {
                        item.itemData = Qt.binding(function() { return modelData })
                    }
                }
            }
        }

        Item { Layout.fillWidth: true }
    }

    Component {
        id: buttonComponent

        LuminToolButton {
            property var itemData: null

            iconText: itemData && itemData.icon !== undefined ? itemData.icon : (itemData && itemData.text || "")
            iconSize: itemData && itemData.iconSize !== undefined ? itemData.iconSize : 14
            implicitWidth: itemData && itemData.width !== undefined ? itemData.width : 32
            implicitHeight: itemData && itemData.height !== undefined ? itemData.height : 28
            enabled: itemData && itemData.enabled !== undefined ? itemData.enabled : true

            ToolTip.text: itemData && itemData.tooltip || ""
            ToolTip.visible: hovered && ToolTip.text !== ""
            ToolTip.delay: 500

            onClicked: if (itemData && itemData.action) itemData.action()
        }
    }

    Component {
        id: separatorComponent

        LuminSeparator {
            horizontal: false
            length: 20
        }
    }
}
