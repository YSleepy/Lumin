import QtQuick

Rectangle {
    property bool active: false
    property string hintPosition: ""

    color: active ? "#30569cd6" : "#101e1e1e"
    border.color: active ? "#569cd6" : "#444444"
    border.width: active ? 2 : 1
    radius: 2

    Rectangle {
        anchors.centerIn: parent
        width: Math.min(parent.width * 0.6, 200)
        height: Math.min(parent.height * 0.6, 80)
        color: active ? "#40569cd6" : "#151e1e1e"
        radius: 4
        visible: active

        Text {
            anchors.centerIn: parent
            text: hintPosition === "center" ? "⊞ 停靠到中央" : ""
            color: "#ffffff"
            font.pixelSize: 14
        }
    }
}
