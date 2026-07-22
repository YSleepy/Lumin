import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Dialogs
import Lumin.Editor 1.0

Rectangle {
    id: panel
    color: "#1e1e1e"

    property alias fileSelector: fileSelector
    property alias markdownView: markdownView
    property int dockPosition: 0

    ColumnLayout {
        anchors.fill: parent
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

                Text {
                    text: qsTr("数学文档")
                    color: "#cccccc"
                    font.pixelSize: 13
                    Layout.leftMargin: 4
                }

                ComboBox {
                    id: fileSelector
                    Layout.fillWidth: true
                    Layout.preferredHeight: 28
                    model: ["数学基础.md", "向量运算.md", "矩阵运算.md", "四元数.md", "坐标系变换.md"]
                    onCurrentTextChanged: {
                        var basePath = Qt.resolvedUrl("../../Doc/Math/");
                        var path = basePath + currentText;
                        markdownView.LoadFile(path.replace("file:///", ""));
                    }
                }

                Button {
                    text: qsTr("打开文件...")
                    onClicked: fileDialog.open()
                }

                Button {
                    text: qsTr("分离")
                    visible: dockPosition !== 0
                    onClicked: {
                        if (dockPosition !== 0) {
                            var info = mainWindow.undockPanel(dockPosition);
                            if (info && info.window) {
                                info.window.dockPosition = 0;
                                info.window.show();
                            }
                        }
                    }
                }

                Button {
                    text: qsTr("✕")
                    width: 30
                    onClicked: {
                        if (dockPosition !== 0) {
                            mainWindow.undockPanel(dockPosition);
                        }
                    }
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
    }
}
