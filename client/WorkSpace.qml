import QtQuick
import QtQuick.Controls
import Flashback.Database
import Flashback.EntryList
import Flashback.NoteModel
import Flashback.BoxModel

Item {
    id: workspace

    property int short_side: parent.height > parent.width ? parent.width : parent.height
    property int long_side:  parent.height < parent.width ? parent.width : parent.height
    property string orientation: parent.height > parent.width ? "vertical" : "horizontal"

    anchors.top: parent.top
    anchors.topMargin: orientation == "vertical" ? long_side * 10 / 100 : short_side * 10 / 100
    anchors.bottom: parent.bottom
    anchors.left: parent.left
    anchors.leftMargin: orientation == "vertical" ? short_side * 15 / 100 : long_side * 20 / 100
    anchors.right: parent.right
    anchors.rightMargin: orientation == "vertical" ? short_side * 15 / 100 : long_side * 20 / 100

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

    function next_page()
    {
        console.log("next pushed");
    }

    function back_page()
    {
        stack.pop(StackView.Immediate);
        page_indicator.clear();
    }

    StackView {
        id: stack
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: page_indicator.top
        anchors.bottomMargin: Math.min(20, parent.height * 2 / 100)
        initialItem: menu
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

    Database {
        id: database
    }

    Component {
        id: menu

        SpaceMenu {
            id: space
            color: workspace.foreground
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
                color: workspace.foreground
                font {
                    family: workspace.font.family
                    pixelSize: workspace.font.pixelSize * 70 / 100
                }
                headline_text: headline
                heading_color: workspace.text_color
                // designator_text: designator
                // designator_color: workspace.text_color
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
                color: workspace.foreground
                font {
                    family: workspace.font.family
                    pixelSize: workspace.font.pixelSize * 70 / 100
                }
                headline_text: headline
                heading_color: workspace.text_color
                designator_text: designator
                designator_color: workspace.text_color
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
                color: workspace.foreground
                font {
                    family: workspace.font.family
                    pixelSize: workspace.font.pixelSize * 70 / 100
                }
                headline_text: headline
                heading_color: workspace.text_color
                designator_text: designator
                designator_color: workspace.text_color
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
                color: workspace.foreground
                font {
                    family: workspace.font.family
                    pixelSize: workspace.font.pixelSize * 70 / 100
                }
                headline_text: headline
                heading_color: workspace.text_color
                designator_text: designator
                designator_color: workspace.text_color
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
                        item.block_id = id;
                        item.model = database.practice_blocks(id);
                        item.heading = heading;
                        item.font.family = workspace.font.family
                        item.font.pixelSize = workspace.font.pixelSize * 70 / 100
                        item.text_color = workspace.text_color
                        item.background = workspace.background
                        item.foreground = workspace.foreground
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
                        item.block_id = id;
                        item.model = database.note_blocks(id);
                        item.heading = heading;
                        item.font.family = workspace.font.family
                        item.font.pixelSize = workspace.font.pixelSize * 70 / 100
                        item.text_color = workspace.text_color
                        item.background = workspace.background
                        item.foreground = workspace.foreground

                        page_indicator.page_count = repeater.count
                        page_indicator.set_page(0);
                        // note_id
                        // state
                        // creation
                        // last_update
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
    }

    Component {
        id: page_model

        Item {
            id: page
            height: parent.height
            width: parent.width

            property int block_id
            property string heading
            property font font
            property var model
            property color text_color
            property color background
            property color foreground

            Box {
                id: head
                text_color: page.text_color
                background: page.foreground
                font: page.font
                radius: 20
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.right: parent.right
                vertical_alignment: Text.AlignVCenter
                horizontal_alignment: Text.AlignLeft

                block_id: page.block_id
                content: page.heading
                type: 'Text'
                format: TextEdit.RichText
            }

            Rectangle {
                color: page.foreground
                radius: 20
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: head.bottom
                anchors.topMargin: 20
                anchors.bottom: parent.bottom

                Rectangle {
                    id: body_frame
                    color: page.background
                    radius: parent.radius * 80 / 100
                    anchors.fill: parent
                    anchors.margins: parent.radius * 80 / 100

                    Flickable {
                        anchors.fill: parent
                        anchors.margins: 20
                        flickableDirection: Flickable.VerticalFlick
                        contentWidth: width
                        contentHeight: page_container.height
                        clip: true

                        Column {
                            id: page_container
                            width: parent.width
                            spacing: 10

                            Repeater {
                                model: page.model
                                delegate: Box {
                                    anchors.left: parent.left
                                    anchors.right: parent.right
                                    font.family: workspace.font.family
                                    font.pixelSize: workspace.font.pixelSize * 55 / 100
                                    radius: body_frame.radius * 80 / 100
                                    text_color: workspace.text_color
                                    background: workspace.foreground
                                    vertical_alignment: Text.AlignTop
                                    horizontal_alignment: Text.AlignLeft

                                    block_id: model.block_id
                                    position: model.position
                                    content: model.content
                                    type: model.type
                                    language: model.language
                                    last_update: model.last_update
                                }
                            }
                        }
                    }
                }
            }
        }
    }

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
