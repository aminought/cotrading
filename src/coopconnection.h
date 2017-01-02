#ifndef COOPCONNECTION_H
#define COOPCONNECTION_H

#include <memory>
#include "coopserver.h"
#include "coopclient.h"
#include "coopmessage.h"

class CoopConnection {
public:
    CoopConnection(std::unique_ptr<CoopServer> server, std::unique_ptr<CoopClient> client):
        server(std::move(server)), client(std::move(client)) {}
    ~CoopConnection();
    void start_coop_server();
    void connect_to_coop_server();
    void send_coop_data(const CoopMessage& message);
private:
    std::unique_ptr<CoopServer> server;
    std::unique_ptr<CoopClient> client;
    bool server_started = false;
    bool client_connected = false;
};

#endif // COOPCONNECTION_H
