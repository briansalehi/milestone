import QtQuick

Rectangle {
    id: button
    width: button.size
    height: parent.height * 2 / 3
    anchors.verticalCenter: parent.verticalCenter
    radius: 10
    color: disabled ? Qt.darker(button.color) : button.color

    property string text
    property font font
    property int size
    property color color
    property color text_color
    property bool disabled

    signal clicked

    Text {
        text: button.text
        color: button.text_color
        font: button.font
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
        onClicked: {
            button.clicked();
        }
        onEntered: {
            if (!button.disabled)
            {
                parent.color = Qt.lighter(button.color);
            }
        }
        onExited: {
            if (!button.disabled)
            {
                parent.color = button.color;
            }
        }
    }
}
