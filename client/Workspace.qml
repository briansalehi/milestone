import QtQuick

Item {
    id: workspace
    anchors.horizontalCenter: parent.horizontalCenter
    anchors.top: parent.top
    anchors.topMargin: parent.height / 10
    anchors.bottom: parent.bottom
    anchors.bottomMargin: parent.height / 10
    width: parent.width / 10 * 5

    property color entry_color
    property string entry_font

    Column {
        id: entries
        width: parent.width
        height: parent.height
        spacing: 10

        Entry {
            background_color: entry_color
            foreground_color: 'white'
            entry_font: workspace.entry_font
            headline: "Modern CMake for C++"
            updated: "2 days ago"
        }

        Entry {
            background_color: entry_color
            foreground_color: 'white'
            entry_font: workspace.entry_font
            headline: "Boost.Asio C++ Network Programming Cookbook"
            updated: "47 days ago"
        }
    }
}
