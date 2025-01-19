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
    property bool alreadyClickedOnce: false
    property int id_number
    signal selected

    Rectangle {
        id: space
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
            anchors.left: space.left
            anchors.leftMargin: 15
            anchors.right: update_id.left
            anchors.rightMargin: 10
            anchors.verticalCenter: space.verticalCenter
        }

        Text {
            id: update_id
            text: entry.designator_text
            color: entry.designator_color
            font: entry.font
            elide: Text.ElideRight
            anchors.right: space.right
            anchors.rightMargin: text == "" ? 5 : 15
            anchors.verticalCenter: space.verticalCenter
        }

        MouseArea {
            anchors.fill: parent
            hoverEnabled: true
            onClicked: {
                if (entry.alreadyClickedOnce) {
                    entry.alreadyClickedOnce = false;
                    space.color = entry.color;
                    entry.selected();
                }
                else {
                    entry.alreadyClickedOnce = true;
                    space.color = Qt.lighter(entry.color, 2);
                }
            }
            onDoubleClicked: {
                entry.alreadyClickedOnce = false
                space.color = entry.color;
                entry.selected();
            }
            onEntered: {
                space.color = Qt.lighter(entry.color, 1.5);
            }
            onExited: {
                space.color = entry.color;
                entry.alreadyClickedOnce = false
            }
        }
    }
}
