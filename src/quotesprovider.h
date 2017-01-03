#ifndef QUOTESPROVIDER_H
#define QUOTESPROVIDER_H

#include <memory>
#include <vector>
#include "contract.h"
#include "timebar.h"

class QuotesProvider {
public:
    virtual ~QuotesProvider();
    virtual void logon() = 0;
    virtual void logout() = 0;
    virtual std::unique_ptr<Contract> resolve_symbol(Symbol symbol) = 0;
    virtual std::vector<TimeBar> get_historical_data(const Contract& contract, bpt::time_duration duration) = 0;
};

#endif // QUOTESPROVIDER_H
