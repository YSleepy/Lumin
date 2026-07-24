import QtQuick 2.15
import QtQuick.Controls 2.15
import Qt5Compat.GraphicalEffects

MenuBar {
    id: root
    spacing: menuSpacing

    property string menuTextColor: "white"
    property int menuSpacing: 8

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
        MenuItem { text: "Markdown" }
        MenuItem { text: "关于Lumin" }
    }

    delegate: MenuBarItem {
        id: control
        contentItem: Text {
            text: control.text
            font: control.font
            color: root.menuTextColor
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }
    }
}