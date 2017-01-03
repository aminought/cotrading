#ifndef COOPSERVERMESSAGE_H
#define COOPSERVERMESSAGE_H

#include <vector>
#include <memory>
#include <json.hpp>
#include "chart/horizontalline.h"

namespace ct {
namespace coop {

class CoopMessage {
public:
    CoopMessage() = default;
    CoopMessage(const CoopMessage&) = default;
    ~CoopMessage() = default;

    std::vector<std::shared_ptr<chart::HorizontalLine>> get_lines() const;
    nlohmann::json to_json() const;
    void set_lines(const std::vector<std::shared_ptr<chart::HorizontalLine>>& lines);
    void add_line(const std::shared_ptr<chart::HorizontalLine> line);

private:
    std::vector<std::shared_ptr<chart::HorizontalLine>> lines;
};

}
}

#endif // COOPSERVERMESSAGE_H
