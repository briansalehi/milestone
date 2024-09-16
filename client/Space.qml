import QtQuick

Rectangle {
    id: space
    color: Qt.lighter(entry_color)

    property int minimum_size: 200
    property int preferred_size
    property color entry_color
    property string entry_font
    property int entry_font_size
    property string title
    signal clicked()

    width: preferred_size < minimum_size ? minimum_size : preferred_size
    height: preferred_size < minimum_size ? minimum_size : preferred_size
    radius: preferred_size * 5 / 100

    Text {
        anchors.centerIn: parent
        color: 'white'
        font.family: entry_font
        font.pixelSize: entry_font_size
        text: title
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

    MouseArea {
        id: area
        anchors.fill: parent
        hoverEnabled: true
        onClicked: { space.clicked(); }
        onEntered: { parent.color = Qt.lighter(parent.color, 1.5); }
        onExited: { parent.color = Qt.lighter(entry_color); }
    }
}
