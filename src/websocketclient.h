#ifndef WEBSOCKETCLIENT_H
#define WEBSOCKETCLIENT_H

#include <websocketpp/client.hpp>
#include <websocketpp/config/asio_client.hpp>
#include <fstream>

namespace wspp = websocketpp;
using Client = wspp::client<wspp::config::asio_tls_client>;

class WebSocketClient {
public:
    WebSocketClient();
    ~WebSocketClient();
    void connect(std::string uri);
    std::string send(std::string message);
private:
    Client client;
    std::condition_variable cond;
    std::mutex m;
    std::string answer;
    std::thread client_thread;
    std::ofstream log;
    wspp::connection_hdl handler;
};

#endif // WEBSOCKETCLIENT_H
