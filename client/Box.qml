import QtQuick

Item {
    id: box

    property string text
    property color color
    property color background
    property font font

    Rectangle {
        id: box_area
        color: box.background
        radius: 20
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        height: box_text.implicitHeight + 30

        TextEdit {
            id: box_text
            text: box.text
            font.family: box.font.family
            font.pixelSize: box.font.pixelSize * 60 / 100
            color: box.color
            verticalAlignment: Text.AlignLeft
            horizontalAlignment: Text.AlignTop
            wrapMode: Text.WordWrap
            anchors.fill: parent
            anchors.margins: 30
            readOnly: true
            focus: false
            enabled: false
        }
    }
}
