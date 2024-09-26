import QtQuick

Item {
    id: controls

    property font font
    property color color
    property color text_color
    property bool next_disabled
    property bool back_disabled
    signal nextClicked
    signal backClicked

    ControlButton {
        id: back
        size: parent.width / 3
        text: "Back"
        color: controls.color
        default_color: controls.color
        font: controls.font
        text_color: controls.text_color
        disabled: controls.back_disabled
        anchors.top: parent.top
        onClicked: { controls.backClicked(); }
    }

    ControlButton {
        id: next
        size: parent.width / 3
        text: "Next"
        color: controls.color
        default_color: controls.color
        font: controls.font
        text_color: controls.text_color
        disabled: controls.next_disabled
        anchors.bottom: parent.bottom
        onClicked: { controls.nextClicked(); }
    }
}
