#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "SimplePolygon.hpp"

class Triangle final : public SimplePolygon
{
public:
    Triangle(
        double x0, double y0,
        double x1, double y1,
        double x2, double y2)
        : SimplePolygon{
              {PlaneVector::fromXY(x0, y0),
               PlaneVector::fromXY(x1, y1),
               PlaneVector::fromXY(x2, y2)}}
    {
    }
};

#endif