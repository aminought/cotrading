#include "coopserver.h"
#include <QDebug>
#include <json.hpp>


namespace ct {
namespace coop {

CoopServer::CoopServer() {
    this->server.set_message_handler([] (auto, auto) { });

    this->server.set_socket_init_handler([this] (auto, auto&) {
        qDebug() << "Socket init handler";
    });

    this->server.set_open_handler([this] (auto hdl) {
        qDebug() << "Connection opened";
        this->handles.emplace_back(hdl);
    });

    this->server.set_fail_handler([] (auto) {
        qDebug() << "Fail";
    });
}

CoopServer::~CoopServer() {
    if(started) {
        this->stop();
    }
}

void CoopServer::start() {
    qDebug() << "Coop server thread starting";
    this->server_thread = std::thread([this] () {
        this->server.init_asio();
        this->server.listen(9009);
        this->server.start_accept();
        this->server.run();
        qDebug() << "Coop server thread was stopped";
    });

    qDebug() << "Coop server thread was started";
    qDebug() << "Coop server message thread starting";

    this->message_sender_thread = std::thread([this] () {
        need_to_send = true;
        while(this->need_to_send) {
            if(!this->server_message_queue.empty()) {
                this->server_message_queue.consume_one([this] (auto message) {
                    for(auto handle: this->handles) {
                        this->server.send(handle, message, wspp::frame::opcode::TEXT);
                    }
                });
            } else {
                std::this_thread::sleep_for(100ms);
            }
        }
    });
    qDebug() << "Coop server message thread was started";
    started = true;
}

void CoopServer::stop() {
    this->need_to_send = false;
    this->message_sender_thread.join();
    this->server.stop_listening();
    this->server.stop();
    this->server_thread.join();
    started = false;
}

void CoopServer::add_server_message(const CoopMessage& message) {
    this->server_message_queue.push(message.to_json().dump());

}

}
}
