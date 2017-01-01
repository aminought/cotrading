import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1

ToolBar {
    property var ctChartCanvas
    height: toolLayout.height + 5

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
                ctChartCanvas.ctx.reset()
                ctChartCanvas.requestPaint()
                _chart_controller.removeHorizontalLines()
            }
        }
    }
}
