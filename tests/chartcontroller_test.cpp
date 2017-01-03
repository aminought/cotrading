#include <gtest/gtest.h>
#include <QDateTime>
#include <QDate>
#include <QTime>
#include <QTimeZone>
#include "core/chartcontroller.h"

using ct::trading::model::TimeBar;
using ct::core::ChartController;

std::vector<TimeBar> create_time_bars() {
    std::vector<TimeBar> time_bars;
    time_bars.push_back((TimeBar(bpt::time_from_string("2016-12-20 00:00:00"), 100, 100, 100, 100, 100)));
    time_bars.push_back((TimeBar(bpt::time_from_string("2016-12-26 00:00:00"), 100, 300, 100, 100, 100)));
    time_bars.push_back((TimeBar(bpt::time_from_string("2016-12-22 00:00:00"), 100, 200, 100, 100, 100)));
    time_bars.push_back((TimeBar(bpt::time_from_string("2016-12-29 00:00:00"), 100, 700, 100, 100, 100)));
    return time_bars;
}

TEST(LOAD_DATA, CHARTCONTROLLER_TEST) {
    ChartController contr(nullptr, nullptr);
    std::vector<TimeBar> time_bars = create_time_bars();

    contr.load_data(time_bars);
    auto y_min = contr.get_y_min();
    auto y_max = contr.get_y_max();
    auto x_min = contr.get_x_min();
    auto x_max = contr.get_x_max();

    EXPECT_EQ(100, y_min);
    EXPECT_EQ(700, y_max);
    EXPECT_EQ(QDateTime(QDate(2016, 12, 20), QTime(), QTimeZone::utc()).toUTC(), x_min);
    EXPECT_EQ(QDateTime(QDate(2016, 12, 29), QTime(), QTimeZone::utc()).toUTC(), x_max);
}
