#include "contract.h"

namespace ct {
namespace trading {
namespace model {

int Contract::get_id() const {
    return id;
}

std::string Contract::get_symbol() const {
    return symbol;
}

}
}
}
