import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Page {
    readonly property real h1Factor: 0.25
    readonly property real h2Factor: 0.2
    readonly property real h3Factor: 0.14
    readonly property real buttonH1Factor: 0.1

    readonly property int h1Max: 48
    readonly property int h2Max: 48
    readonly property int h3Max: 36
    readonly property int buttonH1Max: 64

    signal goToArena()
    signal goToExploration()
    signal goToMarket()
    signal goToTraining()
    signal goToRanking()
    signal logout()

    RowLayout {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 30

        ColumnLayout {
            spacing: 10
            Layout.preferredWidth: parent.width * 0.25
            Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter

            Label {
                text: "Player"
                font.pixelSize: h2(parent.width)
            }

            Label {
                text: "Level: " + User.level
                font.pixelSize: h3(parent.width)
            }

            Label {
                text: "Experience: " + User.experience
                font.pixelSize: h3(parent.width)
            }

            Label {
                text: "Money: " + User.money
                font.pixelSize: h3(parent.width)
            }
        }

        ColumnLayout {
            spacing: 10
            Layout.preferredWidth: parent.width * 0.45
            Layout.alignment: Qt.AlignHCenter

            Image {
                source: "qrc:/resources/gladiators/hoplomachus.png"
                fillMode: Image.PreserveAspectFit
                Layout.fillWidth: true
                Layout.preferredWidth: 350
                Layout.preferredHeight: 350
            }

            Image {
                source: "qrc:/resources/weapons/spear.png"
                fillMode: Image.PreserveAspectFit
                Layout.fillWidth: true
                Layout.preferredWidth: 150
                Layout.preferredHeight: 150
                Layout.alignment: Qt.AlignHCenter | Qt.AlignBottom
            }

            Label {
                text: "Nameless"
                font.pixelSize: h1(parent.width)
                Layout.alignment: Qt.AlignHCenter
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
                text: "Exploration"
                onClicked: goToExploration()
            }

            Button {
                Layout.fillWidth: true
                Layout.maximumWidth: 400
                font.pixelSize: buttonH1(parent.width)
                padding: parent.width * 0.08
                text: "Market"
                onClicked: goToMarket()
            }

            Button {
                Layout.fillWidth: true
                Layout.maximumWidth: 400
                font.pixelSize: buttonH1(parent.width)
                padding: parent.width * 0.08
                text: "Training"
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
                text: "Logout"
                onClicked: logout()
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

    function buttonH1(width) {
        return Math.max(1, Math.min(width * buttonH1Factor, buttonH1Max))
    }
}