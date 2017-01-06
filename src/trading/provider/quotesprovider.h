#ifndef QUOTESPROVIDER_H
#define QUOTESPROVIDER_H

#include <memory>
#include <vector>

#include "trading/model/contract.h"
#include "trading/model/timebar.h"

namespace ct {
namespace trading {
namespace provider {

class QuotesProvider {
public:
    virtual ~QuotesProvider();
    virtual void logon() = 0;
    virtual void logout() = 0;
    virtual std::unique_ptr<trading::model::Contract> resolve_symbol(trading::model::Symbol symbol) = 0;
    virtual std::vector<trading::model::TimeBar> get_historical_data(
        const trading::model::Contract& contract, const bpt::time_duration& duration) = 0;
};

}
}
}

#endif // QUOTESPROVIDER_H
