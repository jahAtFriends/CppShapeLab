#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "SimplePolygon.hpp"

class Rectangle : public SimplePolygon {
private:
    const double height;
    const double width;
    static std::vector<PlaneVector> getVertsFromDims(const double& x, const double& y, const double& width, const double& height);
public:
    Rectangle(const double& x, const double& y, const double& width, const double& height)
        : SimplePolygon(getVertsFromDims(x, y, width, height))
        , height{height}, width{width}
    {
    }

    const double area() const override {
        return width * height;
    }

    const double perimeter() const override {
        return 2 * width + 2 * height;
    }

    static Rectangle fromCenter(const double& cx, const double& cy, const double& w, const double& h);
};

#endif