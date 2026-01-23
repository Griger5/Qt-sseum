import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs
import QtQuick.Layouts

Page {
    property bool busy: false

    signal goToLogin()
    signal registrationSuccessful()

    MessageDialog {
        id: errorDialog
        title: "Error"
    }

    ColumnLayout {
        anchors.centerIn: parent
        spacing: 20
        width: parent.width * 0.8

        Text {
            text: "Register"
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
                placeholderText: "Choose a username"
                Layout.fillWidth: true
                Layout.maximumWidth: 400
                Layout.alignment: Qt.AlignHCenter
            }
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
                placeholderText: "Choose a password"
                Layout.fillWidth: true
                Layout.maximumWidth: 400
                Layout.alignment: Qt.AlignHCenter
            }
        }

        ColumnLayout {
            spacing: 5
            Layout.alignment: Qt.AlignHCenter

            Label {
                text: "Confirm Password"
                Layout.fillWidth: true
                Layout.maximumWidth: 400
                Layout.alignment: Qt.AlignLeft
            }

            TextField {
                id: passwordConfirmInput;
                echoMode: TextInput.Password;
                placeholderText: "Re-enter password"
                Layout.fillWidth: true
                Layout.maximumWidth: 400
                Layout.alignment: Qt.AlignHCenter
            }
        }

        Button {
            text: busy ? "Working..." : "Register"
            enabled: !busy
            Layout.fillWidth: true
            Layout.maximumWidth: 400
            Layout.alignment: Qt.AlignHCenter
            onClicked: {
                if (passwordInput.text !== passwordConfirmInput.text) {
                    errorDialog.text = "Passwords do not match!";
                    errorDialog.open();
                    return;
                }

                busy = true
                registrationClient.registerUserAsync(usernameInput.text, emailInput.text, passwordInput.text);
            }
        }

        Button {
            text: "Already have an account?"
            Layout.fillWidth: true
            Layout.maximumWidth: 400
            Layout.alignment: Qt.AlignHCenter
            flat: true
            onClicked: goToLogin();
        }
    }

    Connections {
        target: registrationClient

        function onRegistrationSuccessful() {
            busy = false;
            goToLogin();
        }

        function onUserAlreadyExists() {
            busy = false;
            errorDialog.text = "User with this email already exists!";
            errorDialog.open();
        }

        function onErrorOccurred(error) {
            busy = false;
            errorDialog.text = error;
            errorDialog.open();
        }
    }
}