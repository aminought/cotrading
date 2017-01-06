#ifndef PROVIDERSESSION_H
#define PROVIDERSESSION_H

#include <string>

namespace ct {
namespace trading {
namespace provider {

class ProviderSession {
public:
    explicit ProviderSession(std::string&& token): token(std::move(token)) {}
    std::string get_token() const;
protected:
    std::string token;
};

}
}
}

#endif // PROVIDERSESSION_H
