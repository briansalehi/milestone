import QtQuick

Item {
    id: root
    height: 45
    width: height * 2

    property alias color: background.color
    property alias text: label.text
    signal clicked

    Rectangle {
        id: background
        radius: 5
        color: 'lightgreen'
        anchors.fill: root

        Text {
            id: label
            anchors.centerIn: parent
            font.family: 'OpenSans'
            font.pixelSize: 18
            horizontalAlignment: Text.AlignHCenter
        }
    }

    MouseArea {
        anchors.fill: root
        onClicked: { root.clicked(); }
    }
}
