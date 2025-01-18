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
    property color font_color: '#B0B0B0'
    property int short_side: height > width ? width : height
    property int long_side:  height < width ? width : height
    property string orientation: height > width ? "vertical" : "horizontal"

    function percent(value, percentage)
    {
        return value * percentage / 100;
    }

    function lock_window()
    {
        workspace.enabled = false;
        shadow.visible = true;
    }

    function unlock_window()
    {
        workspace.enabled = true;
        shadow.visible = false;
    }

    Rectangle {
        id: shadow
        visible: false
        anchors.fill: parent
        color: window.color
        z: 99

        Item {
            anchors.centerIn: parent
            z: 100

            Text {
                id: loading_text
                font.pixelSize: window.font_big
                color: window.font_color
                text: "LOADING"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter

                onImplicitHeightChanged: {
                    parent.width = width
                    parent.height = height
                }

                SequentialAnimation on opacity {
                    running: shadow.visible
                    loops: Animation.Infinite
                    NumberAnimation { to: 0.0; duration: 1000 }
                    PauseAnimation { duration: 500 }
                    NumberAnimation { to: 1.0; duration: 1000 }
                    PauseAnimation { duration: 500 }
                }
            }
        }
    }

    WorkSpace {
        id: workspace
        foreground: Qt.lighter(window.color)
        background: window.color
        font: window.font
        text_color: window.font_color
        enabled: false

        anchors.top: parent.top
        anchors.topMargin: window.orientation == "vertical" ? window.percent(window.long_side, 8) : window.percent(window.short_side, 10)
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.leftMargin: window.orientation == "vertical" ? window.percent(window.short_side, 10) : window.percent(window.long_side, 20)
        anchors.right: parent.right
        anchors.rightMargin: window.orientation == "vertical" ? window.percent(window.short_side, 10) : window.percent(window.long_side, 20)

        onShowBack: {
            back.visible = true
        }
        onHideBack: {
            back.visible = false
        }

        onLock: {
            window.lock_window();
        }

        onUnlock: {
            window.unlock_window();
        }
    }

    Rectangle {
        id: back
        visible: false
        color: Qt.lighter(window.color)
        anchors.right: workspace.left
        anchors.rightMargin: 20
        anchors.verticalCenter: parent.verticalCenter
        height: Math.max(100, window.percent(window.long_side, 15))
        width: window.percent(back.height, 25)

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

    Rectangle {
        id: next
        visible: false
        color: Qt.lighter(window.color)
        anchors.left: workspace.right
        anchors.leftMargin: 20
        anchors.verticalCenter: parent.verticalCenter
        height: Math.max(100, window.percent(window.long_side, 15))
        width: window.percent(back.height, 25)

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
}
