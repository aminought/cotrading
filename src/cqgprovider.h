#ifndef CQGPROVIDER_H
#define CQGPROVIDER_H

#include "cqgclient.h"
#include "quotesprovider.h"
#include <string>
#include <boost/date_time/posix_time/posix_time.hpp>

class CqgProvider: public QuotesProvider {
public:
    CqgProvider(std::unique_ptr<CqgClient> client): client(std::move(client)) {}
    std::tuple<std::string, boost::posix_time::ptime> logon();
private:
    std::unique_ptr<CqgClient> client;
};

#endif // CQGPROVIDER_H
