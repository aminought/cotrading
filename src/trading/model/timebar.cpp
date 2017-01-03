#include "timebar.h"


namespace ct {
namespace trading {
namespace model {

bpt::ptime TimeBar::get_time() const {
    return time;
}

int TimeBar::get_open() const {
    return open;
}

int TimeBar::get_close() const {
    return close;
}

int TimeBar::get_high() const {
    return high;
}

int TimeBar::get_low() const {
    return low;
}

int TimeBar::get_volume() const {
    return volume;
}

}
}
}
