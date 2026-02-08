import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Page {
    readonly property real h1Factor: 0.25
    readonly property real h2Factor: 0.2
    readonly property real h3Factor: 0.14
    readonly property real h4Factor: 0.05
    readonly property real buttonH1Factor: 0.1

    readonly property int h1Max: 48
    readonly property int h2Max: 48
    readonly property int h3Max: 36
    readonly property int h4Max: 20
    readonly property int buttonH1Max: 64

    signal goToArena()
    signal goToExploration()
    signal goToMarket()
    signal goToTraining()
    signal goToRanking()
    signal logoutRequested()

    RowLayout {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 30

        ColumnLayout {
            spacing: 10
            Layout.preferredWidth: parent.width * 0.25
            Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter

            Label {
                text: User.username
                font.pixelSize: h2(parent.width)
            }

            Label {
                text: "Level: " + User.level
                font.pixelSize: h3(parent.width)
            }

            Label {
                text: "Doświadczenie: " + User.experience
                font.pixelSize: h3(parent.width)
            }

            Label {
                text: "Złoto: " + User.money
                font.pixelSize: h3(parent.width)
            }
        }

        ColumnLayout {
            spacing: 10
            Layout.preferredWidth: parent.width * 0.45
            Layout.alignment: Qt.AlignHCenter

            Image {
                source: "qrc:/resources/gladiators/" + Gladiator.gladiatorClass.toLowerCase() + ".png"
                fillMode: Image.PreserveAspectFit
                Layout.fillWidth: true
                Layout.preferredWidth: 250
                Layout.preferredHeight: 250
            }

            Image {
                source: "qrc:/resources/weapons/" + Weapon.name.split(' ')[1].toLowerCase() + ".png"
                fillMode: Image.PreserveAspectFit
                Layout.fillWidth: true
                Layout.preferredWidth: 100
                Layout.preferredHeight: 100
                Layout.alignment: Qt.AlignHCenter | Qt.AlignBottom
            }

            Label {
                text: Gladiator.name
                font.pixelSize: h1(parent.width)
                Layout.alignment: Qt.AlignHCenter
            }

            Label {
                text: "Broń: " + Weapon.name
                font.pixelSize: h4(parent.width)
            }

            Label {
                text: "Siła: " + Number(Gladiator.strength + Weapon.strength)
                font.pixelSize: h4(parent.width)
            }

            Label {
                text: "Zręczność: " + Number(Gladiator.dexterity + Weapon.dexterity)
                font.pixelSize: h4(parent.width)
            }

            Label {
                text: "Obrona: " + Number(Gladiator.defence + Weapon.defence)
                font.pixelSize: h4(parent.width)
            }

            Label {
                text: "Zdrowie: " + Number(Gladiator.vitality + Weapon.vitality)
                font.pixelSize: h4(parent.width)
            }

            Label {
                text: "HP: " + 3 * (Gladiator.vitality + Weapon.vitality) * User.level
                font.pixelSize: h4(parent.width)
            }

            Label {
                text: "Obrażenia: " + Math.ceil(Weapon.min * Math.ceil((Gladiator.strength + Weapon.strength)/10)) + " - " + Math.ceil(Weapon.max * (1 + User.level/10) * Math.ceil((Gladiator.strength + Weapon.strength)/10))
                font.pixelSize: h4(parent.width)
            }
        }

        ColumnLayout {
            spacing: 10
            Layout.rightMargin: 0
            Layout.preferredWidth: parent.width * 0.25
            Layout.alignment: Qt.AlignRight | Qt.AlignVCenter

            Button {
                Layout.fillWidth: true
                Layout.maximumWidth: 400
                font.pixelSize: buttonH1(parent.width)
                padding: parent.width * 0.08
                text: "Arena"
                onClicked: goToArena()
            }

            Button {
                Layout.fillWidth: true
                Layout.maximumWidth: 400
                font.pixelSize: buttonH1(parent.width)
                padding: parent.width * 0.08
                text: "Eksploracja"
                onClicked: goToExploration()
            }

            Button {
                Layout.fillWidth: true
                Layout.maximumWidth: 400
                font.pixelSize: buttonH1(parent.width)
                padding: parent.width * 0.08
                text: "Rynek"
                onClicked: goToMarket()
            }

            Button {
                Layout.fillWidth: true
                Layout.maximumWidth: 400
                font.pixelSize: buttonH1(parent.width)
                padding: parent.width * 0.08
                text: "Trener"
                onClicked: goToTraining()
            }

            Button {
                Layout.fillWidth: true
                Layout.maximumWidth: 400
                font.pixelSize: buttonH1(parent.width)
                padding: parent.width * 0.08
                text: "Ranking"
                onClicked: goToRanking()
            }

            Button {
                Layout.fillWidth: true
                Layout.maximumWidth: 150
                Layout.alignment: Qt.AlignHCenter
                text: "Wyloguj"
                onClicked: logoutRequested()
            }
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
}