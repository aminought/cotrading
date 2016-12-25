#include "cqgclient.h"

std::string CqgClient::host_name = "demoapi.cqg.com:443";

void CqgClient::connect() {
    this->client = std::make_unique<WSSClient>(CqgClient::host_name);
    this->clientThread = std::make_unique<std::thread>([this] () {
        client->start();
    });
}

enum Opcode {
    TEXT = 129,
    BINARY = 130
};

std::string CqgClient::send_and_receive(std::string message) {
    std::string m_str;
    this->client->onmessage = [&m_str] (auto message) {
        m_str = std::move(message->string());
    };

    auto send_stream = std::make_shared<WSSClient::SendStream>();
    *send_stream << message;
    this->client->send(send_stream, nullptr, Opcode::BINARY);

    return m_str;
}
