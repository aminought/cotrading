#ifndef CQGCLIENT_H
#define CQGCLIENT_H

#include <string>
#include <thread>
#include "cqgsession.h"
#include "websocketclient.h"
#include <boost/date_time/posix_time/ptime.hpp>


namespace bpt = boost::posix_time;

class CqgClient {
public:
    CqgClient() = default;
    CqgClient(std::string user_name, std::string password, std::string client_id, int account_id):
        user_name(user_name),
        password(password),
        client_id(client_id),
        account_id(account_id) {}
    virtual ~CqgClient() = default;
    virtual void connect();
    virtual std::string send(std::string);
    virtual std::string get_user_name() const;
    virtual std::string get_password() const;
    virtual std::string get_client_id() const;
    virtual int get_account_id() const;
    std::weak_ptr<CqgSession> get_session() const;
    void create_session(std::string token, bpt::ptime base_time);

private:
    std::string user_name;
    std::string password;
    std::string client_id;
    int account_id;
    std::shared_ptr<CqgSession> session;

    std::unique_ptr<WebSocketClient> client;
};

#endif // CQGCLIENT_H
