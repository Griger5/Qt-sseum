import QtQuick
import QtQuick.Controls

ApplicationWindow {
    width: 400
    height: 220
    visible: true
    title: "Qt gRPC Client"

    Column {
        anchors.centerIn: parent
        spacing: 12

        TextField {
            id: nameField
            placeholderText: "Enter your name"
        }

        Button {
            text: "Say Hello"
            onClicked: {
                resultLabel.text = grpcClient.sayHello(nameField.text)
            }
        }

        Label {
            id: resultLabel
            text: ""
        }
    }
}