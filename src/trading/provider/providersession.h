#ifndef PROVIDERSESSION_H
#define PROVIDERSESSION_H

#include <string>

namespace ct {
namespace trading {
namespace provider {

class ProviderSession {
public:
    ProviderSession(std::string token): token(token) {}
    std::string get_token() const;
protected:
    std::string token;
};

}
}
}

#endif // PROVIDERSESSION_H
