import QtQuick

Rectangle {
    id: entry
    height: 70
    radius: 13

    property color background_color
    property color foreground_color
    property string entry_font
    property string name
    property string sections
    property int entryWidth

    color: Qt.lighter(background_color)

    Text {
        id: headline_id
        text: name
        color: foreground_color
        font.pixelSize:  24
        font.family: entry_font
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        anchors.left: parent.left
        anchors.leftMargin: 15
        anchors.verticalCenter: parent.verticalCenter
    }

    Text {
        id: update_id
        text: sections
        color: Qt.darker(foreground_color)
        font.pixelSize: 24
        font.family: entry_font
        anchors.right: parent.right
        anchors.rightMargin: 15
        anchors.verticalCenter: parent.verticalCenter
    }
}
