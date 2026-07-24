import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Control {
    id: root

    property string dockTitle: "Untitled"
    property bool closable: true
    default property alias contentData: contentArea.data
    property alias contentHost: contentArea
    property QtObject pane: null

    signal closeRequested()
    signal dragStarted()

    implicitWidth: 200
    implicitHeight: 150

    background: Rectangle {
        color: "#1e1e1e"
        border.color: "#3f3f46"
        border.width: 1
    }

    contentItem: ColumnLayout {
        spacing: 0

        Rectangle {
            id: titleBar
            Layout.fillWidth: true
            Layout.preferredHeight: 28
            color: (root.pane && root.pane.currentItem === root) ? "#007acc" : "#2d2d30"

            RowLayout {
                anchors.fill: parent
                anchors.leftMargin: 8
                anchors.rightMargin: 4
                spacing: 0

                Text {
                    text: root.dockTitle
                    color: "#cccccc"
                    font.pixelSize: 12
                    Layout.fillWidth: true
                    Layout.alignment: Qt.AlignVCenter
                    elide: Text.ElideRight
                }

                ToolButton {
                    visible: root.closable
                    Layout.preferredWidth: 20
                    Layout.preferredHeight: 20
                    Layout.alignment: Qt.AlignVCenter
                    onClicked: root.closeRequested()

                    contentItem: Text {
                        text: "×"
                        color: "#cccccc"
                        font.pixelSize: 14
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }

                    background: Rectangle {
                        color: parent.hovered ? "#e74c3c" : "transparent"
                        radius: 2
                    }
                }
            }

            MouseArea {
                anchors.fill: parent
                onClicked: root.dragStarted()
            }
        }

        Item {
            id: contentArea
            Layout.fillWidth: true
            Layout.fillHeight: true
            clip: true
        }
    }
}
