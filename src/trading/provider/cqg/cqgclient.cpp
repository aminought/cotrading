#include "cqgclient.h"


namespace ct {
namespace trading {
namespace provider {
namespace cqg {

std::string uri = "wss://demoapi.cqg.com:443";

CqgClient::~CqgClient() {
    if(connected) {
        this->disconnect();
    }
}

void CqgClient::connect() {
    this->client = std::make_unique<network::WebSocketClient>();
    this->client->connect(uri);
    this->connected = true;
}

void CqgClient::disconnect() {
    this->client->disconnect();
    this->connected = false;
}

enum Opcode {
    TEXT = 129,
    BINARY = 130
};

std::string CqgClient::send(const std::string&& message) {
    return this->client->send(message);
}

std::string CqgClient::get_next_answer(const std::chrono::system_clock::duration& timeout) {
    return this->client->get_next_answer(timeout);
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

void CqgClient::create_session(const std::string& token, const bpt::ptime& base_time) {
    session = std::make_shared<CqgSession>(token, base_time);
}

// use std::weak_ptr because session could be terminated
std::weak_ptr<CqgSession> CqgClient::get_session() const {
    return std::weak_ptr<CqgSession>(session);
}

}
}
}
}
