#ifndef CQGPROVIDER_H
#define CQGPROVIDER_H

#include "cqgclient.h"
#include "quotesprovider.h"
#include <string>

class CqgProvider: public QuotesProvider {
public:
    CqgProvider(std::shared_ptr<CqgClient> client): client(client) {}
    void logon() override;
private:
    std::shared_ptr<CqgClient> client;
};

#endif // CQGPROVIDER_H
