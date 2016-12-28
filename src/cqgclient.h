#ifndef CQGCLIENT_H
#define CQGCLIENT_H

#include <string>
#include <thread>
#include "../libs/Simple-WebSocket-Server/client_wss.hpp"

using WSSClient = SimpleWeb::SocketClient<SimpleWeb::WSS>;

class CqgClient {
public:
    CqgClient() = default;
    CqgClient(std::string user_name, std::string password, std::string client_id, int account_id):
        user_name(std::move(user_name)),
        password(std::move(password)),
        client_id(std::move(client_id)),
        account_id(account_id) {}
    virtual ~CqgClient() = default;
    virtual void connect();
    virtual std::string send_and_receive(std::string);
    virtual std::string get_user_name() const;
    virtual std::string get_password() const;
    virtual std::string get_client_id() const;
    virtual int get_account_id() const;

private:
    std::string user_name;
    std::string password;
    std::string client_id;
    int account_id;
    std::unique_ptr<WSSClient> client;
    static std::string host_name;
};

#endif // CQGCLIENT_H
