#ifndef HORIZONTALLINE_H
#define HORIZONTALLINE_H


class HorizontalLine {
public:
    HorizontalLine(int y): y(y) {}
    int get_y() const;
private:
    int y;
};

#endif // HORIZONTALLINE_H
