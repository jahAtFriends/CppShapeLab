#ifndef POLYGON_HPP
#define POLYGON_HPP

#include "MeasurableShape.hpp"
#include <vector>
#include <iosfwd>
#include <utility>

class Polygon : public MeasurableShape
{
private:
    std::vector<PlaneVector> m_verts{};
    std::vector<PlaneVector> m_sidelengths{};
    static std::vector<PlaneVector> getSidesFromVerts(const std::vector<PlaneVector>& verts);

public:
    explicit Polygon(std::vector<PlaneVector> verts);
    double perimeter() const override;
    PlaneVector center() const override;
    double area() const override;
    // friend std::ostream &operator<<(std::ostream &os, const Polygon &p);

    void print(std::ostream& os) const override;
};

#endif