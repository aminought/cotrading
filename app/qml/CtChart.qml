import QtQuick 2.0
import QtQuick.Controls 1.4
import QtCharts 2.0

ChartView {
    property alias ctChartCanvas: ctChartCanvas
    objectName: "chart_view"
    antialiasing: true
    property var x_axis
    property var y_axis

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
                }
            }
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