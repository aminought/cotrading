import QtQuick 2.0
import QtQuick.Controls 1.4
import QtCharts 2.0

ChartView {
    property alias ctChartCanvas: ctChartCanvas
    objectName: "chart_view"
    antialiasing: true
    property var x_axis
    property var y_axis

    function paintLine(y) {
        ctChartCanvas.paintLine(y)
    }

    function removeLines() {
        ctChartCanvas.removeLines()
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

    function loadChart() {
        var line_series = ctChart.createSeries(
                    ChartView.SeriesTypeLine, "",
                    ctChart.createDateTimeAxis("dd.MM.yyyy hh:mm"),
                    ctChart.createValueAxis(_chart_controller.y_min,
                                            _chart_controller.y_max))
        var prices = _chart_controller.y
        var times = _chart_controller.x
        for (var i = 0; i < prices.length; ++i) {
            line_series.append(times[i], prices[i])
        }
    }

    function clearChart() {
        ctChart.removeAllSeries()
        ctChart.x_axis.destroy()
        ctChart.y_axis.destroy()
    }

    Canvas {
        id: ctChartCanvas
        anchors.fill: parent
        property var ctx: getContext("2d")
        property bool drawState: false

        MouseArea {
            anchors.fill: parent
            onClicked: {
                if (ctChartCanvas.drawState) {
                    var y = mouse.y
                    ctChartCanvas.paintLine(y)
                    _chart_controller.addHorizontalLine(y)
                    _menu_controller.send_coop_data()
                }
            }
        }

        function removeLines() {
            ctChartCanvas.ctx.reset()
            ctChartCanvas.requestPaint()
            _chart_controller.removeHorizontalLines()
        }

        function paintLine(y) {
            var ctx = ctChartCanvas.ctx
            ctx.lineWidth = 1
            ctx.strokeStyle = "#ff0000"
            ctx.beginPath()
            ctx.moveTo(0, y)
            ctx.lineTo(parent.width, y)
            ctx.closePath()
            ctx.stroke()
            ctChartCanvas.requestPaint()
        }
    }
}
