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
    flags: Qt.FramelessWindowHint

    property int font_big: 42
    property int font_medium: 32
    property int font_regular: 24
    property int font_small: 18

    Rectangle {
        id: titlebar
        color: Qt.lighter(window.color)
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: parent.height * 4 / 100

        Text {
            id: window_name
            text: "Milestone"
            color: "white"
            width: Math.max(100, parent.width * 10 / 100)
            elide: Text.ElideRight
            font.pixelSize: font_small
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.verticalCenter: parent.verticalCenter
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignLeft
        }

        Row {
            id: window_buttons
            spacing: 5
            anchors.right: parent.right
            anchors.rightMargin: 20
            anchors.top: parent.top
            anchors.bottom: parent.bottom

            Rectangle {
                id: minimize_button
                height: parent.height
                width: parent.height
                color: titlebar.color

                Text {
                    text: "-"
                    color: "white"
                    font.family: window.font.family
                    font.pixelSize: font_small
                    font.bold: true
                    anchors.fill: parent
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        window.showMinimized();
                    }
                }
            }

            Rectangle {
                id: maximize_button
                height: parent.height
                width: parent.height
                color: titlebar.color

                Text {
                    text: window.visibility === Window.Maximized ? "o" : "O"
                    color: "white"
                    font.family: window.font.family
                    font.pixelSize: font_small
                    font.bold: true
                    anchors.fill: parent
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        window.visibility = window.visibility === Window.Maximized ? Window.Windowed : Window.Maximized;
                    }
                }
            }

            Rectangle {
                id: quit_button
                height: parent.height
                width: parent.height
                color: titlebar.color

                Text {
                    text: "X"
                    color: "white"
                    font.family: window.font.family
                    font.pixelSize: font_small
                    font.bold: true
                    anchors.fill: parent
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        Qt.quit()
                    }
                }
            }
        }

        MouseArea {
            id: drag_area
            anchors.left: parent.left
            anchors.right: window_buttons.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            drag.target: window.window
            onPressed: {
                drag_area.cursorShape = Qt.SizeAllCursor;
            }
            onReleased: {
                drag_area.cursorShape = Qt.ArrowCursor;
            }
            onPositionChanged: {
                // console.log("position changes from", window.x, window.y, "to", drag_area.pressedX, drag_area.pressedY);
            }
        }
    }

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
