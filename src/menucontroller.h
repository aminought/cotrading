#ifndef MENUCONTROLLER_H
#define MENUCONTROLLER_H

#include <QObject>
#include "config.h"
#include "providerconnectionfactory.h"
#include "providerconnection.h"

class MenuController : public QObject {
    Q_OBJECT
public:
    explicit MenuController(QObject *parent = 0);
    MenuController(std::shared_ptr<Config> config, std::shared_ptr<ProviderConnection> provider_connection):
        config(config),
        provider_connection(provider_connection) {}
public slots:
    void connect(ProviderType provider = ProviderType::CQG);
private:
    std::shared_ptr<Config> config;
    std::shared_ptr<ProviderConnection> provider_connection;
    std::shared_ptr<QuotesProvider> provider;
};

#endif // MENUCONTROLLER_H
