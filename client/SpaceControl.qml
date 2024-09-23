import QtQuick

Item {
    id: controls
    anchors.horizontalCenter: parent.horizontalCenter
    width: parent.width * 5 / 10
    height: parent.height * 10 / 100

    property font font
    property color color
    property color text_color
    signal clicked

    Row {
        spacing: 15
        anchors.fill: parent

        ControlButton {
            id: back
            size: parent.width / 3
            text: "Back"
            color: controls.color
            font: controls.font
            text_color: controls.text_color
            onClicked: { controls.clicked(); }
        }

        ControlButton {
            id: next
            size: parent.width / 3
            text: "Next"
            color: controls.color
            font: controls.font
            text_color: controls.text_color
            onClicked: { controls.clicked(); }
        }
    }
}
