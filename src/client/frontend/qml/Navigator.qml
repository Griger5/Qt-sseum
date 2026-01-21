import QtQuick
import QtQuick.Controls

Item {
    property StackView stackView

    Component {
        id: loginComponent
        LoginPage {
            onGoToRegister: showRegister()
            onLoginSuccess: showGreeter()
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
            onLogoutRequested: showLogin()
        }
    }

    function showLogin() {
        stackView.clear()
        stackView.push(loginComponent)
    }

    function showRegister() {
        stackView.push(registerComponent)
    }

    function showGreeter() {
        stackView.replace(greeterComponent)
    }
}