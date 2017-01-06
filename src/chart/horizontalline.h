#ifndef HORIZONTALLINE_H
#define HORIZONTALLINE_H


namespace ct {
namespace chart {

class HorizontalLine {
public:
    explicit HorizontalLine(int y): y(y) {}
    int get_y() const;
private:
    int y;
};

}
}

#endif // HORIZONTALLINE_H
