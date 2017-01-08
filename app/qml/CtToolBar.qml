import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtCharts 2.0

ToolBar {
    property var ctChartCanvas
    property var ctChart
    height: toolLayout.height + 5

    RowLayout {
        anchors.left: parent.left

        ComboBox {
            id: combo
            currentIndex: 0
            model: ListModel {
                id: symbols
                ListElement { text: qsTr("CL (Crude Oil)") }
                ListElement { text: qsTr("GC (Gold)") }
            }

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


            onActivated: {
                // This is available in all editors.
                console.log(currentIndex)
                _toolbar_controller.load_historical_data(currentIndex)
                ctChart.removeAllSeries()
                ctChart.x_axis.destroy()
                ctChart.y_axis.destroy()
                var line_series = ctChart.createSeries(
                            ChartView.SeriesTypeLine, "",
                            combo.createDateTimeAxis("dd.MM.yyyy hh:mm"),
                            combo.createValueAxis(_chart_controller.y_min,
                                                    _chart_controller.y_max))
                var prices = _chart_controller.y
                var times = _chart_controller.x
                for (var i = 0; i < prices.length; ++i) {
                    line_series.append(times[i], prices[i])
                }
            }
        }
    }

    RowLayout {
        id: toolLayout
        anchors.right: parent.right

        ToolButton {
            text: qsTr("Draw line")
            checkable: true

            onClicked: {
                if (!ctChartCanvas.drawState) {
                    statusLabel.text = qsTr("Line drawing")
                } else {
                    statusLabel.text = qsTr("Connection established")
                }
                ctChartCanvas.drawState = !ctChartCanvas.drawState
            }
        }

        ToolButton {
            text: qsTr("Clear")
            onClicked: {
                ctChartCanvas.removeLines()
            }
        }
    }
}
