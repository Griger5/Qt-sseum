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
            text: "Zarejetruj konto"
            font.pointSize: 24
            horizontalAlignment: Text.AlignHCenter
            Layout.alignment: Qt.AlignHCenter
        }

        ColumnLayout {
            spacing: 5
            Layout.alignment: Qt.AlignHCenter

            Label {
                text: "Nick"
                Layout.fillWidth: true
                Layout.maximumWidth: 400
                Layout.alignment: Qt.AlignLeft
            }

            TextField {
                id: usernameInput;
                placeholderText: "Wybierz swój nick"
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
                placeholderText: "Wybierz swój email"
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
                placeholderText: "Wybierz hasło"
                Layout.fillWidth: true
                Layout.maximumWidth: 400
                Layout.alignment: Qt.AlignHCenter
            }
        }

        ColumnLayout {
            spacing: 5
            Layout.alignment: Qt.AlignHCenter

            Label {
                text: "Powtórz hasło"
                Layout.fillWidth: true
                Layout.maximumWidth: 400
                Layout.alignment: Qt.AlignLeft
            }

            TextField {
                id: passwordConfirmInput;
                echoMode: TextInput.Password;
                placeholderText: "Powtórz hasło"
                Layout.fillWidth: true
                Layout.maximumWidth: 400
                Layout.alignment: Qt.AlignHCenter
            }
        }

        Button {
            text: busy ? "Working..." : "Zarejestruj"
            enabled: !busy
            Layout.fillWidth: true
            Layout.maximumWidth: 400
            Layout.alignment: Qt.AlignHCenter
            onClicked: {
                if (passwordInput.text !== passwordConfirmInput.text) {
                    errorDialog.text = "Hasła się nie zgadzają!";
                    errorDialog.open();
                    return;
                }

                busy = true
                registrationClient.registerUserAsync(usernameInput.text, emailInput.text, passwordInput.text);
            }
        }

        Button {
            text: "Masz już konto?"
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
            errorDialog.text = "Użytkwonik z tym emailem już istnieje!";
            errorDialog.open();
        }

        function onDatabaseUnavailable() {
            busy = false;
            errorDialog.text = "Serwer nieodpowiada, spróbuj ponownie później";
            errorDialog.open();
        }

        function onErrorOccurred(error) {
            busy = false;
            errorDialog.text = error;
            errorDialog.open();
        }
    }
}