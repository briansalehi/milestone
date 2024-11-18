import QtQuick

Item {
    id: box

    /* database properties */
    property int block_id
    property int position
    property string content
    property string type
    property string language
    property string last_update

    /* customization properties */
    property color text_color
    property var format
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
            anchors.fill: parent
            anchors.margins: 15
            focus: false
            onContentSizeChanged: box.height = contentHeight + 30

            wrapMode: box.type === 'Code' ? Text.NoWrap : Text.WordWrap
            Component.onCompleted: {
                switch (box.type)
                {
                case 'Text': ;
                    text.textFormat = box.format ? box.format : TextEdit.MarkdownText
                    break
                case 'Code': ;
                    text.textFormat = TextEdit.PlainText
                    break
                default:
                    if (box.block_id > 0)
                    {
                        console.log('block_id:', box.block_id, 'does not have either of type Code or Text, assuming plain text.')
                    }
                    text.textFormat = TextEdit.PlainText
                }
            }

            readOnly: true
            enabled: false
        }
    }
}
