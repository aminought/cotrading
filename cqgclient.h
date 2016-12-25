#ifndef CQGCLIENT_H
#define CQGCLIENT_H

#include <string>
#include <thread>
#include "Simple-WebSocket-Server/client_wss.hpp"

using WSSClient = SimpleWeb::SocketClient<SimpleWeb::WSS>;

class CqgClient {
public:
    CqgClient(std::string user_name, std::string password, std::string client_id, int account_id): user_name(std::move(user_name)),
        password(std::move(password)),
        client_id(std::move(client_id)),
        account_id(account_id) {}
    void connect();
    std::string send_and_receive(std::string);
private:
    std::string user_name;
    std::string password;
    std::string client_id;
    int account_id;
    std::unique_ptr<WSSClient> client;
    static std::string host_name;
    std::unique_ptr<std::thread> clientThread;
};

#endif // CQGCLIENT_H
