#include "contract.h"

#include <map>

namespace ct {
namespace trading {
namespace model {

int Contract::get_id() const {
    return id;
}

std::string Contract::get_symbol() const {
    return symbol;
}

std::string Contract::get_name_of_symbol(Symbol s) {
    static std::map<Symbol, std::string> symbol_to_name;
    symbol_to_name[Symbol::CL] = "CL";
    symbol_to_name[Symbol::GC] = "GC";
    return symbol_to_name[s];
}

}
}
}
