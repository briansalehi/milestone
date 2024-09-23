import QtQuick

Item {
    id: page
    anchors.fill: parent
    anchors.topMargin: parent.height * 10 / 100
    anchors.bottomMargin: parent.height * 10 / 100
    anchors.leftMargin: parent.width * 20 / 100
    anchors.rightMargin: parent.width * 20 / 100

    property color color
    property color text_color
    property font font
    property int size
    property string text

    Column {
        anchors.fill: parent

        Heading {
            text: page.text
            font: page.font
            color: page.text_color
        }
    }
}
