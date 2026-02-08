import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs
import QtQuick.Layouts

Page {
    readonly property real h1Factor: 0.25
    readonly property real h2Factor: 0.2
    readonly property real h3Factor: 0.14
    readonly property real h4Factor: 0.09
    readonly property real buttonH1Factor: 0.1

    readonly property int h1Max: 48
    readonly property int h2Max: 48
    readonly property int h3Max: 36
    readonly property int h4Max: 20
    readonly property int buttonH1Max: 64

    readonly property int str: 0
    readonly property int dex: 1
    readonly property int def: 2
    readonly property int vit: 3

    signal goToMainPage()

    MessageDialog {
        id: errorDialog
        title: "Error"
    }

    RowLayout {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 30

        ColumnLayout {
            spacing: 10
            Layout.minimumWidth: parent.width * 0.25
            Layout.maximumWidth: parent.width * 0.25
            Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
            Layout.fillWidth: true

            Label {
                text: "Złoto: " + User.money
                font.pixelSize: h3(parent.width)
                Layout.fillWidth: true
            }

            Label {
                text: Gladiator.name
                font.pixelSize: h3(parent.width)
                Layout.fillWidth: true
            }

            Label {
                text: "Siła: " + Number(Gladiator.strength + Weapon.strength)
                font.pixelSize: h4(parent.width)
                Layout.fillWidth: true
            }

            Label {
                text: "Zręczność: " + Number(Gladiator.dexterity + Weapon.dexterity)
                font.pixelSize: h4(parent.width)
                Layout.fillWidth: true
            }

            Label {
                text: "Obrona: " + Number(Gladiator.defence + Weapon.defence)
                font.pixelSize: h4(parent.width)
                Layout.fillWidth: true
            }

            Label {
                text: "Zdrowie: " + Number(Gladiator.vitality + Weapon.vitality)
                font.pixelSize: h4(parent.width)
                Layout.fillWidth: true
            }

            Label {
                text: "HP: " + 3 * (Gladiator.vitality + Weapon.vitality) * User.level
                font.pixelSize: h4(parent.width)
                Layout.fillWidth: true
            }

            Label {
                text: "Obrażenia: " + Math.ceil(Weapon.min * Math.ceil((Gladiator.strength + Weapon.strength)/10)) + " - " + Math.ceil(Weapon.max * (1 + User.level/10) * Math.ceil((Gladiator.strength + Weapon.strength)/10))
                font.pixelSize: h4(parent.width)
                Layout.fillWidth: true
            }
        }

        ColumnLayout {
            spacing: 10
            Layout.minimumWidth: parent.width * 0.33
            Layout.maximumWidth: parent.width * 0.33
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter

            Label {
                text: "Trener"
                font.pixelSize: h2(parent.width)
                Layout.alignment: Qt.AlignHCenter
            }

            Image {
                source: "qrc:/resources/misc/trainer.png"
                fillMode: Image.PreserveAspectFit
                Layout.alignment: Qt.AlignHCenter
                Layout.fillWidth: true
                Layout.preferredWidth: 250
                Layout.preferredHeight: 250
            }

            Label {
                text: "Koszt: 100"
                font.pixelSize: h2(parent.width)
                Layout.alignment: Qt.AlignHCenter
            }

            Button {
                Layout.fillWidth: true
                Layout.maximumWidth: 400
                font.pixelSize: buttonH1(parent.width)
                padding: parent.width * 0.08
                text: "Dodaj Siłe"
                onClicked: add_stat(str)
            }

            Button {
                Layout.fillWidth: true
                Layout.maximumWidth: 400
                font.pixelSize: buttonH1(parent.width)
                padding: parent.width * 0.08
                text: "Dodaj Zręczność"
                onClicked: add_stat(dex)
            }

            Button {
                Layout.fillWidth: true
                Layout.maximumWidth: 400
                font.pixelSize: buttonH1(parent.width)
                padding: parent.width * 0.08
                text: "Dodaj Obrone"
                onClicked: add_stat(def)
            }

            Button {
                Layout.fillWidth: true
                Layout.maximumWidth: 400
                font.pixelSize: buttonH1(parent.width)
                padding: parent.width * 0.08
                text: "Dodaj Zdrowie"
                onClicked: add_stat(vit)
            }
        }

        ColumnLayout {
            spacing: 10
            Layout.rightMargin: 0
            Layout.preferredWidth: parent.width * 0.25
            Layout.alignment: Qt.AlignRight | Qt.AlignVCenter

            Button {
                Layout.fillWidth: true
                Layout.maximumWidth: 200
                font.pixelSize: buttonH1(parent.width)
                padding: parent.width * 0.08
                text: "Wróc"
                onClicked: goToMainPage()
            }
        }
    }

    function add_stat(stat) {
        if (User.money >= 100) {
            trainerClient.upgradeStatAsync(Gladiator.id, stat, 1)
        }
        else {
            errorDialog.text = "Nie wystarczająco złota!"
            errorDialog.open()
        }
    }

    function h1(width) {
        return Math.max(1, Math.min(width * h1Factor, h1Max))
    }

    function h2(width) {
        return Math.max(1, Math.min(width * h2Factor, h2Max))
    }

    function h3(width) {
        return Math.max(1, Math.min(width * h3Factor, h3Max))
    }

    function h4(width) {
        return Math.max(1, Math.min(width * h4Factor, h4Max))
    }

    function buttonH1(width) {
        return Math.max(1, Math.min(width * buttonH1Factor, buttonH1Max))
    }

    Connections {
        target: sessionLogic

        function onProfileReady() {
            goToMainPage()
        }

        function onErrorOccurred(error) {
            errorDialog.text = error
            errorDialog.open()
        }
    }
}