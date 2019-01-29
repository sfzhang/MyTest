import QtQuick 2.0

Text {
	width: 100; height: 100
    text: msg.author    // invokes Message::author() to get this value

	MouseArea {
    	anchors.fill: parent
        onClicked: {
        	var result = msg.postMessage("Hello from QML")
            console.log("Result of postMessage():", result)
            msg.refresh();
        }
    }

    Component.onCompleted: {
    	msg.author = "Jonah"  // invokes Message::setAuthor()
    }
}
