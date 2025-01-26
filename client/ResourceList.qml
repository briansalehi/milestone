import QtQuick

ListView {
    id: resource_list
    spacing: 10

    property var database
    property font font
    property color background
    property color foreground
    property color text_color

    signal selected(int index)

    model: database.resources()
    delegate: resource

    Component {
        id: resource

        Resource {
            Component.onCompleted: {
                width =      Qt.binding(() => { return resource_list.width;      });
                font =       Qt.binding(() => { return resource_list.font;       });
                background = Qt.binding(() => { return resource_list.background; });
                foreground = Qt.binding(() => { return resource_list.foreground; });
                text_color = Qt.binding(() => { return resource_list.text_color; });
                selected.connect((index) => { resource_list.selected(index);   });
            }
        }
    }
}
