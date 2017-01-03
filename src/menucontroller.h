#ifndef MENUCONTROLLER_H
#define MENUCONTROLLER_H

#include <QObject>
#include "config.h"
#include "providerconnectionfactory.h"
#include "providerconnection.h"
#include "chartcontroller.h"
#include "coopconnection.h"

class MenuController : public QObject {
    Q_OBJECT
public:
    explicit MenuController(QObject *parent = 0);
    MenuController(std::shared_ptr<Config> config,
                   std::shared_ptr<ProviderConnection> provider_connection,
                   std::shared_ptr<ChartController> chart_controller,
                   std::shared_ptr<CoopConnection> coop_connection):
        config(config),
        provider_connection(provider_connection),
        coop_connection(coop_connection),
        chart_controller(chart_controller) {}
public slots:
    void connect(ProviderType provider = ProviderType::CQG);
    void disconnect();
    void start_coop_server();
    void connect_to_coop_server();
    void send_coop_data();
private:
    std::shared_ptr<Config> config;
    std::shared_ptr<ProviderConnection> provider_connection;
    std::shared_ptr<QuotesProvider> provider;
    std::shared_ptr<CoopConnection> coop_connection;
    std::shared_ptr<ChartController> chart_controller;
};

#endif // MENUCONTROLLER_H
