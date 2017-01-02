#include "coopconnection.h"


CoopConnection::~CoopConnection() {
    if(this->server_started) {
        this->server->stop();
        this->server_started = false;
    }
    if(this->client_connected) {
        this->client->disconnect();
        this->client_connected = false;
    }
}

void CoopConnection::start_coop_server() {
    this->server->start();
    this->server_started = true;
}

void CoopConnection::connect_to_coop_server() {
    this->client->connect();
    this->client_connected = true;
}

void CoopConnection::send_coop_data(const CoopMessage &message) {
    this->server->add_server_message(message);
}
