#include <iostream>
#include <vector>
#include "PlaneVector.hpp"
#include "Polygon.hpp"
#include "SimplePolygon.hpp"
#include "Rectangle.hpp"

int main() {
    std::vector<PlaneVector> verts {
        PlaneVector::fromXY(1, 1),
        PlaneVector::fromXY(0, 0),
        PlaneVector::fromXY(1, 0),
        PlaneVector::fromXY(0, 1),
    };

    // SimplePolygon p {verts};
    // std::cout << p.area() << '\n';
    // std::cout << p.perimeter() << '\n';

    Rectangle p {1, 1, 3, 4};
    std::cout << p.area() << '\n';
    std::cout << p.perimeter() << '\n';

    //std::cout << p << '\n';

    return 0;
}