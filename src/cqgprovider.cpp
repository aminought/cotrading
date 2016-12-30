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
    logon->set_client_version("c++-client");

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

std::vector<TimeBar> CqgProvider::get_historical_data(std::shared_ptr<Contract> contract, bpt::time_duration duration) {
    auto base_time = this->client->get_session().lock()->get_base_time();
    auto client_msg = WA::ClientMsg();
    auto tb_req = client_msg.add_time_bar_request();
    tb_req->set_request_id(0);
    tb_req->set_request_type(WA::TimeBarRequest::GET);
    auto params = tb_req->mutable_time_bar_parameters();
    params->set_contract_id(static_cast<unsigned int>(contract->get_id()));
    params->set_bar_unit(WA::TimeBarParameters::MIN);
    params->set_units_number(1);
    params->set_from_utc_time((bpt::second_clock::universal_time() - base_time - duration).total_milliseconds());

    auto complete = false;
    auto answer = this->client->send(client_msg.SerializeAsString());
    std::vector<TimeBar> time_bars;
    while(!complete) {
        auto server_msg = WA::ServerMsg();
        server_msg.ParseFromString(answer);
        auto report_size = server_msg.time_bar_report_size();
        for(int i=0; i<report_size; ++i) {
            auto tb_report = server_msg.time_bar_report(i);
            auto bar_size = tb_report.time_bar_size();
            for(int j=0; j<bar_size; ++j) {
                auto cqg_time_bar = tb_report.time_bar(j);
                auto time = base_time + bpt::milliseconds(cqg_time_bar.bar_utc_time());
                auto open = cqg_time_bar.open_price();
                auto close = cqg_time_bar.close_price();
                auto high = cqg_time_bar.high_price();
                auto low = cqg_time_bar.low_price();
                auto volume = static_cast<int>(cqg_time_bar.volume());
                auto time_bar = TimeBar(time, open, close, high, low, volume);
                time_bars.emplace_back(std::move(time_bar));
            }
            complete = tb_report.is_report_complete();
        }
        if(!complete) {
            using namespace std::chrono_literals;
            answer = this->client->get_next_answer(2s);
        }
    }

    return time_bars;
}
