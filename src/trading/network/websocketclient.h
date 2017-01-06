#ifndef WEBSOCKETCLIENT_H
#define WEBSOCKETCLIENT_H

#include <fstream>
#include <websocketpp/client.hpp>
#include <websocketpp/config/asio_client.hpp>
#include <boost/lockfree/spsc_queue.hpp>

namespace wspp = websocketpp;
namespace blf = boost::lockfree;
using AsioTlsClient = wspp::client<wspp::config::asio_tls_client>;
using namespace std::chrono_literals;

namespace ct {
namespace trading {
namespace network {

class WebSocketClient {
public:
    WebSocketClient();
    ~WebSocketClient();
    void connect(const std::string& uri);
    void disconnect();
    std::string send(const std::string& message);
    std::string get_next_answer(const std::chrono::system_clock::duration& timeout);
private:
    AsioTlsClient client;
    blf::spsc_queue<std::string, blf::capacity<10000>> answer_queue;

    std::thread client_thread;
    std::mutex m;
    std::condition_variable cond;

    wspp::connection_hdl handler;
    bool connected = false;
};

}
}
}

#endif // WEBSOCKETCLIENT_H
