import QtQuick 2.5
import QtQuick.Dialogs 1.2
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1

Dialog {
    id: ctSettings
    visible: false
    title: qsTr("Settings")
    standardButtons: StandardButton.Ok | StandardButton.Apply | StandardButton.Cancel
    onAccepted: _settings_controller.save_config(userName.text, password.text,
                                                clientId.text, accountId.text)

    GridLayout {
        columns: 2
        anchors.horizontalCenter: parent.horizontalCenter

        Label {
            text: "User name"
            height: userName.height
        }

        TextField {
            id: userName
        }


        Label {
            text: "Password"
            height: password.height
        }

        TextField {
            id: password
        }

        Label {
            text: "Client Id"
            height: clientId.height
        }

        TextField {
            id: clientId
        }

        Label {
            text: "Account id"
            height: accountId.height
        }

        TextField {
            id: accountId
        }
    }

    Component.onCompleted: {
        userName.text = _settings_controller.load_user_name()
        password.text = _settings_controller.load_password()
        clientId.text = _settings_controller.load_client_id()
        accountId.text = _settings_controller.load_account_id()
    }
}
