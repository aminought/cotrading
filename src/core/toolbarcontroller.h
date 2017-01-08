#ifndef TOOLBARCONTROLLER_H
#define TOOLBARCONTROLLER_H

#include <QObject>
#include "trading/provider/sharedproviderconnection.h"
#include "core/chartcontroller.h"
#include "trading/model/contract.h"


namespace ct {
namespace core {

class ToolBarController : public QObject {
    Q_OBJECT

public:
    explicit ToolBarController(QObject *parent = 0): QObject(parent) {}
    ToolBarController(std::shared_ptr<ct::trading::provider::SharedProviderConnection> provider_connection,
                      std::shared_ptr<ct::core::ChartController> chart_controller):
        provider_connection(provider_connection),
        chart_controller(chart_controller) {}

public slots:
    void load_historical_data(int symbol);

private:
    std::shared_ptr<ct::trading::provider::SharedProviderConnection> provider_connection;
    std::shared_ptr<ct::core::ChartController> chart_controller;
};

}
}

#endif // TOOLBARCONTROLLER_H
