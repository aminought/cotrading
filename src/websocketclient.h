#ifndef WEBSOCKETCLIENT_H
#define WEBSOCKETCLIENT_H

#include <fstream>
#include <websocketpp/client.hpp>
#include <websocketpp/config/asio_client.hpp>
#include <boost/lockfree/spsc_queue.hpp>

namespace wspp = websocketpp;
namespace blf = boost::lockfree;
using Client = wspp::client<wspp::config::asio_tls_client>;
using namespace std::chrono_literals;

class WebSocketClient {
public:
    WebSocketClient();
    ~WebSocketClient();
    void connect(std::string uri);
    std::string send(std::string message);
    std::string get_next_answer(std::chrono::system_clock::duration timeout);
private:
    Client client;
    std::condition_variable cond;
    std::mutex m;
    blf::spsc_queue<std::string, blf::capacity<10000>> answer_queue;
    std::thread client_thread;
    std::ofstream log;
    wspp::connection_hdl handler;
};

#endif // WEBSOCKETCLIENT_H
