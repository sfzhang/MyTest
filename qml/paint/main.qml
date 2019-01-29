import QtQuick 2.5
import QtQuick.Window 2.2

Window {
    visible: true

    width: 600
    height: 600

    Point {
        id: pointA
        x: 50
        y: 50
    }

    Point {
        id: pointB
        x: 250
        y: 50
    }

    Point {
        id: pointC
        x: 250
        y: 250
    }

    Point {
        id: pointD
        x: 50
        y: 250
    }


    Item {
        anchors.fill: parent

        Canvas {
            id: canvas
            anchors.fill: parent
            onPaint: {
                var ctx = canvas.getContext('2d');
                ctx.moveTo(pointA.x, pointA.y);
                ctx.lineTo(pointB.x, pointB.y);
                ctx.lineTo(pointC.x, pointC.y);
                ctx.lineTo(pointD.x, pointD.y);
                ctx.lineTo(pointA.x, pointA.y);
                ctx.stroke();
            }
            Component.onCompleted: {
                pointA.dragged.connect(repaint)
                pointB.dragged.connect(repaint)
                pointC.dragged.connect(repaint)
                pointD.dragged.connect(repaint)
            }

            function repaint() {
                var ctx = getContext("2d");
                ctx.clearRect(0, 0, canvas.width, canvas.height);
                ctx.beginPath();
                requestPaint()
            }
        }
    }
}
