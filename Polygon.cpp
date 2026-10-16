#include "Polygon.hpp"
#include <iostream>

Polygon::Polygon(const std::vector<PlaneVector> v)
    : verts(std::move(v))
    , sidelengths(getSidesFromVerts(v))
{
}

const std::vector<PlaneVector> Polygon::getSidesFromVerts(const std::vector<PlaneVector> v) {
    std::vector<PlaneVector> sides;
    sides.reserve(v.size());

    for (int i = 0; i < v.size(); i++) {
        int j = (i + 1) % v.size();
        sides.push_back(v[j] - v[i]);
    }

    return sides;
}

const double Polygon::perimeter() const
{
    double perim = 0;
    for (int i = 0; i < sidelengths.size(); i++)
    {
        perim += sidelengths[i].norm();
    }

    return perim;
}

const double Polygon::area() const
{
    double area = 0;

    for (int i = 0; i < verts.size(); i++)
    {
        int j = (i + 1) % verts.size();
        area += verts[i].cross(verts[j]);
    }

    return area / 2.0;
}

const PlaneVector Polygon::center() const
{
    double avgX{0}, avgY{0};

    for (int i = 0; i < sidelengths.size(); i++)
    {
        avgX += (verts[i].x() - avgX) / (i + 1.);
        avgY += (verts[i].y() - avgY) / (i + 1.);
    }



    return PlaneVector::fromXY(avgX, avgY);
}

std::ostream& operator<<(std::ostream& os, const Polygon& p) {
    os << "Polygon size " << p.verts.size() << '\n';
    
    for (int i = 0; i < p.verts.size(); i++) {
        os << '\t' << p.verts[i] << '\n';
    }

     std::cout << "area: " << p.area() << '\t' << "perimeter: " << p.perimeter() << '\t' << "center: " << p.center() << '\n';

    return os;
}

