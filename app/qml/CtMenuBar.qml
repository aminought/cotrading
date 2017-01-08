import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtCharts 2.0

MenuBar {
    property var ctChart

    Menu {
        title: qsTr("File")

        MenuItem {
            id: settingsMenuItem
            text: qsTr("Settings")
            onTriggered: {
                var component = Qt.createComponent("CtSettings.qml")
                if (component.status === Component.Ready) {
                    var dialog = component.createObject(window)
                    dialog.modality = Qt.WindowModal
                    dialog.visible = true
                }
            }
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
            id: cqgMenu
            title: qsTr("CQG")


            MenuItem {
                property bool connected: false
                id: connectMenuItem
                text: qsTr("Connect")

                onTriggered: {
                    if (!connected) {
                        _menu_controller.connect(100)
                        statusLabel.text = qsTr("Connection established")
                        ctChart.loadChart()
                        connected = true
                        text = qsTr("Disconnect")
                    } else {
                        _menu_controller.disconnect()
                        connected = false
                        text = qsTr("Connect")
                        ctChart.clearChart()
                        statusLabel.text = qsTr("Disconnected")
                    }
                }
            }
        }
    }

    Menu {
        title: qsTr("Cooperation")

        MenuItem {
            text: qsTr("Start server")

            onTriggered: {
                _menu_controller.start_coop_server()
            }
        }

        MenuItem {
            text: qsTr("Connect to server")

            onTriggered: {
                _menu_controller.connect_to_coop_server()
            }
        }
    }
}
