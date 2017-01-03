#include "coopclient.h"
#include "iostream"

#include <QDebug>
#include <QMetaObject>
#include <QList>

CoopClient::CoopClient() {
    this->client.set_open_handler([this] (auto) {
        this->notify_cond.notify_one();
    });

    this->client.set_message_handler([this] (auto, Client::message_ptr msg) {
        auto message = msg->get_payload();
        std::cout << message << std::endl;
        this->coop_connection->handle_client_message(message);
    });
}

CoopClient::~CoopClient() {
    if(connected) {
        this->disconnect();
    }
}

void CoopClient::connect() {
    wspp::lib::error_code ec;
    this->client.init_asio();
    auto conn = this->client.get_connection("ws://127.0.0.1:9009", ec);
    if(ec) {
        qDebug() << ec.message().data();
        return;
    }
    this->client.connect(conn);
    this->handle = conn->get_handle();

    this->client_thread = std::thread([this] () {
        this->client.run();
    });

    std::unique_lock<std::mutex> lock(this->notify_mutex);
    this->notify_cond.wait(lock);
    connected = true;
}

void CoopClient::disconnect() {
    this->client.stop();
    this->client_thread.join();
    connected = false;
}

void CoopClient::set_coop_connection(std::shared_ptr<CoopConnection> coop_connection) {
    this->coop_connection = coop_connection;
}
