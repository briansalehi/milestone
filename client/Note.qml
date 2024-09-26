import QtQuick

Item {
    id: note
    anchors.fill: parent

    property string text
    property color color
    property color text_color
    property font font
    property int size

    property int note_id_value
    property string heading_value
    property string state_value
    property string creation_value
    property string last_update_value
    property string blocks_value

    BasicPage {
        id: page

        heading: note.heading_value
        color: note.color
        text_color: note.text_color
        font: note.font
        size: note.size
    }
}
