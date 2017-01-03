#ifndef CQGSESSION_H
#define CQGSESSION_H

#include <boost/date_time/posix_time/ptime.hpp>
#include "trading/provider/providersession.h"

namespace bpt = boost::posix_time;

namespace ct {
namespace trading {
namespace provider {
namespace cqg {

class CqgSession: public provider::ProviderSession {
public:
    CqgSession(std::string token, bpt::ptime base_time): provider::ProviderSession(token), base_time(base_time) {}
    bpt::ptime get_base_time() const;
private:
    bpt::ptime base_time;
};

}
}
}
}

#endif // CQGSESSION_H
