#include "cqgprovider.h"
#include <iostream>
#include <string>
#include <boost/date_time/posix_time/ptime.hpp>
#include <boost/date_time/time_parsing.hpp>
#include <webapi_1.pb.h>

namespace bpt = boost::posix_time;
namespace bdt = boost::date_time;
namespace WA = WebAPI_1;

void CqgProvider::logon() {
    auto client_msg = WA::ClientMsg();
    auto logon = client_msg.mutable_logon();

    logon->set_user_name(client->get_user_name());
    logon->set_password(client->get_password());
    logon->set_client_id(client->get_client_id());
    logon->set_client_version("python-client");

    this->client->connect();
    auto answer = this->client->send(std::move(client_msg.SerializeAsString()));

    auto server_msg = WA::ServerMsg();
    server_msg.ParseFromString(answer);

    auto logon_result = server_msg.logon_result();
    if(logon_result.result_code() == 0) {
        auto base_time_str = logon_result.base_time();
        auto base_time = bdt::parse_delimited_time<bpt::ptime>(base_time_str, 'T');
        std::string token = logon_result.session_token();

        this->client->create_session(token, base_time);
    }
}

std::unique_ptr<Contract> CqgProvider::resolve_symbol(Symbol symbol) {
    auto client_msg = WA::ClientMsg();
    auto info_req = client_msg.add_information_request();
    info_req->set_id(0);
    auto res_req = info_req->mutable_symbol_resolution_request();
    res_req->set_symbol("CL");
    auto answer = this->client->send(std::move(client_msg.SerializeAsString()));

    auto server_msg = WA::ServerMsg();
    server_msg.ParseFromString(answer);

    auto contract_metadata = server_msg.information_report().Get(0).symbol_resolution_report().contract_metadata();
    auto id = contract_metadata.contract_id();
    auto symbol_str = contract_metadata.contract_symbol();
    return std::make_unique<Contract>(id, std::move(symbol_str));
}
