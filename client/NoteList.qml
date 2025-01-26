import QtQuick
import QtQuick.Controls

SwipeView {
    id: note_list
    spacing: 10
    orientation: Qt.Horizontal

    signal lastNoteViewed(int index)
    signal currentNoteIndexChanged(int index)

    required property int section_index
    required property var database
    property font text_font
    property color background_color
    property color foreground_color
    property color text_color
    // property int width
    // property int height

    Component.onCompleted: {
        console.log("note_list.section.index:", note_list.section_index);
        console.log("note_list.font:", note_list.text_font.family);
        console.log("note_list.width:", note_list.width);
        console.log("note_list.height:", note_list.height);
        console.log("note_list.background:", note_list.background_color);
        console.log("note_list.foreground:", note_list.foreground_color);
        console.log("note_list.text.color:", note_list.text_color);
        console.log();
    }

    Repeater {
        id: repeater
        model: note_list.database.notes(note_list.section_index)
        delegate: note

        Component {
            id: note

            Note {
                Component.onCompleted: {
                    max_width = Qt.binding(() => { return note_list.width; });
                    max_height = Qt.binding(() => { return note_list.height; });
                    font = Qt.binding(() => { return note_list.text_font; });
                    background = Qt.binding(() => { return note_list.background_color; });
                    foreground = Qt.binding(() => { return note_list.foreground_color; });
                    text_color = Qt.binding(() => { return note_list.text_color; });
                }
            }
        }
    }

    onCurrentIndexChanged: {
        var total = count - 1;
        page_indicator.set_page(currentIndex);

        // log study completion when reached last section
        if (total !== 0 && currentIndex === total)
        {
            database.section_study_completed(selected_section_id);
        }
    }
}
