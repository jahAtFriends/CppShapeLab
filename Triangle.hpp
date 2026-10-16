#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "SimplePolygon.hpp"

class Triangle : public SimplePolygon
{
public:
    Triangle(
        const double &x0, const double &y0,
        const double &x1, const double &y1,
        const double &x2, const double &y2)
        : SimplePolygon {
            std::vector<PlaneVector> {
                PlaneVector::fromXY(x0, y0),
                PlaneVector::fromXY(x1, y1),
                PlaneVector::fromXY(x2, y2)
            }
        }
    {
    }
};

#endif