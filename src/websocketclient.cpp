#include "websocketclient.h"
#include <QDebug>
#include <iostream>
#include <fstream>

WebSocketClient::WebSocketClient() {
    this->log.open("output.log");
    this->client.get_alog().set_ostream(&this->log);
    this->client.get_elog().set_ostream(&this->log);
    this->client.set_access_channels(websocketpp::log::alevel::all);
    this->client.set_access_channels(websocketpp::log::alevel::all);
    this->client.set_error_channels(websocketpp::log::elevel::all);
    this->client.init_asio();
    this->client.set_tls_init_handler([] (auto) {
        return wspp::lib::make_shared<boost::asio::ssl::context>(boost::asio::ssl::context::tlsv1);
    });
    this->client.set_message_handler([this] (auto, Client::message_ptr msg) {
        this->answer = msg->get_payload();
        cond.notify_one();
    });
}

WebSocketClient::~WebSocketClient() {
    this->client.stop();
    this->log.close();
}

void WebSocketClient::connect(std::string uri) {
    wspp::lib::error_code ec;
    auto conn = this->client.get_connection(uri, ec);
    if(ec) {
        qDebug() << "Unable to get connection: " << ec.message().data();
        return;
    }
    this->client.connect(conn);
    this->handler = conn->get_handle();

    this->client_thread = std::thread([&uri, this] () {
        qDebug() << "Websocket client thread started";
        this->client.run();
        qDebug() << "Websocket client thread stopped";
    });
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(5s);
}

std::string WebSocketClient::send(std::string message) {
    this->client.send(this->handler, message, wspp::frame::opcode::BINARY);
    std::unique_lock<std::mutex> lock(this->m);
    this->cond.wait(lock);
    return answer;
}
