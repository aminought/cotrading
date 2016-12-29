#ifndef PROVIDERCONNECTION_H
#define PROVIDERCONNECTION_H

#include <memory>
#include "quotesprovider.h"
#include "config.h"

class ProviderConnection {
public:
    ProviderConnection(std::shared_ptr<QuotesProvider> provider): provider(provider) {}
    virtual ~ProviderConnection() = default;
    virtual void connect(std::shared_ptr<Config> config) = 0;
protected:
    std::shared_ptr<QuotesProvider> provider;
};

#endif // PROVIDERCONNECTION_H
