#ifndef CQGCONNECTION_H
#define CQGCONNECTION_H

#include "cqgprovider.h"
#include "trading/provider/providerconnection.h"

namespace ct {
namespace trading {
namespace provider {
namespace cqg {

class CqgConnection: public provider::ProviderConnection {
public:
    CqgConnection() = default;
    std::shared_ptr<provider::QuotesProvider> connect(const core::Config& config) override;
    std::shared_ptr<provider::QuotesProvider> get_provider() override;
private:
    std::shared_ptr<provider::QuotesProvider> provider;
};

}
}
}
}

#endif // CQGCONNECTION_H
