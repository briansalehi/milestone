import QtQuick

Item {
    id: note
    anchors.fill: parent

    property string text
    property color color
    property color text_color
    property font font
    property int size

    Page {
        anchors.fill: parent

        text: note.text
        color: note.color
        text_color: note.text_color
        font: note.font
        size: note.size
    }
}
