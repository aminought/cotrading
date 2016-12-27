#ifndef CQGPROVIDER_H
#define CQGPROVIDER_H

#include "cqgclient.h"
#include "quotesprovider.h"
#include <string>
#include <chrono>

class CqgProvider: public QuotesProvider {
public:
    CqgProvider(std::unique_ptr<CqgClient> client): client(std::move(client)) {}
    std::tuple<std::string, std::chrono::system_clock::time_point> logon();
private:
    std::unique_ptr<CqgClient> client;
};

#endif // CQGPROVIDER_H
