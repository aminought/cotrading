#include "cqgclient.h"

std::string uri = "wss://demoapi.cqg.com:443";

void CqgClient::connect() {
    this->client = std::make_unique<WebSocketClient>();
    this->client->connect(uri);
}

enum Opcode {
    TEXT = 129,
    BINARY = 130
};

std::string CqgClient::send(std::string message) {
    return this->client->send(message);
}

std::string CqgClient::get_user_name() const {
    return user_name;
}

std::string CqgClient::get_password() const {
    return password;
}

std::string CqgClient::get_client_id() const {
    return client_id;
}

int CqgClient::get_account_id() const {
    return account_id;
}

void CqgClient::create_session(std::string token, bpt::ptime base_time) {
    session = std::make_shared<CqgSession>(token, base_time);
}

// use std::weak_ptr because session could be terminated
std::weak_ptr<CqgSession> CqgClient::get_session() const {
    return std::weak_ptr<CqgSession>(session);
}
