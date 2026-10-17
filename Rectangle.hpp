#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "SimplePolygon.hpp"
#include <cmath>

class Rectangle : public SimplePolygon {
private:
    double m_height;
    double m_width;
    static std::vector<PlaneVector> getVertsFromDims(double x, double y, double width, double height);
public:
    Rectangle(double x, double y, double width, double height)
        : SimplePolygon(getVertsFromDims(x, y, width, height))
        , m_height{std::abs(height)}, m_width{std::abs(width)}
    {
    }

    double area() const override {
        return m_width * m_height;
    }

    double perimeter() const override {
        return 2 * m_width + 2 * m_height;
    }

    static Rectangle fromCenter(double cx, double cy, double w, double h);
};

#endif