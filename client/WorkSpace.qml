import QtQuick
import QtQuick.Controls
import Flashback.Database
import Flashback.EntryList

Item {
    id: workspace
    anchors.top: parent.top
    anchors.topMargin: parent.height * 20 / 100
    anchors.bottom: parent.bottom
    anchors.bottomMargin: parent.height * 10 / 100
    anchors.left: parent.left
    anchors.leftMargin: parent.width * 25 / 100
    anchors.right: parent.right
    anchors.rightMargin: parent.width * 25 / 100

    property font font
    property color color
    property color text_color

    StackView {
        id: stack
        anchors.fill: parent
        initialItem: menu
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
            id: list

            Database {
                id: database;
            }

            model: database.subjects()
            spacing: 10

            delegate: EntryView {
                id: entry
                color: workspace.color
                font {
                    family: workspace.font.family
                    pixelSize: workspace.font.pixelSize * 70 / 100
                }
                headline_text: headline
                heading_color: "white"
                designator_text: designator
                designator_color: "white"
                width: ListView.view.width
                onSelected: {
                    var selected_entry = list.itemAtIndex(index);

                    if (selected_entry)
                    {
                        console.log("selected", selected_entry.headline_text)
                    }
                }
            }
        }
    }

    Component {
        id: study

        ListView {
            id: list

            Database {
                id: database
            }

            model: database.studying_resources()
            spacing: 10

            delegate: EntryView {
                id: entry
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
                    var selected_entry = list.itemAtIndex(index);

                    if (selected_entry)
                    {
                        console.log("selected", selected_entry.headline_text)
                    }
                }
            }
        }
    }

    Component {
        id: edit

        ListView {
            id: list

            Database {
                id: database;
            }

            model: database.editing_resources()
            spacing: 10

            delegate: EntryView {
                id: entry
                color: workspace.color
                font {
                    family: workspace.font.family
                    pixelSize: workspace.font.pixelSize * 70 / 100
                }
                headline_text: headline
                heading_color: "white"
                designator_text: designator
                designator_color: "white"
                width: ListView.view.width
                onSelected: {
                    var selected_entry = list.itemAtIndex(index);

                    if (selected_entry)
                    {
                        console.log("selected", selected_entry.headline_text)
                    }
                }
            }
        }
    }

    /*
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

    */
}
