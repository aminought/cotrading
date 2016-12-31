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
        std::string answer = msg->get_payload();
        this->answer_queue.push(answer);
        cond.notify_one();
    });
    this->client.set_open_handler([this] (auto) {
        this->cond.notify_one();
    });
}

WebSocketClient::~WebSocketClient() {
    this->disconnect();
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
    std::unique_lock<std::mutex> lock(this->m);
    this->cond.wait(lock);
}

void WebSocketClient::disconnect() {
    this->client.stop();
    this->client_thread.join();
    this->log.close();
}

std::string WebSocketClient::send(std::string message) {
    this->client.send(this->handler, message, wspp::frame::opcode::BINARY);
    std::unique_lock<std::mutex> lock(this->m);
    this->cond.wait(lock);
    std::string answer;
    this->answer_queue.pop(&answer);
    return answer;
}

std::string WebSocketClient::get_next_answer(std::chrono::system_clock::duration timeout) {
    auto start = std::chrono::system_clock::now();
    while(!this->answer_queue.read_available()) {
        if(std::chrono::system_clock::now() - start > timeout) {
            return "";
        }
        std::this_thread::sleep_for(10ms);
    }
    std::string answer;
    this->answer_queue.pop(&answer, 1);
    return answer;
}
