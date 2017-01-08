#include <QtDebug>
#include <QString>
#include "menucontroller.h"


namespace ct {
namespace core {

void MenuController::connect(trading::provider::ProviderType provider_type) {
    trading::provider::ProviderConnectionFactory factory;
    this->provider_connection->change_connection(factory.get_provider_connection(provider_type));
    this->provider = provider_connection->connect(*config);
    if(provider != nullptr) {
        auto contract = provider->resolve_symbol(trading::model::Symbol::CL);
        auto time_bars = provider->get_historical_data(*contract, bpt::hours(24*30));
        std::reverse(time_bars.begin(), time_bars.end());
        qDebug() << "Time bars was gotten";
        this->chart_controller->load_data(time_bars);
        qDebug() << "Data was set";
    }
}

void MenuController::disconnect() {
    this->provider_connection = nullptr;
    this->provider = nullptr;
    this->chart_controller->clear_data();
}

void MenuController::start_coop_server() {
    this->coop_connection->start_coop_server();
}

void MenuController::connect_to_coop_server() {
    this->coop_connection->connect_to_coop_server();
}

void MenuController::send_coop_data() {
    auto lines = chart_controller->get_lines();
    coop::CoopMessage message;
    for(auto line: lines) {
        qDebug() << line.get_y();
        message.add_line(std::make_shared<chart::HorizontalLine>(line));
    }
    this->coop_connection->send_coop_data(message);
}

}
}
