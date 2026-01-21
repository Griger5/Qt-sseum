import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Page {
    signal goToRegister()
    signal loginSuccessful()

    ColumnLayout {
        anchors.centerIn: parent
        spacing: 20
        width: parent.width * 0.8

        Text {
            text: "Login"
            font.pointSize: 24
            horizontalAlignment: Text.AlignHCenter
            Layout.alignment: Qt.AlignHCenter
        }

        ColumnLayout {
            spacing: 5
            Layout.alignment: Qt.AlignHCenter

            Label {
                text: "Username"
                Layout.fillWidth: true
                Layout.maximumWidth: 400
                Layout.alignment: Qt.AlignLeft
            
            }
            TextField {
                id: usernameInput;
                placeholderText: "Enter your username"
                Layout.fillWidth: true
                Layout.maximumWidth: 400
                Layout.alignment: Qt.AlignHCenter
                }
        }

        ColumnLayout {
            spacing: 5
            Layout.alignment: Qt.AlignHCenter

            Label {
                text: "Password"
                Layout.fillWidth: true
                Layout.maximumWidth: 400
                Layout.alignment: Qt.AlignLeft
            }

            TextField { 
                id: passwordInput;
                echoMode: TextInput.Password;
                placeholderText: "Enter your password"
                Layout.fillWidth: true
                Layout.maximumWidth: 400
                Layout.alignment: Qt.AlignHCenter
            }
        }

        Button {
            text: "Login"
            Layout.fillWidth: true
            Layout.maximumWidth: 400
            Layout.alignment: Qt.AlignHCenter
            onClicked: loginSuccessful()
        }

        Button {
            text: "Don't have an account yet?"
            Layout.fillWidth: true
            Layout.maximumWidth: 400
            Layout.alignment: Qt.AlignHCenter
            flat: true
            onClicked: goToRegister()
        }
    }
}