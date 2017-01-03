#ifndef COOPCONNECTION_H
#define COOPCONNECTION_H

#include <memory>
#include <core/chartcontroller.h>
#include "coopserver.h"
#include "coopclient.h"
#include "coopmessage.h"

namespace ct {
namespace coop {

class CoopClient;
class CoopConnection: public std::enable_shared_from_this<CoopConnection> {
public:
    CoopConnection(std::unique_ptr<CoopServer> server,
                   std::unique_ptr<coop::CoopClient> client,
                   std::shared_ptr<core::ChartController> chart_controller);
    ~CoopConnection();
    void start_coop_server();
    void connect_to_coop_server();
    void send_coop_data(const CoopMessage& message);
    void handle_client_message(const std::string& message);
    void init_client();
private:
    std::unique_ptr<CoopServer> server;
    std::unique_ptr<CoopClient> client;
    std::shared_ptr<core::ChartController> chart_controller;
    bool server_started = false;
    bool client_connected = false;
};

}
}

#endif // COOPCONNECTION_H
