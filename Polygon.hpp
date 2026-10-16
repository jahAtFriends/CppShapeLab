#ifndef POLYGON_HPP
#define POLYGON_HPP

#include "MeasurableShape.hpp"
#include <vector>
#include <iostream>
#include <utility>

class Polygon : public MeasurableShape
{
private:
    std::vector<PlaneVector> verts{};
    std::vector<PlaneVector> sidelengths{};
    static const std::vector<PlaneVector> getSidesFromVerts(const std::vector<PlaneVector> verts);

public:
    Polygon(const std::vector<PlaneVector> verts);
    const double perimeter() const override;
    const PlaneVector center() const override;
    const double area() const override;
    friend std::ostream &operator<<(std::ostream &os, const Polygon &p);
};

#endif