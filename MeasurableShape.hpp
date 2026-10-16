#ifndef MEASURABLE_SHAPE_HPP
#define MEASURABLE_SHAPE_HPP

#include "PlaneVector.hpp"

class MeasurableShape {
public:
    virtual const double perimeter() const = 0;
    virtual const PlaneVector center() const = 0;
    virtual const double area() const = 0;

    virtual ~MeasurableShape() = default;
};

#endif