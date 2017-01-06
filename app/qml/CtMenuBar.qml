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

            function createValueAxis(min, max) {
                ctChart.y_axis = Qt.createQmlObject(
                            "import QtQuick 2.5; import QtCharts 2.0; ValueAxis {id: x_axis; min: "
                            + min + "; max: " + max + " }", ctChart)
                return ctChart.y_axis
            }

            function createDateTimeAxis(format) {
                var create_str = "import QtQuick 2.5; import QtCharts 2.0; DateTimeAxis {id: y_axis; format: '" + format
                        + "'; min: _chart_controller.x_min; max: _chart_controller.x_max}"
                ctChart.x_axis = Qt.createQmlObject(create_str, ctChart)
                return ctChart.x_axis
            }

            function createChart() {
                var line_series = ctChart.createSeries(
                            ChartView.SeriesTypeLine, "",
                            cqgMenu.createDateTimeAxis("dd.MM.yyyy hh:mm"),
                            cqgMenu.createValueAxis(_chart_controller.y_min,
                                                    _chart_controller.y_max))
                var prices = _chart_controller.y
                var times = _chart_controller.x
                for (var i = 0; i < prices.length; ++i) {
                    line_series.append(times[i], prices[i])
                }
            }

            MenuItem {
                property bool connected: false
                id: connectMenuItem
                text: qsTr("Connect")

                onTriggered: {
                    if (!connected) {
                        _menu_controller.connect(100)
                        statusLabel.text = qsTr("Connection established")
                        cqgMenu.createChart()
                        connected = true
                        text = qsTr("Disconnect")
                    } else {
                        _menu_controller.disconnect()
                        connected = false
                        text = qsTr("Connect")
                        ctChart.removeAllSeries()
                        ctChart.x_axis.destroy()
                        ctChart.y_axis.destroy()
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
