#include "chartcontroller.h"
#include <boost/date_time/posix_time/conversion.hpp>

ChartController::ChartController(QObject *parent) {

}

int ChartController::get_y_min() const {
    return y_min;
}

int ChartController::get_y_max() const {
    return y_max;
}

QDateTime ChartController::get_x_min() const {
    return x_min;
}

QDateTime ChartController::get_x_max() const {
    return x_max;
}

QList<int> ChartController::get_y() const {
    return y;
}

QVariantList ChartController::get_x() const {
    return x;
}

void ChartController::load_data(std::vector<TimeBar> time_bars) {
    auto y_min = time_bars[0].get_close();
    auto y_max = time_bars[0].get_close();
    auto x_min = time_bars[0].get_time();
    auto x_max = time_bars[0].get_time();

    auto ptime_to_qdatetime = [] (bpt::ptime ptime) {
        return QDateTime::fromTime_t(static_cast<unsigned int>(bpt::to_time_t(ptime))).toUTC();
    };

    for(auto bar: time_bars) {
        auto close = bar.get_close();
        auto time = bar.get_time();
        y_min = std::min(close, y_min);
        y_max = std::max(close, y_max);
        x_min = std::min(time, x_min);
        x_max = std::max(time, x_max);
        y.append(close);
        x << QVariant(ptime_to_qdatetime(time));
    }

    this->y_min = y_min;
    this->y_max = y_max;
    this->x_min = ptime_to_qdatetime(x_min);
    this->x_max = ptime_to_qdatetime(x_max);
}

void ChartController::clear_data() {
    this->x.clear();
    this->y.clear();
}
