import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.1
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
                    chartView.y_axis = Qt.createQmlObject(
                                "import QtQuick 2.5; import QtCharts 2.0; ValueAxis {id: x_axis; min: "
                                + min + "; max: " + max + " }", chartView)
                    return chartView.y_axis
                }

                function createDateTimeAxis(format) {
                    var create_str = "import QtQuick 2.5; import QtCharts 2.0; DateTimeAxis {id: y_axis; format: '" + format
                            + "'; min: _chart_controller.x_min; max: _chart_controller.x_max}"
                    chartView.x_axis = Qt.createQmlObject(create_str, chartView)
                    return chartView.x_axis
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
                            chartView.removeAllSeries()
                            chartView.x_axis.destroy()
                            chartView.y_axis.destroy()
                            statusLabel.text = qsTr("Disconnected")
                        }
                    }
                }
            }
        }
    }

    toolBar: ToolBar {
        height: toolLayout.height + 5
        RowLayout {
            id: toolLayout
            ToolButton {
                text: qsTr("Draw line")
                checkable: true
                onClicked: {
                    if (!chartCanvas.drawState) {
                        statusLabel.text = qsTr("Line drawing")
                    } else {
                        statusLabel.text = qsTr("Connection established")
                    }
                    chartCanvas.drawState = !chartCanvas.drawState
                }
            }
            ToolButton {
                text: qsTr("Clear")
                onClicked: {
                    chartCanvas.ctx.reset()
                    chartCanvas.requestPaint()
                }
            }
        }
    }

    ChartView {
        id: chartView
        objectName: "chart_view"
        anchors.fill: parent
        antialiasing: true
        property var x_axis
        property var y_axis

        Canvas {
            id: chartCanvas
            anchors.fill: parent
            property var ctx: getContext("2d")
            property bool drawState: false

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    if (chartCanvas.drawState) {
                        chartCanvas.paintLine(mouse.y)
                    }
                }
            }

            function paintLine(y) {
                var ctx = chartCanvas.ctx
                ctx.lineWidth = 1
                ctx.strokeStyle = "#ff0000"
                ctx.beginPath()
                ctx.moveTo(0, y)
                ctx.lineTo(parent.width, y)
                ctx.closePath()
                ctx.stroke()
                chartCanvas.requestPaint()
            }

        }
    }

    statusBar: StatusBar {
        RowLayout {
            Label {
                id: statusLabel
                text: "Disconnected"
            }
        }
    }
}
