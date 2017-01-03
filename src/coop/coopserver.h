#ifndef COOPSERVER_H
#define COOPSERVER_H

#include <thread>
#include <fstream>
#include <websocketpp/server.hpp>
#include <websocketpp/config/asio.hpp>
#include <boost/lockfree/spsc_queue.hpp>
#include "coopmessage.h"

namespace wspp = websocketpp;
namespace blf = boost::lockfree;
using Server = wspp::server<wspp::config::asio>;
using namespace std::chrono_literals;

namespace ct {
namespace coop {

class CoopServer {
public:
    CoopServer();
    ~CoopServer();
    void start();
    void stop();
    void add_server_message(const CoopMessage& message);
private:
    Server server;
    std::vector<wspp::connection_hdl> handles;
    blf::spsc_queue<std::string, blf::capacity<10>> server_message_queue;

    std::thread server_thread;
    std::condition_variable notify_cond;
    std::mutex notify_mutex;
    std::thread message_sender_thread;

    std::atomic_bool need_to_send;
    bool started = false;
};

}
}

#endif // COOPSERVER_H
