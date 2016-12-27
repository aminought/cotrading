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
        onAccepted: _settings_controller.saveConfig(user_name.text,
                                                    password.text,
                                                    client_id.text,
                                                    account_id.text)

        Column {
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 3

            TextField {
                id: user_name
                placeholderText: qsTr("Username")
            }

            TextField {
                id: password
                placeholderText: qsTr("Password")
            }

            TextField {
                id: client_id
                placeholderText: qsTr("Client id")
            }

            TextField {
                id: account_id
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

            MenuSeparator {
            }

            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit()
            }
        }

        Menu {
            title: qsTr("Connection")

            Menu {
                title: qsTr("CQG")

                MenuItem {
                    text: qsTr("Connect")
                    onTriggered: _menu_controller.connect(100)
                }
            }
        }
    }
}
