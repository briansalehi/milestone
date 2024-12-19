import QtQuick

Item
{
    id: board

    property int height
    property int width
    property font font
    property var model
    property int radius

    Flickable
    {
        anchors.fill: parent
        anchors.margins: 20
        flickableDirection: Flickable.VerticalFlick
        contentWidth: width
        contentHeight: page_container.height
        clip: true

        Column
        {
            id: page_container
            width: parent.width
            spacing: 10

            Repeater
            {
                model: board.model

                Box
                {
                    anchors.left: parent.left
                    anchors.right: parent.right
                    font.family: board.font.family
                    font.pixelSize: board.font.pixelSize * 55 / 100
                    radius: board.radius * 80 / 100
                    text_color: workspace.text_color
                    background: workspace.foreground
                    vertical_alignment: Text.AlignTop
                    horizontal_alignment: Text.AlignLeft

                    block_id: model.block_id
                    position: model.position
                    content: model.content
                    type: model.type
                    language: model.language
                    last_update: model.last_update
                }
            }
        }
    }
}
