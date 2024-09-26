import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material

ApplicationWindow {
    id: window
    title: qsTr("Milestone")
    visible: true
    visibility: Window.Maximized
    Material.theme: Material.Dark
    minimumHeight: 800
    minimumWidth: 600
    font.family: "Noto Sans"
    font.pixelSize: 42

    property int font_big: 42
    property int font_medium: 32
    property int font_regular: 24
    property int font_small: 18

    ControlButton {
        id: back
        size: parent.width / 3
        text: "<"
        color: Qt.lighter(window.color)
        default_color: Qt.lighter(window.color)
        font: window.font
        text_color: "white"
        disabled: false
        anchors.right: workspace.left
        anchors.rightMargin: 30
        anchors.verticalCenter: parent.verticalCenter
        width: 60
        height: workspace.height / 3
        onClicked: { workspace.back_page(); }
    }

    WorkSpace {
        id: workspace
        color: Qt.lighter(window.color)
        font: window.font
        text_color: "white"
    }

    ControlButton {
        id: next
        size: parent.width / 3
        text: ">"
        color: Qt.lighter(window.color)
        default_color: Qt.lighter(window.color)
        font: window.font
        text_color: "white"
        disabled: false
        anchors.left: workspace.right
        anchors.leftMargin: 30
        anchors.verticalCenter: parent.verticalCenter
        width: 60
        height: workspace.height / 3
        onClicked: { workspace.next_page(); }
    }

    /*
    Login {
        id: login
        heading: "Login"
        fontFamily: window.fontFamily
        fontSize: 58
        onClicked: {
            heading = "Logging in"
            login.visible = false
        }
    }
    */
}
