import QtQuick 2.5
import QtQuick.Dialogs 1.2
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1

Dialog {
    id: ctSettings
    modality: Qt.WindowModal
    title: qsTr("Settings")
    standardButtons: StandardButton.Ok | StandardButton.Apply | StandardButton.Cancel
    onAccepted: _settings_controller.saveConfig(userName.text, password.text,
                                                clientId.text, accountId.text)

    Column {
        anchors.horizontalCenter: parent.horizontalCenter
        spacing: 3

        TextField {
            id: userName
            placeholderText: qsTr("Username")
        }

        TextField {
            id: password
            placeholderText: qsTr("Password")
        }

        TextField {
            id: clientId
            placeholderText: qsTr("Client id")
        }

        TextField {
            id: accountId
            placeholderText: qsTr("Account id")
        }
    }
}
