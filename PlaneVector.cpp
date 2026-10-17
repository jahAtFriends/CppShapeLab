#include "PlaneVector.hpp"

#include <cmath>
#include <ostream>

// These functions need <cmath>, whose functions aren't constexpr until
// C++26, so they're defined here and not inline in the header.

PlaneVector PlaneVector::fromPolar(double r, double theta) {
    return PlaneVector{r * std::cos(theta), r * std::sin(theta)};
}

double PlaneVector::theta() const {
    // Avoid atan2(0, -0) = pi
    if (*this == ZERO) {
        return 0.0;
    }
    return std::atan2(m_y, m_x);
}

double PlaneVector::norm() const {
    return std::sqrt(normSquared());
}

PlaneVector PlaneVector::unitVector() const {
    if (*this == ZERO) {
        return ZERO;
    }
    return *this / norm();
}

PlaneVector PlaneVector::rotate(double alpha) const {
    // Apply the rotation matrix directly. Going through polar form instead
    // would cost a sqrt and an atan2 and would lose precision.
    const double c = std::cos(alpha);
    const double s = std::sin(alpha);
    return PlaneVector{c * m_x - s * m_y, s * m_x + c * m_y};
}

std::ostream& operator<<(std::ostream& os, const PlaneVector& v) {
    return os << '<' << v.x() << ", " << v.y() << '>';
}
