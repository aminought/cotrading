#include "coopconnection.h"

namespace ct {
namespace coop {

CoopConnection::CoopConnection(std::unique_ptr<CoopServer> server,
                               std::unique_ptr<CoopClient> client,
                               std::shared_ptr<core::ChartController> chart_controller):
    server(std::move(server)), client(std::move(client)), chart_controller(chart_controller) { }

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

void CoopConnection::handle_client_message(const std::string& message) {
    this->chart_controller->update_chart_based_on_message(message);
}

void CoopConnection::init_client() {
    this->client->set_coop_connection(shared_from_this());
}

}
}
