#ifndef SIMPLEPOLYGON_HPP
#define SIMPLEPOLYGON_HPP

#include "Polygon.hpp"

class SimplePolygon: public Polygon {
public:
    explicit SimplePolygon(std::vector<PlaneVector> verts)
        : Polygon(sortVertsCounterclockwise(std::move(verts))){}
private:
    static std::vector<PlaneVector> sortVertsCounterclockwise(std::vector<PlaneVector> verts);
};

#endif