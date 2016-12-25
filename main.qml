import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2


ApplicationWindow {
    id: window
    visible: true
    width: 640
    height: 480

    Dialog {
        id: settingsDialog
        visible: false
        title: qsTr("Settings")
        standardButtons: StandardButton.Ok | StandardButton.Apply | StandardButton.Cancel
        onAccepted: console.log("Saving")

        Column {
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 3

            TextField {
                placeholderText: qsTr("Username")
            }

            TextField {
                placeholderText: qsTr("Password")
            }

            TextField {
                placeholderText: qsTr("Client id")
            }

            TextField {
                placeholderText: qsTr("Account id")
            }
        }
    }

    menuBar: MenuBar {
        Menu {
            title: qsTr("File")

            MenuItem {
                text: qsTr("Settings")
                onTriggered: settingsDialog.open()
            }

            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit()
            }
        }
    }
}
