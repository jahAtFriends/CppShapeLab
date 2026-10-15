#include "SimplePolygon.hpp"
#include <algorithm>
#include <cmath>


std::vector<PlaneVector> SimplePolygon::sortVertsCounterclockwise(std::vector<PlaneVector> verts) {
    double centerX = 0.0;
    double centerY = 0.0;

    for (PlaneVector v : verts) {
        centerX += v.x();
        centerY += v.y();
    }

    const double averageX = centerX / verts.size();
    const double averageY = centerY / verts.size();

    std::sort(verts.begin(), verts.end(), [&](const PlaneVector& a, const PlaneVector& b) {
        double y0 = a.y() - averageY, x0 = a.x() - averageX;
        double y1 = b.y() - averageY, x1 = b.x() - averageX;

        return std::atan2(y0, x0) < std::atan2(y1, x1);
    });

    return verts;
}