#include "Polygon.hpp"
#include <iostream>
#include <cstddef>

Polygon::Polygon(std::vector<PlaneVector> v)
    : m_verts(std::move(v))
    , m_sidelengths(getSidesFromVerts(m_verts))
{
}

std::vector<PlaneVector> Polygon::getSidesFromVerts(const std::vector<PlaneVector>& v) {
    std::vector<PlaneVector> sides;
    sides.reserve(v.size());

    for (std::size_t i = 0; i < v.size(); ++i) {
        const auto j = (i + 1) % v.size();
        sides.push_back(v[j] - v[i]);
    }

    return sides;
}

double Polygon::perimeter() const
{
    double perim = 0;
    for (const auto& v: m_sidelengths)
    {
        perim += v.norm();
    }

    return perim;
}

/**
 * Computes the signed area of the given polygon. Area traversed
 * in a clockwise direction is always negative.
 * @return The signed area of the polygon.
 */
double Polygon::area() const
{
    double area = 0;

    for (std::size_t  i = 0; i < m_verts.size(); i++)
    {
        std::size_t j = (i + 1) % m_verts.size();
        area += m_verts[i].cross(m_verts[j]);
    }

    return area / 2.0;
}

PlaneVector Polygon::center() const
{
    double avgX{0}, avgY{0};

    for (std::size_t i = 0; i < m_verts.size(); i++)
    {
        double count = static_cast<double>(i);
        avgX += (m_verts[i].x() - avgX) / (count + 1);
        avgY += (m_verts[i].y() - avgY) / (count + 1);
    }

    return PlaneVector::fromXY(avgX, avgY);
}

void Polygon::print(std::ostream& os) const {
    os << "Polygon size " << m_verts.size() << '\n';
    for (const auto& v : m_verts) {
        os << '\t' << v << '\n';
    }

     os << "area: " << area() << '\t' << "perimeter: " << perimeter() << '\t' << "center: " << center() << '\n';
}

// std::ostream& operator<<(std::ostream& os, const Polygon& p) {
//     os << "Polygon size " << p.verts.size() << '\n';
    
//     for (int i = 0; i < p.verts.size(); i++) {
//         os << '\t' << p.verts[i] << '\n';
//     }

//      os << "area: " << p.area() << '\t' << "perimeter: " << p.perimeter() << '\t' << "center: " << p.center() << '\n';

//     return os;
// }

