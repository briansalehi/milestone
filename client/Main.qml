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

    WorkSpace {
        id: workspace
        visible: false
        entry_color: Qt.lighter(window.color)
        entry_font: window.font.family
        entry_font_size: font_regular
        anchors.top: parent.top
        anchors.topMargin: parent.height * 10 / 100
        anchors.bottom: parent.bottom
        anchors.bottomMargin: parent.height * 10 / 100
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width * 5 / 10
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
