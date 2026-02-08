import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs
import QtQuick.Layouts

Page {
    property bool busy: false

    signal goToRegister()
    signal goToMainPage()

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
                placeholderText: "Wpisz swój email"
                Layout.fillWidth: true
                Layout.maximumWidth: 400
                Layout.alignment: Qt.AlignHCenter
                }
        }

        ColumnLayout {
            spacing: 5
            Layout.alignment: Qt.AlignHCenter

            Label {
                text: "Hasło"
                Layout.fillWidth: true
                Layout.maximumWidth: 400
                Layout.alignment: Qt.AlignLeft
            }

            TextField { 
                id: passwordInput;
                echoMode: TextInput.Password;
                placeholderText: "Wpisz swoje hasło"
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
            text: "Nie masz jeszcze konta?"
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
            sessionLogic.onLoginSuccessful()
        }

        function onInvalidCredentials() {
            busy = false
            errorDialog.text = "Zły email lub hasło!"
            errorDialog.open()
        }

        function onAuthUnavailable() {
            busy = false
            errorDialog.text = "Serwer nieodpowiada. Spróbuj ponownie później."
            errorDialog.open()
        }

        function onErrorOccurred(error) {
            busy = false
            errorDialog.text = error
            errorDialog.open()
        }
    }

    Connections {
        target: sessionLogic

        function onProfileReady() {
            goToMainPage()
        }

        function onErrorOccurred(error) {
            busy = false
            errorDialog.text = error
            errorDialog.open()
        }
    }
}