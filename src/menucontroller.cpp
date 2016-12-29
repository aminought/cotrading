#include "menucontroller.h"
#include "cqgprovider.h"
#include "cqgclient.h"
#include <QtDebug>
#include "providerconnectionfactory.h"


void MenuController::connect(ProviderType provider_type) {
    ProviderConnectionFactory factory;
    this->provider_connection = factory.get_provider_connection(provider_type);
    provider_connection->connect(this->config);
}
