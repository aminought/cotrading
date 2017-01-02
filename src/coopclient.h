#ifndef COOPCLIENT_H
#define COOPCLIENT_H

#include <QObject>
#include <websocketpp/client.hpp>
#include <websocketpp/config/asio_client.hpp>
#include <boost/lockfree/spsc_queue.hpp>

namespace wspp = websocketpp;
namespace blf = boost::lockfree;
using Client = wspp::client<wspp::config::asio_client>;
using namespace std::chrono_literals;

class CoopClient {
public:
    CoopClient(QObject* chart);
    ~CoopClient();
    void connect();
    void disconnect();
private:
    Client client;
    std::condition_variable notify_cond;
    std::mutex notify_mutex;
//    blf::spsc_queue<std::string, blf::capacity<10>> answer_queue;
    std::thread client_thread;
    wspp::connection_hdl handle;
    QObject* chart;
    bool connected = false;

};

#endif // COOPCLIENT_H
