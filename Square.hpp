#ifndef SQUARE_HPP
#define SQUARE_HPP

#include "Rectangle.hpp"

class Square final : public Rectangle {
public:
    Square(double x, double y, double l)
        : Rectangle(x, y, l, l)
    {
    }

    static Square fromCenter(double x, double y, double l) {
        return {
            x - l / 2.,
            y - l / 2.,
            l
        };
    }
};

#endif