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

            onActivated: {
                _toolbar_controller.load_historical_data(currentIndex)
                ctChart.clearChart()
                ctChart.loadChart()
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
