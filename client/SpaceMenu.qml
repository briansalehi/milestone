import QtQuick

Item {
    id: menu

    property font font
    property color color
    property color text_color
    property int space_size: parent.width * 31 / 100
    signal spaceSelected(string space)

    Flow {
        spacing: parent.width * 3 / 100
        anchors.fill: parent

        Space {
            id: practice
            text: "Practice"
            font: menu.font
            text_color: menu.text_color
            color: menu.color
            preferred_size: menu.space_size
            onClicked: {
                menu.spaceSelected("practice");
            }
        }

        Space {
            id: study
            text: "Study"
            font: menu.font
            text_color: menu.text_color
            color: menu.color
            preferred_size: menu.space_size
            onClicked: {
                menu.spaceSelected("study");
            }
        }
    }
}
