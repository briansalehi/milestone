import QtQuick
import QtQuick.Controls
import Flashback.EntryList

Item {
    id: workspace

    property color entry_color
    property string entry_font
    property int entry_font_size
    property EntryList entries

    ListView {
        id: list
        anchors.fill: parent
        model: entries
        spacing: 13

        delegate: EntryView {
            id: entry
            background_color: entry_color
            foreground_color: 'white'
            entry_font: workspace.entry_font
            font_size: entry_font_size
            headline_text: headline
            designator_text: designator
            width: ListView.view.width
        }
    }
}
