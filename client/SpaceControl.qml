import QtQuick

Item {
    id: controls
    anchors.horizontalCenter: parent.horizontalCenter
    width: parent.width * 5 / 10
    height: parent.height * 10 / 100

    property string font_family
    property int font_size
    property color button_color
    signal clicked

    Row {
        spacing: 15
        anchors.fill: parent

        ControlButton {
            id: back
            button_size: parent.width / 3
            button_text: "Back"
            button_color: controls.button_color
            button_font: font_family
            button_font_size: font_size
            button_font_color: "white"
            onClicked: { controls.clicked(); }
        }

        ControlButton {
            id: next
            button_size: parent.width / 3
            button_text: "Next"
            button_color: controls.button_color
            button_font: font_family
            button_font_size: font_size
            button_font_color: "white"
            onClicked: { controls.clicked(); }
        }
    }
}
