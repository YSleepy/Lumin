import QtQuick 2.15
import QtQuick.Controls 2.15
import "../Theme"

MenuBar {
    id: root
    spacing: LuminTheme.menuSpacing

    property int menuSpacing: 8
    Component.onCompleted:{
        console.info("[LuminMainMenuBar] x:", x, " y:", y, " w:", width, " h:", height)
    }

    Menu {
        title: "文件"

        Action { text: "打开"; onTriggered: console.log("打开") }
        Action { text: "保存"; onTriggered: console.log("保存") }
        MenuSeparator {}
        Action { text: "退出"; onTriggered: Qt.quit() }
    }
    Menu {
        title: "编辑"

        Action { text: "剪切" }
        Action { text: "复制" }
    }
    Menu {
        title: "帮助"

        Action { text: "Markdown" }
        Action { text: "关于Lumin" }
    }

    delegate: MenuBarItem {
        id: control
        contentItem: Text {
            text: control.text
            font: control.font
            color: control.hovered ? LuminTheme.textMain : LuminTheme.textSoft
            opacity: control.hovered ? 1.0 : 0.8
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }

        background: Rectangle {
            color: control.hovered ? LuminTheme.hoverBg : "transparent"
            radius: LuminTheme.radius
        }
    }
}
