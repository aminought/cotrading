#ifndef TIMEBAR_H
#define TIMEBAR_H

#include <boost/date_time/posix_time/ptime.hpp>

namespace bpt = boost::posix_time;

class TimeBar {
public:
    TimeBar(bpt::ptime time, int open, int close, int high, int low, int volume):
        time(time), open(open), close(close), high(high), low(low), volume(volume) {}
    bpt::ptime get_time() const;

    int get_open() const;
    int get_close() const;
    int get_high() const;
    int get_low() const;
    int get_volume() const;

private:
    bpt::ptime time;
    int open;
    int close;
    int high;
    int low;
    int volume;
};

#endif // TIMEBAR_H
