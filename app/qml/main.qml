import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtCharts 2.0

ApplicationWindow {
    id: window
    objectName: "window"
    visible: true
    width: 640
    height: 480

    menuBar: CtMenuBar {
        id: ctMenuBar
    }

    toolBar: CtToolBar {
        id: ctToolBar
    }

    CtChart {
        id: ctChart
        objectName: "ctChart"
        anchors.fill: parent
    }

    statusBar: StatusBar {
        RowLayout {
            Label {
                id: statusLabel
                text: "Disconnected"
            }
        }
    }

    Component.onCompleted: {
        ctToolBar.ctChartCanvas = ctChart.ctChartCanvas
        ctMenuBar.ctChart = ctChart
    }
}
