// import QtQuick
// import QtQuick.Controls
// import QtQuick.Layouts

// Page {
//     readonly property real h1Factor: 0.25
//     readonly property real h2Factor: 0.2
//     readonly property real h3Factor: 0.14
//     readonly property real h4Factor: 0.05
//     readonly property real buttonH1Factor: 0.1

//     readonly property int h1Max: 48
//     readonly property int h2Max: 48
//     readonly property int h3Max: 36
//     readonly property int h4Max: 20
//     readonly property int buttonH1Max: 64

//     signal goToArena()
//     signal goToExploration()
//     signal goToMarket()
//     signal goToTraining()
//     signal goToRanking()
//     signal logoutRequested()

//     RowLayout {
//         anchors.fill: parent
//         anchors.margins: 20
//         spacing: 30

//         ColumnLayout {
//             spacing: 10
//             Layout.preferredWidth: parent.width * 0.45
//             Layout.alignment: Qt.AlignHCenter

//             Image {
//                 source: "qrc:/resources/gladiators/" + gladiator1.gladiatorClass.toLowerCase() + ".png"
//                 fillMode: Image.PreserveAspectFit
//                 Layout.fillWidth: true
//                 Layout.preferredWidth: 250
//                 Layout.preferredHeight: 250
//             }

//             Image {
//                 source: "qrc:/resources/weapons/" + Weapon.name.split(' ')[1].toLowerCase() + ".png"
//                 fillMode: Image.PreserveAspectFit
//                 Layout.fillWidth: true
//                 Layout.preferredWidth: 100
//                 Layout.preferredHeight: 100
//                 Layout.alignment: Qt.AlignHCenter | Qt.AlignBottom
//             }

//             Label {
//                 text: Gladiator.name
//                 font.pixelSize: h1(parent.width)
//                 Layout.alignment: Qt.AlignHCenter
//             }

//             Label {
//                 text: "Item: " + Weapon.name
//                 font.pixelSize: h4(parent.width)
//             }

//             Label {
//                 text: "Strength: " + Number(Gladiator.strength + Weapon.strength)
//                 font.pixelSize: h4(parent.width)
//             }

//             Label {
//                 text: "Dexterity: " + Number(Gladiator.dexterity + Weapon.dexterity)
//                 font.pixelSize: h4(parent.width)
//             }

//             Label {
//                 text: "Defence: " + Number(Gladiator.defence + Weapon.defence)
//                 font.pixelSize: h4(parent.width)
//             }

//             Label {
//                 text: "Vitality: " + Number(Gladiator.vitality + Weapon.vitality)
//                 font.pixelSize: h4(parent.width)
//             }

//             Label {
//                 text: "HP: " + 3 * (Gladiator.vitality + Weapon.vitality) * User.level
//                 font.pixelSize: h4(parent.width)
//             }

//             Label {
//                 text: "Damage: " + Math.ceil(Weapon.min * Math.ceil((Gladiator.strength + Weapon.strength)/10)) + " - " + Math.ceil(Weapon.max * (1 + User.level/10) * Math.ceil((Gladiator.strength + Weapon.strength)/10))
//                 font.pixelSize: h4(parent.width)
//             }
//         }
//     }

//     function h1(width) {
//         return Math.max(1, Math.min(width * h1Factor, h1Max))
//     }

//     function h2(width) {
//         return Math.max(1, Math.min(width * h2Factor, h2Max))
//     }

//     function h3(width) {
//         return Math.max(1, Math.min(width * h3Factor, h3Max))
//     }

//     function h4(width) {
//         return Math.max(1, Math.min(width * h4Factor, h4Max))
//     }

//     function buttonH1(width) {
//         return Math.max(1, Math.min(width * buttonH1Factor, buttonH1Max))
//     }
// }

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Page {
    readonly property real h1Factor: 0.18
    readonly property real h4Factor: 0.05

    readonly property int h1Max: 36
    readonly property int h4Max: 20

    ListModel {
        id: opponentsModel
    }

    signal fightRequested(string opponentId)
    signal goToMainPage()

    RowLayout {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 30

        Repeater {
            model: opponentsModel

            ColumnLayout {
                spacing: 8
                Layout.fillHeight: true
                Layout.preferredWidth: parent.width * 0.3
                Layout.alignment: Qt.AlignTop

                Image {
                    source: "qrc:/resources/gladiators/" + gladiator_class.toLowerCase() + ".png"
                    fillMode: Image.PreserveAspectFit
                    Layout.maximumWidth: 200
                    Layout.fillWidth: true
                }

                Image {
                    source: "qrc:/resources/weapons/" + item_name.split(' ')[1].toLowerCase() + ".png"
                    fillMode: Image.PreserveAspectFit
                    Layout.preferredWidth: 100
                    Layout.alignment: Qt.AlignHCenter
                }

                Label {
                    text: username + " (Lv. " + level + ")"
                    font.pixelSize: h1(parent.width)
                    horizontalAlignment: Text.AlignHCenter
                    Layout.fillWidth: true
                }

                Label {
                    text: "Klasa: " + gladiator_name
                    font.pixelSize: h4(parent.width)
                }

                Label {
                    text: "Broń: " + item_name
                    font.pixelSize: h4(parent.width)
                }

                Label {
                    text: "Siła: " + strength
                    font.pixelSize: h4(root.width)
                }

                Label {
                    text: "Zręczność: " + dexterity
                    font.pixelSize: h4(root.width)
                }

                Label {
                    text: "Obrona: " + defence
                    font.pixelSize: h4(root.width)
                }

                Label {
                    text: "Zdrowie: " + vitality
                    font.pixelSize: h4(root.width)
                }

                Label {
                    text: "Obrażenia: " + min + " - " + max
                    font.pixelSize: h4(root.width)
                }

                Item {
                    Layout.fillHeight: true
                }

                Button {
                    text: "Walcz"
                    Layout.fillWidth: true
                    onClicked: root.fightRequested(id)
                }
            }
        }
    }

    function h1(width) {
        return Math.max(1, Math.min(width * h1Factor, h1Max))
    }

    function h4(width) {
        return Math.max(1, Math.min(width * h4Factor, h4Max))
    }

    Component.onCompleted: {
        arenaClient.getOpponentsAsync(3)
    }

    Connections {
        target: arenaClient

        function onOpponentsReceived(opponents) {
            opponentsModel.clear()

            for (let i = 0; i < opponents.length; ++i) {
                opponentsModel.append(opponents[i])
            }
        }

        function onErrorOccurred(error) {
            console.error("Arena error:", error)
        }
    }
}
