import QtQuick 2.0
Item {
    id: root

    signal dragged()

    Rectangle {
        anchors.centerIn: parent
        width: 20
        height: 20
        color: "blue"
        opacity: 0.3

        MouseArea {
            anchors.fill: parent
            drag.target: root
            onPositionChanged: {
                if(drag.active) {
                    dragged()
                }
            }
        }
    }
}
