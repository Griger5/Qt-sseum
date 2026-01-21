// import QtQuick
// import QtQuick.Controls

// ApplicationWindow {
//     width: 500
//     height: 500
//     visible: true
//     title: "Qt gRPC Client"

//     StackView {
//         id: stackView
//         anchors.fill: parent
//         initialItem: LoginPage {
//             onGoToRegister: stackView.replace("RegisterPage.qml")
//         }
//     }
// }

import QtQuick
import QtQuick.Controls

ApplicationWindow {
    id: window
    width: 700
    height: 700
    visible: true
    title: "Qt gRPC Client"

    StackView {
        id: stackView
        anchors.fill: parent
    }

    Navigator {
        id: navigator
        stackView: stackView
    }

    Component.onCompleted: navigator.showLogin()
}
