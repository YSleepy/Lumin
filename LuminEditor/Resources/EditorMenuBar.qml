import QtQuick
import QtQuick.Controls

MenuBar {
    background: Rectangle { color: "transparent" }

    Menu {
        title: qsTr("文件(&F)")

        Action {
            text: qsTr("新建项目(&N)...")
            shortcut: StandardKey.New
            onTriggered: {}
        }

        Action {
            text: qsTr("打开项目(&O)...")
            shortcut: StandardKey.Open
            onTriggered: {}
        }

        MenuSeparator {}

        Action {
            text: qsTr("保存场景(&S)")
            shortcut: StandardKey.Save
            onTriggered: {}
        }

        Action {
            text: qsTr("另存为...")
            shortcut: StandardKey.SaveAs
            onTriggered: {}
        }

        MenuSeparator {}

        Action {
            text: qsTr("退出(&X)")
            shortcut: StandardKey.Quit
            onTriggered: Qt.quit()
        }
    }

    Menu {
        title: qsTr("编辑(&E)")

        Action {
            text: qsTr("撤销(&U)")
            shortcut: StandardKey.Undo
            onTriggered: {}
        }

        Action {
            text: qsTr("重做(&R)")
            shortcut: StandardKey.Redo
            onTriggered: {}
        }

        MenuSeparator {}

        Action {
            text: qsTr("剪切(&X)")
            shortcut: StandardKey.Cut
            onTriggered: {}
        }

        Action {
            text: qsTr("复制(&C)")
            shortcut: StandardKey.Copy
            onTriggered: {}
        }

        Action {
            text: qsTr("粘贴(&P)")
            shortcut: StandardKey.Paste
            onTriggered: {}
        }

        Action {
            text: qsTr("删除(&D)")
            shortcut: StandardKey.Delete
            onTriggered: {}
        }

        MenuSeparator {}

        Action {
            text: qsTr("编辑器设置...")
            onTriggered: {}
        }
    }

    Menu {
        title: qsTr("Git")

        Action {
            text: qsTr("提交(&C)...")
            onTriggered: {}
        }

        Action {
            text: qsTr("推送(&P)")
            onTriggered: {}
        }

        Action {
            text: qsTr("拉取(&L)")
            onTriggered: {}
        }

        MenuSeparator {}

        Action {
            text: qsTr("查看历史...")
            onTriggered: {}
        }

        Action {
            text: qsTr("查看差异")
            onTriggered: {}
        }
    }

    Menu {
        title: qsTr("项目(&P)")

        Action {
            text: qsTr("运行(&R)")
            onTriggered: {}
        }

        Action {
            text: qsTr("打包...")
            onTriggered: {}
        }

        MenuSeparator {}

        Action {
            text: qsTr("项目设置...")
            onTriggered: {}
        }
    }

    Menu {
        title: qsTr("帮助(&H)")

        Action {
            text: qsTr("Lumin数学文档(&M)")
            shortcut: "Ctrl+M"
            onTriggered: mainWindow.openMathDoc()
        }

        MenuSeparator {}

        Action {
            text: qsTr("关于 LuminEditor(&A)")
            onTriggered: {}
        }

        Action {
            text: qsTr("关于 Qt")
            onTriggered: {}
        }
    }
}
