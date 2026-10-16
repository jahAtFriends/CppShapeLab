#include <numbers>
#include "Circle.hpp"

const double Circle::perimeter() const {
    return 2. * m_r * std::numbers::pi;
}

const PlaneVector Circle::center() const {
    return m_center;
}

const double Circle::area() const {
    return std::numbers::pi * m_r * m_r;
}

const double Circle::circumference() const {
    return perimeter();
}

std::ostream& operator<<(std::ostream& os, const Circle& c) {
    os << "Circle: \n";
    os << "Center: " << c.m_center << " \t radius: " << c.m_r << " \t area: " << c.area() << '\n';
    return os;
}