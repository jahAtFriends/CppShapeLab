#ifndef SQUARE_HPP
#define SQUARE_HPP

#include "Rectangle.hpp"

class Square : public Rectangle {
public:
    Square(const double& x, const double& y, const double& l)
        : Rectangle(x, y, l, l)
    {
    }

    static Square fromCenter(const double& x, const double& y, const double& l) {
        return {
            x - l / 2.,
            y - l / 2.,
            l
        };
    }
};

#endif