#include "SimplePolygon.hpp"
#include <algorithm>
#include <cmath>


std::vector<PlaneVector> SimplePolygon::sortVertsCounterclockwise(std::vector<PlaneVector> verts) {
    double centerX = 0.0;
    double centerY = 0.0;

    for (const auto& v : verts) {
        centerX += v.x();
        centerY += v.y();
    }

    const double count = static_cast<double>(verts.size());
    const double averageX = centerX / count;
    const double averageY = centerY / count;

    std::sort(verts.begin(), verts.end(), [&](const PlaneVector& a, const PlaneVector& b) {
        double y0 = a.y() - averageY, x0 = a.x() - averageX;
        double y1 = b.y() - averageY, x1 = b.x() - averageX;

        return std::atan2(y0, x0) < std::atan2(y1, x1);
    });

    return verts;
}