import QtQuick

EntryView {
    id: section

    required property var model

    index: model.index
    headline: model.index
    designator: model.index

    property font font
    property color foreground
    property color background
    property color text_color

    color: foreground
    heading_color: text_color
    designator_color: text_color
    // font.family: font.family
    // font.pixelSize: font.pixelSize * 70 / 100
}
