#ifndef QUOTESPROVIDER_H
#define QUOTESPROVIDER_H


class QuotesProvider {
public:
    virtual ~QuotesProvider();
    virtual void logon() = 0;
};

#endif // QUOTESPROVIDER_H
