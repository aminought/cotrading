#include "providerconnectionfactory.h"
#include "trading/provider/cqg/cqgconnection.h"


namespace ct {
namespace trading {
namespace provider {


ProviderConnectionFactory::ProviderConnectionFactory() {

}

std::unique_ptr<ProviderConnection> ProviderConnectionFactory::get_provider_connection(ProviderType provider_type) {
    switch(provider_type) {
    case ProviderType::CQG:
        return std::make_unique<cqg::CqgConnection>();
    default:
        return std::make_unique<cqg::CqgConnection>();
    }
}

}
}
}
