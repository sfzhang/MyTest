import QtQuick 2.12
import QtQuick.Window 2.2
import QtQml 2.2

import Quick 1.0

Window {
    visible: true
    width: 400
    height: 400

    Quick {
        id: quick
        anchors.top: parent.top
        anchors.left: parent.left

        width: parent.width
        height: parent.height
    }
}
