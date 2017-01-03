#ifndef CQGCONNECTION_H
#define CQGCONNECTION_H

#include "cqgprovider.h"
#include "providerconnection.cpp"

class CqgConnection: public ProviderConnection {
public:
    CqgConnection() = default;
    std::unique_ptr<QuotesProvider> connect(const Config& config) override;
};

#endif // CQGCONNECTION_H
