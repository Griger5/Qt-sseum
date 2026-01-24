import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs
import QtQuick.Layouts

Page {
    property bool busy: false

    signal goToRegister()
    signal loginSuccessful()

    MessageDialog {
        id: errorDialog
        title: "Error"
    }

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
                text: "Email"
                Layout.fillWidth: true
                Layout.maximumWidth: 400
                Layout.alignment: Qt.AlignLeft
            
            }
            TextField {
                id: emailInput;
                placeholderText: "Enter your email"
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
            onClicked: {
                busy = true;
                authClient.issueTokenAsync(emailInput.text, passwordInput.text)
            }
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

    Connections {
        target: authClient

        function onTokensIssued() {
            busy = false
            loginSuccessful()
        }

        function onInvalidCredentials() {
            busy = false
            errorDialog.text = "Invalid email or password!"
            errorDialog.open()
        }

        function onAuthUnavailable() {
            busy = false
            errorDialog.text = "The service is currently unavailable. Try again later."
            errorDialog.open()
        }

        function onErrorOccurred(error) {
            busy = false
            errorDialog.text = error
            errorDialog.open()
        }
    }
}