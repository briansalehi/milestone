import QtQuick

Rectangle
{
    id: frame

    property color foreground
    property color background

    color: frame.foreground
    radius: 20

    Rectangle
    {
        color: frame.background
        radius: parent.radius * 80 / 100
        anchors.fill: parent
        anchors.margins: parent.radius * 80 / 100
    }
}
