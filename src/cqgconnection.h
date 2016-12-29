#ifndef CQGCONNECTION_H
#define CQGCONNECTION_H

#include "cqgprovider.h"
#include "providerconnection.cpp"

class CqgConnection: public ProviderConnection {
public:
    CqgConnection(std::shared_ptr<CqgProvider> provider): ProviderConnection(provider) {}
    void connect(std::shared_ptr<Config> config) override;
};

#endif // CQGCONNECTION_H
