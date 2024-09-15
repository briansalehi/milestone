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

    Database {
        id: database
    }

    Grid {
        id: spaces
        anchors.fill: workspace
        spacing: 30

        Space {
            title: "Study"
            entry_font: window.font.family
            entry_color: window.color
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
            onClicked: {
                workspace.entries = database.subjects();
                spaces.visible = false;
                controls.visible = true;
                workspace.visible = true;
            }
        }
    }

    Item {
        id: controls
        visible: false
        anchors.top: parent.top
        anchors.bottom: workspace.top
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
                anchors.verticalCenter: parent.verticalCenter

                Text {
                    text: "Back"
                    anchors.centerIn: parent
                    color: "white"
                    font.family: window.font.family
                    font.pixelSize: 24
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
