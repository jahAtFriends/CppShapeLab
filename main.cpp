#include <iostream>
#include <vector>
#include "Square.hpp"
#include "Circle.hpp"
#include "Triangle.hpp"

int main()
{

    Polygon p{
        {
            PlaneVector::fromXY(1, 1),
            PlaneVector::fromXY(0, 0),
            PlaneVector::fromXY(1, 0),
            PlaneVector::fromXY(0, 1),
        }};
    
    std::cout << p << '\n';

    Rectangle r = Rectangle::fromCenter(2., 2., 10, 10);
    std::cout << r;

    Circle c = Circle{0., 1., 4.};
    std::cout << c;

    return 0;
}