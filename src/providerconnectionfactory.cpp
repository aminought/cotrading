#include "providerconnectionfactory.h"
#include "cqgconnection.h"
#include "cqgprovider.h"
#include "config.h"

ProviderConnectionFactory::ProviderConnectionFactory() {

}

std::unique_ptr<ProviderConnection> ProviderConnectionFactory::get_provider_connection(ProviderType provider_type) {
    switch(provider_type) {
    case ProviderType::CQG:
        return std::make_unique<CqgConnection>(std::make_shared<CqgProvider>(nullptr));
    default:
        return std::make_unique<CqgConnection>(std::make_shared<CqgProvider>(nullptr));
    }
}
