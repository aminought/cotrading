#ifndef CQGPROVIDER_H
#define CQGPROVIDER_H

#include "cqgclient.h"
#include "quotesprovider.h"
#include "timebar.h"
#include <string>

class CqgProvider: public QuotesProvider {
public:
    CqgProvider(std::shared_ptr<CqgClient> client): client(client) {}
    void logon() override;
    std::unique_ptr<Contract> resolve_symbol(Symbol symbol) override;
    std::vector<TimeBar> get_historical_data(std::shared_ptr<Contract> contract, bpt::time_duration duration);
private:
    std::shared_ptr<CqgClient> client;
};

#endif // CQGPROVIDER_H
