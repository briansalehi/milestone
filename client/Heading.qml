import QtQuick

Item {
    id: heading
    anchors.left: parent.left
    anchors.right: parent.right
    anchors.top: parent.top
    height: parent.height * 20 / 100

    property string text
    property font font
    property color color
    property color background
    signal textClicked

    Row {
        id: placeholder
        anchors.fill: parent
        spacing: 5

        Rectangle {
            id: data_placeholder
            width: placeholder.width // should be changed when new element is placed nearby
            height: placeholder.height
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            color: heading.background

            Text {
                id: data
                text: heading.text
                color: heading.color
                font: heading.font
                anchors.fill: parent
                anchors.margins: 3
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }

            MouseArea {
                anchors.fill: parent
                onClicked: { heading.textClicked(); }
            }
        }
    }
}
