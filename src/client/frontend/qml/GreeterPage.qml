import QtQuick
import QtQuick.Controls

Item {
    property bool busy: false

    Column {
        anchors.centerIn: parent
        spacing: 12

        TextField {
            id: nameField
            placeholderText: "Enter your name"
        }

        Button {
            text: busy ? "Working..." : "Say Hello"
            enabled: !busy
            onClicked: {
                busy = true
                resultLabel.text = ""
                greeterClient.sayHelloAsync(nameField.text)
            }
        }

        Label {
            id: resultLabel
            text: ""
        }
    }

    Connections {
        target: greeterClient

        function onHelloReceived(message) {
            busy = false
            resultLabel.text = message
        }

        function onErrorOccurred(error) {
            busy = false
            resultLabel.text = "Error: " + error
        }
    }
}