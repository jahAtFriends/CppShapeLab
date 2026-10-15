#include "PlaneVector.hpp"
#include <cmath>
#include <iostream>



PlaneVector::PlaneVector(const double& x, const double& y) 
    :m_components{Pair<double, double>{x, y}}
{
}

PlaneVector PlaneVector::fromXY(const double& x, const double& y) {
    return PlaneVector{x, y};
}

PlaneVector PlaneVector::fromPolar(const double& r, const double& theta) {
    return PlaneVector{r * std::cos(theta), r * std::sin(theta)};
}

const PlaneVector& PlaneVector::ZERO() {
    static const PlaneVector zero_instance{0, 0};
    return zero_instance;
}

const double& PlaneVector::x() const {
    return m_components.first();
}

const double& PlaneVector::y() const {
    return m_components.second();
}

const double PlaneVector::r() const {
    return norm();
}

const double PlaneVector::theta() const {
    if (*this == ZERO()) {
        return 0;
    }

    return std::atan2(y(), x());
}

PlaneVector PlaneVector::plus(const PlaneVector& that) const {
    return fromXY(x() + that.x(), y() + that.y());
}

PlaneVector PlaneVector::minus(const PlaneVector& that) const {
    return fromXY(x() - that.x(), y() - that.y());
}

const double PlaneVector::dot(const PlaneVector& that) const {
    return x() * that.x() + y() * that.y();
}

PlaneVector PlaneVector::scl(double& scl) const {
    return fromXY(scl * x(), scl * y());
}

const double PlaneVector::normSquared() const {
    return x() * x() + y() * y();
}

const double PlaneVector::norm() const {
    return std::sqrt(normSquared());
}

PlaneVector PlaneVector::unitVector() const {
    if (*this == ZERO()) {
        return ZERO();
    }

    double scaleFactor = 1.0 / norm();
    return scl(scaleFactor);
}

const double PlaneVector::cross(const PlaneVector& that) const {
    return x() * that.y() - y() * that.x();
}

PlaneVector PlaneVector::rotate(const double& alpha) const {
    if (*this == ZERO()) {
        return ZERO();
    }

    return fromPolar(r(), theta() + alpha);
}

bool operator==(const PlaneVector& left, const PlaneVector& right) {
    return (left.x() == right.x()) && (left.y() == right.y());
}

std::ostream& operator<<(std::ostream& os, const PlaneVector &v) {
    os << '<' << v.x() << ", " << v.y() << '>';
    return os;
}

PlaneVector PlaneVector::operator+(const PlaneVector& that) const {
    return this->plus(that);
}

PlaneVector PlaneVector::operator-(const PlaneVector& that) const {
    return this->minus(that);
}