import QtQuick

Window {
    id: root
    width: 1000
    height: 600
    visible: true
    title: qsTr("Flashback")

    property int padding: 20

    Rectangle {
        id: background
        color: '#383838'
        anchors.fill: parent
    }

    Rectangle {
        id: sidebar
        color: Qt.darker(background.color, 1.2)
        width: root.width / 3 - root.padding
        height: root.height - root.padding * 2
        radius: 5

        anchors.right: parent.right
        anchors.rightMargin: root.padding
        anchors.verticalCenter: parent.verticalCenter

        ListModel {
            id: topics

            ListElement { triggered: function() { }; name: 'Boost' }
            ListElement { triggered: function() { }; name: 'C++' }
            ListElement { triggered: function() { }; name: 'CMake' }
            ListElement { triggered: function() { }; name: 'Docker' }
            ListElement { triggered: function() { }; name: 'GDB' }
            ListElement { triggered: function() { }; name: 'Linux Kernel' }
            ListElement { triggered: function() { }; name: 'Mathematics' }
            ListElement { triggered: function() { }; name: 'OpenCV' }
            ListElement { triggered: function() { }; name: 'Qt' }
            ListElement { triggered: function() { }; name: 'Tmux' }
            ListElement { triggered: function() { }; name: 'x64 Assembly' }
        }

        ListView {
            id: view
            anchors.fill: parent
            anchors.margins: root.padding
            spacing: 5
            model: topics
            delegate: create_topic
            clip: true
        }
    }

    Component {
        id: create_topic

        Topic {
            required property int index
            required property string name

            title: name
            onClicked: { editor.heading = title }
        }
    }

    Rectangle {
        id: editor
        color: Qt.darker(background.color, 1.2)
        width: root.width * 2 / 3 - root.padding * 2
        height: root.height - root.padding * 2
        radius: 5

        property alias heading: label.text

        anchors.left: parent.left
        anchors.leftMargin: root.padding
        anchors.verticalCenter: parent.verticalCenter

        Rectangle {
            id: preview
            color: background.color
            anchors.fill: parent
            anchors.margins: root.padding
            anchors.bottomMargin: buttom_layout.height + root.padding * 2
            radius: 5

            Text {
                id: label
                color: 'white'
                font.family: 'OpenSans'
                font.pixelSize: 24
                anchors.top: parent.top
                anchors.topMargin: root.padding
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }

        Flow {
            id: buttom_layout
            anchors.bottom: parent.bottom
            anchors.bottomMargin: root.padding
            anchors.right: parent.right
            anchors.rightMargin: root.padding
            spacing: 20

            Button {
                color: 'lightsteelblue'
                text: 'Previous'
            }

            Button {
                color: 'lightsteelblue'
                text: 'Next'
            }
        }
    }
}
