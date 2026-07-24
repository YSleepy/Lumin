// MainMenuBar.qml
import QtQuick 2.15
import QtQuick.Controls 2.15
import Qt5Compat.GraphicalEffects

MenuBar {
    id: root
    spacing: 8
    Menu {
        title: "文件"
        MenuItem { text: "打开"; onTriggered: console.log("打开") }
        MenuItem { text: "保存"; onTriggered: console.log("保存") }
        MenuSeparator {}
        MenuItem { text: "退出"; onTriggered: Qt.quit() }
    }
    Menu {
        title: "编辑"
        MenuItem { text: "剪切" }
        MenuItem { text: "复制" }
    }
    Menu {
        title: "帮助"
        MenuItem { text: "关于" }
    }
    Component.onCompleted: {
        Qt.callLater(function() {
            var items = root.contentItem.children
            for (var i = 0; i < items.length; ++i) {
                var item = items[i]
                if (item.hasOwnProperty("contentItem") && item.contentItem) {
                    item.contentItem.color = "white"
                }
            }
        })
    }
}