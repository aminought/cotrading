#ifndef CONTRACT_H
#define CONTRACT_H

#include <string>

namespace ct {
namespace trading {
namespace model {

enum Symbol {
    CL = 1,
    GC = 0
};

class Contract {
public:
    Contract(int id, std::string symbol): id(id), symbol(symbol) {}
    int get_id() const;
    std::string get_symbol() const;
    static std::string get_name_of_symbol(Symbol s);

private:
    int id;
    std::string symbol;
};

}
}
}

#endif // CONTRACT_H
