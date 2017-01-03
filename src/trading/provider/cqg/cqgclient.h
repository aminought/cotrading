#ifndef CQGCLIENT_H
#define CQGCLIENT_H

#include <string>
#include <thread>
#include <boost/date_time/posix_time/ptime.hpp>
#include "cqgsession.h"
#include "trading/network/websocketclient.h"


namespace bpt = boost::posix_time;

namespace ct {
namespace trading {
namespace provider {
namespace cqg {

class CqgClient {
public:
    CqgClient() = default;
    CqgClient(std::string user_name, std::string password, std::string client_id, int account_id):
        user_name(user_name),
        password(password),
        client_id(client_id),
        account_id(account_id) {}
    virtual ~CqgClient();
    virtual void connect();
    virtual void disconnect();
    virtual std::string send(const std::string&& message);
    virtual std::string get_next_answer(std::chrono::system_clock::duration timeout);
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

    std::unique_ptr<network::WebSocketClient> client;
    bool connected = false;
};

}
}
}
}

#endif // CQGCLIENT_H
