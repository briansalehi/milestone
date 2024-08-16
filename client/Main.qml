import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material

ApplicationWindow {
    title: qsTr("Milestone")
    visible: true
    visibility: Window.Maximized
    Material.theme: Material.Dark
    minimumHeight: 800
    minimumWidth: 600

    Login {
        id: login

        heading: "Login"
        fontSize: 58
        onClicked: {
            login.heading = "Logging In"
        }
    }
}
