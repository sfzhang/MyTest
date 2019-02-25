import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.VirtualKeyboard 2.2
import RingNode 1.0

Window {
    id: window
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    RingNode {
        id: node
        anchors.top: parent.top
        anchors.left: parent.left

        width: parent.width
        height: parent.height
    }
}
