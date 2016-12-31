#ifndef MENUCONTROLLER_H
#define MENUCONTROLLER_H

#include <QObject>
#include "config.h"
#include "providerconnectionfactory.h"
#include "providerconnection.h"
#include "chartcontroller.h"

class MenuController : public QObject {
    Q_OBJECT
public:
    explicit MenuController(QObject *parent = 0);
    MenuController(std::shared_ptr<Config> config,
                   std::shared_ptr<ProviderConnection> provider_connection,
                   ChartController* chart_controller):
        config(config),
        provider_connection(provider_connection),
        chart_controller(chart_controller) {}
public slots:
    void connect(ProviderType provider = ProviderType::CQG);
    void disconnect();
private:
    std::shared_ptr<Config> config;
    std::shared_ptr<ProviderConnection> provider_connection;
    std::shared_ptr<QuotesProvider> provider;
    ChartController* chart_controller;
};

#endif // MENUCONTROLLER_H
