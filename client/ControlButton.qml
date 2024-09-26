import QtQuick

Rectangle {
    id: button
    width: button.size
    height: button.size
    radius: 10

    property string text
    property font font
    property int size
    property color text_color
    property bool disabled
    property color default_color

    signal clicked

    color: disabled ? Qt.darker(button.color) : button.color

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
                parent.color = Qt.lighter(button.default_color);
            }
        }
        onExited: {
            if (!button.disabled)
            {
                parent.color = button.default_color;
            }
        }
    }
}
