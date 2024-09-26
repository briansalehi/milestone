import QtQuick
import QtQuick.Controls
import Flashback.Database
import Flashback.EntryList
import Flashback.NoteModel

Item {
    id: workspace
    anchors.top: parent.top
    anchors.topMargin: parent.height * 10 / 100
    anchors.bottom: parent.bottom
    anchors.bottomMargin: parent.height * 10 / 100
    anchors.left: parent.left
    anchors.leftMargin: parent.width * 25 / 100
    anchors.right: parent.right
    anchors.rightMargin: parent.width * 25 / 100

    property font font
    property color color
    property color text_color
    property int selected_section_id
    property int selected_note_id

    StackView {
        id: stack
        anchors.fill: parent
        initialItem: menu
    }

    Database {
        id: database
    }

    SpaceControl {
        id: controls
        color: workspace.color
        text_color: workspace.text_color
        anchors.top: parent.top
        anchors.bottom: workspace.top
        font: workspace.font
        onClicked: { }
    }

    Component {
        id: menu

        SpaceMenu {
            id: space
            color: workspace.color
            font: workspace.font
            text_color: workspace.text_color
            onSpaceSelected: function(space) {
                switch (space)
                {
                case "practice":
                    stack.push(practice, {}, StackView.Immediate);
                    break;
                case "study":
                    stack.push(study, {}, StackView.Immediate);
                    break;
                case "edit":
                    stack.push(edit, {}, StackView.Immediate);
                    break;
                }
            }
        }
    }

    Component {
        id: practice

        ListView {
            id: practice_list
            spacing: 10
            model: database.subjects()

            delegate: EntryView {
                color: workspace.color
                font {
                    family: workspace.font.family
                    pixelSize: workspace.font.pixelSize * 70 / 100
                }
                headline_text: headline
                heading_color: "white"
                designator_text: designator
                designator_color: "white"
                id_number: id
                width: ListView.view.width
                onSelected: {
                    var selected_entry = practice_list.itemAtIndex(index);

                    if (selected_entry)
                    {
                    }
                }
            }
        }
    }

    Component {
        id: study

        ListView {
            id: study_list
            spacing: 10
            model: database.studying_resources()

            delegate: EntryView {
                color: workspace.color
                font {
                    family: workspace.font.family
                    pixelSize: workspace.font.pixelSize * 70 / 100
                }
                headline_text: headline
                heading_color: "white"
                designator_text: designator
                designator_color: "white"
                id_number: id
                width: ListView.view.width
                onSelected: {
                    var selected_entry = study_list.itemAtIndex(index);

                    if (selected_entry)
                    {
                        selected_section_id = selected_entry.id_number;
                        stack.push(studying_sections, {}, StackView.Immediate);
                    }
                }
            }
        }
    }

    Component {
        id: edit

        ListView {
            id: edit_list
            spacing: 10
            model: database.editing_resources()

            delegate: EntryView {
                color: workspace.color
                font {
                    family: workspace.font.family
                    pixelSize: workspace.font.pixelSize * 70 / 100
                }
                headline_text: headline
                heading_color: "white"
                designator_text: designator
                id_number: id
                designator_color: "white"
                width: ListView.view.width
                onSelected: {
                    var selected_entry = edit_list.itemAtIndex(index);

                    if (selected_entry)
                    {
                    }
                }
            }
        }
    }

    Component {
        id: studying_sections

        ListView {
            id: studying_section_list
            spacing: 10
            model: database.get_studying_sections(selected_section_id)

            delegate: EntryView {
                color: workspace.color
                font {
                    family: workspace.font.family
                    pixelSize: workspace.font.pixelSize * 70 / 100
                }
                headline_text: headline
                heading_color: "white"
                designator_text: designator
                designator_color: "white"
                id_number: id
                width: ListView.view.width
                onSelected: {
                    var selected_entry = studying_section_list.itemAtIndex(index);

                    if (selected_entry)
                    {
                        selected_note_id = selected_entry.id_number;
                        stack.push(studying_notes, {}, StackView.Immediate);
                    }
                }
            }
        }
    }

    Component {
        id: studying_notes

        ListView {
            id: studying_note_list
            spacing: 10
            model: database.section_studying_notes(selected_note_id)

            delegate: Item {
                id: note
                height: ListView.view.height
                width: ListView.view.width

                Rectangle {
                    id: head
                    color: workspace.color
                    radius: 20
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.top: parent.top
                    height: head_text.implicitHeight + 30

                    Text {
                        id: head_text
                        text: heading
                        anchors.fill: parent
                        anchors.margins: 30
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignLeft
                        wrapMode: Text.WordWrap
                        font {
                            family: workspace.font.family
                            pixelSize: workspace.font.pixelSize * 70 / 100
                        }
                        color: workspace.text_color
                    }
                }

                Rectangle {
                    id: body
                    color: workspace.color
                    radius: 20
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.top: head.bottom
                    anchors.topMargin: 20
                    anchors.bottom: parent.bottom

                    Flickable {
                        anchors.fill: parent
                        contentWidth: parent.width
                        contentHeight: parent.height - 30
                        clip: true

                        Text {
                            id: blocks_text
                            text: blocks
                            anchors.fill: parent
                            anchors.margins: 30
                            verticalAlignment: Text.AlignLeft
                            horizontalAlignment: Text.AlignTop
                            wrapMode: Text.WordWrap
                            font {
                                family: workspace.font.family
                                pixelSize: workspace.font.pixelSize * 70 / 100
                            }
                            color: workspace.text_color
                        }
                    }
                }
                // note_id_value: note_id
                // heading_value: heading
                // state_value: state
                // creation_value: creation
                // last_update_value: last_update
                // blocks_value: blocks
            }

            Item {
                height: studying_note_list.height * 20 / 100
                width: studying_note_list.width

                Row {
                    ControlButton {
                        text: "Previous"
                        disabled: true
                        color: workspace.color
                        font: workspace.font
                        size: 80
                        text_color: "white"
                    }

                    ControlButton {
                        text: "Next"
                        disabled: true
                        color: workspace.color
                        font: workspace.font
                        size: 80
                        text_color: "white"
                    }
                }
            }
        }
    }
}
