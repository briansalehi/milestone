import QtQuick
import QtQuick.Controls
import Flashback.Database
import Flashback.EntryList

Item {
    id: workspace

    property color entry_color
    property string entry_font
    property int entry_font_size
    property EntryList entries
    property Database database

    state: "menu"

    states: [
        State {
            name: "menu"
            PropertyChanges { target: workspace; entries: EntryList{} }
            PropertyChanges { target: list; visible: false }
        },
        State {
            name: "practice"
            PropertyChanges { target: workspace; entries: database.resources() }
            PropertyChanges { target: list; visible: true }
        },
        State {
            name: "study"
            PropertyChanges { target: workspace; entries: database.subjects() }
            PropertyChanges { target: list; visible: true }
        }
    ]

    ListView {
        id: list
        visible: false
        anchors.top: parent.top
        anchors.bottom: page_control.top
        anchors.bottomMargin: parent.height * 2 / 100
        anchors.left: parent.left
        anchors.right: parent.right
        model: workspace.entries
        spacing: 10

        delegate: EntryView {
            id: entry
            background_color: entry_color
            foreground_color: "white"
            entry_font: workspace.entry_font
            font_size: entry_font_size
            headline_text: headline
            designator_text: designator
            width: ListView.view.width
            onClicked: { page_control.visible = true; }
        }
    }

    SpaceMenu {
        id: menu
        visible: false
    }

    SpaceControl {
        id: controls
        visible: false
        anchors.top: parent.top
        anchors.bottom: workspace.top
        button_color: Qt.lighter(window.color)
        font_size: font_medium
        font_family: window.font.family
        onClicked: {
            controls.visible = false
            workspace.visible = false
            spaces.visible = true
        }
    }
}
