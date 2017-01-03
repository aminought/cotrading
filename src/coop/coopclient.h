#ifndef COOPCLIENT_H
#define COOPCLIENT_H

#include <QObject>
#include <websocketpp/client.hpp>
#include <websocketpp/config/asio_client.hpp>
#include <boost/lockfree/spsc_queue.hpp>
#include "coopconnection.h"

namespace wspp = websocketpp;
namespace blf = boost::lockfree;
using AsioClient = wspp::client<wspp::config::asio_client>;
using namespace std::chrono_literals;

namespace ct {
namespace coop {

class CoopConnection;
class CoopClient {
public:
    CoopClient();
    ~CoopClient();
    void connect();
    void disconnect();
    void set_coop_connection(std::shared_ptr<CoopConnection> coop_connection);
private:
    AsioClient client;
    bool connected = false;
    std::condition_variable notify_cond;
    std::mutex notify_mutex;
    std::thread client_thread;

    wspp::connection_hdl handle;

    std::shared_ptr<CoopConnection> coop_connection;
};

}
}

#endif // COOPCLIENT_H
