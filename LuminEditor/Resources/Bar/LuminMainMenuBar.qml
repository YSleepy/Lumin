import QtQuick
import "../Common"

LuminMenuBar {
    id: root

    LuminMenu {
        title: "文件"

        LuminMenuItem { text: "新建"; onTriggered: console.log("新建") }
        LuminMenuItem { text: "打开"; onTriggered: console.log("打开") }
        LuminMenuItem { text: "保存"; onTriggered: console.log("保存") }

        LuminMenuSeparator {}

        LuminMenuItem { text: "退出"; onTriggered: Qt.quit() }
    }

    LuminMenu {
        title: "编辑"

        LuminMenuItem { text: "撤销"; onTriggered: console.log("撤销") }
        LuminMenuItem { text: "重做"; onTriggered: console.log("重做") }

        LuminMenuSeparator {}

        LuminMenuItem { text: "剪切"; onTriggered: console.log("剪切") }
        LuminMenuItem { text: "复制"; onTriggered: console.log("复制") }
        LuminMenuItem { text: "粘贴"; onTriggered: console.log("粘贴") }
    }

    LuminMenu {
        title: "视图"

        LuminMenuItem { text: "资源管理器"; onTriggered: console.log("资源管理器") }
        LuminMenuItem { text: "输出面板"; onTriggered: console.log("输出面板") }
        LuminMenuItem { text: "属性面板"; onTriggered: console.log("属性面板") }
    }

    LuminMenu {
        title: "帮助"

        LuminMenuItem { text: "Markdown 文档"; onTriggered: console.log("Markdown 文档") }
        LuminMenuItem { text: "关于 Lumin"; onTriggered: console.log("关于 Lumin") }
    }
}
