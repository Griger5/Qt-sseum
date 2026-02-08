import QtQuick
import QtQuick.Controls

Item {
    property StackView stackView

    Component {
        id: loginComponent
        LoginPage {
            onGoToRegister: showRegister()
            onGoToMainPage: showMainPage()
        }
    }

    Component {
        id: registerComponent
        RegisterPage {
            onGoToLogin: showLogin()
        }
    }

    Component {
        id: mainPageComponent
        MainPage {
            onLogoutRequested: logout()
            onGoToTraining: showTraining()
            onGoToArena: showArena()
        }
    }

    Component {
        id: trainerComponent
        TrainerPage {
            onGoToMainPage: goBack()
        }
    }

    Component {
        id: arenaComponent
        ArenaPage {
            onGoToMainPage: goBack()
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

    function showMainPage() {
        stackView.replace(stackView.currentItem, mainPageComponent)
    }

    function goBack() {
        stackView.pop()
    }

    function showTraining() {
        stackView.push(trainerComponent)
    }

    function showArena() {
        stackView.push(arenaComponent)
    }

    function showGreeter() {
        stackView.replace(greeterComponent)
    }
}