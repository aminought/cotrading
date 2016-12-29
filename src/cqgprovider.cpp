#include "cqgprovider.h"
#include "../libs/cqg_webapi/webapi_1.pb.h"
#include <iostream>
#include <string>
#include <boost/date_time/posix_time/ptime.hpp>
#include <boost/date_time/time_parsing.hpp>

namespace bpt = boost::posix_time;
namespace bdt = boost::date_time;

void CqgProvider::logon() {
    auto client_msg = WebAPI_1::ClientMsg();
    auto logon = client_msg.mutable_logon();

    logon->set_user_name(client->get_user_name());
    logon->set_password(client->get_password());
    logon->set_client_id(client->get_client_id());
    logon->set_client_version(client->get_client_id());

    this->client->connect();
    auto answer = this->client->send_and_receive(client_msg.SerializeAsString());

    auto server_msg = WebAPI_1::ServerMsg();
    server_msg.ParseFromString(answer);

    auto logon_result = server_msg.logon_result();
    if(logon_result.result_code() == 0) {
        auto base_time_str = logon_result.base_time();
        auto base_time = bdt::parse_delimited_time<bpt::ptime>(base_time_str, 'T');
        std::string token = logon_result.session_token();

        this->client->create_session(token, base_time);
    }
}
