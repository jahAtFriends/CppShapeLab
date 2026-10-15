#ifndef MEASURABLE_SHAPE_HPP
#define MEASURABLE_SHAPE_HPP

#include "PlaneVector.hpp"

class MeasurableShape {
public:
    virtual double perimeter() const = 0;
    virtual PlaneVector center() const = 0;
    virtual double area() const = 0;

    virtual ~MeasurableShape() = default;
};

#endif