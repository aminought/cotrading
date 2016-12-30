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
        auto contract = provider->resolve_symbol(Symbol::CL);
        qDebug() << contract->get_id() << " " << QString(contract->get_symbol().data());
    }
    // TODO: Get quotes and show chart
}
