import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3

ApplicationWindow {
    id: mainWindow
    visible: true
    width: 1280
    height: 720
    title: "LuminEditor"

    // 数学文档相关
    property bool mathDocDocked: false
    property var mathDocWindow: null

    menuBar: MenuBar {
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
                onTriggered: OpenMathDoc()
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

    // 主内容区
    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        // 停靠的数学文档面板
        Loader {
            id: dockedMathDoc
            Layout.fillWidth: true
            Layout.preferredHeight: 300
            visible: mathDocDocked
            active: mathDocDocked
            sourceComponent: mathDocComponent
        }

        // 中央区域（编辑器视口等，暂时占位）
        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: "#1e1e1e"

            Text {
                anchors.centerIn: parent
                text: qsTr("编辑视口区域")
                color: "#555555"
                font.pixelSize: 24
            }
        }
    }

    // 数学文档组件（停靠和独立窗口共用）
    Component {
        id: mathDocComponent

        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 0
            spacing: 0

            Rectangle {
                Layout.fillWidth: true
                Layout.preferredHeight: 36
                color: "#2d2d2d"

                RowLayout {
                    anchors.fill: parent
                    anchors.margins: 4
                    spacing: 4

                    ComboBox {
                        id: fileSelector
                        Layout.fillWidth: true
                        model: [
                            "数学基础.md",
                            "向量运算.md",
                            "矩阵运算.md",
                            "四元数.md",
                            "坐标系变换.md"
                        ]
                        onCurrentTextChanged: ReloadDoc()
                    }

                    Button {
                        text: qsTr("刷新")
                        onClicked: ReloadDoc()
                    }

                    Button {
                        text: mathDocDocked ? qsTr("分离") : qsTr("停靠")
                        onClicked: ToggleDock()
                    }
                }
            }

            ScrollView {
                Layout.fillWidth: true
                Layout.fillHeight: true

                TextArea {
                    id: contentView
                    readOnly: true
                    textFormat: TextEdit.RichText
                    wrapMode: TextEdit.Wrap
                    selectByMouse: true
                    font.family: "Microsoft YaHei"
                    color: "#cccccc"

                    background: Rectangle {
                        color: "#1e1e1e"
                    }

                    text: qsTr("选择文档以查看数学内容。")
                }
            }

            function ReloadDoc() {
                var basePath = Qt.resolvedUrl("../Doc/Math/");
                var path = basePath + fileSelector.currentText;
                contentView.text = renderer.LoadFile(path.replace("file:///", ""));
            }
        }
    }

    // 独立窗口组件
    Component {
        id: mathDocWindowComponent

        Window {
            id: docWindow
            width: 800
            height: 600
            title: qsTr("Lumin数学文档")
            flags: Qt.Window | Qt.WindowCloseButtonHint | Qt.WindowTitleHint

            property bool isDocked: false

            onClosing: {
                mainWindow.mathDocWindow = null;
            }

            Loader {
                anchors.fill: parent
                sourceComponent: mathDocComponent
                onLoaded: {
                    // 覆盖组件内的 ToggleDock 函数
                    item.ToggleDock = function() {
                        docWindow.close();
                        mainWindow.mathDocDocked = true;
                        mainWindow.mathDocWindow = null;
                    };
                }
            }
        }
    }

    // 全局函数：打开数学文档
    function OpenMathDoc() {
        if (mathDocWindow) {
            mathDocWindow.raise();
            mathDocWindow.requestActivate();
            return;
        }

        if (mathDocDocked) {
            return;
        }

        var window = mathDocWindowComponent.createObject(mainWindow);
        mathDocWindow = window;
        window.show();
    }

    function ToggleDock() {
        if (mathDocDocked) {
            mathDocDocked = false;
            var window = mathDocWindowComponent.createObject(mainWindow);
            mathDocWindow = window;
            window.show();
        } else {
            if (mathDocWindow) {
                mathDocWindow.close();
                mathDocWindow = null;
            }
            mathDocDocked = true;
        }
    }

    // 注册渲染器
    LMarkdownRenderer {
        id: renderer
    }
}
