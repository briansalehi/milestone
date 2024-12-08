import QtQuick
import Flashback.BoxModel

Item
{
    id: paper

    property int height
    property int width
    property font font
    property var model
    property color background
    property color foreground

    property int block_id
    property string heading
    property color text_color

    Column
    {
        spacing: 20

        Box
        {
            id: head
            text_color: paper.text_color
            background: paper.foreground
            font: paper.font
            radius: 20
            width: parent.width
            vertical_alignment: Text.AlignVCenter
            horizontal_alignment: Text.AlignLeft

            block_id: paper.block_id
            content: paper.heading
            type: 'Text'
            format: TextEdit.RichText
        }

        Frame
        {
            width: parent.width
            height: parent.height

            Board
            {
                height: parent.height
                width: parent.width
                font.family: paper.font.family
                font.pixelSize: paper.font.pixelSize * 55 / 100
                model: paper.model
                radius: parent.radius * 80 / 100
            }
        }
    }
}
