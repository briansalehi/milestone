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

        EntryView {
            id: practice
            font: menu.font
            color: menu.color
            headline_text: "Practice"
            heading_color: menu.text_color
            width: menu.space_size
            height: menu.space_size
            onSelected: {
                menu.spaceSelected("practice");
            }
        }

        EntryView {
            id: study
            font: menu.font
            color: menu.color
            headline_text: "Study"
            heading_color: menu.text_color
            width: menu.space_size
            height: menu.space_size
            onSelected: {
                menu.spaceSelected("study");
            }
        }
    }
}
