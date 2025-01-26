import QtQuick

Item {
    id: entry
    height: 70

    required property int index
    required property string headline
    required property string designator

    property color color
    property font font
    property color heading_color
    property color designator_color
    property bool alreadyClickedOnce: false

    signal selected(int index)

    Rectangle {
        id: space
        anchors.fill: parent
        radius: 13
        color: entry.color

        Text {
            id: headline_id
            text: entry.headline
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
            text: entry.designator
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
                    entry.selected(entry.index);
                }
                else {
                    entry.alreadyClickedOnce = true;
                    space.color = Qt.lighter(entry.color, 2);
                }
            }
            onDoubleClicked: {
                entry.alreadyClickedOnce = false
                space.color = entry.color;
                entry.selected(entry.index);
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
