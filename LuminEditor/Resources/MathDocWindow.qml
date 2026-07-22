import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.5
import Lumin.Editor 1.0

Window {
    id: mathDocWindow
    width: 800
    height: 600
    title: qsTr("Lumin数学文档")
    flags: Qt.Window | Qt.WindowCloseButtonHint | Qt.WindowTitleHint

    property string currentFile: ""
    property bool docked: false

    // 停靠信号
    signal RequestDock();
    signal RequestUndock();

    LMarkdownRenderer {
        id: renderer
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 0
        spacing: 0

        // 工具栏
        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: 36
            color: "#2d2d2d"

            RowLayout {
                anchors.fill: parent
                anchors.margins: 4
                spacing: 4

                // 文件选择
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
                    onCurrentTextChanged: {
                        var basePath = Qt.resolvedUrl("../../Doc/Math/");
                        var path = basePath + currentText;
                        contentView.text = renderer.LoadFile(path.replace("file:///", ""));
                    }
                }

                // 刷新按钮
                Button {
                    text: qsTr("刷新")
                    onClicked: {
                        var basePath = Qt.resolvedUrl("../../Doc/Math/");
                        var path = basePath + fileSelector.currentText;
                        contentView.text = renderer.LoadFile(path.replace("file:///", ""));
                    }
                }

                // 停靠/分离按钮
                Button {
                    text: docked ? qsTr("分离") : qsTr("停靠")
                    onClicked: {
                        if (docked) {
                            RequestUndock();
                        } else {
                            RequestDock();
                        }
                    }
                }
            }
        }

        // 内容区域
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

                text: qsTr("选择左侧文件以查看数学文档。\n\n文档文件位于 Doc/Math/ 目录下。")
            }
        }
    }

    Component.onCompleted: {
        // 尝试加载默认文件
        var basePath = Qt.resolvedUrl("../../Doc/Math/");
        var defaultFile = basePath + "数学基础.md";
        var content = renderer.LoadFile(defaultFile.replace("file:///", ""));
        if (content.indexOf("无法打开") < 0) {
            contentView.text = content;
        }
    }
}
