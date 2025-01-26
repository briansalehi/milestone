import QtQuick

Item {
    id: page

    required property var model

    property int index: model.index
    property string heading: model.heading

    property int width
    property int height
    property font font
    property color text_color
    property color background
    property color foreground

    Component.onCompleted: {
        console.log("note.index:", index);
        console.log("note.heading:", heading);
        console.log("note.font:", font.family);
        console.log("note.width:", width);
        console.log("note.height:", height);
        console.log("note.background:", background);
        console.log("note.foreground:", foreground);
    }

    Box {
        id: heading
        text_color: page.text_color
        background: page.foreground
        font: page.font
        radius: 20
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        vertical_alignment: Text.AlignVCenter
        horizontal_alignment: Text.AlignLeft

        block_id: page.index
        content: page.heading
        type: 'Text'
        format: TextEdit.RichText
    }

    Rectangle {
        color: page.foreground
        radius: 20
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: heading.bottom
        anchors.topMargin: 20
        anchors.bottom: parent.bottom

        Rectangle {
            id: body_frame
            color: page.background
            radius: parent.radius * 80 / 100
            anchors.fill: parent
            anchors.margins: parent.radius * 80 / 100

            Flickable {
                anchors.fill: parent
                anchors.margins: 20
                flickableDirection: Flickable.VerticalFlick
                contentWidth: width
                contentHeight: page_container.height
                clip: true

                Column {
                    id: page_container
                    width: parent.width
                    spacing: 10

                    Repeater {
                        model: page.model
                        delegate: box_delegate
                    }
                }
            }
        }
    }

    Component {
        id: box_delegate

        Box {
            property font font
            property color text_color
            property color background
            property int block_id
            property int position
            property string content
            property string type
            property string language
            property string last_update

            anchors.left: parent.left
            anchors.right: parent.right
            font.pixelSize: font.pixelSize * 80 / 100
            // radius: body_frame.radius * 80 / 100
            vertical_alignment: Text.AlignTop
            horizontal_alignment: Text.AlignLeft
        }
    }
}
