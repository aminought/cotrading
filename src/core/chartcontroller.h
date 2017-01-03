#ifndef CHARTCONTROLLER_H
#define CHARTCONTROLLER_H

#include <QObject>
#include <QDateTime>
#include <QVariant>
#include <boost/date_time/posix_time/ptime.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include "chart/horizontalline.h"
#include "trading/model/timebar.h"

namespace bpt = boost::posix_time;

namespace ct {
namespace core {

class ChartController: public QObject {
    Q_OBJECT
    Q_PROPERTY(QDateTime x_min READ get_x_min)
    Q_PROPERTY(QDateTime x_max READ get_x_max)
    Q_PROPERTY(int y_min READ get_y_min)
    Q_PROPERTY(int y_max READ get_y_max)
    Q_PROPERTY(QList<int> y READ get_y)
    Q_PROPERTY(QVariantList x READ get_x)

public:
    explicit ChartController(QObject* /*parent*/, QObject* chart): chart(chart) {}
    int get_y_min() const;
    int get_y_max() const;
    QDateTime get_x_min() const;
    QDateTime get_x_max() const;
    QList<int> get_y() const;
    QVariantList get_x() const;

    std::vector<chart::HorizontalLine> get_lines() const;
    void load_data(std::vector<trading::model::TimeBar>& time_bars);
    void clear_data();
    void update_chart_based_on_message(const std::string& message);

public slots:
    void addHorizontalLine(int y);
    void removeHorizontalLines();

private:
    int y_min;
    int y_max;
    QDateTime x_min;
    QDateTime x_max;
    QList<int> y;
    QVariantList x;
    std::vector<chart::HorizontalLine> lines;

    QObject* chart;
};

}
}

#endif // CHARTCONTROLLER_H
