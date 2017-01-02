#ifndef CHARTCONTROLLER_H
#define CHARTCONTROLLER_H

#include <QObject>
#include <QDateTime>
#include <QVariant>
#include <boost/date_time/posix_time/ptime.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include "timebar.h"
#include "horizontalline.h"

namespace bpt = boost::posix_time;

class ChartController: public QObject {
    Q_OBJECT
    Q_PROPERTY(QDateTime x_min READ get_x_min)
    Q_PROPERTY(QDateTime x_max READ get_x_max)
    Q_PROPERTY(int y_min READ get_y_min)
    Q_PROPERTY(int y_max READ get_y_max)
    Q_PROPERTY(QList<int> y READ get_y)
    Q_PROPERTY(QVariantList x READ get_x)
    Q_PROPERTY(QObject* chart_canvas WRITE set_chart_canvas)

public:
    explicit ChartController(QObject *parent = 0);
    int get_y_min() const;
    int get_y_max() const;
    QDateTime get_x_min() const;
    QDateTime get_x_max() const;
    QList<int> get_y() const;
    QVariantList get_x() const;
    void load_data(std::vector<TimeBar> time_bars);
    void clear_data();
    std::vector<HorizontalLine> get_lines() const;
    void set_chart_canvas(QObject* chart_canvas);

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
    std::vector<HorizontalLine> lines;
    QObject* chart_canvas;
};

#endif // CHARTCONTROLLER_H
