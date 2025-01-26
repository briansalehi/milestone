import QtQuick

EntryView {
    id: resource

    required property var model

    index: model.index
    headline: model.headline
    designator: model.designator

    property font font
    property color foreground
    property color background
    property color text_color

    color: foreground
    heading_color: text_color
    designator_color: text_color
}
