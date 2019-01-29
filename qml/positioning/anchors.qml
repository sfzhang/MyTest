import QtQuick 2.0

Item {
    Rectangle {
        id: rect1
        color: "blue"
        width: 50; height: 50
    }

    Rectangle {
        id: rect2
        color: "red"
        width: 50; height: 50

        anchors.left: rect1.right
        anchors.top: rect1.bottom
    }
}
