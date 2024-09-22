import QtQuick

Item {
    id: page
    anchors.fill: parent
    anchors.topMargin: parent.height * 10 / 100
    anchors.bottomMargin: parent.height * 10 / 100
    anchors.leftMargin: parent.width * 20 / 100
    anchors.rightMargin: parent.width * 20 / 100

    property color text_color
    property string text_font
    property int text_size

    Column {
        anchors.fill: parent

        Heading {
            color: text_color
            font: text_font
            size: text_size
        }
    }
}
