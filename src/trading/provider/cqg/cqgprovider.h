#ifndef CQGPROVIDER_H
#define CQGPROVIDER_H

#include <string>
#include "cqgclient.h"
#include "trading/model/timebar.h"
#include "trading/provider/quotesprovider.h"


namespace ct {
namespace trading {
namespace provider {
namespace cqg {

class CqgProvider: public provider::QuotesProvider {
public:
    CqgProvider(std::shared_ptr<CqgClient> client): client(client) {}
    ~CqgProvider();
    void logon() override;
    void logout() override;
    std::unique_ptr<trading::model::Contract> resolve_symbol(trading::model::Symbol symbol) override;
    std::vector<trading::model::TimeBar> get_historical_data(const trading::model::Contract& contract,
            bpt::time_duration duration) override;
private:
    std::shared_ptr<CqgClient> client;
    bool connected = false;
};

}
}
}
}

#endif // CQGPROVIDER_H
