import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2
import QtCharts 2.0

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
                id: cqgMenu
                title: qsTr("CQG")

                function createValueAxis(min, max) {
                    return Qt.createQmlObject(
                                "import QtQuick 2.5; import QtCharts 2.0; ValueAxis { min: "
                                + min + "; max: " + max + " }", chartView)
                }

                function createDateTimeAxis(format) {
                    var create_str = "import QtQuick 2.5; import QtCharts 2.0; DateTimeAxis { format: '" + format
                            + "'; min: _chart_controller.x_min; max: _chart_controller.x_max}"
                    return Qt.createQmlObject(create_str, chartView)
                }

                function createChart() {
                    var line_series = chartView.createSeries(
                                ChartView.SeriesTypeLine, "",
                                cqgMenu.createDateTimeAxis("dd.MM.yyyy hh:mm"),
                                cqgMenu.createValueAxis(
                                    _chart_controller.y_min,
                                    _chart_controller.y_max))
                    var prices = _chart_controller.y
                    var times = _chart_controller.x
                    for(var i=0; i<prices.length; ++i) {
                        line_series.append(times[i], prices[i])
                    }

                }

                MenuItem {
                    text: qsTr("Connect")
                    onTriggered: {
                        _menu_controller.connect(100)
                        cqgMenu.createChart()
                    }
                }
            }
        }
    }

    ChartView {
        id: chartView
        objectName: "chart_view"
        anchors.fill: parent
        antialiasing: true
    }
}
