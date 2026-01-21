import QtQuick
import QtQuick.Controls

Item {
    property StackView stackView

    Component {
        id: loginComponent
        LoginPage {
            onGoToRegister: showRegister()
            onLoginSuccessful: showGreeter()
        }
    }

    Component {
        id: registerComponent
        RegisterPage {
            onGoToLogin: showLogin()
        }
    }

    Component {
        id: greeterComponent
        GreeterPage {
            onLogoutRequested: logout()
        }
    }

    function logout() {
        stackView.clear()
        stackView.push(loginComponent)
    }

    function showLogin() {
        stackView.replace(stackView.currentItem, loginComponent)
    }

    function showRegister() {
        stackView.replace(stackView.currentItem, registerComponent)
    }

    function showGreeter() {
        stackView.replace(greeterComponent)
    }
}