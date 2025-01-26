import QtQuick
import QtQuick.Controls
import Flashback.Database
import Flashback.EntryList
import Flashback.NoteModel
import Flashback.BoxModel

Item {
    id: workspace

    property font font
    property color foreground
    property color background
    property color text_color
    property int selected_subject_id
    property int selected_topic_id
    property int selected_resource_id
    property int selected_section_id

    signal showBack
    signal hideBack
    signal showNext
    signal hideNext
    signal lock
    signal unlock

    function next_page()
    {
        console.log("next pushed");
    }

    function back_page()
    {
        stack.pop(StackView.Immediate);
        page_indicator.clear();
    }

    property var last_request
    property var last_caller
    property var last_arg

    function dispatch_request(command, caller, arg)
    {
        if (caller)
        {
            workspace.last_request = command;
            workspace.last_caller = caller;
            workspace.last_arg = arg;
        }

        if (command == "subjects")
        {
            return database.subjects();
        }
        else if (command == "resources")
        {
            return database.resources()
        }
        else if (command == "topics")
        {
            return database.topics(arg);
        }
        else if (command == "practices")
        {
            return database.practices(arg);
        }
        else if (command == "sections")
        {
            return database.sections(arg);
        }
        else if (command == "notes")
        {
            return database.notes(arg);
        }
    }

    function expandResource(index){
        stack.push(section_list, { index: index, database: database }, StackView.Immediate);
    }

    function expandSection(index) {
        stack.push(note_list, {section_index: index, database: database}, StackView.Immediate);
    }

    Database {
        id: database

        onConnectionStateChanged: function(is_connected) {
            if (is_connected)
            {
                var last_request = workspace.last_request
                var last_caller = workspace.last_caller
                var last_arg = workspace.last_arg

                if (last_request && last_caller)
                {
                    last_caller.model = workspace.dispatch_request(last_request, null, last_arg);
                }

                workspace.unlock();
            }
            else
            {
                workspace.lock();
            }
        }
    }

    StackView {
        id: stack
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: page_indicator.top
        anchors.bottomMargin: Math.min(20, parent.height * 2 / 100)
        initialItem: space
        onCurrentItemChanged: {
            if (depth > 1)
            {
                workspace.showBack();
            }
            else
            {
                workspace.hideBack();
            }
        }
    }

    SpaceMenu {
        id: space
        color: workspace.foreground
        font: workspace.font
        text_color: workspace.text_color
        onSpaceSelected: function(space) {
            switch (space)
            {
            // case "practice":
            //     stack.push(subject_list, {}, StackView.Immediate);
            //     break;
            case "study":
                stack.push(resource_list, { database: database }, StackView.Immediate);
                break;
            }
        }
    }

    Component {
        id: resource_list

        ResourceList {
            Component.onCompleted: {
                font =       Qt.binding(() => { return workspace.font;       });
                background = Qt.binding(() => { return workspace.background; });
                foreground = Qt.binding(() => { return workspace.foreground; });
                text_color = Qt.binding(() => { return workspace.text_color; });
                selected.connect((index) => { expandResource(index); });
            }
        }
    }

    Component {
        id: section_list

        SectionList {
            Component.onCompleted: {
                font =       Qt.binding(() => { return workspace.font;       });
                background = Qt.binding(() => { return workspace.background; });
                foreground = Qt.binding(() => { return workspace.foreground; });
                text_color = Qt.binding(() => { return workspace.text_color; });
                selected.connect((index) => { expandSection(index); });
            }
        }
    }

    Component {
        id: note_list

        NoteList {
            Component.onCompleted: {
                text_font = Qt.binding(() => { return workspace.font; });
                background_color = Qt.binding(() => { return workspace.background; });
                foreground_color = Qt.binding(() => { return workspace.foreground; });
                text_color = Qt.binding(() => { return workspace.text_color; });
            }
        }
    }

    // Component {
    //     id: subject_list

    //     ListView {
    //         id: subjects_list_view
    //         spacing: 10
    //         model: workspace.dispatch_request("subjects", this)

    //         delegate: EntryView {
    //             color: workspace.foreground
    //             font {
    //                 family: workspace.font.family
    //                 pixelSize: workspace.font.pixelSize * 70 / 100
    //             }
    //             headline_text: headline
    //             heading_color: workspace.text_color
    //             // designator_text: designator
    //             // designator_color: workspace.text_color
    //             id_number: id
    //             width: ListView.view.width
    //             onSelected: {
    //                 var selected_entry = subjects_list_view.itemAtIndex(index);

    //                 if (selected_entry)
    //                 {
    //                     selected_subject_id = selected_entry.id_number;
    //                     stack.push(topic_list, {}, StackView.Immediate);
    //                 }
    //             }
    //         }
    //     }
    // }

    // Component {
    //     id: topic_list

    //     ListView {
    //         id: topics_list_view
    //         spacing: 10
    //         model: workspace.dispatch_request("topics", this, selected_subject_id)

    //         delegate: EntryView {
    //             color: workspace.foreground
    //             font {
    //                 family: workspace.font.family
    //                 pixelSize: workspace.font.pixelSize * 70 / 100
    //             }
    //             headline_text: headline
    //             heading_color: workspace.text_color
    //             designator_text: designator
    //             designator_color: workspace.text_color
    //             id_number: id
    //             width: ListView.view.width
    //             onSelected: {
    //                 var selected_entry = topics_list_view.itemAtIndex(index);

    //                 if (selected_entry)
    //                 {
    //                     selected_topic_id = selected_entry.id_number;
    //                     stack.push(practice_list, {}, StackView.Immediate);
    //                 }
    //             }
    //         }
    //     }
    // }

    // Component {
    //     id: practice_list

    //     SwipeView {
    //         spacing: 10
    //         orientation: Qt.Horizontal

    //         Repeater {
    //             id: repeater
    //             model: workspace.dispatch_request("practices", this, selected_topic_id)

    //             Loader {
    //                 // active: SwipeView.isCurrentItem || SwipeView.isNextItem || SwipeView.isPreviousItem
    //                 sourceComponent: page_model
    //                 onLoaded: {
    //                     item.block_id = id;
    //                     item.model = database.practice_blocks(id);
    //                     item.heading = heading;
    //                     item.font.family = workspace.font.family
    //                     item.font.pixelSize = workspace.font.pixelSize * 70 / 100
    //                     item.text_color = workspace.text_color
    //                     item.background = workspace.background
    //                     item.foreground = workspace.foreground
    //                     // note_id
    //                     // state
    //                     // creation
    //                     // last_update
    //                 }
    //             }
    //         }
    //     }
    // }

    Item {
        id: page_indicator
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        height: parent.height * 10 / 100

        property int page_count
        property var read_pages: []
        property int current_index

        function clear() {
            page_count = 0;
            read_pages = [];
        }

        function set_page(index) {
            var item = indicator_repeater.itemAt(index)
            if (item)
                item.color = Qt.lighter(workspace.foreground, 2.2);

            current_index = read_pages.indexOf(index)
            if (current_index !== -1)
                read_pages.splice(current_index, 1)

            read_pages.forEach(function(page) {
                var item = indicator_repeater.itemAt(page);
                if (item)
                {
                    item.color = Qt.lighter(workspace.foreground, 1.5);
                }
            });

            read_pages.push(index);
        }

        Flow {
            anchors.fill: parent
            spacing: Math.max(3, parent.width * 1 / 100)

            Repeater {
                id: indicator_repeater
                model: page_indicator.page_count

                Rectangle {
                    width: Math.max(20, parent.width * 2 / 100)
                    height: width / 2
                    radius: width / 3
                    color: Qt.darker(workspace.foreground, 1.1)
                }
            }
        }
    }
}
