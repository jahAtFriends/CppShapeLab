#include "Rectangle.hpp"

std::vector<PlaneVector> Rectangle::getVertsFromDims(const double& x, const double& y, const double& width, const double& height) {
    return {
        PlaneVector::fromXY(x, y),
        PlaneVector::fromXY(x + width, y),
        PlaneVector::fromXY(x + width, y + height),
        PlaneVector::fromXY(x, y + height)
    };
}

Rectangle Rectangle::fromCenter(const double& x, const double& y, const double& width, const double& height) {
    return {
        x - width / 2.,
        y - height / 2.,
        width,
        height
    };
}