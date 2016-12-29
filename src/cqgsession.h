#ifndef CQGSESSION_H
#define CQGSESSION_H

#include <providersession.h>
#include <boost/date_time/posix_time/ptime.hpp>

namespace bpt = boost::posix_time;

class CqgSession: public ProviderSession {
public:
    CqgSession(std::string token, bpt::ptime base_time): ProviderSession(token), base_time(base_time) {}
    bpt::ptime get_base_time() const;
private:
    bpt::ptime base_time;
};

#endif // CQGSESSION_H
