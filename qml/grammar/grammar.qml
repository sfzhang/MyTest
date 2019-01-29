// rectangle.qml

import QtQuick 2.6

// The root element is the Rectangle
Rectangle {
    // name this element root
    id: root

    // properties: <name>: <value>
    width: 600; height: 400

    // color property
    color: "#D8D8D8"

    // Declare a nested element (child of root)
    Image {
        id: cottage

        // Reference the parent
        x: (parent.width - width) / 2
        y: 40

        // Source
        source: "cottage.png"
    }

    // Anther child of root
    Text {
        // un-named element

        // Reference element by id
        y: cottage.y + cottage.height + 20

        // Reference root element
        width: root.width

        horizontalAlignment: Text.AlignHCenter
        text: "Cottage"

        /*
           Font properties
           font.family: "Helvetica"
           font.pointSize: 24
           font.color: #FF1010
         */
        font {
            family: "Helvetica"
            pointSize: 18
        }
    }
}
