import QtQuick

ListView {
    id: section_list
    spacing: 10

    required property int index
    required property var database

    property font font
    property color background
    property color foreground
    property color text_color

    signal selected(int index)

    model: database.sections(index)
    delegate: section

    Component {
        id: section

        Section {
            Component.onCompleted: {
                width = Qt.binding(() => { return section_list.width; });
                font = Qt.binding(() => { return section_list.font; });
                background = Qt.binding(() => { return section_list.background; });
                foreground = Qt.binding(() => { return section_list.foreground; });
                text_color = Qt.binding(() => { return section_list.text_color; });
                selected.connect((index) => { section_list.selected(index); });
            }
        }
    }
}
