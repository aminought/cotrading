#include "cqgclient.h"

std::string CqgClient::host_name = "demoapi.cqg.com:443";

void CqgClient::connect() {
    this->client = std::make_unique<WSSClient>(CqgClient::host_name);
}

enum Opcode {
    TEXT = 129,
    BINARY = 130
};

std::string CqgClient::send_and_receive(std::string message) {
    std::string m_str;
    this->client->onmessage = [&m_str, this] (auto message) {
        m_str.append(message->string());
        this->client->stop();
    };

    this->client->onopen = [this, &message] () {
        auto send_stream = std::make_shared<WSSClient::SendStream>();
        *send_stream << message;
        this->client->send(send_stream, nullptr, Opcode::BINARY);
    };

    this->client->start();

    return m_str;
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
