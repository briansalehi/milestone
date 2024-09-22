import QtQuick

Item {
    id: space
    width: space.size
    height: space.size

    property int minimum_size: 200
    property int preferred_size
    property int size: preferred_size < minimum_size ? minimum_size : preferred_size
    property color color
    property font font
    property string text
    property color text_color
    signal clicked()

    Rectangle {
        anchors.fill: parent
        color: space.color
        radius: space.size * 8 / 100

        Text {
            text: space.text
            color: space.text_color
            font: space.font
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            anchors.centerIn: parent
        }

        MouseArea {
            id: area
            anchors.fill: parent
            hoverEnabled: true
            onClicked: { space.clicked(); }
            onEntered: { parent.color = Qt.lighter(space.color, 1.5); }
            onExited: { parent.color = space.color; }
        }
    }
}
