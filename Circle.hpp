#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "MeasurableShape.hpp"
#include <iosfwd>
#include <cmath>

class Circle final : public MeasurableShape {
private:
    PlaneVector m_center;
    double      m_r;

public:
    Circle(double x, double y, double r)
        : m_center{PlaneVector::fromXY(x,y)}
        , m_r{std::abs(r)}
    {
    }

    double perimeter()        const override;
    double area()             const override;
    PlaneVector center()      const override;
    double circumference()    const;

    void print(std::ostream& os) const override;

    //friend std::ostream& operator<<(std::ostream& os, const Circle& c);
};

#endif