import QtQuick
import QtQuick.Window
import QtQuick.Layouts
import "../Theme"
import "../Common"

Rectangle {
    id: root

    height: LuminTheme.titleBarHeight
    color: backgroundColor
    z: 1

    property string title: ""
    property string iconSource: ""
    property color backgroundColor: LuminTheme.bg0
    property Window targetWindow: null

    // 菜单栏以 Component 形式传入，由本组件负责实例化与布局
    property Component menuBarComponent: null
    readonly property var menuBar: menuBarLoader.item

    property alias showWindowButtons: windowButtons.visible

    RowLayout {
        anchors.fill: parent
        spacing: 0

        // 图标 + 标题
        RowLayout {
            Layout.leftMargin: 8
            Layout.alignment: Qt.AlignVCenter
            spacing: 8

            Image {
                visible: root.iconSource !== ""
                source: root.iconSource
                Layout.preferredWidth: 20
                Layout.preferredHeight: 20
                fillMode: Image.PreserveAspectFit
            }

            Text {
                visible: root.title !== ""
                text: root.title
                color: LuminTheme.textMain
                font.pixelSize: 13
                verticalAlignment: Text.AlignVCenter
            }
        }

        // 菜单栏
        Loader {
            id: menuBarLoader
            Layout.leftMargin: root.menuBarComponent ? 8 : 0
            Layout.alignment: Qt.AlignVCenter
            Layout.preferredHeight: root.height
            sourceComponent: root.menuBarComponent
        }

        // 可拖拽区域：菜单栏右边界到窗口控制区左侧
        MouseArea {
            id: dragArea
            Layout.fillWidth: true
            Layout.fillHeight: true
            acceptedButtons: Qt.LeftButton

            onPressed: {
                if (root.targetWindow)
                    root.targetWindow.startSystemMove()
            }

            onDoubleClicked: {
                if (!root.targetWindow)
                    return
                if (root.targetWindow.visibility === Window.Maximized)
                    root.targetWindow.showNormal()
                else
                    root.targetWindow.showMaximized()
            }
        }

        // 窗口生命控制区
        LuminWindowButtons {
            id: windowButtons
            Layout.alignment: Qt.AlignVCenter
            targetWindow: root.targetWindow
            buttonHeight: root.height
        }
    }
}
