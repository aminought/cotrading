#include "sharedproviderconnection.h"


namespace ct {
namespace trading {
namespace provider {

std::shared_ptr<QuotesProvider> SharedProviderConnection::connect(const ct::core::Config &config) {
    return this->provider_connection->connect(config);
}

std::shared_ptr<QuotesProvider> SharedProviderConnection::get_provider() {
    return this->provider_connection->get_provider();
}

void SharedProviderConnection::change_connection(std::unique_ptr<ProviderConnection> provider_connection) {
    this->provider_connection = std::move(provider_connection);
}

}
}
}
