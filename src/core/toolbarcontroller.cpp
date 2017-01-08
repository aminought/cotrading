#include "toolbarcontroller.h"


void ct::core::ToolBarController::load_historical_data(int symbol) {
    auto provider = this->provider_connection->get_provider();
    if(provider != nullptr) {
        auto contract = provider->resolve_symbol(static_cast<ct::trading::model::Symbol>(symbol));
        auto time_bars = provider->get_historical_data(*contract, bpt::hours(30*24));
        this->chart_controller->clear_data();
        this->chart_controller->load_data(time_bars);
    }
}
