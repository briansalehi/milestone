import QtQuick
import QtWebView

Window {
    id: root
    width: 1280
    height: 768
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
        width: ((root.width / 3) < 300 ? (root.width / 3) : 300) - root.padding
        height: root.height - root.padding * 2
        radius: 5

        anchors.right: parent.right
        anchors.rightMargin: root.padding
        anchors.verticalCenter: parent.verticalCenter

        ListModel {
            id: subjects

            ListElement { name: 'Boost' }
            ListElement { name: 'C++' }
            ListElement { name: 'CMake' }
            ListElement { name: 'Docker' }
            ListElement { name: 'GDB' }
            ListElement { name: 'Linux Kernel' }
            ListElement { name: 'Mathematics' }
            ListElement { name: 'OpenCV' }
            ListElement { name: 'Qt' }
            ListElement { name: 'Tmux' }
            ListElement { name: 'x64 Assembly' }
        }

        ListModel {
            id: topics

            ListElement { name: 'Asynchronous IO Context'; }
            ListElement { name: 'Asynchronous Event Processing Loop'; }
            ListElement { name: 'Queueing Asynchronous Tasks'; }
            ListElement { name: 'Serializing Event Processing Loop'; }
            ListElement { name: 'Handling Exceptional Event Processing Loop Control FLow'; }
            ListElement { name: 'Deadline Timer'; }
            ListElement { name: 'Endpoint'; }
            ListElement { name: 'Active Socket'; }
            ListElement { name: 'Passive Socket'; }
            ListElement { name: 'Resolving DNS'; }
            ListElement { name: 'Synchronous TCP Client'; }
            ListElement { name: 'Synchronous TCP Connection'; }
            ListElement { name: 'Asynchronous TCP Connection'; }
            ListElement { name: 'Writing into and Reading from Socket'; }
        }

        ListView {
            id: view
            anchors.fill: parent
            anchors.margins: root.padding
            spacing: 5
            model: subjects
            delegate: subject_entry
            clip: true
        }
    }

    Component {
        id: subject_entry

        Subject {
            required property int index
            required property string name

            title: name
            onClicked: {
                view.header = topic_heading;
                view.model = topics
                view.delegate = topic_entry
            }
        }
    }

    Component {
        id: topic_entry

        Topic {
            required property int index
            required property string name

            title: name
        }
    }

    Component {
        id: topic_heading

        Subject {
            required property int index
            required property string name

            title: 'Boost'
        }
    }

    Rectangle {
        id: editor
        color: Qt.darker(background.color, 1.2)
        width: root.width - sidebar.width - root.padding
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
                onLoadingChanged: reminder.start()
            }

            Timer {
                id: reminder
                interval: 1000
                running: true
                repeat: false
                onTriggered: webview.reload()
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
