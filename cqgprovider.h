#ifndef CQGPROVIDER_H
#define CQGPROVIDER_H

#include "cqgclient.h"
#include "quotesprovider.h"
#include <string>
#include <chrono>

class CqgProvider: public QuotesProvider {
public:
    CqgProvider();
    std::tuple<std::string, std::chrono::system_clock::time_point> logon();
private:
    std::string host_name;
    CqgClient client;
};

#endif // CQGPROVIDER_H
