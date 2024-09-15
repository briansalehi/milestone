import QtQuick

Rectangle {
    id: space
    color: Qt.lighter(entry_color)
    width: parent.width / 3
    height: parent.width / 3
    radius: parent.width * 5 / 100

    property color entry_color
    property string entry_font
    property string title
    signal clicked()

    Text {
        anchors.centerIn: parent
        color: 'white'
        font.family: entry_font
        font.pixelSize: 42
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
