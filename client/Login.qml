import QtQuick
import QtQuick.Controls

Item {
    id: login
    anchors.fill: parent
    visible: true

    property alias heading: heading.text
    property alias headingColor: heading.color
    property alias fontSize: heading.font.pixelSize
    property alias fontFamily: login.fieldFontFamily
    signal clicked

    property string fieldFontFamily: "Utopia"
    property int fieldWidth: 300
    property int fieldHeight: 65
    property int fieldFontSize: 28

    Text {
        id: heading
        text: "Login"
        color: "lightgray"
        font.pixelSize: 58
        font.family: login.fieldFontFamily
        elide: Text.ElideNone
        focus: true
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: parent.height / 10 * 2
        verticalAlignment: Text.AlignHCenter
        horizontalAlignment: Text.AlignVCenter
        KeyNavigation.tab: identity
    }

    Column {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: heading.bottom
        anchors.topMargin: login.height / 10
        spacing: 20

        TextField {
            id: identity
            placeholderText: "Username or Email"
            placeholderTextColor: "gray"
            width: login.fieldWidth
            height: login.fieldHeight
            font.pixelSize: login.fieldFontSize
            font.family: login.fieldFontFamily
            visible: true
            focus: false
            maximumLength: 100
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            KeyNavigation.tab: passphrase
            Keys.onReturnPressed: validate_input()
        }

        TextField {
            id: passphrase
            placeholderText: "Passphrase"
            placeholderTextColor: "gray"
            width: login.fieldWidth
            height: login.fieldHeight
            font.pixelSize: login.fieldFontSize
            font.family: login.fieldFontFamily
            visible: true
            focus: false
            echoMode: TextInput.Password
            maximumLength: 100
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            KeyNavigation.tab: submit
            Keys.onReturnPressed: validate_input()
        }

        Rectangle {
            id: submit
            width: login.fieldWidth
            height: login.fieldHeight
            anchors.horizontalCenter: parent.horizontalCenter
            color: "green"
            focus: false
            KeyNavigation.tab: heading
            Keys.onReturnPressed: validate_input()

            MouseArea {
                anchors.fill: parent
                onClicked: validate_input()
            }

            Text {
                text: "Submit"
                color: "black"
                font.pixelSize: login.fieldFontSize
                font.family: login.fieldFontFamily
                anchors.centerIn: parent
                verticalAlignment: Text.AlignHCenter
                horizontalAlignment: Text.AlignVCenter
            }
        }

        Item {
            id: register
            width: login.fieldWidth
            height: login.fieldHeight
            anchors.horizontalCenter: parent.horizontalCenter

            Text {
                text: "Register"
                color: "blue"
                font.family: login.fieldFontFamily
                font.pixelSize: 18
                verticalAlignment: Text.AlignHCenter
                horizontalAlignment: Text.VCenter
                anchors.right: parent.right
                anchors.top: parent.top
            }
        }
    }

    function validate_input() {
        if (identity.text.length && passphrase.text.length) {
            login.clicked();
        }
    }
}
