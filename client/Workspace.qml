import QtQuick
import QtQuick.Controls
import Flashback.EntryList

Item {
    id: workspace
    anchors.horizontalCenter: parent.horizontalCenter
    anchors.top: parent.top
    anchors.topMargin: parent.height / 10
    anchors.bottom: parent.bottom
    anchors.bottomMargin: parent.height / 10
    width: parent.width / 10 * 5

    property color entry_color
    property string entry_font
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
            headline_text: headline
            designator_text: designator
            width: ListView.view.width
        }
    }
}
