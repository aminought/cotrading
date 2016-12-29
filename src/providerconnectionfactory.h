#ifndef PROVIDERCONNECTIONFACTORY_H
#define PROVIDERCONNECTIONFACTORY_H

#include "providerconnection.h"
#include "config.h"

enum ProviderType {
    CQG = 100
};

class ProviderConnectionFactory {
public:
    ProviderConnectionFactory();
    std::unique_ptr<ProviderConnection> get_provider_connection(ProviderType provider_type);
};

#endif // PROVIDERCONNECTIONFACTORY_H
