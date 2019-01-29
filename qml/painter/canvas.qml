import QtQuick 2.5
import QtQuick.Window 2.2

Window {
    id: root
    width: 512
    height: 512
    visible: true

    Canvas {
        id: canvas
        width: parent.width
        height: parent.height

        onPaint: {
            var context = getContext("2d")
            context.reset()
            context.lineWidth = 1

            context.strokeStyle = Qt.rgba(255, 0, 0, 1)
            context.ellipse(mouse.mouseX - 5, mouse.mouseY - 5, 10, 10)
            context.stroke()
        }

        MouseArea {
            id: mouse
            anchors.fill: parent
            hoverEnabled: true
            onPositionChanged: canvas.requestPaint()
        }
    }
}

