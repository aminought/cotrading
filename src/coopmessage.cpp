#include "coopmessage.h"


std::vector<std::shared_ptr<HorizontalLine>> CoopMessage::get_lines() const {
    return this->lines;
}

void CoopMessage::set_lines(const std::vector<std::shared_ptr<HorizontalLine>>& lines) {
    this->lines = lines;
}

void CoopMessage::add_line(const std::shared_ptr<HorizontalLine> line) {
    this->lines.push_back(line);
}

nlohmann::json CoopMessage::to_json() const {
    namespace nl = nlohmann;
    auto json = nl::json::array();
    for(auto line: this->lines) {
        nl::json object_obj;
        nl::json line_obj;
        line_obj["y"] = line->get_y();
        object_obj["line"] = line_obj;
        json.push_back(object_obj);
    }
    return json;
}
