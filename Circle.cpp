#include <numbers>
#include "Circle.hpp"
#include <iostream>

double Circle::perimeter() const {
    return 2. * m_r * std::numbers::pi;
}

PlaneVector Circle::center() const {
    return m_center;
}

double Circle::area() const {
    return std::numbers::pi * m_r * m_r;
}

double Circle::circumference() const {
    return perimeter();
}

// std::ostream& operator<<(std::ostream& os, const Circle& c) {
//     os << "Circle: \n";
//     os << "Center: " << c.m_center << " \t radius: " << c.m_r << " \t area: " << c.area() << '\n';
//     return os;
// }

void Circle::print(std::ostream& os) const {
    os << "Circle: \n";
    os << "Center: " << m_center << " \t radius: " << m_r << " \t area: " << area() << '\n';
}