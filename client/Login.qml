import QtQuick

Item {
    id: login
    anchors.fill: parent
    visible: true

    property alias heading: heading.text
    property alias headingColor: heading.color
    property alias fontSize: heading.font.pixelSize
    signal clicked

    Text {
        id: heading
        text: "Login"
        color: "lightgray"
        font.family: "Dejavu"
        font.pixelSize: 58
        elide: Text.ElideNone
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: parent.height / 10 * 2
        verticalAlignment: Text.AlignHCenter
        horizontalAlignment: Text.AlignVCenter
    }

    property int fieldWidth: 300
    property int fieldHeight: 65
    property int fieldFontSize: 28

    Column {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: heading.bottom
        anchors.topMargin: login.height / 10
        spacing: 20

        Rectangle {
            color: "gray"
            width: fieldWidth
            height: fieldHeight
            anchors.horizontalCenter: parent.horizontalCenter

            TextInput {
                id: identity
                text: "Username or Email"
                anchors.fill: parent
                font.pixelSize: fieldFontSize
                color: "white"
                visible: true
                focus: true
                maximumLength: 100
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                KeyNavigation.tab: passphrase
                Keys.onReturnPressed: login.clicked()
            }
        }

        Rectangle {
            color: "gray"
            width: fieldWidth
            height: fieldHeight
            anchors.horizontalCenter: parent.horizontalCenter

            TextInput {
                id: passphrase
                text: "Passphrase"
                anchors.fill: parent
                font.pixelSize: fieldFontSize
                color: "white"
                visible: true
                echoMode: TextInput.Password
                maximumLength: 100
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                KeyNavigation.tab: submit
                Keys.onReturnPressed: login.clicked()
            }
        }

        Rectangle {
            id: submit
            width: fieldWidth
            height: fieldHeight
            anchors.horizontalCenter: parent.horizontalCenter
            color: "green"
            KeyNavigation.tab: identity
            Keys.onReturnPressed: login.clicked()

            MouseArea {
                anchors.fill: parent
                onClicked: login.clicked()
            }

            Text {
                text: "Submit"
                color: "black"
                font.pixelSize: fieldFontSize
                font.family: "Dejavu"
                anchors.centerIn: parent
                verticalAlignment: Text.AlignHCenter
                horizontalAlignment: Text.AlignVCenter
            }
        }

        Item {
            id: register
            width: fieldWidth
            height: fieldHeight
            anchors.horizontalCenter: parent.horizontalCenter

            Text {
                text: "Register"
                color: "blue"
                font.family: "Dejavu"
                font.pixelSize: 18
                verticalAlignment: Text.AlignHCenter
                horizontalAlignment: Text.VCenter
                anchors.right: parent.right
                anchors.top: parent.top
            }
        }
    }
}
