import QtQuick

Item {
    id: box
    height: text.implicitHeight * 2

    /* database properties */
    property int block_id
    property int position
    property string content
    property string type
    property string language
    property string last_update

    /* customization properties */
    property color text_color
    property color background
    property font font
    property int radius
    property var vertical_alignment
    property var horizontal_alignment

    Rectangle {
        color: box.background
        radius: box.radius
        anchors.fill: parent

        TextEdit {
            id: text
            text: box.content
            font.family: box.font.family
            font.pixelSize: box.font.pixelSize
            color: box.text_color
            verticalAlignment: box.vertical_alignment
            horizontalAlignment: box.horizontal_alignment
            wrapMode: Text.WordWrap
            anchors.fill: parent
            anchors.margins: box.height * 20 / 100
            readOnly: true
            focus: false
            enabled: false
        }
    }
}
