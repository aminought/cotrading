#ifndef MENUCONTROLLER_H
#define MENUCONTROLLER_H

#include <QObject>
#include <trading/provider/sharedproviderconnection.h>
#include "coop/coopconnection.h"
#include "trading/provider/providerconnectionfactory.h"
#include "config.h"
#include "chartcontroller.h"


namespace ct {
namespace core {

class MenuController : public QObject {
    Q_OBJECT
public:
    explicit MenuController(QObject *parent = 0);
    MenuController(std::shared_ptr<Config> config,
                   std::shared_ptr<trading::provider::SharedProviderConnection> provider_connection,
                   std::shared_ptr<ChartController> chart_controller,
                   std::shared_ptr<coop::CoopConnection> coop_connection):
        config(config),
        provider_connection(provider_connection),
        coop_connection(coop_connection),
        chart_controller(chart_controller) {}
public slots:
    void connect(trading::provider::ProviderType provider = trading::provider::ProviderType::CQG);
    void disconnect();
    void start_coop_server();
    void connect_to_coop_server();
    void send_coop_data();
private:
    std::shared_ptr<Config> config;
    std::shared_ptr<trading::provider::SharedProviderConnection> provider_connection;
    std::shared_ptr<trading::provider::QuotesProvider> provider;
    std::shared_ptr<coop::CoopConnection> coop_connection;
    std::shared_ptr<ChartController> chart_controller;
};

}
}

#endif // MENUCONTROLLER_H
