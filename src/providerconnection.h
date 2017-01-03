#ifndef PROVIDERCONNECTION_H
#define PROVIDERCONNECTION_H

#include <memory>
#include "quotesprovider.h"
#include "config.h"

class ProviderConnection {
public:
    virtual ~ProviderConnection() = default;
    virtual std::unique_ptr<QuotesProvider> connect(const Config& config) = 0;
};

#endif // PROVIDERCONNECTION_H
