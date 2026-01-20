import QtQuick
import QtQuick.Controls

ApplicationWindow {
    width: 400
    height: 220
    visible: true
    title: "Qt gRPC Client"

    StackView {
        id: stack
        anchors.fill: parent
    }

    Component.onCompleted: {
        stack.push("GreeterPage.qml")
    }
}