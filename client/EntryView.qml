import QtQuick

Item {
    id: entry
    height: 70

    property color color
    property font font
    property string headline_text
    property color heading_color
    property string designator_text
    property color designator_color
    property bool doubleClicked: false

    signal selected

    property int id_number

    Rectangle {
        anchors.fill: parent
        radius: 13
        color: entry.color

        Text {
            id: headline_id
            text: entry.headline_text
            color: entry.heading_color
            font: entry.font
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            elide: Text.ElideRight
            anchors.left: parent.left
            anchors.leftMargin: 15
            anchors.right: update_id.left
            anchors.rightMargin: 10
            anchors.verticalCenter: parent.verticalCenter
        }

        Text {
            id: update_id
            text: entry.designator_text
            color: entry.designator_color
            font: entry.font
            elide: Text.ElideRight
            anchors.right: parent.right
            anchors.rightMargin: 15
            anchors.verticalCenter: parent.verticalCenter
        }

        MouseArea {
            anchors.fill: parent
            hoverEnabled: true
            onClicked: {
                if (entry.doubleClicked) {
                    entry.selected();
                    entry.doubleClicked = false
                }
                else {
                    entry.doubleClicked = true
                }

                parent.color = Qt.lighter(entry.color, 2);
            }
            onDoubleClicked: {
                entry.selected();
            }
            onEntered: {
                parent.color = Qt.lighter(entry.color, 1.5);
            }
            onExited: {
                parent.color = entry.color;
            }
        }
    }
}
