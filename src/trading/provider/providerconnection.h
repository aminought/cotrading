#ifndef PROVIDERCONNECTION_H
#define PROVIDERCONNECTION_H

#include <memory>
#include "core/config.h"
#include "quotesprovider.h"


namespace ct {
namespace trading {
namespace provider {

class ProviderConnection {
public:
    virtual ~ProviderConnection() = default;
    virtual std::shared_ptr<QuotesProvider> connect(const core::Config& config) = 0;
    virtual std::shared_ptr<QuotesProvider> get_provider() = 0;
};

}
}
}

#endif // PROVIDERCONNECTION_H
