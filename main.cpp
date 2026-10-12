#include <iostream>
#include "PlaneVector.hpp"

int main() {
    PlaneVector u = PlaneVector::fromXY(1, 2);
    PlaneVector v = PlaneVector::fromXY(3, 4);

    std::cout << u;
    std::cout << v;

    PlaneVector sum = u - v;

    std::cout << sum;

    return 0;
}