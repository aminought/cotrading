#include "menucontroller.h"
#include "cqgprovider.h"
#include "cqgclient.h"
#include <QtDebug>
#include <QString>
#include "providerconnectionfactory.h"
#include "contract.h"


void MenuController::connect(ProviderType provider_type) {
    ProviderConnectionFactory factory;
    this->provider_connection = factory.get_provider_connection(provider_type);
    this->provider = provider_connection->connect(this->config);
    if(provider != nullptr) {
        std::shared_ptr<Contract> contract = provider->resolve_symbol(Symbol::CL);
        auto time_bars = provider->get_historical_data(contract, bpt::hours(24*30));
        qDebug() << "Get time bars";
    }
    // TODO: Get quotes and show chart
}
