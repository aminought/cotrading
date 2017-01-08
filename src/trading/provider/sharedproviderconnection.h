#ifndef SHAREDPROVIDERCONNECTION_H
#define SHAREDPROVIDERCONNECTION_H

#include "trading/provider/providerconnection.h"


namespace ct {
namespace trading {
namespace provider {

class SharedProviderConnection: public ProviderConnection {
public:
    SharedProviderConnection() = default;
    SharedProviderConnection(std::unique_ptr<ProviderConnection> provider_connection):
        provider_connection(std::move(provider_connection)) {}
    std::shared_ptr<QuotesProvider> connect(const core::Config& config);
    std::shared_ptr<QuotesProvider> get_provider();
    void change_connection(std::unique_ptr<ProviderConnection> provider_connection);
private:
    std::unique_ptr<ProviderConnection> provider_connection;
};

}
}
}

#endif // SHAREDPROVIDERCONNECTION_H
