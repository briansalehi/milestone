import QtQuick

Item {
    id: menu
    anchors.top: parent.top
    anchors.topMargin: parent.height * 2 / 10
    anchors.bottom: parent.bottom
    anchors.bottomMargin: parent.height * 2 / 10
    anchors.horizontalCenter: parent.horizontalCenter
    width: parent.width * 5 / 10

    signal clicked

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
                menu.clicked();
            }
        }

        Space {
            title: "Practice"
            entry_font: window.font.family
            entry_color: window.color
            entry_font_size: font_big
            preferred_size: parent.width / 3
            onClicked: {
                menu.clicked();
            }
        }
    }
}
