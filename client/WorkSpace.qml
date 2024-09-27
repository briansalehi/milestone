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
    property int selected_subject_id
    property int selected_topic_id
    property int selected_resource_id
    property int selected_section_id

    function next_page()
    {
        console.log("next pushed");
    }

    function back_page()
    {
        stack.pop(StackView.Immediate);
    }

    StackView {
        id: stack
        anchors.fill: parent
        initialItem: menu
    }

    Database {
        id: database
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
                    stack.push(subject_list, {}, StackView.Immediate);
                    break;
                case "study":
                    stack.push(resource_list, {}, StackView.Immediate);
                    break;
                }
            }
        }
    }

    Component {
        id: subject_list

        ListView {
            id: subjects_list_view
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
                    var selected_entry = subjects_list_view.itemAtIndex(index);

                    if (selected_entry)
                    {
                        selected_subject_id = selected_entry.id_number;
                        stack.push(topic_list, {}, StackView.Immediate);
                    }
                }
            }
        }
    }

    Component {
        id: resource_list

        ListView {
            id: resources_list_view
            spacing: 10
            model: database.resources()

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
                    var selected_entry = resources_list_view.itemAtIndex(index);

                    if (selected_entry)
                    {
                        selected_resource_id = selected_entry.id_number;
                        stack.push(section_list, {}, StackView.Immediate);
                    }
                }
            }
        }
    }

    Component {
        id: topic_list

        ListView {
            id: topics_list_view
            spacing: 10
            model: database.topics(selected_subject_id)

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
                    var selected_entry = topics_list_view.itemAtIndex(index);

                    if (selected_entry)
                    {
                        selected_topic_id = selected_entry.id_number;
                        stack.push(practice_list, {}, StackView.Immediate);
                    }
                }
            }
        }
    }

    Component {
        id: section_list

        ListView {
            id: section_list_view
            spacing: 10
            model: database.sections(selected_resource_id)

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
                    var selected_entry = section_list_view.itemAtIndex(index);

                    if (selected_entry)
                    {
                        selected_section_id = selected_entry.id_number;
                        stack.push(note_list, {}, StackView.Immediate);
                    }
                }
            }
        }
    }

    Component {
        id: practice_list

        SwipeView {
            spacing: 10
            orientation: Qt.Horizontal

            Repeater {
                id: repeater
                model: database.practices(selected_topic_id)

                Loader {
                    // active: SwipeView.isCurrentItem || SwipeView.isNextItem || SwipeView.isPreviousItem
                    sourceComponent: page_model
                    onLoaded: {
                        item.heading = heading;
                        item.blocks = blocks;
                        // note_id
                        // state
                        // creation
                        // last_update
                    }
                }
            }
        }
    }

    Component {
        id: note_list

        SwipeView {
            spacing: 10
            orientation: Qt.Horizontal

            Repeater {
                id: repeater
                model: database.notes(selected_section_id)

                Loader {
                    // active: SwipeView.isCurrentItem || SwipeView.isNextItem || SwipeView.isPreviousItem
                    sourceComponent: page_model
                    onLoaded: {
                        item.heading = heading;
                        item.blocks = blocks;
                        // note_id
                        // state
                        // creation
                        // last_update
                    }
                }
            }
        }
    }

    Component {
        id: page_model

        Item {
            id: note_placeholder

            height: parent.height
            width: parent.width

            property string heading
            property string blocks
            // note_id
            // state
            // creation
            // last_update

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
                    text: note_placeholder.heading
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

                ScrollView {
                    anchors.fill: parent
                    anchors.margins: 30
                    ScrollBar.horizontal.policy: ScrollBar.AlwaysOff

                    TextArea {
                        id: blocks_text
                        text: note_placeholder.blocks
                        verticalAlignment: Text.AlignLeft
                        wrapMode: Text.WordWrap
                        horizontalAlignment: Text.AlignTop
                        font {
                            family: workspace.font.family
                            pixelSize: workspace.font.pixelSize * 60 / 100
                        }
                        color: workspace.text_color
                    }
                }
            }
        }
    }
}
