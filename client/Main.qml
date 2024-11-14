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
    property color font_color: 'lightgray'

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
            color: window.font_color
            width: Math.max(100, parent.width * 10 / 100)
            elide: Text.ElideRight
            font.pixelSize: window.font_small
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
                    color: window.font_color
                    font.family: window.font.family
                    font.pixelSize: window.font_small
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
                    color: window.font_color
                    font.family: window.font.family
                    font.pixelSize: window.font_small
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
                    color: window.font_color
                    font.family: window.font.family
                    font.pixelSize: window.font_small
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

    Rectangle {
        id: back
        visible: false
        color: Qt.lighter(window.color)
        anchors.right: workspace.left
        anchors.rightMargin: 30
        anchors.verticalCenter: parent.verticalCenter
        height: Math.max(100, workspace.height / 4)
        width: height / 4

        Canvas {
            anchors.fill: parent
            onPaint: {
                var ctx = getContext("2d");

                // Clear the canvas before drawing
                ctx.clearRect(0, 0, width, height);

                // Begin path for the triangle
                ctx.beginPath();
                ctx.moveTo(0, height / 2);  // Top point
                ctx.lineTo(0, 0);  // Bottom left point
                ctx.lineTo(width, 0); // Bottom right point
                ctx.closePath();

                // Fill the triangle with a color
                ctx.fillStyle = window.color;
                ctx.fill();

                // Begin path for the triangle
                ctx.beginPath();
                ctx.moveTo(0, height / 2);  // Top point
                ctx.lineTo(0, height);  // Bottom left point
                ctx.lineTo(width, height); // Bottom right point
                ctx.closePath();

                // Fill the triangle with a color
                ctx.fillStyle = window.color;
                ctx.fill();
            }

            MouseArea {
                anchors.fill: parent
                hoverEnabled: true
                onClicked: {
                    workspace.back_page();
                }
                onEntered: {
                    back.color = Qt.lighter(window.color, 2);
                }
                onExited: {
                    back.color = Qt.lighter(window.color);
                }
            }
        }
    }

    WorkSpace {
        id: workspace
        color: Qt.lighter(window.color)
        font: window.font
        text_color: window.font_color
        onShowBack: {
            back.visible = true
        }
        onHideBack: {
            back.visible = false
        }
    }

    Rectangle {
        id: next
        visible: false
        color: Qt.lighter(window.color)
        anchors.left: workspace.right
        anchors.leftMargin: 30
        anchors.verticalCenter: parent.verticalCenter
        height: Math.max(100, workspace.height / 4)
        width: height / 4

        MouseArea {
            anchors.fill: parent
            hoverEnabled: true
            onClicked: {
                workspace.next_page();
            }
            onEntered: {
                next.color = Qt.lighter(window.color, 2);
            }
            onExited: {
                next.color = Qt.lighter(window.color);
            }
        }

        Canvas {
            anchors.fill: parent
            onPaint: {
                var ctx = getContext("2d");

                // Clear the canvas before drawing
                ctx.clearRect(0, 0, width, height);

                // Begin path for the triangle
                ctx.beginPath();
                ctx.moveTo(0, 0);  // Top point
                ctx.lineTo(width, 0);  // Bottom left point
                ctx.lineTo(width, height / 2); // Bottom right point
                ctx.closePath();

                // Fill the triangle with a color
                ctx.fillStyle = window.color;
                ctx.fill();

                // Begin path for the triangle
                ctx.beginPath();
                ctx.moveTo(0, height);  // Top point
                ctx.lineTo(width, height);  // Bottom left point
                ctx.lineTo(width, height / 2); // Bottom right point
                ctx.closePath();

                // Fill the triangle with a color
                ctx.fillStyle = window.color;
                ctx.fill();
            }
        }
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
