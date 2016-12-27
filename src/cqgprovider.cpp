#include "cqgprovider.h"
#include "../libs/cqg_webapi/webapi_1.pb.h"

#include <iostream>

std::tuple<std::string, std::chrono::system_clock::time_point> CqgProvider::logon() {
    auto client_msg = WebAPI_1::ClientMsg();
    auto logon = client_msg.mutable_logon();
    logon->set_user_name(client->get_user_name());
    logon->set_password(client->get_password());
    logon->set_client_id(client->get_client_id());
    logon->set_client_version(client->get_client_id());

    this->client->connect();
    auto answer = this->client->send_and_receive(client_msg.SerializeAsString());
    std::cout << answer << std::endl;

    return std::tuple<std::string, std::chrono::system_clock::time_point>();
}
