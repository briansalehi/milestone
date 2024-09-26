import QtQuick

Item {
    id: page
    // anchors.fill: parent
    // anchors.top: parent.top
    // anchors.topMargin: parent.height * 10 / 100
    // anchors.bottom: parent.bottom
    // anchors.bottomMargin: parent.height * 10 / 100
    // anchors.leftMargin: parent.width * 20 / 100
    // anchors.rightMargin: parent.width * 20 / 100

    property string heading
    property string content
    property color text_color
    property color color
    property font font
    property int size

    Item {
        anchors.fill: parent

        Column {
            spacing: 30

            Heading {
                id: heading
                text: page.heading
                font: page.font
                color: page.text_color
                background: page.color
            }

            Rectangle {
                id: content
                color: page.color
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: heading.bottom
                anchors.topMargin: 30
                anchors.bottom: parent.bottom

                Text {
                    anchors.fill: parent
                    text: page.content
                    font: page.font
                    color: page.text_color
                }
            }
        }
    }
}
