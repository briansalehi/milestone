import QtQuick

Rectangle {
    id: button
    width: button_size
    height: parent.height * 2 / 3
    anchors.verticalCenter: parent.verticalCenter
    radius: 10
    color: button_color

    property color button_color: "black"
    property string button_text: "Button"
    property string button_font: "Nato Sans"
    property string button_font_color: "white"
    property int button_size: 100
    property int button_font_size: 24

    signal clicked

    Text {
        text: button_text
        color: button_font_color
        font.family: button_font
        font.pixelSize: button_font_size
        anchors.fill: parent
        anchors.leftMargin: 5
        anchors.rightMargin: 5
        elide: Text.ElideRight
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true
        onClicked: { button.clicked(); }
        onEntered: { parent.color = Qt.lighter(button_color); }
        onExited: { parent.color = button_color; }
    }
}
