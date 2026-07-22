import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Dialogs
import Lumin.Editor 1.0

ColumnLayout {
    id: panel
    anchors.fill: parent
    anchors.margins: 0
    spacing: 0

    // 当前停靠位置（由外部设置）
    property int dockPosition: MainWindow.DockPosition.None

    Rectangle {
        Layout.fillWidth: true
        Layout.preferredHeight: 36
        color: "#2d2d2d"

        RowLayout {
            anchors.fill: parent
            anchors.margins: 4
            spacing: 4

            Text {
                text: qsTr("数学文档")
                color: "#cccccc"
                font.pixelSize: 13
                Layout.leftMargin: 4
            }

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
                onCurrentTextChanged: reloadBuiltinDoc()
            }

            Button {
                text: qsTr("打开文件...")
                onClicked: fileDialog.open()
            }

            Button {
                text: qsTr("✕")
                width: 30
                onClicked: closePanel()
            }
        }
    }

    LMarkdownView {
        id: markdownView
        Layout.fillWidth: true
        Layout.fillHeight: true
        readOnly: true
    }

    FileDialog {
        id: fileDialog
        title: qsTr("打开 Markdown 文件")
        nameFilters: ["Markdown files (*.md)", "All files (*)"]
        onAccepted: {
            markdownView.LoadFile(selectedFile);
            fileSelector.currentIndex = -1;
        }
    }

    function reloadBuiltinDoc() {
        var basePath = Qt.resolvedUrl("../../Doc/Math/");
        var path = basePath + fileSelector.currentText;
        markdownView.LoadFile(path.replace("file:///", ""));
    }

    function closePanel() {
        if (dockPosition !== MainWindow.DockPosition.None) {
            mainWindow.undockPanel(dockPosition);
        } else if (typeof docWindow !== "undefined" && docWindow) {
            docWindow.close();
        }
    }
}
