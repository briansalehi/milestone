import QtQuick
import QtWebView

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

            ListElement { triggered: function() { }; link: 'boost.md';       name: 'Boost' }
            ListElement { triggered: function() { }; link: 'cpp.md';         name: 'C++' }
            ListElement { triggered: function() { }; link: 'cmake.md';       name: 'CMake' }
            ListElement { triggered: function() { }; link: 'docker.md';      name: 'Docker' }
            ListElement { triggered: function() { }; link: 'gdb.md';         name: 'GDB' }
            ListElement { triggered: function() { }; link: 'kernel.md';      name: 'Linux Kernel' }
            ListElement { triggered: function() { }; link: 'mathematics.md'; name: 'Mathematics' }
            ListElement { triggered: function() { }; link: 'opencv.md';      name: 'OpenCV' }
            ListElement { triggered: function() { }; link: 'qt.md';          name: 'Qt' }
            ListElement { triggered: function() { }; link: 'tmux.md';        name: 'Tmux' }
            ListElement { triggered: function() { }; link: 'assembly.md';    name: 'x64 Assembly' }
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
            required property string link

            title: name
            //onClicked: { preview.url = link }
        }
    }

    Rectangle {
        id: editor
        color: Qt.darker(background.color, 1.2)
        width: root.width * 2 / 3 - root.padding * 2
        height: root.height - root.padding * 2
        radius: 5

        // property alias url: webview.address

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

            WebView {
                id: webview
                anchors.fill: parent
                anchors.margins: 5
                url: 'http://localhost:1337'
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
