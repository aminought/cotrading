#ifndef CQGPROVIDER_H
#define CQGPROVIDER_H

#include "cqgclient.h"
#include "quotesprovider.h"
#include "timebar.h"
#include <string>

class CqgProvider: public QuotesProvider {
public:
    CqgProvider(std::shared_ptr<CqgClient> client): client(client) {}
    ~CqgProvider();
    void logon() override;
    void logout() override;
    std::unique_ptr<Contract> resolve_symbol(Symbol symbol) override;
    std::vector<TimeBar> get_historical_data(const Contract& contract, bpt::time_duration duration) override;
private:
    std::shared_ptr<CqgClient> client;
    bool connected = false;
};

#endif // CQGPROVIDER_H
