#ifndef QUOTESPROVIDER_H
#define QUOTESPROVIDER_H

#include "contract.h"
#include <memory>

class QuotesProvider {
public:
    virtual ~QuotesProvider();
    virtual void logon() = 0;
    virtual std::unique_ptr<Contract> resolve_symbol(Symbol symbol) = 0;
};

#endif // QUOTESPROVIDER_H
