import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material
import Flashback.Database

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

    Database {
        id: database
    }

    Item {
        id: spaces
        anchors.top: parent.top
        anchors.topMargin: parent.height * 1 / 10
        anchors.bottom: parent.bottom
        anchors.bottomMargin: parent.height * 1 / 10
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width * 5 / 10

        Flow {
            spacing: 30
            anchors.fill: parent

            Space {
                title: "Study"
                entry_font: window.font.family
                entry_color: window.color
                entry_font_size: font_big
                preferred_size: parent.width / 3
                onClicked: {
                    workspace.entries = database.resources();
                    spaces.visible = false;
                    controls.visible = true;
                    workspace.visible = true;
                }
            }

            Space {
                title: "Practice"
                entry_font: window.font.family
                entry_color: window.color
                entry_font_size: font_big
                preferred_size: parent.width / 3
                onClicked: {
                    workspace.entries = database.subjects();
                    spaces.visible = false;
                    controls.visible = true;
                    workspace.visible = true;
                }
            }
        }
    }

    Item {
        id: controls
        visible: false
        anchors.top: parent.top
        anchors.topMargin: 15
        anchors.bottom: workspace.top
        anchors.bottomMargin: 15
        anchors.left: workspace.left
        anchors.right: workspace.right

        Row {
            spacing: 15
            anchors.fill: parent

            Rectangle {
                radius: 15
                width: controls.width / 3
                height: controls.height * 2 / 3
                color: Qt.lighter(window.color)

                Text {
                    text: "Back"
                    anchors.centerIn: parent
                    color: "white"
                    font.family: window.font.family
                    font.pixelSize: font_medium
                }

                MouseArea {
                    anchors.fill: parent
                    hoverEnabled: true
                    onClicked: {
                        controls.visible = false
                        workspace.visible = false
                        spaces.visible = true
                    }
                    onEntered: { parent.color = Qt.lighter(parent.color); }
                    onExited: { parent.color = Qt.lighter(window.color); }
                }
            }
        }
    }

    Workspace {
        id: workspace
        visible: false
        entry_color: window.color
        entry_font: window.font.family
        entry_font_size: font_regular
        anchors.top: parent.top
        anchors.topMargin: parent.height / 10
        anchors.bottom: parent.bottom
        anchors.bottomMargin: parent.height / 10
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
