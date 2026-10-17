#ifndef MEASURABLE_SHAPE_HPP
#define MEASURABLE_SHAPE_HPP

#include "PlaneVector.hpp"

class MeasurableShape {
public:
    virtual double perimeter() const = 0;
    virtual PlaneVector center() const = 0;
    virtual double area() const = 0;

    virtual void print(std::ostream& os) const = 0;

    friend std::ostream& operator<<(std::ostream& os, const MeasurableShape& s) {
        s.print(os);
        return os;
    }

    virtual ~MeasurableShape() = default;
};

#endif