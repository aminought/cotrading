#ifndef CONTRACT_H
#define CONTRACT_H

#include <string>

namespace ct {
namespace trading {
namespace model {

enum class Symbol {
    CL
};

class Contract {
public:
    Contract(int id, std::string symbol): id(id), symbol(symbol) {}
    int get_id() const;
    std::string get_symbol() const;

private:
    int id;
    std::string symbol;
};

}
}
}

#endif // CONTRACT_H
